/******************************************************************************
*                                                                             *
*                         COPYRIGHT (C)   SAE                                 *
*                         ALL RIGHTS RESERVED                                 *
*                                                                             *
*    The copying, use, distribution or disclosure of the confidential and     *
*    proprietary information contained in this document(s) is strictly        *
*    prohibited without prior written consent. Any breach shall subject       *
*    the infringing party to remedies. The owner reserves all rights in       *
*    the event of the grant of a patent or the registration of a utility      *
*    model or design.                                                         *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Module Description:  module to provide a realtime scheduler	          *
*     Module Name:         %name:     ECAN.c %                                *
*     Module Version:      %version:  2 %                                     *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	  		                                                      *
*                                                                             *
*     Controller:                                                             *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*				  %created_by:   maolei %                                     *
*									                                          *
*     Date:       %date_modified:  2013-10-08 %                 			  *
*                                                                             *
******************************************************************************/

/**** includes ***************************************************************/
#include "ECAN_cfg.h"
#include "ECAN.h" /* DSP2833x Examples Include File*/
#include "DEVICE.h"
#include "DEVICE_cfg.h"
#include "GPIO.h"
#include "PIE_CTRL.h"
#include "SYS_CTRL.h"

/**** definitions*************************************************************/
#pragma DATA_SECTION(ECAN_ECanaRegs,"ECanaRegsFile");
volatile struct ECAN_REGS ECAN_ECanaRegs;

#pragma DATA_SECTION(ECAN_ECanaMboxes,"ECanaMboxesFile");
volatile struct ECAN_MBOXES ECAN_ECanaMboxes;

#pragma DATA_SECTION(ECAN_ECanaLAMRegs,"ECanaLAMRegsFile");
volatile struct LAM_REGS ECAN_ECanaLAMRegs;

#pragma DATA_SECTION(ECAN_ECanaMOTSRegs,"ECanaMOTSRegsFile");
volatile struct MOTS_REGS ECAN_ECanaMOTSRegs;

#pragma DATA_SECTION(ECAN_ECanaMOTORegs,"ECanaMOTORegsFile");
volatile struct MOTO_REGS ECAN_ECanaMOTORegs;

#pragma DATA_SECTION(ECAN_ECanbRegs,"ECanbRegsFile");
volatile struct ECAN_REGS ECAN_ECanbRegs;

#pragma DATA_SECTION(ECAN_ECanbMboxes,"ECanbMboxesFile");
volatile struct ECAN_MBOXES ECAN_ECanbMboxes;

#pragma DATA_SECTION(ECAN_ECanbLAMRegs,"ECanbLAMRegsFile");
volatile struct LAM_REGS ECAN_ECanbLAMRegs;

#pragma DATA_SECTION(ECAN_ECanbMOTSRegs,"ECanbMOTSRegsFile");
volatile struct MOTS_REGS ECAN_ECanbMOTSRegs;

#pragma DATA_SECTION(ECAN_ECanbMOTORegs,"ECanbMOTORegsFile");
volatile struct MOTO_REGS ECAN_ECanbMOTORegs;

volatile struct ECAN_REGS *ECAN_mp_Regs[2];
volatile struct ECAN_MBOXES *ECAN_mp_MBoxes[2];
volatile struct LAM_REGS *ECAN_mp_LAM_Regs[2];
volatile struct ECAN_REGS ECAN_ms_Regs_Shadow[2];

const UNUM16 ECAN_mu16_Register_Ref = (UNUM16)9;

UNUM32 recHighBytes[10] = {(UNUM16)0}; /*add yfc!!!!!!!!!!!!!!!!!!!!!*/
UNUM32 recLowBytes[10] = {(UNUM16)0};  /*add yfc!!!!!!!!!!!!!!!!!!!!!*/
UNUM32 GROUP_FLAG[5] = {(UNUM16)0};/* add lrq!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/**** functions **************************************************************/
/**********************************************************************
* FUNCTION: TO initialize ECAN Module:
* This function initializes ECAN Module.
* You can select ECANA or ECANB individually.
* If you want to select ECANA and ECANB both, you should Call this function twice with the right parameter.
* This function initializes the selected ECAN module to a known state.
* Including Pins configuration£»
* Including Mailbox Initialization£»
* Including CAN related registers Initialization£»
* Including CAN Baud Rate configuration£»
* Including related Interruption configuration;
**********************************************************************/
void ECAN_InitModule( void )
{
/* if DSP28_ECANA is ENABLE which is defined in "device.h" */
#if DSP28_ECANA
	EALLOW;
	SYS_SysCtrlRegs.PCLKCR0.bit.ECANAENCLK = (UNUM16)BIT_SET; /* ECAN Module CLK Enable */
	EDIS;
	ECAN_mp_Regs[ECAN_ECANA_SN] = &ECAN_ECanaRegs; /* Address ECANA ECAN Registers */
	ECAN_mp_MBoxes[ECAN_ECANA_SN] = &ECAN_ECanaMboxes; /* Address ECANA Mailbox Registers */
	ECAN_mp_LAM_Regs[ECAN_ECANA_SN] = &ECAN_ECanaLAMRegs; /* Address ECANA LAM Registers */
	ECAN_InitECan((UNUM16)ECAN_ECANA_SN);
#endif

#if DSP28_ECANB
	EALLOW;
	SYS_SysCtrlRegs.PCLKCR0.bit.ECANBENCLK = (UNUM16)BIT_SET;		/* ECAN Module CLK Enable */
	EDIS;
	ECAN_mp_Regs[ECAN_ECANB_SN] = &ECAN_ECanbRegs;			/* Address ECANB eCAN Registers */
	ECAN_mp_MBoxes[ECAN_ECANB_SN] = &ECAN_ECanbMboxes;		/* Address ECANB Mailbox Registers */
	ECAN_mp_LAM_Regs[ECAN_ECANB_SN] = &ECAN_ECanbLAMRegs;	/* Address ECANB LAM Registers */
	ECAN_InitECan((UNUM16)ECAN_ECANB_SN);
#endif

}

