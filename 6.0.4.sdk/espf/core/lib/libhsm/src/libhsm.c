/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup libhsm
 * @{
 *
 * @file libhsm.c
 * @brief This is a hierarchical state machine engine library.
 *
 * @}
 */

#include "libhsm.h"
#include "libhsm_cfg.h"
#include <stddef.h>

static const char *CC_NONAME = "unknown\0";

static inline char *HSM_sf_STR(char *str, char *ifnull_str);
static inline bool  HSM_sf_IsStateComposite(const sState_t *const pState);
static inline void  HSM_sf_TraceEntryAction(const sState_t *const pState);
static inline void  HSM_sf_TraceExitAction(const sState_t *const pState);

static const sTransition_t *HSM_sf_getActiveTransition(sState_t *const               pSMRoot,
                                                       const sState_t *const         pState,
                                                       const sHSM_EventType_t *const pEv);

static const sState_t *HSM_sf_TriggerStateEvent(sState_t *const               pSMRoot,
                                                const sState_t *const         pActiveState,
                                                const sHSM_EventType_t *const pEv);

static void HSM_sf_ExecuteExitActions(sState_t *const pSMRoot, const sState_t *const pActiveState,
                                      const sState_t *const         pTopState,
                                      const sHSM_EventType_t *const pEv);

static const sState_t *HSM_sf_ExecuteEntryActions(sState_t *const               pSMRoot,
                                                  const sState_t *const         pTopState,
                                                  const sState_t *const         pTargetState,
                                                  const sHSM_EventType_t *const pEv);

static const sState_t *const HSM_sf_FindCommonParent(const sState_t *const pSourceState,
                                                     const sState_t *const pTargetState);

static void HSM_sf_AddToStackSafe(const sState_t **const pStateStack, const sState_t *const pState,
                                  uint8_t *const pSlotIndex);

bool HSM_TriggerEvent_raw(sState_t *const pSMRoot, const sHSM_EventType_t *const pEv)
{
    bool res = false;

    // to avoid some compiler warnings in case the trace macros are not defined and
    // the CC_NONAME becomes unused (currently used only by the trace macros)
    (void)CC_NONAME;

    if ((pSMRoot != NULL) && (pEv != NULL))
    {
        const sState_t *pTargetState = NULL;

        // this function accepts only the SM root state which must be configured as
        // composite
        HSM_ASSERT(HSM_sf_IsStateComposite(pSMRoot));
        HSM_ASSERT(HSM_DOWNCAST_COMPOSITE(pSMRoot)->pInitalState != NULL);

        switch (pEv->id)
        {
            case eHSM_StdEvent_Reset:
                {
                    // execute all exit actions up to root before going to intial state
                    // (this aims to perform any kind of deinitialization on the existing
                    // active hierarchy of states to ensure the the SM goes to Init state
                    // clean)
                    if (HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState != NULL)
                    {
                        HSM_sf_ExecuteExitActions(
                            pSMRoot, HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState, pSMRoot, pEv);
                    }

                    pTargetState = HSM_DOWNCAST_COMPOSITE(pSMRoot)->pInitalState;

                    // execute entry actions for the initial state
                    const sState_t *pTargetStateReached =
                        HSM_sf_ExecuteEntryActions(pSMRoot, pSMRoot, pTargetState, pEv);

                    HSM_ASSERT(pTargetState == pTargetStateReached);

                    break;
                }

            default:
                {
                    pTargetState = HSM_sf_TriggerStateEvent(
                        pSMRoot, HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState, pEv);

                    break;
                }
        }

        // switch to transition target state
        if (pTargetState != NULL)
        {
            if ((pEv->id != eHSM_StdEvent_Periodic) ||
                ((pEv->id == eHSM_StdEvent_Periodic) &&
                 (HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState != pTargetState)))
            {
                HSM_TRACE_INFO(
                    "[%s:0x%08x] %s -- %d --> %s\r", HSM_sf_STR(pSMRoot->pName, "n/a\0"),
                    (uint32_t)pSMRoot,
                    (HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState != NULL)
                        ? HSM_sf_STR(HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState->pName,
                                     CC_NONAME)
                        : ("()"),
                    pEv->id, HSM_sf_STR(pTargetState->pName, CC_NONAME));
            }

            HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState = pTargetState;

            res = true;
        }
        else
        {
            HSM_TRACE_DEBUG("[%s:0x%08x] Unhandled event: %d\r",
                            HSM_sf_STR(pSMRoot->pName, CC_NONAME), (uint32_t)pSMRoot, pEv->id);
        }
    }

    return res;
}

