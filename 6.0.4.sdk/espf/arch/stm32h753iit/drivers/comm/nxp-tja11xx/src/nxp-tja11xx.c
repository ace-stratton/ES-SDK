#include "nxp-tja1100.h"
#include "cmsis_gcc.h"

int32_t TJA1100_RegisterBusIO(phy_Object_t *pObj, tja1100_IOCtx_t *ioctx)
{
    int32_t phy_status;

    if ((!pObj) || (!ioctx->ReadReg) || (!ioctx->WriteReg) || (!ioctx->GetTick))
    {
        phy_status = PHY_STATUS_ERROR;
    }
    else
    {
        pObj->IO.Init = ioctx->Init;
        pObj->IO.DeInit = ioctx->DeInit;
        pObj->IO.ReadReg = ioctx->ReadReg;
        pObj->IO.WriteReg = ioctx->WriteReg;
        pObj->IO.GetTick = ioctx->GetTick;

        phy_status = PHY_STATUS_OK;
    }

    return phy_status;
}

static int phy_modify(phy_Object_t *pObj, uint32_t regnum, uint16_t mask, uint16_t set)
{
    int ret;
    uint32_t new, regvalue;

    ret = pObj->IO.ReadReg(pObj->DevAddr, regnum, &regvalue);

    if (ret >= 0)
    {
        new = (regvalue & ~mask) | set;

        if (new != regvalue)
        {
            ret = pObj->IO.WriteReg(pObj->DevAddr, regnum, new);
        }
        else
        {
            ret = 0;
        }
    }

    return ret < 0 ? ret : 1;
}

static int phy_write(phy_Object_t *pObj, uint32_t regnum, uint16_t regvalue)
{
    return pObj->IO.WriteReg(pObj->DevAddr, regnum, regvalue);
}

static int phy_read(phy_Object_t *pObj, uint32_t regnum, uint16_t *regvalue)
{
    uint32_t data;

    int ret = pObj->IO.ReadReg(pObj->DevAddr, regnum, &data);
    if (ret == PHY_STATUS_OK)
    {
        *regvalue = (uint16_t) data;
    }

    return ret;
}

static int phy_check_bit(
        phy_Object_t *pObj,
        uint32_t regnum,
        uint16_t mask,
        uint8_t *bit_state)
{
    int ret;
    uint32_t regvalue;

    ret = pObj->IO.ReadReg(pObj->DevAddr, regnum, &regvalue);

    if (ret >= 0)
    {
        *bit_state = (regvalue & mask) ? 1 : 0;
    }

    return (ret < 0) ? ret : PHY_STATUS_OK;
}

static int phy_set_bits(phy_Object_t *pObj, uint32_t regnum, uint16_t val)
{
    return phy_modify(pObj, regnum, 0, val);
}

static int phy_clear_bits(phy_Object_t *pObj, uint32_t regnum, uint16_t val)
{
    return phy_modify(pObj, regnum, val, 0);
}

static int tja11xx_enable_reg_write(phy_Object_t *pObj)
{
    return phy_set_bits(pObj, TJA1100_EXTENDED_CTRL, TJA1100_EXTENDED_CTRL_CONFIG_EN);
}

static int tja11xx_soft_reset(phy_Object_t *pObj)
{
    int ret;

    /* set a software reset  */
    ret = phy_set_bits(pObj, TJA1100_BASIC_CTRL, TJA1100_BASIC_CTRL_RESET);

    return ret;
}

