/******************************************************************************
*                                                                             *
*                         COPYRIGHT (C)   SAE		                          *
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
*     Module Name:         %name:     DEFAULT_ISR.c %                         *
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
*     Date:       %date_modified:  Wed Apr  4 14:57:59 2012 %                 *
*                                                                             *
******************************************************************************/

/**** includes ***************************************************************/
#include "DEVICE.h" /*DSP2833x Headerfile Include File*/
#include "DEVICE_cfg.h"
#include "DEFAULT_ISR.h"
/*#include "DSP2833x_Examples.h"*/ /*DSP2833x Examples Include File*/

/**** functions **************************************************************/
/*INT1.3 - Reserved*/

/*INT1.4*/
interrupt void  XINT1_ISR( void )
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT1.5*/
interrupt void  XINT2_ISR( void )
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT1.6*/
interrupt void  ADCINT_ISR( void ) /*ADC*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT1.7*/
/*interrupt void  TINT0_ISR(void) // CPU-Timer 0
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
}*/

/*INT1.8*/
interrupt void  WAKEINT_ISR( void ) /*WD, LOW Power*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*-----------------------------------------------------------
PIE Group 2 - MUXed into CPU INT2
-----------------------------------------------------------*/
/*INT2.1*/
interrupt void EPWM1_TZINT_ISR( void ) /*EPWM-1*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT2.2*/
interrupt void EPWM2_TZINT_ISR( void ) /*EPWM-2*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT2.3*/
interrupt void EPWM3_TZINT_ISR( void ) /*EPWM-3*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT2.4*/
interrupt void EPWM4_TZINT_ISR( void ) /*EPWM-4*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT2.5*/
interrupt void EPWM5_TZINT_ISR( void ) /*EPWM-5*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT2.6*/
interrupt void EPWM6_TZINT_ISR( void ) /*EPWM-6*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT2.7 - Reserved*/
/*INT2.8 - Reserved*/

/*-----------------------------------------------------------
PIE Group 3 - MUXed into CPU INT3
-----------------------------------------------------------*/
/*INT 3.1*/
interrupt void EPWM1_INT_ISR( void ) /*EPWM-1*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT3.2*/
interrupt void EPWM2_INT_ISR( void ) /*EPWM-2*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT3.3*/
interrupt void EPWM3_INT_ISR( void ) /*EPWM-3*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT3.4*/
interrupt void EPWM4_INT_ISR( void ) /*EPWM-4*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT3.5*/
interrupt void EPWM5_INT_ISR( void ) /*EPWM-5*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT3.6*/
interrupt void EPWM6_INT_ISR( void ) /*EPWM-6*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT3.7 - Reserved*/
/*INT3.8 - Reserved*/

/*-----------------------------------------------------------
PIE Group 4 - MUXed into CPU INT4
-----------------------------------------------------------*/
/*INT 4.1*/
interrupt void ECAP1_INT_ISR( void ) /*ECAP-1*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT4.2*/
interrupt void ECAP2_INT_ISR( void ) /*ECAP-2*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT4.3*/
interrupt void ECAP3_INT_ISR( void ) /*ECAP-3*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT4.4*/
interrupt void ECAP4_INT_ISR( void ) /*ECAP-4*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT4.5*/
interrupt void ECAP5_INT_ISR( void ) /*ECAP-5*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT4.6*/
interrupt void ECAP6_INT_ISR( void ) /*ECAP-6*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT5.3 - Reserved*/
/*INT5.4 - Reserved*/
/*INT5.5 - Reserved*/
/*INT5.6 - Reserved*/
/*INT5.7 - Reserved*/
/*INT5.8 - Reserved*/

/*-----------------------------------------------------------
PIE Group 6 - MUXed into CPU INT6
-----------------------------------------------------------*/
/*INT6.1*/
interrupt void SPIRXINTA_ISR( void ) /*SPI-A*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
   /*for(;;);*/
}

/*INT6.2*/
interrupt void SPITXINTA_ISR( void ) /*SPI-A*/
{
  /* Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
   /*for(;;);*/
}

/* INT6.7 - Reserved*/
/* INT6.8 - Reserved*/

/* INT7.7 - Reserved*/
/* INT7.8 - Reserved*/

