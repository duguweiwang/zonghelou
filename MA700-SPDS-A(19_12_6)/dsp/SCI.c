/*********************************************************************
*                                                                    *
*           COPYRIGHT (C)    SAEShanghai , China                     *
*                         ALL RIGHTS RESERVED                        *
*                                                                    *
*The copying, use, distribution or disclosure of the confidential and*
*proprietary information contained in this document(s) is strictly   *
*prohibited without prior written consent. Any breach shall subject  *
*the infringing party to remedies. The owner reserves all rights in  *
*the event of the grant of a patent or the registration of a utility *
*model or design.                                                    *
*                                                                    *
*--------------------------------------------------------------------*
*                     MODULE DESCRIPTION                             *
* Module Name:        SCI.C                                          *
* Module Version:                                                    *
*--------------------------------------------------------------------*
* Original Author:    WangJian                                       *
* Date:               2015-4-1                                       *
* -------------------------------------------------------------------*
*                          CHANGE HISTORY                            *
* Date            modifier             description                   *
* 2017/3/30       SunXiaopeng       update the data structure        *
* -------------------------------------------------------------------*
*                          CHANGE HISTORY                            *
* Date       Modifier          Description                           *
* 2017/8/6   ZhaoMingming  update the related format and some error  *
*        according to the  C919 CPAs&DCS Source Code Review          *
*********************************************************************/
/*****************Includes*******************************************/
#include "SCI.h"
#include "gpio.h"
/*#include "CBIT.h"*/
#include "GPIO_APP.h"
/***************Definitions*****************************************/
#pragma DATA_SECTION(SCI_SciaRegs,"SciaRegsFile");/*#pragma is used to register definition*/
volatile struct SCI_REGS SCI_SciaRegs;

#pragma DATA_SECTION(SCI_ScibRegs,"ScibRegsFile");/*#pragma is used to register definition*/
volatile struct SCI_REGS SCI_ScibRegs;

#pragma DATA_SECTION(SCI_ScicRegs,"ScicRegsFile");/*#pragma is used to register definition*/
volatile struct SCI_REGS SCI_ScicRegs;

/**********Functions Declarations*************************************/


/*******************************************************************
*Function:   Sci_Init                                              *
*Description:initialize the SCI Module.                            *
*------------------------------------------------------------------*
*GLOBAL VARIABLE     USAGE DESCRIPTION                             *
*NONE                NONE                                          *
*------------------------------------------------------------------*
*PARAMETER           DESCRIPTION                                   *
*NONE                NONE                                          *
*------------------------------------------------------------------*
*RETURN VALUE        DESCRIPTION                                   *
*NONE                NONE                                          *
*******************************************************************/
void Sci_Init(void)
{
    /*SCIA I/O*/
    SCI_SciaRegs.SCICTL1.bit.SWRESET=0U;     /*Reset SCI*/
    EALLOW;
    GPIO_GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 1U;    /* SCIRXDA*/
    GPIO_GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 1U;    /* SCITXDA*/
    EDIS;
    /*------------------------------------------------------*/
    SCI_SciaRegs.SCICCR.bit.STOPBITS=0U;     /*1 stop bit*/
    SCI_SciaRegs.SCICCR.bit.PARITYENA=0U;    /*No parity*/
    SCI_SciaRegs.SCICCR.bit.LOOPBKENA=0U;    /*No loopback*/
    SCI_SciaRegs.SCICCR.bit.ADDRIDLE_MODE=0U;/*idle-line protocol*/
    SCI_SciaRegs.SCICCR.bit.SCICHAR=7U;      /*8 char bits*/

    SCI_SciaRegs.SCICTL1.bit.TXENA=1U;       /*Enable SCIA-TX*/
    SCI_SciaRegs.SCICTL1.bit.RXENA=1U;       /*Enable SCIA-RX*/

    SCI_SciaRegs.SCIHBAUD = (292U /256U);    /* Baudrate Highbyte*/
    SCI_SciaRegs.SCILBAUD = 292U & 0x00FFU;  /* Baudrate Lowbyte*/

    SCI_SciaRegs.SCICTL1.bit.SWRESET=1U;     /*Reset SCI*/
}

/*******************************************************************
*Function:   SCI_Tx_Data                                           *
*Description:transmit the data                                     *
*------------------------------------------------------------------*
*GLOBAL VARIABLE     USAGE DESCRIPTION                             *
*NONE                NONE                                          *
*------------------------------------------------------------------*
*PARAMETER           DESCRIPTION                                   *
*au16_dat            the sent data                                 *
*------------------------------------------------------------------*
*RETURN VALUE        DESCRIPTION                                   *
*NONE                NONE                                          *
*******************************************************************/
void SCI_Tx_Data(UNUM16 au16_data)
{
    SCI_SciaRegs.SCITXBUF = au16_data;            /* send data*/
    SCI_SciaRegs.SCICTL2.bit.TXRDY;
    while ( SCI_SciaRegs.SCICTL2.bit.TXEMPTY == 0U)   /*wait for TX -empty*/
    {
    }
}

/*******************************************************************
*Function:   SCI_Rx_Data                                           *
*Description:Receive a data                                        *
*------------------------------------------------------------------*
*GLOBAL VARIABLE     USAGE DESCRIPTION                             *
*NONE                NONE                                          *
*------------------------------------------------------------------*
*PARAMETER           DESCRIPTION                                   *
*NONE                NONE                                          *
*------------------------------------------------------------------*
*RETURN VALUE        DESCRIPTION                                   *
*lu16_dat       Return received data, if no data received return 0 *
*******************************************************************/
UNUM16 SCI_Rx_Data(void)
{
    UNUM16 lu16_dat=256U;
    if(SCI_SciaRegs.SCIRXST.bit.RXRDY ==1U ) /*New data coming*/
    {
        lu16_dat=SCI_SciaRegs.SCIRXBUF.bit.RXDT;
    }
    return lu16_dat;
}

/*******************************************************************
*Function:   SCI_Error_Process                                     *
*Description:process SCI error                                     *
*------------------------------------------------------------------*
*GLOBAL VARIABLE     USAGE DESCRIPTION                             *
*NONE                NONE                                          *
*------------------------------------------------------------------*
*PARAMETER           DESCRIPTION                                   *
*NONE                NONE                                          *
*------------------------------------------------------------------*
*RETURN VALUE        DESCRIPTION                                   *
*NONE                NONE                                          *
*******************************************************************/
void SCI_Error_Process(void)
{
    if(SCI_SciaRegs.SCIRXST.bit.RXERROR ==1U)
    {
        SCI_SciaRegs.SCICTL1.bit.SWRESET =0U;/*reset SCI*/
        SCI_SciaRegs.SCICTL1.bit.SWRESET =1U;
    }
}

/*===========================================================================*/
/* End of SourceCode.*/
/*===========================================================================*/