static int32_t TJA1100_Init_internal(phy_Object_t *pObj)
{
    uint32_t tickstart = 0, regvalue = 0;
    int32_t status = PHY_STATUS_OK;

    if (pObj->IO.Init != 0)
    {
        /* GPIO and Clocks initialization */
        pObj->IO.Init();
    }

    // tja1100 default address is 0. since we use only one PHY we stick to default
    pObj->DevAddr = 0;

    if (pObj->IO.ReadReg(pObj->DevAddr, TJA1100_PHY_ID1, &regvalue) < 0)
    {
        return PHY_STATUS_READ_ERROR;
    }

    if (regvalue != TJA1100_PHY_ID1_OUI_MSB_DEFAULT)
    {
        return PHY_STATUS_ERROR;
    }

    //!!! This is the most important command!!!
    status = tja11xx_enable_reg_write(pObj);
    if (IS_ERROR(status))
    {
        return status;
    }

    /* set a software reset  */
    status = tja11xx_soft_reset(pObj);
    if (IS_ERROR(status))
    {
        return status;
    }

    /* get software reset status */
    tickstart = pObj->IO.GetTick();
    uint8_t softreset = 1;
    do
    {
        status = phy_check_bit(pObj, TJA1100_BASIC_CTRL, TJA1100_BASIC_CTRL_RESET, &softreset);
        if (IS_ERROR(status))
        {
            return status;
        }

        if ((pObj->IO.GetTick() - tickstart) > TJA1100_SW_RESET_TO)
        {
            return PHY_STATUS_RESET_TIMEOUT;
        }
    }
    while (softreset);

    status = phy_write(
            pObj,
            TJA1100_CONFIG1,
            (TJA1100_CONFIG1_MASTER_SLAVE |
            TJA1100_CONFIG1_TX_AMPLITUDE_1000MV |
            TJA1100_CONFIG1_MII_MODE_MII |
            TJA1100_CONFIG1_MII_DRIVER_STANDARD));
    if (IS_ERROR(status))
    {
        return status;
    }

    phy_modify(pObj, TJA1100_EXTENDED_CTRL,
    TJA1100_EXTENDED_CTRL_POWER_MODE_MASK,
    TJA1100_EXTENDED_CTRL_LINK_CONTROL | TJA1100_EXTENDED_CTRL_POWER_MODE_NORMAL);

    //Extended control register
    if (IS_ERROR(status))
    {
        return status;
    }

    /* ACK interrupts by reading the status register */
    uint16_t interrupt_status;
    status = phy_read(pObj, TJA1100_INT_SRC, &interrupt_status);
    if (IS_ERROR(status))
    {
        return status;
    }

    return status;
}

int32_t TJA1100_Init(phy_Object_t *pObj)
{
    uint32_t tickstart = 0;
    int32_t status = PHY_STATUS_OK;

    if (pObj->Is_Initialized == 0)
    {
        status = TJA1100_Init_internal(pObj);
        if (IS_ERROR(status))
        {
            return status;
        }
    }

    tickstart = pObj->IO.GetTick();

    /* Wait for 2s to perform initialization */
    while ((pObj->IO.GetTick() - tickstart) <= TJA1100_INIT_TO)
    {
        __NOP();
    }

    pObj->Is_Initialized = 1;

    return status;
}

int32_t TJA1100_DeInit(phy_Object_t *pObj)
{
    if (pObj->Is_Initialized > 0)
    {
        if (pObj->IO.DeInit != 0)
        {
            if (pObj->IO.DeInit() < 0)
            {
                return PHY_STATUS_ERROR;
            }
        }

        pObj->Is_Initialized = 0;
    }

    return PHY_STATUS_OK;
}

int32_t TJA1100_GetLinkState(phy_Object_t *pObj)
{
    uint32_t readval = 0;

    /* Read Status register  */
    if (pObj->IO.ReadReg(pObj->DevAddr, TJA1100_BASIC_STAT, &readval) < 0)
    {
        return PHY_STATUS_READ_ERROR;
    }

    /* Read Status register again */
    if (pObj->IO.ReadReg(pObj->DevAddr, TJA1100_BASIC_STAT, &readval) < 0)
    {
        return PHY_STATUS_READ_ERROR;
    }

    if ((readval & TJA1100_BASIC_STAT_LINK_STATUS) == 0)
    {
        /* Return Link Down status */
        return PHY_STATUS_LINK_DOWN;
    }
    else
    {
        return PHY_STATUS_100MBITS_FULLDUPLEX;
    }
}

/*
 * Remote loopback mode is suitable to test the signal layer of TJA1100
 * https://endurosat.atlassian.net/wiki/spaces/SPE/pages/2433253640/Test+strategy+for+OBC19+PHY#Testing-the-analog-signal-end-connector-PHY
 * https://endurosat.atlassian.net/wiki/spaces/SPE/pages/2432467460/Schematics#Signal-part-of-TJA1100
 *
 * */
int32_t TJA1100_EnableLoopbackModeRemote(phy_Object_t *pObj)
{
    phy_modify(pObj, TJA1100_EXTENDED_CTRL,
            TJA1100_EXTENDED_CTRL_LOOPBACK_MODE_MASK,
            TJA1100_EXTENDED_CTRL_LOOPBACK_MODE_REMOTE);

    return phy_set_bits(pObj, TJA1100_BASIC_CTRL, TJA1100_BASIC_CTRL_LOOPBACK);
}

int32_t TJA1100_DisableLoopbackModeRemote(phy_Object_t *pObj)
{
    return phy_clear_bits(pObj, TJA1100_BASIC_CTRL, TJA1100_BASIC_CTRL_LOOPBACK);
}