/* Initialize ECAN module */
void ECAN_InitECan( UNUM16 au16_ECanModuleSN )
{
	UNUM16 lu16_Loop_i;
	UNUM16 lu16_ECAN_WaitCounter = (UNUM16)ECAN_MAX_WAIT_COUNTER;
/* Create a shadow register structure for the CAN control registers. */
/* This is needed, since only 32-bit access is allowed to these registers. */
/* 16-bit access to these registers could potentially corrupt the register contents or return false data. */
/* This is especially true while writing to/reading from a bit (or group of bits) among bits 16 - 31 */

	EALLOW;		/* EALLOW enables access to protected bits. */
/* Configure ECAN TX pins for CAN operation using ECAN registers */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTIOC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANTIOC.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTIOC.bit.TXFUNC = (UNUM16)BIT_SET;
    ECAN_mp_Regs[au16_ECanModuleSN]->CANTIOC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTIOC.all;

/* Configure ECAN RX pins for CAN operation using ECAN registers */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRIOC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANRIOC.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRIOC.bit.RXFUNC = (UNUM16)BIT_SET;
    ECAN_mp_Regs[au16_ECanModuleSN]->CANRIOC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRIOC.all;
    
/* Configure ECAN for HECC mode(required to access mailboxes 16 thru 31) */
/* HECC mode also enables time-stamping feature */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all;
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.SCB = (UNUM16)BIT_SET; /* ECAN MODE */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.STM  = (UNUM16)BIT_SET; /* NORMAL MODE */
	ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all;
    EDIS;
    
/* Disable all Mailboxes  */
    ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all = (UNUM32)0x00000000; /* Required before writing the MSGIDs */

/* Initialize all bits of 'Master Control Field' to zero */
/* Some bits of MSGCTRL register come up in an unknown state. */
/* For proper operation, all bits (including reserved bits) of MSGCTRL must be initialized to zero. */
/* In ECAN Mode, the number of Mailbox is 32. */

    for ( lu16_Loop_i = (UNUM16)0; lu16_Loop_i < (UNUM16)ECAN_MBOX_NUM; lu16_Loop_i++ )
    {
        ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_Loop_i].MSGCTRL.all = (UNUM32)0x00000000;
        ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_Loop_i].MSGID.all = (UNUM32)0x00000000;
    }

/* TAn, RMPn, GIFn bits are all zero upon reset and are cleared again as a matter of precaution. */
/* CANTA -- Register -- Mailbox Transmission Acknowledge Bits (TA) */
/* 0 = the message is not sent. */
/* 1 = if the message of mailbox n is sent successfully, the bit n of this register is set.  */
/* Note:  To  reset  a TA bit by software:  write a ¡®1¡¯ into it. */
	ECAN_mp_Regs[au16_ECanModuleSN]->CANTA.all	= (UNUM32)0xFFFFFFFFU; /* Clear all TAn bits */
/* CANRMP -- Register -- Mailbox Receive Message Pending Bits (RMP) */
/* 0 = the mailbox does not contain a message. */
/* 1 = the mailbox contains a valid message. */
/* Note:  To  reset  a RMP bit by software:  write a ¡®1¡¯ into it. */
	ECAN_mp_Regs[au16_ECanModuleSN]->CANRMP.all = (UNUM32)0xFFFFFFFFU; /* Clear all RMPn bits */
/* CANGIF0 -- Register -- Interrupt Flag Bits */
/* 0 = Interrupt has not occurred */
/* 1 = Interrupt  has occurred */
             /*ECAN_mp_Regs[au16_ECanModuleSN]->CANGIF0.all = (UNUM32)0xFFFFFFFF;*/ /* Clear all interrupt flag bits */
/* CANGIF1 -- Register -- Interrupt Flag Bits */
/* 0 = Interrupt has not occurred */
/* 1 = Interrupt  has occurred */
     	     /*ECAN_mp_Regs[au16_ECanModuleSN]->CANGIF1.all = (UNUM32)0xFFFFFFFF;*/
/* CANMIM -- Register -- Mailbox Interrupt Mask Bits (MIM) */
/* 0 = mailbox interrupt is disabled. */
/* 1 = mailbox interrupt is enabled. */
/* An Interrupt is generated if a message has been transmitted successfully or if a message has been received without an error. */
    EALLOW;
             /*ECAN_mp_Regs[au16_ECanModuleSN]->CANMIM.all = (UNUM32)0xFFFFFFFF;*/ /* Set all MIMn bits, Enable Mailboxes Interrupt */
 /* CANMIL -- Register -- Mailbox Interrupt Level Bits (MIL) */
 /* 0 = mailbox interrupt is generated on HECC_INT_REQ[0] line. */
 /* 1 = mailbox interrupt is generated on HECC_INT_REQ[1] line. */
             /*ECAN_mp_Regs[au16_ECanModuleSN]->CANMIL.all = (UNUM32)0;*/	/* All Mailbox Interrupt produced on interrupt line #1 */