bool HSM_TriggerEvent(sState_t *const pSMRoot, const uint32_t event_id)
{
    sHSM_EventType_t evt;

    evt.id = event_id;

    return HSM_TriggerEvent_raw(pSMRoot, &evt);
}

const sState_t *HSM_GetActiveState(sState_t *const pSMRoot)
{
    const sState_t *pActiveState = NULL;

    if (pSMRoot != NULL)
    {
        if ((pSMRoot->eType == eHSM_StateType_Composite) && (NULL == pSMRoot->pParent))
        {
            pActiveState = HSM_DOWNCAST_COMPOSITE(pSMRoot)->pActiveState;
        }
        else
        {
            HSM_TRACE_ERROR("pSMRoot does not point to a valid root state.\r");
        }
    }
    else
    {
        HSM_TRACE_ERROR("pSMRoot is NULL\r");
    }

    return pActiveState;
}

static const sTransition_t *HSM_sf_getActiveTransition(sState_t *const               pSMRoot,
                                                       const sState_t *const         pState,
                                                       const sHSM_EventType_t *const pEv)
{
    const sTransition_t *pActiveTrans = (sTransition_t *)NULL;

    HSM_ASSERT(pSMRoot != NULL);
    HSM_ASSERT(pState != (sState_t *)NULL);
    HSM_ASSERT(pEv != NULL);

    // finite state handling
    const sTransition_t *const *pTransIter       = pState->pTransitionList;
    const sTransition_t        *pTransitionEntry = (pTransIter != NULL) ? (*pTransIter) : (NULL);

    while (pTransitionEntry != NULL)
    {
        if (pTransitionEntry->eventId == pEv->id)
        {
            // check transition guard condition
            if (pTransitionEntry->guardFunc != NULL)
            {
                if (true == (*pTransitionEntry->guardFunc)(pSMRoot, pEv))
                {
                    pActiveTrans = pTransitionEntry;
                    break;
                }
            }
            else
            {
                pActiveTrans = pTransitionEntry;
                break;
            }
        }

        pTransIter += 1;
        pTransitionEntry = *(pTransIter);
    }

    return pActiveTrans;
}

static const sState_t *const HSM_sf_FindCommonParent(const sState_t *const pSourceState,
                                                     const sState_t *const pTargetState)
{
    const sState_t *pStatePath[HSM_MAX_NEST_LEVEL] = { NULL };
    uint8_t         u8StateIndex                   = 0U;

    const sState_t *pCommonRoot = (sState_t *)NULL;
    const sState_t *pStateIter  = pSourceState;

    HSM_ASSERT(pSourceState != NULL);
    HSM_ASSERT(pTargetState != NULL);

    // build the reverse path from the source state to the root and store it for
    // future reference
    while (pStateIter->pParent != NULL)
    {
        HSM_sf_AddToStackSafe(pStatePath, pStateIter->pParent, &u8StateIndex);

        pStateIter = pStateIter->pParent;
    }

    // now scan the reverse path from the second target state and check if it is
    // present in the source state path to determine the LCA
    pStateIter = pTargetState;

    bool bLcaFound = false;

    while ((pStateIter->pParent != NULL) && (!bLcaFound))
    {
        for (uint8_t src_idx = 0; src_idx < u8StateIndex; src_idx++)
        {
            if (pStateIter->pParent == pStatePath[src_idx])
            {
                // we are at the top of the hiearchy, just drop off the search...
                pCommonRoot = pStateIter->pParent;
                bLcaFound   = true;
                break;
            }
        }

        pStateIter = pStateIter->pParent;
    }

    return pCommonRoot;
}

