/*******************************************************************
*              SAE COPYRIGHT (C) SAEShanghai, China                *
*                        ALL RIGHTS RESERVED                       *
* The copying, use, distribution or disclosure of the confidential *
* and proprietary information contained in this document(s) is     *
* strictly prohibited without prior written consent. Any breach    *
* shall subject the infringing party to remedies. The owner        *
* reserves all rights in the event of the grant of a patent or the *
* registration of a utility model or design.                       *
*------------------------------------------------------------------*
*                      MODULE DESCRIPTION                          *
* Module Name:       I2C                                      *
* Module Version:                                                  *
*------------------------------------------------------------------*
* Original Author: HuangLiling                                     *
* Date:20170303                                                    *
*------------------------------------------------------------------*
*                        CHANGE HISTORY                            *
* DATE       Modifier       DESCRIPTION                            *
*2017/04/05 huangliling Code optimization according to the SCS(CR452)*
*2017/04/10 huangliling update IIC code according to bootload IIC(CR455)*
*2017/07/13 huangliling update for code review                     *
* *****************************************************************/


/*****************************Includes*****************************/
#include "I2C.h"
#include "DEVICE.h"
#include "GPIO.h"
#include "PIE_CTRL.h"
#include "DEVICE_cfg.h"
#include "WDG_cfg.h"

/*************Definitions******************************************/

/*************Variable Declarations********************************/
#pragma DATA_SECTION(I2caRegs,"I2caRegsFile");
volatile struct I2C_REGS I2caRegs;
const UNUM16 I2C_mu16_Register_Ref = (UNUM16)8;

/*************Functions Declarations*******************************/


STATIC UNUM16 I2C_ReadOneBlock(UNUM16 *ap_I2C_Buffer,UNUM16 au16_I2C_Address,UNUM16 au16_I2C_Len);
STATIC UNUM16 I2C_SendReadAddr(UNUM16 au16_I2C_Address);
STATIC UNUM16 I2C_WaitRxReady(UNUM16 au16_I2C_Len);
STATIC UNUM16 I2C_ReadData(UNUM16 *ap_I2C_Buffer, UNUM16 au16_I2C_Len);