/* CANMC Register CCR bit -- Change Configuration Request (CCR) */
/* 0 = software requests normal operation */
/* 1 = software requests write access to CANBTC, CANGAM, LAM[0] and LAM[3]. */
/* A request is granted by the CAN module with flag CCE (CANES) = 1. */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all;
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.CCR = (UNUM16)BIT_SET ; /* Set CCR = 1 */
    ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all;
    EDIS;

/* CANES Register CCE bit -- Change Configuration Enable (CCE) */
/* 0 = CPU cannot write into configuration registers. */
/* 1 = CPU has write access into configuration registers. */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANES.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANES.all;
    do
	{
	    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANES.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANES.all;
	    lu16_ECAN_WaitCounter--;
	} while( ( (UNUM16)ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANES.bit.CCE != (UNUM16)1 ) && (lu16_ECAN_WaitCounter != (UNUM16)0) ); /* Wait for CCE bit to be set. */

/* Configure Baud Rate for ECAN -- START */
/* To change the Baud Rate, remedy the MACRO definition in "ECAN.h" */
    EALLOW;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANBTC.all;
/* System Frequency 150MHz */
#if ( CPU_FRQ_150MHZ )
    #if ( ECAN_CAN_BAUDRATE_50KBPS )
        ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.BRPREG = (UNUM16)99;
	#endif
	#if ( ECAN_CAN_BAUDRATE_100KBPS )
        ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.BRPREG = (UNUM16)49;
	#endif
	#if ( ECAN_CAN_BAUDRATE_125KBPS )
        ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.BRPREG = (UNUM16)39;
	#endif
	#if ( ECAN_CAN_BAUDRATE_250KBPS )
        ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.BRPREG = (UNUM16)19;
	#endif
	#if ( ECAN_CAN_BAUDRATE_500KBPS )
        ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.BRPREG = (UNUM16)9;
    #endif
    #if ( ECAN_CAN_BAUDRATE_1000KBPS )
        ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.BRPREG = (UNUM16)4;
	#endif
	#if ( ECAN_CAN_SAMPLEPOINTONE )
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG2REG = (UNUM16)2;
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG1REG = (UNUM16)10;
	#endif
	#if ( ECAN_CAN_SAMPLEPOINTTWO )
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG2REG = (UNUM16)3;
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG1REG = (UNUM16)9;
	#endif
	#if ( ECAN_CAN_SAMPLEPOINTTHREE )
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG2REG = (UNUM16)4;
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG1REG = (UNUM16)8;
	#endif
	#if ( ECAN_CAN_SAMPLEPOINTFOUR )
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG2REG = (UNUM16)5;
		ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.TSEG1REG = (UNUM16)7;
	#endif
#endif


    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.SAM = (UNUM16)BIT_SET;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.bit.SJWREG = (UNUM16)ECAN_CAN_SJWVALUE;
    
    ECAN_mp_Regs[au16_ECanModuleSN]->CANBTC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANBTC.all;

	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all;
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.CCR = (UNUM16)BIT_CLEAR ; /* Set CCR = 0 */
    ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all;
    EDIS;

    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANES.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANES.all;
    do
    {
       ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANES.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANES.all;
    } while((ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANES.bit.CCE)); /* Wait for CCE bit to be  cleared */

    /* Configure Baud Rate for ECAN -- END */
    EALLOW;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all;
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.CCR  = (UNUM16)BIT_CLEAR; /* CPU Require Normal Operate */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.PDR  = (UNUM16)BIT_CLEAR; /* Normal Operate */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.DBO  = (UNUM16)BIT_CLEAR; /* Send/Receive the MSB Byte first */
	/*ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.DBO  = (UNUM16)BIT_SET;  Send/Receive the LSB Byte first  yfc fix*/
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.WUBA = (UNUM16)BIT_CLEAR; /* Out of Power-down Mode */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.CDR  = (UNUM16)BIT_CLEAR; /* CPU Require Normal Operate */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.ABO  = (UNUM16)BIT_CLEAR; /* Auto Recover bus */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.SRES = (UNUM16)BIT_CLEAR; /* No Influence */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.MBNR = (UNUM16)BIT_CLEAR; /* Number of Mailbox */
	ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all;
    EDIS; 
}

