/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup Services
 * @{
 *
 * @addtogroup payload_sched Payload Scheduler
 * @{
 *
 * @file payload_scheduler.c
 * @brief Main implementation of the Payload Scheduler service.
 *
 * @}
 * @}
 */

#include <math.h>
#include "AppTasks.h"
#include "SdMngr.h"
#include "string.h"
#include "CommandsApi.h"
#include "payload_scheduler.h"

#include "conops_payload.h"
#include "datetime.h"


#define MAX_SCHEDULED_RECORDS           (40u)      /**< maximum number of scheduling records in a single file */

#define MINIMAL_POSSIBLE_DURATION       (60u)      /*< minimum time to wait for the payload to finish work before being stopped */

typedef struct
{
    record_t records[MAX_SCHEDULED_RECORDS];
} scheduled_data_t;

payload_flag_t conops_payload_flags[PAYLOAD_COUNT];

/** @brief schedule file name buffer */
static char sched_file_name[FF_LFN_BUF] = { '\0' };

static scheduled_data_t schedule_data;
static bool schedule_dirty = false;
static bool schedule_reload = false;

static osThreadId_t PayloadScheduler_TaskHandle;
static const osThreadAttr_t PayloadScheduler_attributes =
{
  .name = "PayloadScheduler_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 32
};

static void psched_task(void * argument);
static void psched_update_conops_flags(void);

static bool file_read(void)    // we are counting on single-thread access to the routines in this module
{
    FIL file;
    FRESULT res;
    bool ret = false;

    if ('\0' != sched_file_name[0])
    {
        (void) memset(&file, 0, sizeof(file));
        res = SdMngr_f_open(&file, sched_file_name, FA_READ | FA_OPEN_EXISTING);
        if (res == FR_OK)
        {
            UINT bytes_read;
            SdMngr_f_lseek(&file, 0);
            res = SdMngr_f_read(&file, &schedule_data, sizeof(schedule_data), &bytes_read);
            SdMngr_f_close(&file);
            if (bytes_read > 0)
            {
                schedule_dirty = false;
                ret = true;
            }
        }
    }

    return ret;
}

static bool file_write(void)    // we are counting on single-thread access to the routines in this module
{
    FIL file;
    FRESULT res;
    bool ret = false;

    memset(&file, 0, sizeof(file));
    res = SdMngr_f_open(&file, sched_file_name, FA_WRITE | FA_CREATE_ALWAYS);
    if (res == FR_OK)
    {
        UINT bytes_written;
        SdMngr_f_lseek(&file, 0);
        res = SdMngr_f_write(&file, &schedule_data, sizeof(schedule_data), &bytes_written);
        SdMngr_f_close(&file);
        if (bytes_written == sizeof(schedule_data))
        {
            schedule_dirty = false;
            ret = true;
        }
    }

    return ret;
}

static void records_clear(void)
{
    for (uint16_t i = 0; i < MAX_SCHEDULED_RECORDS; i++)
    {
        record_t *const pRecord = &(schedule_data.records[i]);
        pRecord->payload_id = PAYLOAD_EMPTY_RECORD;
        pRecord->time = 0;
        pRecord->duration = 0;
        memset(&(pRecord->adcs_args), 0x00, sizeof(pRecord->adcs_args));
        memset(pRecord->payload_args, 0x00, sizeof(pRecord->payload_args));
    }

    schedule_dirty = true;
    (void)file_write();
}

// order of checking "evaluate_XXX" functions is important - optimization issue
static inline bool evaluate_expired(const record_time_t now, record_t *const pRecord)
{
    bool ret = false;
    if (now > (pRecord->time + pRecord->duration))
    {
        // the record is expired - no sense to waste time on it!
        ret = true;
    }

    return ret;
}

// order of checking "evaluate_XXX" functions is important - optimization issue
static bool evaluate_time_action(const record_time_t now, record_t *const pRecord)
{
    if (now < (pRecord->time - pRecord->payload_boot_time - pRecord->adcs_args.adcs_prep_time))
    {
        return false;
    }

    return true;
}