static void HSM_sf_ExecuteExitActions(sState_t *const pSMRoot, const sState_t *const pActiveState,
                                      const sState_t *const         pTopState,
                                      const sHSM_EventType_t *const pEv)
{
    const sState_t *pStateIter = (sState_t *)NULL;

    HSM_ASSERT(pSMRoot != NULL);
    HSM_ASSERT(pActiveState != NULL);
    HSM_ASSERT(pTopState != NULL);

    // trigger current state exit function if such exists
    if (pActiveState->onExitFunc != NULL)
    {
        HSM_sf_TraceExitAction(pActiveState);
        (*pActiveState->onExitFunc)(pSMRoot, pEv);
    }

    // preserve history state
    if (NULL != pActiveState->pParent)
    {
        HSM_DOWNCAST_COMPOSITE(pActiveState->pParent)->pHistoryState = pActiveState;
    }

    // ...now go up the hierarchy and execute all parent exit actions
    pStateIter = pActiveState->pParent;

    while ((pStateIter != NULL) && (pStateIter != pTopState))
    {
        if (pStateIter->onExitFunc != NULL)
        {
            HSM_sf_TraceExitAction(pStateIter);
            (*pStateIter->onExitFunc)(pSMRoot, pEv);
        }

        if (NULL != pStateIter->pParent)
        {
            // preserve history state
            HSM_DOWNCAST_COMPOSITE(pStateIter->pParent)->pHistoryState = pStateIter;
        }

        pStateIter = pStateIter->pParent;
    }
}

static const sState_t *HSM_sf_ExecuteEntryActions(sState_t *const               pSMRoot,
                                                  const sState_t *const         pTopState,
                                                  const sState_t *const         pTargetState,
                                                  const sHSM_EventType_t *const pEv)
{
    const sState_t *pStateIter                      = (sState_t *)NULL;
    const sState_t *pStateStack[HSM_MAX_NEST_LEVEL] = { NULL };
    const sState_t *pFinalState                     = (sState_t *)NULL;
    uint8_t         u8StateStackIndex               = 0U;

    HSM_ASSERT(pSMRoot != NULL);
    HSM_ASSERT(pTopState != NULL);
    HSM_ASSERT(pTargetState != NULL);

    HSM_sf_AddToStackSafe(pStateStack, pTargetState, &u8StateStackIndex);

    // ...now go up the hierarchy and build the entry functions stack
    pStateIter = pTargetState->pParent;

    while ((pStateIter != NULL) && (pStateIter != pTopState))
    {
        HSM_sf_AddToStackSafe(pStateStack, pStateIter, &u8StateStackIndex);

        pStateIter = pStateIter->pParent;
    }

    // ...unwind the stack and execute the nested state entry functions in the
    // correct order
    while (u8StateStackIndex > 0U)
    {
        u8StateStackIndex--;
        pStateIter = pStateStack[u8StateStackIndex];

        if (pStateIter->onEntryFunc != NULL)
        {
            HSM_sf_TraceEntryAction((sState_t *)pStateIter);
            (*pStateIter->onEntryFunc)(pSMRoot, pEv);
        }
    }

    if (true == HSM_sf_IsStateComposite(pTargetState))
    {
        // oops, this is a composite state, hence drill down to initial state if any
        if (HSM_DOWNCAST_COMPOSITE(pTargetState)->pInitalState != NULL)
        {
            pStateIter = HSM_DOWNCAST_COMPOSITE(pTargetState)->pInitalState;

            // initial state is also a composite, don't quit drilling...
            while (true == HSM_sf_IsStateComposite(pStateIter))
            {
                if (pStateIter->onEntryFunc != NULL)
                {
                    HSM_sf_TraceEntryAction(pStateIter);
                    (*pStateIter->onEntryFunc)(pSMRoot, pEv);
                }

                pStateIter = HSM_DOWNCAST_COMPOSITE(pStateIter)->pInitalState;
            }

            // finally execute leaf state entry function
            if (pStateIter->onEntryFunc != NULL)
            {
                HSM_sf_TraceEntryAction(pStateIter);
                (*pStateIter->onEntryFunc)(pSMRoot, pEv);
            }

            pFinalState = pStateIter;
        }
    }
    else
    {
        pFinalState = pTargetState;
    }

    return pFinalState;
}