/*********************************************************************
* FUNCTION: Initialize GPIO:
* This function initializes GPIO pins to function as ECAN pins
* Each GPIO pin can be configured as a GPIO pin or up to 3 different
* peripheral functional pins. By default all pins come up as GPIO
* inputs after reset.
* Caution:
* Only one GPIO pin should be enabled for CANTXA/B operation.
* Only one GPIO pin should be enabled for CANRXA/B operation.
* Comment out other unwanted lines.
**********************************************************************/
void ECAN_InitECanGPIO( void )
{
	/* Enable internal pull-up for the selected CAN pins. */
	/* Pull-ups can be enabled or disabled by the user. */
	/* This will enable the pull ups for the specified pins. */
	/* Comment out other unwanted lines. */
	/* To change the PINS configuration for ECAN Module, remedy the MACRO definition in "ecan.h" */
	#if ( DSP28_ECANA )
	    #if ( ECAN_ECANA_PINSSELONE)
	        EALLOW;
	        GpioCtrlRegs.GPAPUD.bit.GPIO18 = ECAN_GPIO_SET_ZERO;	    /* Enable pull-up for GPIO18 (CANRXA) */
	        GpioCtrlRegs.GPAPUD.bit.GPIO19 = ECAN_GPIO_SET_ZERO;	    /* Enable pull-up for GPIO19 (CANTXA) */
	/* Set qualification for selected CAN pins to asynchronous only. */
	/* Inputs are synchronized to SYSCLKOUT by default. */
	/* This will select asynchronous (no qualification) for the selected pins. */
	        GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = ECAN_GPIO_SET_THREE;   /* Asynch qual for GPIO18 (CANRXA) */
	/* Configure eCAN-A pins using GPIO register */
	/* This specifies which of the possible GPIO pins will be eCAN functional pins. */
	        GpioCtrlRegs.GPAMUX2.bit.GPIO18 = ECAN_GPIO_SET_THREE;	/* Configure GPIO18 for CANRXA operation */
	        GpioCtrlRegs.GPAMUX2.bit.GPIO19 = ECAN_GPIO_SET_THREE;	/* Configure GPIO19 for CANTXA operation */
	        EDIS;
	    #endif
	    #if ( ECAN_ECANA_PINSSELTWO )
	        EALLOW;
	        GPIO_GpioCtrlRegs.GPAPUD.bit.GPIO30 = ECAN_GPIO_SET_ZERO;	    /* Enable pull-up for GPIO30 (CANRXA) */
	        GPIO_GpioCtrlRegs.GPAPUD.bit.GPIO31 = ECAN_GPIO_SET_ZERO;	    /* Enable pull-up for GPIO31 (CANTXA) */

	        GPIO_GpioCtrlRegs.GPAQSEL2.bit.GPIO30 = ECAN_GPIO_SET_THREE;   /* Asynch qual for GPIO30 (CANRXA) */

	        GPIO_GpioCtrlRegs.GPAMUX2.bit.GPIO30 = ECAN_GPIO_SET_ONE;	/* Configure GPIO30 for CANRXA operation */
	        GPIO_GpioCtrlRegs.GPAMUX2.bit.GPIO31 = ECAN_GPIO_SET_ONE;	/* Configure GPIO31 for CANTXA operation */
	        EDIS;

	    #endif
	#endif


#if ( DSP28_ECANB )
    #if( ECAN_ECANB_PINSSELONE )
        EALLOW;
	    GpioCtrlRegs.GPAPUD.bit.GPIO8 = ECAN_GPIO_SET_ZERO;	  /* Enable pull-up for GPIO8  (CANTXB) */
        GpioCtrlRegs.GPAPUD.bit.GPIO10 = ECAN_GPIO_SET_ZERO;	  /* Enable pull-up for GPIO10 (CANRXB) */

        GpioCtrlRegs.GPAQSEL1.bit.GPIO10 = ECAN_GPIO_SET_THREE; /* Asynch qual for GPIO10 (CANRXB) */

	    GpioCtrlRegs.GPAMUX1.bit.GPIO8 = ECAN_GPIO_SET_TWO;   /* Configure GPIO8 for CANTXB operation */
        GpioCtrlRegs.GPAMUX1.bit.GPIO10 = ECAN_GPIO_SET_TWO;  /* Configure GPIO10 for CANRXB operation */
        EDIS;
    #endif
    #if ( ECAN_ECANB_PINSSELTWO )
        EALLOW;
        GPIO_GpioCtrlRegs.GPAPUD.bit.GPIO12 = ECAN_GPIO_SET_ZERO;   /* Enable pull-up for GPIO12 (CANTXB) */
        GPIO_GpioCtrlRegs.GPAPUD.bit.GPIO13 = ECAN_GPIO_SET_ZERO;   /* Enable pull-up for GPIO13 (CANRXB) */

        GPIO_GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = ECAN_GPIO_SET_THREE; /* Asynch qual for GPIO13 (CANRXB) */

        GPIO_GpioCtrlRegs.GPAMUX1.bit.GPIO12 = ECAN_GPIO_SET_TWO;  /* Configure GPIO12 for CANTXB operation */
        GPIO_GpioCtrlRegs.GPAMUX1.bit.GPIO13 = ECAN_GPIO_SET_TWO;  /* Configure GPIO13 for CANRXB operation */
        EDIS;
    #endif
    #if ( ECAN_ECANB_PINSSELTHREE )
        EALLOW;
        GpioCtrlRegs.GPAPUD.bit.GPIO16 = ECAN_GPIO_SET_ZERO;   /* Enable pull-up for GPIO16 (CANTXB) */
        GpioCtrlRegs.GPAPUD.bit.GPIO17 = ECAN_GPIO_SET_ZERO;   /* Enable pull-up for GPIO17 (CANRXB) */

        GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = ECAN_GPIO_SET_THREE; /* Asynch qual for GPIO17 (CANRXB) */

        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = ECAN_GPIO_SET_TWO;  /* Configure GPIO16 for CANTXB operation */
        GpioCtrlRegs.GPAMUX2.bit.GPIO17 = ECAN_GPIO_SET_TWO;  /* Configure GPIO17 for CANRXB operation */
        EDIS;
    #endif
    #if ( ECAN_ECANB_PINSSELFOUR )
        EALLOW;
        GpioCtrlRegs.GPAPUD.bit.GPIO20 = ECAN_GPIO_SET_ZERO;   /* Enable pull-up for GPIO20 (CANTXB) */
        GpioCtrlRegs.GPAPUD.bit.GPIO21 = ECAN_GPIO_SET_ZERO;   /* Enable pull-up for GPIO21 (CANRXB) */

        GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = ECAN_GPIO_SET_THREE; /* Asynch qual for GPIO21 (CANRXB) */

        GpioCtrlRegs.GPAMUX2.bit.GPIO20 = ECAN_GPIO_SET_THREE;  /* Configure GPIO20 for CANTXB operation */

        GpioCtrlRegs.GPAMUX2.bit.GPIO21 = ECAN_GPIO_SET_THREE;  /* Configure GPIO21 for CANRXB operation */
        EDIS;
    #endif
#endif
}