/*-----------------------------------------------------------
PIE Group 8 - MUXed into CPU INT8
-----------------------------------------------------------*/
/*INT8.1*/
interrupt void I2CINT1A_ISR( void ) /*I2C-A*/
{
 /*  Insert ISR Code here

  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);*/
}

/*INT8.2*/
interrupt void I2CINT2A_ISR( void ) /*I2C-A*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT8.3 - Reserved*/
/*INT8.4 - Reserved*/

/*INT8.5*/
interrupt void SCIRXINTC_ISR( void ) /*SCI-C*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT8.6*/
interrupt void SCITXINTC_ISR( void ) /*SCI-C*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT8.7 - Reserved*/
/*INT8.8 - Reserved*/


/*-----------------------------------------------------------
PIE Group 9 - MUXed into CPU INT9
-----------------------------------------------------------*/
/*INT9.1*/
interrupt void SCIRXINTA_ISR( void ) /*SCI-A*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT9.2*/
interrupt void SCITXINTA_ISR( void ) /*SCI-A*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT9.3*/
interrupt void SCIRXINTB_ISR( void ) /*SCI-B*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT9.4*/
interrupt void SCITXINTB_ISR( void ) /*SCI-B*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT9.5*/
/*
interrupt void ECAN0INTA_ISR(void)
{
  // Insert ISR Code here

  // To receive more interrupts from this PIE group, acknowledge this interrupt
  // PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
  asm ("      ESTOP0");
  for(;;);
  PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}
*/


interrupt void ECAN0INTA_ISR( void ) /*eCAN-A*/
{
	/*DINT;

	PIE_CTRL_PieCtrlRegs.PIEACK.bit.ACK9 = (UNUM16)1;

	FLG_mu16_LRU_CAN_MailboxSN = ECAN_RecMsgAll( (UNUM16)ECAN_ECANA_SN );

	EINT;*/
}

/*INT9.6*/
interrupt void ECAN1INTA_ISR( void ) /*eCAN-A*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT9.7*/
interrupt void ECAN0INTB_ISR( void ) /*eCAN-B*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT9.8*/
interrupt void ECAN1INTB_ISR( void ) /*eCAN-B*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*-----------------------------------------------------------
PIE Group 10 - MUXed into CPU INT10
-----------------------------------------------------------*/
/* INT10.1 - Reserved*/
/* INT10.2 - Reserved*/
/* INT10.3 - Reserved*/
/* INT10.4 - Reserved*/
/* INT10.5 - Reserved*/
/* INT10.6 - Reserved*/
/* INT10.7 - Reserved*/
/* INT10.8 - Reserved*/

/*-----------------------------------------------------------
PIE Group 11 - MUXed into CPU INT11
-----------------------------------------------------------*/
/* INT11.1 - Reserved*/
/* INT11.2 - Reserved*/
/* INT11.3 - Reserved*/
/* INT11.4 - Reserved*/
/* INT11.5 - Reserved*/
/* INT11.6 - Reserved*/
/* INT11.7 - Reserved*/
/* INT11.8 - Reserved*/

/*-----------------------------------------------------------
PIE Group 12 - MUXed into CPU INT12
-----------------------------------------------------------*/
/*INT12.1*/
interrupt void XINT3_ISR( void ) /*External Interrupt*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT12.2*/
interrupt void XINT4_ISR( void ) /*External Interrupt*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT12.3*/
interrupt void XINT5_ISR( void ) /* External Interrupt*/
{
  /*Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
	ESTOP0;
    /*for(;;);*/
}

/*INT12.4*/
interrupt void XINT6_ISR( void ) /*External Interrupt*/
{
  /* Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*INT12.5*/
interrupt void XINT7_ISR( void ) /* External Interrupt*/
{
  /* Insert ISR Code here
  To receive more interrupts from this PIE group, acknowledge this interrupt
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
  Next two lines for debug only to halt the processor here
  Remove after inserting ISR Code*/
  ESTOP0;
  /*for(;;);*/
}

/*---------------------------------------------------------------------------
Catch All Default ISRs:
---------------------------------------------------------------------------*/
interrupt void PIE_RESERVED( void ) /* Reserved space.  For test.*/
{
    ESTOP0;
    /*for(;;);*/
}

interrupt void rsvd_ISR( void ) /* For test*/
{
	ESTOP0;
    /*for(;;);*/
}

/***************************************************************************
End of file.
***************************************************************************/