static const sState_t *HSM_sf_TriggerStateEvent(sState_t *const               pSMRoot,
                                                const sState_t *const         pActiveState,
                                                const sHSM_EventType_t *const pEv)
{
    const sState_t *pTargetStateReached = pActiveState;

    HSM_ASSERT(pSMRoot != NULL);
    HSM_ASSERT(pEv != NULL);

    if (pActiveState != NULL)
    {
        HSM_TRACE_DEBUG(">> %d >> %s\r", pEv->id, HSM_sf_STR(pActiveState->pName, CC_NONAME));

        const sTransition_t *pActiveTrans = HSM_sf_getActiveTransition(pSMRoot, pActiveState, pEv);

        if (pActiveTrans != NULL)
        {
            const sState_t *pLCA         = NULL;
            const sState_t *pTargetState = pActiveTrans->pTargetState;

            if (pTargetState != NULL)
            {
                // if this is a history state, then redirect the target...
                if (pTargetState->eType == eHSM_StateType_History)
                {
                    HSM_ASSERT(pTargetState->pParent != NULL);
                    pTargetState = HSM_DOWNCAST_COMPOSITE(pTargetState->pParent)->pHistoryState;
                }

                pLCA = HSM_sf_FindCommonParent(pActiveState, pTargetState);

                if ((pEv->id != eHSM_StdEvent_Periodic) ||
                    (pActiveState != pTargetState))
                {
                    HSM_TRACE_DEBUG("trans start: %s -- %d --> %s\r",
                                    HSM_sf_STR(pActiveState->pName, CC_NONAME), pEv->id,
                                    HSM_sf_STR(pTargetState->pName, CC_NONAME));
                }

                HSM_sf_ExecuteExitActions(pSMRoot, pActiveState, pLCA, pEv);
            }
            else
            {
                if (pEv->id != eHSM_StdEvent_Periodic)
                {
                    HSM_TRACE_INFO("internal trans: %s -- %d --> %s\r",
                                   HSM_sf_STR(pActiveState->pName, CC_NONAME), pEv->id,
                                   HSM_sf_STR(pActiveState->pName, CC_NONAME));
                }
            }

            // trigger transition action function if it exists
            if (pActiveTrans->onTransitionActionFunc != NULL)
            {
                pActiveTrans->onTransitionActionFunc(pSMRoot, pEv);
            }

            if (pTargetState != NULL)
            {
                pTargetStateReached = HSM_sf_ExecuteEntryActions(pSMRoot, pLCA, pTargetState, pEv);
            }
        }
        else
        {
            // if this is not the top state, go up the hierarchy to find a handler at
            // upper level...
            if (NULL != pActiveState->pParent)
            {
                pTargetStateReached = HSM_sf_TriggerStateEvent(pSMRoot, pActiveState->pParent, pEv);

                if ((NULL != pTargetStateReached) && (pTargetStateReached != pActiveState))
                {
                    // transition was handled at upper level so we need to execute exit
                    // actions for this state only
                    HSM_sf_ExecuteExitActions(pSMRoot, pActiveState, pActiveState->pParent, pEv);
                }
            }
            else
            {
                pTargetStateReached = NULL;
            }
        }
    }
    else
    {
        HSM_TRACE_ERROR("[%s] error: pActiveState is NULL\r", __func__);
    }

    return pTargetStateReached;
}

static void HSM_sf_AddToStackSafe(const sState_t **const pStateStack, const sState_t *const pState,
                                  uint8_t *const pSlotIndex)
{
    HSM_ASSERT(pStateStack != NULL);
    HSM_ASSERT(pState != NULL);
    HSM_ASSERT(pSlotIndex != NULL);

    if ((*pSlotIndex) < HSM_MAX_NEST_LEVEL)
    {
        pStateStack[(*pSlotIndex)++] = pState;
    }
    else
    {
        HSM_TRACE_ERROR("HSM_MAX_NEST_LEVEL (%d) shall be increased!\r", HSM_MAX_NEST_LEVEL);
        HSM_ASSERT(false);
    }
}

static inline char *HSM_sf_STR(char *str, char *ifnull_str)
{
    return ((str != NULL) ? str : ifnull_str);
}

static inline bool HSM_sf_IsStateComposite(const sState_t *const pState)
{
    return (((HSM_UPCAST_STATE(pState))->eType) == eHSM_StateType_Composite);
}

static inline void HSM_sf_TraceEntryAction(const sState_t *const pState)
{
    HSM_TRACE_DEBUG("-- entry --> %s\r",
                    HSM_sf_STR(((const sState_t *)(pState))->pName, CC_NONAME));
}

static inline void HSM_sf_TraceExitAction(const sState_t *const pState)
{
    HSM_TRACE_DEBUG("%s -- exit -->\r", HSM_sf_STR(((sState_t *)(pState))->pName, CC_NONAME));
}