/***********************************************************************
* FUNCTION: TO Self-Test ECAN Module:
* This function Self-Test ECAN Module, including all mailboxes.
* You can Self-Test ECANA or ECANB individually.
* If you want to Self-Test ECANA and ECANB both, you should Call this function twice with the right parameter.
* This function return Self-Test result in a UNUM32 data as fault status flag.
* In self-test mode, the transmit port also is receive port
**********************************************************************/
UNUM32 ECAN_SelfTest( UNUM16 au16_ECanModuleSN )
{
	UNUM16 lu16_ECanMBoxesSN; /* the mailbox serial number of ECAN Module */
	UNUM32 lu32_ECanRecFrmID; /* the ID of receive frame */
	UNUM32 lu32_ECanRecFrmLowData; /* the low data of receive frame */
	UNUM32 lu32_ECanRecFrmHighData; /* the high data of receive frame */
	UNUM16 lu16_ECanSelfTestNum; /* the number of self test */
	UNUM32 lu32_ECanSelfTestFlag; /* the flag for self test */
	UNUM16 lu16_ECanTestErrCount = (UNUM16)0; /* test error counter */
	UNUM32 ECAN_mu32_TestTimerOut = (UNUM32)0x7FFF; /* test error counter */
	lu32_ECanSelfTestFlag = (UNUM32)0x00000000;
	ECAN_mp_Regs[au16_ECanModuleSN]->CANRMP.all = (UNUM32)0;

	EALLOW; /*GPIO Disable*/
	GPIO_GpioCtrlRegs.GPAMUX2.bit.GPIO30 = (UNUM16)ECAN_GPIO_SET_ZERO; /* Configure GPIO30 for CANRXA operation */
	GPIO_GpioCtrlRegs.GPAMUX2.bit.GPIO31 = (UNUM16)ECAN_GPIO_SET_ZERO; /* Configure GPIO31 for CANTXA operation */
	EDIS;

	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all;

	if ( ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.STM )
	{
		ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all = (UNUM32)0x00000000;
		/* the lower 16 Mailbox will set to be transmit mailbox. */
	    for ( lu16_ECanMBoxesSN = (UNUM16)0; lu16_ECanMBoxesSN < (UNUM16)16; lu16_ECanMBoxesSN++ )
	    {
	    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MSGID.all = ECAN_MBOX_DEF_ID - ( lu16_ECanMBoxesSN );
	    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MSGCTRL.bit.RTR = (UNUM16)BIT_CLEAR;
	    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MSGCTRL.bit.DLC = (UNUM16)8;
	    }
	    /* the higher 16 Mailbox will set to be Receive mailbox. */
	    for ( lu16_ECanMBoxesSN = (UNUM16)16; lu16_ECanMBoxesSN < (UNUM16)ECAN_MBOX_NUM; lu16_ECanMBoxesSN++ )
	    {
	    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MSGID.all = (UNUM32)ECAN_MBOX_DEF_ID - ( (UNUM32)lu16_ECanMBoxesSN - (UNUM32)16 );
			ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MSGCTRL.bit.DLC = (UNUM16)8;
			ECAN_mp_LAM_Regs[au16_ECanModuleSN]->LAM[lu16_ECanMBoxesSN].all = (UNUM32)0;
    		ECAN_mp_LAM_Regs[au16_ECanModuleSN]->LAM[lu16_ECanMBoxesSN].bit.LAMI = (UNUM16)BIT_SET;
	    }
	    /* Mailbox configuration */
	    ECAN_mp_Regs[au16_ECanModuleSN]->CANMD.all = (UNUM32)0xFFFF0000U;
	    ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all = (UNUM32)0xFFFFFFFFU;

	    for ( lu16_ECanMBoxesSN = (UNUM16)0; lu16_ECanMBoxesSN < (UNUM16)16; lu16_ECanMBoxesSN++ )
	    {
	    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MDH.all = ECAN_DEF_SEND_DATA_HIGH;
	    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MDL.all = ECAN_DEF_SEND_DATA_LOW - ( lu16_ECanMBoxesSN );
	    }
        /* Self-Test Start */
	    for ( lu16_ECanSelfTestNum = (UNUM16)0; lu16_ECanSelfTestNum < (UNUM16)ECAN_SELF_TEST_MAX_NUM; lu16_ECanSelfTestNum++ )
	    {
	    	ECAN_mu32_TestTimerOut = (UNUM32)0x7FFFF;
	    	/* send messages from the lower 16 mailboxes */
	    	ECAN_mp_Regs[au16_ECanModuleSN]->CANTRS.all = 0x0000FFFF; /* Set TRS for all transmit mailboxes */

	    	while( (ECAN_mp_Regs[au16_ECanModuleSN]->CANTA.all != 0x0000FFFF) && (ECAN_mu32_TestTimerOut != (UNUM32)0) ) /* Wait for all TAn bits to be set.. */
	    	{
	    		ECAN_mu32_TestTimerOut--;
	    	}

	    	ECAN_mp_Regs[au16_ECanModuleSN]->CANTA.all = 0x0000FFFF; /* Clear all TAn */
	    	ECAN_mp_Regs[au16_ECanModuleSN]->CANTRS.all = (UNUM32)0x0;
			ECAN_mu32_TestTimerOut = (UNUM32)0x1FFF;

			while( (ECAN_mp_Regs[au16_ECanModuleSN]->CANRMP.all != 0xFFFF0000U) && (ECAN_mu32_TestTimerOut != (UNUM32)0))
			{
				ECAN_mu32_TestTimerOut--;
			}

			ECAN_mp_Regs[au16_ECanModuleSN]->CANRMP.all = 0xFFFF0000U;
	    	/* Read from Receive mailboxes and check data */
	    	for ( lu16_ECanMBoxesSN = (UNUM16)16; lu16_ECanMBoxesSN < (UNUM16)ECAN_MBOX_NUM; lu16_ECanMBoxesSN++ )
	    	{
	    		lu32_ECanRecFrmID = ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MSGID.all;
	    		lu32_ECanRecFrmLowData = ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MDL.all;
	    		lu32_ECanRecFrmHighData = ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu16_ECanMBoxesSN].MDH.all;
                if(( lu32_ECanRecFrmID != lu32_ECanRecFrmLowData) || ( lu32_ECanRecFrmHighData != ECAN_DEF_SEND_DATA_HIGH ))
                {
                	lu16_ECanTestErrCount++;
                    lu32_ECanSelfTestFlag &= ~(( (UNUM32)1 << (UNUM32)lu16_ECanMBoxesSN ) | ((UNUM32)1 << ( (UNUM32)lu16_ECanMBoxesSN - (UNUM32)16 )));
                }
                else
                {
                    lu32_ECanSelfTestFlag |= (( (UNUM32)1<<(UNUM32)lu16_ECanMBoxesSN ) | ((UNUM32)1<<((UNUM32)lu16_ECanMBoxesSN - (UNUM32)16 )));
                }
	    	}
	    }
	}
	else
	{
	}
	EALLOW; /*GPIO enable*/
	GPIO_GpioCtrlRegs.GPAMUX2.bit.GPIO30 = (UNUM16)ECAN_GPIO_SET_ONE; /* Configure GPIO30 for CANRXA operation */
	GPIO_GpioCtrlRegs.GPAMUX2.bit.GPIO31 = (UNUM16)ECAN_GPIO_SET_ONE; /* Configure GPIO31 for CANTXA operation */
	EDIS;

	return( lu32_ECanSelfTestFlag );
}