bool PayloadScheduler_addRecord(const uint8_t payload_id, const record_time_t time, const uint16_t duration, record_adcs_t *const adcs_data, const uint8_t flags, const uint8_t *const pay_args)
{
    for (uint16_t i = 0; i < MAX_SCHEDULED_RECORDS; i++)
    {
        record_t *const pRecord = &(schedule_data.records[i]);

        // if the record is currently not in use
        if (pRecord->payload_id >= PAYLOAD_COUNT)
        {
            pRecord->duration = duration;
            if (pRecord->duration < MINIMAL_POSSIBLE_DURATION)
            {
                pRecord->duration = MINIMAL_POSSIBLE_DURATION;
            }

            pRecord->time = time;
            memcpy(&pRecord->adcs_args, adcs_data, sizeof(record_adcs_t));

            pRecord->flags = flags;
            memcpy(&pRecord->payload_args[0], pay_args, sizeof(uint8_t) * 16);

            if (payload_id < PAYLOAD_COUNT)
            {
                pRecord->payload_id = payload_id;
                schedule_reload = false;
                return true;
            }
            else
            {
                // cannot map type! invalid input type!
                return false;
            }
        }
    }

    return false;
}

void PayloadScheduler_clearRecords(void)
{
    records_clear();
}

static void psched_update_conops_flags(void)
{
    // we are counting on periodic calls of the following routine
    PayloadScheduler_state_t conops_flag[PAYLOAD_COUNT];
    uint16_t conops_flag_record_idx[PAYLOAD_COUNT];
    memset(conops_flag, 0, sizeof(conops_flag));
    memset(conops_flag_record_idx, 0, sizeof(conops_flag_record_idx));

    const record_time_t now = (record_time_t) datetime_to_unix_now();

    for (uint16_t i = 0; i < MAX_SCHEDULED_RECORDS; i++)
    {
        record_t *const pRecord = &(schedule_data.records[i]);
        const uint8_t payload_id = pRecord->payload_id;

        if (payload_id < PAYLOAD_COUNT)
        {
            // order of checking "evaluate_XXX" functions is important - optimization issue
            if (!evaluate_expired(now, pRecord))
            {
                if (true == evaluate_time_action(now, pRecord))
                {
                    conops_flag[payload_id] = SCHED_STATE_ACTIVE_PAYLOAD;
                    conops_flag_record_idx[payload_id] = i;
                }
            }
        }
        else
        {
            pRecord->payload_id = PAYLOAD_EMPTY_RECORD;
        }
    }

    for (int i = 0; i < PAYLOAD_COUNT; i++)
    {
        if (conops_payload_flags[i].flag != conops_flag[i])
        {
            conops_payload_flags[i].flag = conops_flag[i];
            memcpy(&(conops_payload_flags[i].sched_data), &(schedule_data.records[conops_flag_record_idx[i]]), sizeof(record_t));

            /* Trigger an event to the ConOps SM */
            conops_payload_trigger_event(i);
        }
    }

    if (true == schedule_dirty)
    {
        file_write();
    }
}

void PayloadScheduler_Reload(const char *p_fname)
{
    if (NULL != p_fname)
    {
        if ('\0' != p_fname[0])
        {
            size_t fname_len = strlen(p_fname);

            (void) memset(sched_file_name, 0, sizeof(sched_file_name));

            (void) memcpy(sched_file_name, p_fname, (size_t) fmin(fname_len, sizeof(sched_file_name)));

            schedule_reload = true;
        }
    }
}

void PayloadScheduler_Init(void)
{
    (void) memset(sched_file_name, 0, sizeof(sched_file_name));

    for (uint16_t i = 0; i < MAX_SCHEDULED_RECORDS; i++)
    {
        schedule_data.records[i].payload_id = 255; // Empty record
    }

    PayloadScheduler_TaskHandle = osThreadNew(psched_task, NULL, &PayloadScheduler_attributes);
    CRIT_ASSERT( PayloadScheduler_TaskHandle );
}

static void psched_task(void * argument)
{
    schedule_reload = true;

    TaskMonitor_TaskInitialized(TASK_PAYLOAD_SCHEDULER);

    for( ; ; )
    {
        if (true == schedule_reload)
        {
            if (true == file_read())
            {
                schedule_reload = false;
            }
        }
        else
        {
            psched_update_conops_flags();
        }

        osDelay(1000);

        TaskMonitor_IamAlive(TASK_PAYLOAD_SCHEDULER);
        vApplicationLowStackCheck(TASK_PAYLOAD_SCHEDULER);
    }
}

PayloadScheduler_state_t PayloadScheduler_getStatus(payload_ctrl_payload_t payload_id)
{
    return (payload_id < PAYLOAD_COUNT) ? (conops_payload_flags[payload_id].flag) : (SCHED_STATE_MAX);
}