STATIC UNUM16 I2C_BlkTx_Addr(UNUM16 *ap_I2C_Buffer, UNUM16 au16_I2C_Address, UNUM16 au16_DataLen, I2C_WR_STATE *ap_State);
STATIC UNUM16 I2C_SendWriteCmd(UNUM16 *ap_I2C_Buffer, UNUM16 au16_I2C_Address,UNUM16 au16_I2C_Len);
STATIC void I2C_BlkTx_W4DataEnd(I2C_WR_STATE *ap_State);
STATIC UNUM16 I2C_BlkTx_Data(UNUM16 *ap_I2C_Buffer,UNUM16 au16_DataLen, I2C_WR_STATE * ap_State);
STATIC UNUM16 I2C_BlkTx_W4Stop(I2C_WR_STATE *ap_State);
/*************Functions Definition*********************************/
/*******************************************************************
*Function: I2C_Init                                                *
*Description: Initialize the I2C                                   *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*     NONE                                                         *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     NONE                NONE                                     *
*******************************************************************/
void I2C_Init(void)
{
    I2caRegs.I2CMDR.all  = (UNUM16)0x0000; /* Take I2C reset Stop I2C when suspended */
    I2caRegs.I2CFFTX.all = (UNUM16)0x0000; /* Disable FIFO mode and TXFIFO */
    I2caRegs.I2CFFRX.all = (UNUM16)0x0040; /* Disable RXFIFO, clear RXFFINT, */

    I2caRegs.I2CPSC.all  = (UNUM16)8;          /* Prescaler - need 7-12 Mhz on module clk (150/15 = 10MHz) */
    I2caRegs.I2CCLKL     = (UNUM16)10;         /* NOTE: must be non zero, 400KHz frequency */
    I2caRegs.I2CCLKH     = (UNUM16)5;          /* NOTE: must be non zero */
    I2caRegs.I2CIER.all  = (UNUM16)0x24;       /* Enable SCD & ARDY interrupts */
    I2caRegs.I2CMDR.all  = (UNUM16)0x0020;     /* Take I2C out of reset */
    I2caRegs.I2CFFTX.all = (UNUM16)0x6000;     /* Enable FIFO mode and TXFIFO */
    I2caRegs.I2CFFTX.bit.TXFFIL = (UNUM16)1;   /* 4 bytes*/
    I2caRegs.I2CFFTX.bit.TXFFIENA = (UNUM16)1; /*enable INT*/
    I2caRegs.I2CFFRX.all = (UNUM16)0x2040;     /* Enable RXFIFO, clear RXFFINT */

    I2caRegs.I2CMDR.bit.NACKMOD = (UNUM16)0; /* In master-receiver, auto send ACK to transmitter */
    I2caRegs.I2CMDR.bit.FREE = (UNUM16)1;    /* runs free, when a breakpoint occurs, continues to operate */
    I2caRegs.I2CMDR.bit.STT = (UNUM16)0;     /* in master mode, setting STT = 1 causes module to generate a START condition on bus */
    I2caRegs.I2CMDR.bit.STP = (UNUM16)0;     /* =1 generate a STOP condition */
    I2caRegs.I2CMDR.bit.MST = (UNUM16)1;     /* 1: master mode, 0: slave mode */
    I2caRegs.I2CMDR.bit.TRX = (UNUM16)0;     /* 1: TX mode, 0: RX mode */
    I2caRegs.I2CMDR.bit.XA  = (UNUM16)0;     /* 0: Normal addressing mode(7-bit address), 1: Expanded(10-bit address) */
    I2caRegs.I2CMDR.bit.RM  = (UNUM16)0;     /* Non repeat mode */
    I2caRegs.I2CMDR.bit.DLB = (UNUM16)0;
    I2caRegs.I2CMDR.bit.IRS = (UNUM16)1;     /* enable I2C module */
    I2caRegs.I2CMDR.bit.STB = (UNUM16)0;     /* NOT in START byte mode */
    I2caRegs.I2CMDR.bit.FDF = (UNUM16)0;     /* not free data */
    I2caRegs.I2CMDR.bit.BC  = (UNUM16)0;     /* 8 bits per data byte */

    I2C_InitGpio();

    return;
}
/*******************************************************************
*Function: I2C_InitGpio                                            *
*Description: Initialize the GPIO for I2C                          *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*     NONE                                                         *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     NONE                NONE                                     *
*******************************************************************/
void I2C_InitGpio(void)
{
    EALLOW;
    GPIO_GpioCtrlRegs.GPBPUD.bit.GPIO32   = (UNUM16)0; /* Enable pull-up for GPIO32 (SDAA)*/
    GPIO_GpioCtrlRegs.GPBPUD.bit.GPIO33   = (UNUM16)0; /* Enable pull-up for GPIO33 (SCLA)*/
    GPIO_GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = (UNUM16)3; /* Asynch input GPIO32 (SDAA) */
    GPIO_GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = (UNUM16)3; /* Asynch input GPIO33 (SCLA) */
    GPIO_GpioCtrlRegs.GPBMUX1.bit.GPIO32  = (UNUM16)1; /* Configure GPIO32 for SDAA operation */
    GPIO_GpioCtrlRegs.GPBMUX1.bit.GPIO33  = (UNUM16)1; /* Configure GPIO33 for SCLA operation */
    EDIS;
}
/*******************************************************************
*Function: I2C_Read                                                *
*Description:Read Data for I2C                                     *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*   NONE                                                           *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*  UNUM16 *            ap_I2C_Buffer                               *
*  UNUM16              au16_I2C_Address                            *
*  UNUM16              au16_DataLen                                *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*   UNUM16               Indicate read successful or failed        *
*******************************************************************/
UNUM16 I2C_Read(UNUM16 *ap_I2C_Buffer,UNUM16 au16_I2C_Address,UNUM16 au16_DataLen)
{
    UNUM16 lu16_I2C_ret = I2C_SUCCESS;
    UNUM16 lu16_I2C_Len = (UNUM16)0;

    do
    {
        if(au16_DataLen<=(UNUM16)16)
        {
            lu16_I2C_Len = au16_DataLen;
        }
        else
        {
            lu16_I2C_Len = (UNUM16)16;
        }
        if( (UNUM16)FALSE == I2C_ReadOneBlock(ap_I2C_Buffer,au16_I2C_Address,lu16_I2C_Len))
        {
            I2C_Init();
            lu16_I2C_ret = I2C_ERROR;
            break;
        }

        WDG_ServiceDog();

        au16_DataLen -= lu16_I2C_Len;      /* refresh data length */
        au16_I2C_Address += lu16_I2C_Len;  /* refresh address */
        ap_I2C_Buffer += lu16_I2C_Len;     /* refresh buffer address*/

    }while(au16_DataLen);

    return lu16_I2C_ret;
}
/*******************************************************************
*Function: I2C_ReadOneBlock                                        *
*Description: Read one block for I2c                               *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    UNUM16           *ap_I2C_Buffer                               *
*    UNUM16            au16_I2C_Address                            *
*    UNUM16            au16_I2C_Len                                *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
* UNUM16               Indicate read successful or failed          *
*******************************************************************/
STATIC UNUM16 I2C_ReadOneBlock(UNUM16 *ap_I2C_Buffer,UNUM16 au16_I2C_Address,UNUM16 au16_I2C_Len)
{
    I2C_RD_STATE lu16_State = I2C_RD_STA_ADDR;
    UNUM16 lu16_Ret = (UNUM16)TRUE;
    UNUM16 TImeOutCount = 0U;

    while(TImeOutCount < 5000U)  /* All operation should be completed within 5 ms */
    {
        switch(lu16_State)
        {
            case I2C_RD_STA_ADDR: /*state 1£¬send address*/
            {
                if((UNUM16)TRUE == I2C_SendReadAddr(au16_I2C_Address))
                {
                    lu16_State = I2C_RD_STA_W4DATA;
                }
                else
                {
                    lu16_Ret = (UNUM16)FALSE;
                }
                break;
            }
            case I2C_RD_STA_W4DATA: /*state 2£¬wait for read flag*/
            {
                if((UNUM16)TRUE == I2C_WaitRxReady(au16_I2C_Len))
                {
                    lu16_State = I2C_RD_STA_DATA;
                }
                else
                {
                    lu16_Ret = (UNUM16)FALSE;
                }
                break;
            }
            case I2C_RD_STA_DATA: /*state 2£¬read data */
            {
                if((UNUM16)TRUE== I2C_ReadData(ap_I2C_Buffer, au16_I2C_Len))
                {
                    lu16_Ret = (UNUM16)TRUE;
                    lu16_State = I2C_RD_STA_W4_END;
                }
                else
                {
                    lu16_Ret = (UNUM16)FALSE;
                }
                break;
            }
            default:
            {
                break;
            }
        }
        DELAY_US(1);
        TImeOutCount++;

        if(lu16_State == I2C_RD_STA_W4_END)
        {
            break;
        }
    }

    return lu16_Ret;
}
/*******************************************************************
*Function: I2C_SendReadCmd                                         *
*Description: Send I2c read command                                *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    UNUM16 au16_I2C_Address                                       *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     UNUM16           Indicate send successful of failed          *
*******************************************************************/
STATIC UNUM16 I2C_SendReadAddr(UNUM16 au16_I2C_Address)
{
    UNUM16 lu16_Ret = (UNUM16)TRUE; /* 0-failed, 1-ok */
    UNUM16 lu16_HighAddr, lu16_LowAddr;

    lu16_HighAddr = au16_I2C_Address>>8;/* set address */
    lu16_LowAddr = au16_I2C_Address & (UNUM16)0xFF;

    if ((UNUM16)I2caRegs.I2CMDR.bit.STP == (UNUM16)1)
    {
        lu16_Ret = (UNUM16)FALSE;
    }
    else if(I2caRegs.I2CSTR.bit.BB) /* Bus busy */
    {
        lu16_Ret = (UNUM16)FALSE;
    }
    else
    {
        I2caRegs.I2CSAR = (UNUM16)au16_I2C_SlaveAddr;
        I2caRegs.I2CCNT = (UNUM16)2;
        I2caRegs.I2CDXR = lu16_HighAddr;
        I2caRegs.I2CDXR = lu16_LowAddr;
        I2caRegs.I2CMDR.all = (UNUM16)0x2620; /* Send data to setup EEPROM address */
    }

    return lu16_Ret;
}
/*******************************************************************
*Function: I2C_WaitRxReady                                         *
*Description:Wait I2C Receive Ready                                *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    UNUM16           au16_I2C_Len                                 *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     UNUM16              NONE                                     *
*******************************************************************/
STATIC UNUM16 I2C_WaitRxReady(UNUM16 au16_I2C_Len)
{
    UNUM16 lu16_Ret = (UNUM16)FALSE; /* 0-OK, 1-Failed */
    UNUM16 lu16_INT_Source;
    lu16_INT_Source = I2caRegs.I2CISRC.all;/* Read INT source */

    if(lu16_INT_Source == I2C_ARDY_ISRC)
    {
        if((UNUM16)I2caRegs.I2CSTR.bit.NACK == (UNUM16)1) /* set length */
        {
            I2caRegs.I2CMDR.bit.STP = (UNUM16)1; /*command a stop */
            I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
        }
        else
        {
            I2caRegs.I2CCNT = au16_I2C_Len;       /*Setup how many bytes to expect*/
            I2caRegs.I2CMDR.all = (UNUM16)0x2C20; /*Send restart as master receiver*/
            lu16_Ret = (UNUM16)TRUE;
        }
    }

    return lu16_Ret;
}
/*******************************************************************
*Function: I2C_ReceiveData                                         *
*Description:Receive I2C data                                      *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    UNUM16 *ap_I2C_Buffer                                         *
*    UNUM16 au16_I2C_Len                                           *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     UNUM16              NONE                                     *
*******************************************************************/
STATIC UNUM16 I2C_ReadData(UNUM16 *ap_I2C_Buffer, UNUM16 au16_I2C_Len)
{
    UNUM16 lu16_Ret = (UNUM16)TRUE; /* 0-fail, 1-ok */
    UNUM16 lu16_INT_Source;
    UNUM16 lu16_I2C_i;
    lu16_INT_Source = I2caRegs.I2CISRC.all;/* Read INT source */

    if(lu16_INT_Source == I2C_SCD_ISRC) /* Stop Condition Received */
    {
        for(lu16_I2C_i=(UNUM16)0; lu16_I2C_i < au16_I2C_Len; lu16_I2C_i++)
        {
            *ap_I2C_Buffer = I2caRegs.I2CDRR;
            ap_I2C_Buffer+=1;

        }
    }
    else
    {
        lu16_Ret = (UNUM16)FALSE;
    }

    return lu16_Ret;
}
/*******************************************************************
*Function: I2C_Write                                               *
*Description:Write data for I2c                                    *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    UNUM16 *ap_I2C_Buffer                                         *
*    UNUM16 au16_I2C_Address                                       *
*    UNUM16 au16_DataLen                                           *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     UNUM16              NONE                                     *
*******************************************************************/
UNUM16 I2C_Write( UNUM16 *ap_I2C_Buffer, UNUM16 au16_I2C_Address, UNUM16 au16_DataLen)
{
    UNUM16 lu16_I2C_ret = I2C_SUCCESS;
    UNUM16 TImeOutCount = 0U;
    I2C_WR_STATE lu16_State = I2C_WR_STA_ADDR;
    UNUM16 lu16_SendLen = 0U;
    UNUM16 lu16_stopFlag=(UNUM16)FALSE;
    while(TImeOutCount < 10000U)
    {
        switch(lu16_State)
        {
            case I2C_WR_STA_ADDR:   /*state 1£¬send address and 14 data*/
            {
                lu16_SendLen = I2C_BlkTx_Addr(ap_I2C_Buffer,au16_I2C_Address,au16_DataLen,&lu16_State);
                au16_DataLen = au16_DataLen - lu16_SendLen;
                ap_I2C_Buffer = (UNUM16*)((UNUM32)ap_I2C_Buffer + (UNUM32)lu16_SendLen);
                break;
            }
            case I2C_WR_STA_W4DATA: /*state 2£¬wait for address send end*/
            {
                I2C_BlkTx_W4DataEnd(&lu16_State);
                break;
            }
            case I2C_WR_STA_DATA:  /*state 3£¬send 16data*/
            {
                lu16_SendLen = I2C_BlkTx_Data(ap_I2C_Buffer,au16_DataLen,&lu16_State);
                au16_DataLen = au16_DataLen - lu16_SendLen;
                ap_I2C_Buffer = (UNUM16*) ((UNUM32)ap_I2C_Buffer + (UNUM32)lu16_SendLen);
                break;
            }
            case I2C_WR_STA_W4_END: /*state 4£¬wait for STOP*/
            {
                if(lu16_stopFlag==(UNUM16)FALSE)
                {
                    lu16_stopFlag=I2C_BlkTx_W4Stop(&lu16_State);
                }
                break;
            }
            default:
            {
                break;
            }
        }

        DELAY_US(1);
        TImeOutCount++;
    }

    if((au16_DataLen > 0U)||(lu16_stopFlag==(UNUM16)FALSE))
    {
        lu16_I2C_ret = I2C_ERROR;
    }

    return lu16_I2C_ret;
}
/*******************************************************************
*Function: I2C_BlkTx_Addr                                          *
*Description:Wait for the address transmission                     *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    UNUM16           *ap_I2C_Buffer                               *
*    UNUM16            au16_I2C_Address                            *
*    UNUM16            au16_I2C_Len                                *
*    I2C_WR_STATE     *ap_State                                    *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*    UNUM16             NONE                                       *
*******************************************************************/
STATIC UNUM16 I2C_BlkTx_Addr(UNUM16 *ap_I2C_Buffer, UNUM16 au16_I2C_Address, UNUM16 au16_DataLen, I2C_WR_STATE *ap_State)
{
    UNUM16 lu16_Len = 0U;

    if(au16_DataLen<=14U)
    {
        lu16_Len = au16_DataLen;
    }
    else
    {
        lu16_Len = 14U;
    }

    if((UNUM16)TRUE == I2C_SendWriteCmd(ap_I2C_Buffer,au16_I2C_Address,au16_DataLen))  /* 0 Send Address and 15 Bytes */
    {
        *ap_State = I2C_WR_STA_W4DATA;  /*Go to Wait Transfer Buffer*/
    }
    else
    {
        I2C_Init();
        lu16_Len = 0U;
    }

    if((au16_DataLen-lu16_Len) == 0U)
    {
        *ap_State = I2C_WR_STA_W4_END;
    }

    return lu16_Len;
}
/*******************************************************************
*Function: I2C_SendWriteCmd                                        *
*Description:Send the address                                      *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*   NONE                                                           *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*  UNUM16             *ap_I2C_Buffer                               *
*  UNUM16              au16_I2C_Address                            *
*  UNUM16              au16_I2C_Len                                *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
* UNUM16             FALSE: success to send, TRUE: fail to send.   *
*******************************************************************/
STATIC UNUM16 I2C_SendWriteCmd(UNUM16 *ap_I2C_Buffer, UNUM16 au16_I2C_Address,UNUM16 au16_I2C_Len)
{
    UNUM16 lu16_Ret = (UNUM16)TRUE; /* 0-fail, 1-ok */
    UNUM16 lu16_I2C_i;
    UNUM16 lu16_datalen = 14U;

    if(I2caRegs.I2CMDR.bit.STP)
    {
        lu16_Ret = (UNUM16)FALSE;
    }
    if(I2caRegs.I2CSTR.bit.BB) /*Bus busy*/
    {
        lu16_Ret = (UNUM16)FALSE;
    }
    else
    {
        I2caRegs.I2CSAR = (UNUM16)au16_I2C_SlaveAddr;
        I2caRegs.I2CCNT = au16_I2C_Len+2U;
        I2caRegs.I2CDXR = au16_I2C_Address>>8;      /*Setup data to send*/
        I2caRegs.I2CDXR = au16_I2C_Address & 0xFFU;

        if(au16_I2C_Len<=14U)
        {
            lu16_datalen = au16_I2C_Len;
        }
        else
        {
            lu16_datalen = 14U;
        }

        for (lu16_I2C_i=0U; lu16_I2C_i<lu16_datalen; lu16_I2C_i++)
        {
            I2caRegs.I2CDXR = *ap_I2C_Buffer;
            ap_I2C_Buffer+=1;
        }
        I2caRegs.I2CMDR.all = 0x6E20U; /* Send start as master transmitter */
    }

    return lu16_Ret;
}
/*******************************************************************
*Function: I2C_BlkTx_W4DataEnd                                     *
*Description:Wait for end                                          *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    I2C_WR_STATE      *ap_State                                   *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     NONE                NONE                                     *
*******************************************************************/
STATIC void I2C_BlkTx_W4DataEnd(I2C_WR_STATE *ap_State)
{
    if((UNUM16)I2caRegs.I2CFFTX.bit.TXFFST == 0U)
    {
        *ap_State = I2C_WR_STA_DATA; /*Ready for Next 14 bytes*/
    }

    return ;
}
/*******************************************************************
*Function: I2C_BlkTx_Data                                          *
*Description: Send up to 16 numbers, return                        *
*the actual transmission length                                    *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*     NONE                                                         *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    UNUM16           *ap_I2C_Buffer                               *
*    UNUM16            au16_DataLen                                *
*    I2C_WR_STATE     *ap_State                                    *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*     UNUM16              NONE                                     *
*******************************************************************/
STATIC UNUM16 I2C_BlkTx_Data(UNUM16 *ap_I2C_Buffer,UNUM16 au16_DataLen, I2C_WR_STATE *ap_State)
{
    UNUM16 lu16_Len = 0U;
    UNUM16 lu16_I2C_i;

    if(au16_DataLen>0U)
    {
        if(au16_DataLen<=16U)
        {
            lu16_Len = au16_DataLen;
        }
        else
        {
            lu16_Len = 16U;
        }

        for (lu16_I2C_i=0U; lu16_I2C_i<lu16_Len; lu16_I2C_i++)
        {
            I2caRegs.I2CDXR = *ap_I2C_Buffer;
            ap_I2C_Buffer+=1;
        }

        *ap_State = I2C_WR_STA_W4DATA; /* Go to Wait Tx Buffer */

        WDG_ServiceDog();

        if((au16_DataLen - lu16_Len) == 0U)
        {
            *ap_State = I2C_WR_STA_W4_END;
        }

    }
    else
    {
        *ap_State = I2C_WR_STA_W4_END;
    }

    return lu16_Len;
}
/*******************************************************************
*Function: I2C_BlkTx_W4Stop                                        *
*Description:Stop Condition Received for I2C                       *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
*   NONE                                                           *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*   I2C_WR_STATE      *ap_State                                    *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
* UNUM16,             FALSE: fail to stop, TRUE: success to stop   *
*******************************************************************/
STATIC UNUM16 I2C_BlkTx_W4Stop(I2C_WR_STATE *ap_State)
{
    UNUM16 lu16_INT_Source;
    UNUM16 lu16_Ret = (UNUM16)FALSE;  /*0-Fail, 1-OK*/

    lu16_INT_Source = I2caRegs.I2CISRC.all;/*Read INT source*/

    if(lu16_INT_Source == I2C_SCD_ISRC) /*Stop Condition Received*/
    {
        lu16_Ret = (UNUM16)TRUE;
    }
    else
    {
        if(I2caRegs.I2CSTR.bit.NACK)
        {
            I2caRegs.I2CMDR.bit.STP = 1U;
            I2caRegs.I2CSTR.all = I2C_CLR_NACK_BIT;
        }
    }

    return lu16_Ret;
}

/*******************************************************************
*Function:  I2C_CheckRegister                                      *
*Description:  This function is used to check I2C register         *
*------------------------------------------------------------------*
*GLOBAL VARIABLE       USAGE DESCRIPTION                           *
* NONE                 NONE                                        *
*------------------------------------------------------------------*
*PARAMETER             DESCRIPTION                                 *
*    NONE               NONE                                       *
*------------------------------------------------------------------*
*RETURNED VALUE        DESCRIPTION                                 *
*  UNUM16        indicates the error of pre-scaler configuration   *
*******************************************************************/

UNUM16 I2C_CheckRegister( void )
{
    UNUM16 lu16_error = (UNUM16)TRUE;
    if( (UNUM16)(I2caRegs.I2CPSC.all) == (UNUM16)I2C_mu16_Register_Ref )
    {
        lu16_error = (UNUM16)FALSE;
    }
    else
    {
        lu16_error = (UNUM16)TRUE;
    }
    return lu16_error;
}


/****************end of file***************************************/