void ECAN_EnterNormalMode( UNUM16 au16_ECanModuleSN )
{
	EALLOW; /* EALLOW enables access to protected bits. */
/* ENTER NORMAL MODE */
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all;
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.bit.STM  = (UNUM16)BIT_CLEAR; /* NORMAL MODE */
	ECAN_mp_Regs[au16_ECanModuleSN]->CANMC.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMC.all;
    EDIS;
}

/*********************************************************************
* Note: Bit timing parameters must be chosen based on the network parameters such
* as the sampling point desired and the propagation delay of the network.
* The propagation delay is a function of length of the cable, delay introduced by
* the transceivers and Optical Coupler (if any).
* 
* The parameters used in this file must be changed taking into account the above
* mentioned factors in order to arrive at the bit-timing parameters suitable
* for a network.
**********************************************************************/

/***********************************************************************
* FUNCTION: Configure ECAN Mailbox for send messages:
* This function configure ECAN mailbox
* This function configure the ECAN mailbox to a work state.
* au16_ECanModuleSN: ECAN module selected, ECANA or ECANB,
* au32_ECanMailbox_SN: 0 thru 15 in SCC Mode
*                       0 thru 31 in ECAN Mode
* au32_MsgID: ID[28:0] bits in MSGID register
* this variable should be defined in App.c file using macro definition.
* ECAN_mu16_SendPriority: TPL[4-0] bits in MSGCTRL register
* ECAN_mu16_DataLength: DLC[3-0] bits in MSGCTRL register
**********************************************************************/
void ECAN_ConfigSendMsgBox( UNUM16 au16_ECanModuleSN,
                            UNUM32 au32_ECanMailbox_SN,
                            UNUM32 au32_MsgID,
                            SNUM16 as16_SendPriority,
                            SNUM16 as16_DataLength )
{
    UNUM32 lu32_Mailbox_SN_bit;
    lu32_Mailbox_SN_bit = (UNUM32)1 << au32_ECanMailbox_SN;
/* Clear related bit in CANTRS register */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANTRS.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all & (~lu32_Mailbox_SN_bit);
	ECAN_mp_Regs[au16_ECanModuleSN]->CANTRS.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all;
/* Confirm Mailbox are Unable, Required before writing the MSGIDs */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all & (~lu32_Mailbox_SN_bit);
    ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all;
/* Frame ID */
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGID.all = au32_MsgID;
/* Extended ID for ARINC-825 */
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGID.bit.IDE = (UNUM16)BIT_SET;
/* Not Use Receive Mask bits */    
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGID.bit.AME = (UNUM16)BIT_CLEAR;
/* Normal Send Mode */    
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGID.bit.AAM = (UNUM16)BIT_CLEAR;
/* Mailbox Send Priority */
    if ((as16_SendPriority >= 0) && (as16_SendPriority < 32))
    {
    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGCTRL.bit.TPL = (UNUM16)as16_SendPriority;
    }
    else
    {
        ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGCTRL.bit.TPL = (UNUM16)0;
    }
/* Remote Sent */
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGCTRL.bit.RTR = (UNUM16)BIT_CLEAR;
/* Data Length */
    if ( (as16_DataLength >= 0) && (as16_DataLength <= 8) )
    {
        ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGCTRL.bit.DLC = (UNUM16)as16_DataLength;
    }
    else
    {
    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGCTRL.bit.DLC = (UNUM16)0;
    }
/* Mailbox Direction Bits */
/* 0 = corresponding mailbox is defined as a transmit mailbox. */
/* 1 = corresponding mailbox is defined as a receive mailbox. */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMD.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all & (~lu32_Mailbox_SN_bit);
    ECAN_mp_Regs[au16_ECanModuleSN]->CANMD.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all;
/* Mailbox Enable Bits */
/* 0 = corresponding mailbox is disabled */
/* 1 = The corresponding mailbox is enabled. A mailbox must be disabled before */
/* writing to the contents of any mailbox identifier field. */
/* ECAN Mailbox #N Enable*/
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all | lu32_Mailbox_SN_bit;
    ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all;
}

/***********************************************************************
* FUNCTION: Configure ECAN Mailbox for receive messages:
* This function configure ECAN mailbox
* This function configure the ECAN mailbox to a work state.
* au16_ECanModuleSN: ECAN module selected, ECANA or ECANB,
* au32_ECanMailbox_SN: 0 thru 15 in SCC Mode
*                       0 thru 31 in ECAN Mode
* au32_MsgID: ID[28:0] bits in MSGID register
* this variable should be defined in App.c file using macro definition.
* ECAN_mu16_SendPriority: TPL[4-0] bits in MSGCTRL register
* ECAN_mu16_DataLength: DLC[3-0] bits in MSGCTRL register
**********************************************************************/
void ECAN_ConfigRecMsgBox( UNUM16 au16_ECanModuleSN,
                           UNUM32 au32_ECanMailbox_SN,
                           UNUM32 au32_MsgID,
                           UNUM32 au32_MsgIDMask,
                           SNUM16 as16_DataLength )
{
    UNUM32 lu32_Mailbox_SN_bit;
    lu32_Mailbox_SN_bit = (UNUM32)1 << au32_ECanMailbox_SN;
/* Confirm Mailbox are Unable, Required before writing the MSGIDs */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all & (~lu32_Mailbox_SN_bit);
    ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all;
/* Frame ID */
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGID.all = au32_MsgID;
/* Extended ID for ARINC-825 */
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGID.bit.IDE = (UNUM16)BIT_SET;
/* Not Use Receive Mask bits */    
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGID.bit.AME = (UNUM16)BIT_SET;
/* Set Related Receive Mask Register */
    ECAN_mp_LAM_Regs[au16_ECanModuleSN]->LAM[au32_ECanMailbox_SN].all = au32_MsgIDMask & (UNUM32)0x1FFFFFFF;
    ECAN_mp_LAM_Regs[au16_ECanModuleSN]->LAM[au32_ECanMailbox_SN].bit.LAMI = (UNUM16)BIT_SET;
/* Data Length */
    if ((as16_DataLength >= 0) && (as16_DataLength <=8))
    {
        ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGCTRL.bit.DLC = (UNUM16)as16_DataLength;
    }
    else
    {
    	ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MSGCTRL.bit.DLC = (UNUM16)0;
    }
/* Mailbox Direction Bits
* 0 = corresponding mailbox is defined as a transmit mailbox.
* 1 = corresponding mailbox is defined as a receive mailbox. */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANMD.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all | lu32_Mailbox_SN_bit;
    ECAN_mp_Regs[au16_ECanModuleSN]->CANMD.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANMD.all;
/* Mailbox Enable Bits */
/* 0 = corresponding mailbox is disabled */
/* 1 = The corresponding mailbox is enabled. A mailbox must be disabled before */
/* writing to the contents of any mailbox identifier field. */
/* ECAN Mailbox #N Enable */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all | lu32_Mailbox_SN_bit;
    ECAN_mp_Regs[au16_ECanModuleSN]->CANME.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANME.all;
}

/***********************************************************************
* FUNCTION: Send a message to CAN bus:
* This function configure ECAN mailbox
* This function configure the ECAN mailbox to a work state.
* au16_ECanModuleSN: ECAN module selected, ECANA or ECANB,
* au32_ECanMailbox_SN: 0 thru 15 in SCC Mode
*                      0 thru 31 in ECAN Mode
* au32_MsgHighBytes:
* au32_MsgLowBytes:
**********************************************************************/
void ECAN_SendMsg( UNUM16 au16_ECanModuleSN,
                   UNUM32 au32_ECanMailbox_SN,
                   UNUM32 au32_MsgHighBytes,
                   UNUM32 au32_MsgLowBytes )
{
    UNUM32 lu32_Mailbox_SN_bit;
    UNUM16 lu16_ECAN_WaitCounter = (UNUM16)ECAN_MAX_WAIT_COUNTER;

    lu32_Mailbox_SN_bit = (UNUM32)1 << au32_ECanMailbox_SN;
    
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MDH.all = au32_MsgHighBytes;
    ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[au32_ECanMailbox_SN].MDL.all = au32_MsgLowBytes;
/* Send the message in related mailbox */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANTRS.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all | lu32_Mailbox_SN_bit;
    ECAN_mp_Regs[au16_ECanModuleSN]->CANTRS.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTRS.all;
/* Wait for the message is send successfully */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTA.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANTA.all;
    do
    {
        ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTA.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANTA.all;
        lu16_ECAN_WaitCounter--;
    } while( ( (UNUM32)( ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTA.all & lu32_Mailbox_SN_bit ) == (UNUM32)0 ) && (lu16_ECAN_WaitCounter != (UNUM16)0) ); /* Wait for TA bit to be set.*/
/* Set related bit to clear sending response */
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTA.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANTA.all;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTA.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTA.all | lu32_Mailbox_SN_bit;
    ECAN_mp_Regs[au16_ECanModuleSN]->CANTA.all  = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANTA.all;
}

UNUM16 ECAN_RecMsgAll( UNUM16 au16_ECanModuleSN )
{
    UNUM32 lu32_CANRecFlag = 0xFFFFFFFFU; /* NOT ALL MAILBOX USED FOR RECEIVE MESSAGES */
    UNUM32 lu32_MailboxSN = (UNUM32)0;
    UNUM32 lu32_TempBitPos = (UNUM32)0;
    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANRMP.all;

    if ( ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all )
    {
        do
        {
    	    lu32_TempBitPos = (UNUM32)1 << lu32_MailboxSN;
		    if ((ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all & lu32_TempBitPos ) == lu32_TempBitPos )
		    {
			    CAN_BUF_PutData( ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu32_MailboxSN].MSGID.all );
			    CAN_BUF_PutData( ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu32_MailboxSN].MSGCTRL.bit.DLC );
			    CAN_BUF_PutData( ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu32_MailboxSN].MDH.all );
			    CAN_BUF_PutData( ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu32_MailboxSN].MDL.all );
			    if(lu32_MailboxSN >  (UNUM16)2)
			    {
			    	recHighBytes[lu32_MailboxSN-(UNUM16)3] = ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu32_MailboxSN].MDH.all; /*add YFC receive command*/
			    	recLowBytes[lu32_MailboxSN-(UNUM16)3] = ECAN_mp_MBoxes[au16_ECanModuleSN]->MBOX[lu32_MailboxSN].MDL.all;  /*add YFC*/

			    }

			    lu32_CANRecFlag ^= lu32_TempBitPos;

			    if( ( ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRML.all & lu32_TempBitPos) == lu32_TempBitPos )
			    {
				    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRML.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRML.all & (~lu32_TempBitPos);
				    ECAN_mp_Regs[au16_ECanModuleSN]->CANRML.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRML.all;
			    }

			    /* clear related RMP bit */
			    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all | lu32_TempBitPos;
			    ECAN_mp_Regs[au16_ECanModuleSN]->CANRMP.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all;
			    ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all & (~lu32_TempBitPos);
		    }
		    else
		    {
		    }
		    if ( lu32_MailboxSN > (UNUM32)31 )
		    {
			    lu32_MailboxSN = (UNUM32)0;
		    }
		    else
		    {
			    lu32_MailboxSN++;
		    }
        }
        while( ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANRMP.all );
    }

    return ( (UNUM16)(~lu32_CANRecFlag) );
}

UNUM16 ECAN_GetBusoffError( UNUM16 au16_ECanModuleSN )
{
	UNUM16 lu16_ErrorFlag = (UNUM16)FALSE;

	if( (UNUM16)(ECAN_mp_Regs[au16_ECanModuleSN]->CANES.bit.BO) == (UNUM16)0 )
	{
	    lu16_ErrorFlag = (UNUM16)FALSE;
	}
    else
    {
        lu16_ErrorFlag = (UNUM16)TRUE;
    }

    return lu16_ErrorFlag;
}


UNUM16 ECAN_CheckRegister( UNUM16 au16_ECanModuleSN )
{
	UNUM16 lu16_error = (UNUM16)TRUE;
	if( (UNUM16)(ECAN_mp_Regs[au16_ECanModuleSN]->CANBTC.bit.BRPREG) == (UNUM16)ECAN_mu16_Register_Ref )
	{
		lu16_error = (UNUM16)FALSE;
	}
	else
	{
		lu16_error = (UNUM16)TRUE;
	}
	return lu16_error;
}

void ECAN_ResetCAN( UNUM16 au16_ECanModuleSN )
{
	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANGIF0.all = ECAN_mp_Regs[au16_ECanModuleSN]->CANGIF0.all;
    if ( ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANGIF0.bit.BOIF0 )
    {
    	ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANGIF0.bit.BOIF0 = (UNUM16)BIT_SET;
    	ECAN_mp_Regs[au16_ECanModuleSN]->CANGIF0.all = ECAN_ms_Regs_Shadow[au16_ECanModuleSN].CANGIF0.all;
    	ECAN_InitECan( au16_ECanModuleSN );
    }
}

/***************************************************************************
End of file.
***************************************************************************/
