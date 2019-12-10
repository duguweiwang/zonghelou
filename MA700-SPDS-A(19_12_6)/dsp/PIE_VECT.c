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
*     Module Description:  	                                                  *
*     Module Name:         %name:     PIE_VECT.c %                            *
*     Module Version:      %version:  2 %                                 *
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
*				  %created_by:   maolei %                                      *
*									                                          *
*     Date:       %date_modified:  Wed Apr  4 14:57:59 2012 %                 *
*                                                                             *
******************************************************************************/

/**** includes ***************************************************************/
#include "PIE_VECT.h"
#include "PIE_VECT_cfg.h"
#include "DEFAULT_ISR.h"
#include "PIE_CTRL.h"

/**** definitions*************************************************************/
#pragma DATA_SECTION(PIE_VECT_PieVectTable,"PieVectTableFile");
struct PIE_VECT_TABLE PIE_VECT_PieVectTable;

/**** definitions*************************************************************/
struct PIE_VECT_TABLE PieVectTableInit = { /*const*/

      &PIE_RESERVED, /* 0  Reserved space*/
      &PIE_RESERVED, /* 1  Reserved space*/
      &PIE_RESERVED, /* 2  Reserved space*/
      &PIE_RESERVED, /* 3  Reserved space*/
      &PIE_RESERVED, /* 4  Reserved space*/
      &PIE_RESERVED, /* 5  Reserved space*/
      &PIE_RESERVED, /* 6  Reserved space*/
      &PIE_RESERVED, /* 7  Reserved space*/
      &PIE_RESERVED, /* 8  Reserved space*/
      &PIE_RESERVED, /* 9  Reserved space*/
      &PIE_RESERVED, /* 10 Reserved space*/
      &PIE_RESERVED, /* 11 Reserved space*/
      &PIE_RESERVED, /* 12 Reserved space*/

/* Non-Peripheral Interrupts*/
      &rsvd_ISR, /*XINT13 or CPU-Timer 1*/
      &rsvd_ISR, /*CPU-Timer2*/
      &rsvd_ISR, /*Datalogging interrupt*/
      &rsvd_ISR, /*RTOS interrupt*/
      &rsvd_ISR, /*Emulation interrupt*/
      &rsvd_ISR, /*Non-maskable interrupt*/
      &rsvd_ISR, /*Illegal operation TRAP*/
      &rsvd_ISR, /*User Defined trap 1*/
      &rsvd_ISR, /*User Defined trap 2*/
      &rsvd_ISR, /*User Defined trap 3*/
      &rsvd_ISR, /*User Defined trap 4*/
      &rsvd_ISR, /*User Defined trap 5*/
      &rsvd_ISR, /*User Defined trap 6*/
      &rsvd_ISR, /*User Defined trap 7*/
      &rsvd_ISR, /*User Defined trap 8*/
      &rsvd_ISR, /*User Defined trap 9*/
      &rsvd_ISR, /*User Defined trap 10*/
      &rsvd_ISR, /*User Defined trap 11*/
      &rsvd_ISR, /*User Defined trap 12*/

/* Group 1 PIE Vectors*/
      &rsvd_ISR, /* 1.1 ADC*/
      &rsvd_ISR, /* 1.2 ADC*/
      &rsvd_ISR, /* 1.3*/
      &rsvd_ISR, /* 1.4*/
      &rsvd_ISR, /* 1.5*/
      &ADCINT_ISR, /* 1.6 ADC*/
      &TINT0_ISR, /* 1.7 Timer 0*/
      &WAKEINT_ISR, /* 1.8 WD, Low Power*/

/* Group 2 PIE Vectors*/
      &EPWM1_TZINT_ISR, /* 2.1 EPWM-1 Trip Zone*/
      &EPWM2_TZINT_ISR, /* 2.2 EPWM-2 Trip Zone*/
      &EPWM3_TZINT_ISR, /* 2.3 EPWM-3 Trip Zone*/
      &EPWM4_TZINT_ISR, /* 2.4 EPWM-4 Trip Zone*/
      &EPWM5_TZINT_ISR, /* 2.5 EPWM-5 Trip Zone*/
      &EPWM6_TZINT_ISR, /* 2.6 EPWM-6 Trip Zone*/
      &rsvd_ISR, /* 2.7*/
      &rsvd_ISR, /* 2.8*/

/* Group 3 PIE Vectors*/
      &EPWM1_INT_ISR, /* 3.1 EPWM-1 Interrupt*/
      &EPWM2_INT_ISR, /* 3.2 EPWM-2 Interrupt*/
      &EPWM3_INT_ISR, /* 3.3 EPWM-3 Interrupt*/
      &EPWM4_INT_ISR, /* 3.4 EPWM-4 Interrupt*/
      &EPWM5_INT_ISR, /* 3.5 EPWM-5 Interrupt*/
      &EPWM6_INT_ISR, /* 3.6 EPWM-6 Interrupt*/
      &rsvd_ISR, /* 3.7*/
      &rsvd_ISR, /* 3.8*/

/* Group 4 PIE Vectors*/
      &ECAP1_INT_ISR, /* 4.1 ECAP-1*/
      &ECAP2_INT_ISR, /* 4.2 ECAP-2*/
      &ECAP3_INT_ISR, /* 4.3 ECAP-3*/
      &ECAP4_INT_ISR, /* 4.4 ECAP-4*/
      &ECAP5_INT_ISR, /* 4.5 ECAP-5*/
      &ECAP6_INT_ISR, /* 4.6 ECAP-6*/
      &rsvd_ISR, /* 4.7*/
      &rsvd_ISR, /* 4.8*/

/* Group 5 PIE Vectors*/
      &rsvd_ISR, /* 5.1 EQEP-1*/
      &rsvd_ISR, /* 5.2 EQEP-2*/
      &rsvd_ISR, /* 5.3*/
      &rsvd_ISR, /* 5.4*/
      &rsvd_ISR, /* 5.5*/
      &rsvd_ISR, /* 5.6*/
      &rsvd_ISR, /* 5.7*/
      &rsvd_ISR, /* 5.8*/

/* Group 6 PIE Vectors*/
      &SPIRXINTA_ISR, /* 6.1 SPI-A*/
      &SPITXINTA_ISR, /* 6.2 SPI-A*/
      &rsvd_ISR, /* 6.3 McBSP-A*/
      &rsvd_ISR, /* 6.4 McBSP-A*/
      &rsvd_ISR, /* 6.5 McBSP-B*/
      &rsvd_ISR, /* 6.6 McBSP-B*/
      &rsvd_ISR, /* 6.7*/
      &rsvd_ISR, /* 6.8*/

/* Group 7 PIE Vectors*/
      &rsvd_ISR, /* 7.1  DMA channel 1*/
      &rsvd_ISR, /* 7.2  DMA channel 2*/
      &rsvd_ISR, /* 7.3  DMA channel 3*/
      &rsvd_ISR, /* 7.4  DMA channel 4*/
      &rsvd_ISR, /* 7.5  DMA channel 5*/
      &rsvd_ISR, /* 7.6  DMA channel 6*/
      &rsvd_ISR, /* 7.7 */
      &rsvd_ISR, /* 7.8 */

/* Group 8 PIE Vectors*/
      &I2CINT1A_ISR, /* 8.1  I2C*/
      &I2CINT2A_ISR, /* 8.2  I2C*/
      &rsvd_ISR, /* 8.3*/
      &rsvd_ISR, /* 8.4*/
      &SCIRXINTC_ISR, /* 8.5  SCI-C*/
      &SCITXINTC_ISR, /* 8.6  SCI-C*/
      &rsvd_ISR, /* 8.7*/
      &rsvd_ISR, /* 8.8*/

/* Group 9 PIE Vectors*/
      &SCIRXINTA_ISR, /* 9.1 SCI-A*/
      &SCITXINTA_ISR, /* 9.2 SCI-A*/
      &SCIRXINTB_ISR, /* 9.3 SCI-B*/
      &SCITXINTB_ISR, /* 9.4 SCI-B*/
      &ECAN0INTA_ISR, /* 9.5 eCAN-A*/
      &ECAN1INTA_ISR, /* 9.6 eCAN-A*/
      &ECAN0INTB_ISR, /* 9.7 eCAN-B*/
      &ECAN1INTB_ISR, /* 9.8 eCAN-B*/

/* Group 10 PIE Vectors*/
      &rsvd_ISR, /* 10.1*/
      &rsvd_ISR, /* 10.2*/
      &rsvd_ISR, /* 10.3*/
      &rsvd_ISR, /* 10.4*/
      &rsvd_ISR, /* 10.5*/
      &rsvd_ISR, /* 10.6*/
      &rsvd_ISR, /* 10.7*/
      &rsvd_ISR, /* 10.8*/

/* Group 11 PIE Vectors*/
      &rsvd_ISR, /* 11.1*/
      &rsvd_ISR, /* 11.2*/
      &rsvd_ISR, /* 11.3*/
      &rsvd_ISR, /* 11.4*/
      &rsvd_ISR, /* 11.5*/
      &rsvd_ISR, /* 11.6*/
      &rsvd_ISR, /* 11.7*/
      &rsvd_ISR, /* 11.8*/

/* Group 12 PIE Vectors*/
      &rsvd_ISR, /* 12.1*/
      &rsvd_ISR, /* 12.2*/
      &rsvd_ISR, /* 12.3*/
      &rsvd_ISR, /* 12.4*/
      &rsvd_ISR, /* 12.5*/
      &rsvd_ISR, /* 12.6*/
      &rsvd_ISR, /* 12.7*/
      &rsvd_ISR, /* 12.8*/
};
/**** functions **************************************************************/
/*******************************************************************************
---------------------------------------------------------------------------
PieVectTable_Init:
---------------------------------------------------------------------------
This function initializes the PIE vector table to a known state.
This function must be executed after boot time.
*******************************************************************************/
void PIE_VECT_Table_Init( void )
{
	SNUM16	i;
	UNUM32 *Source = (void *) &PieVectTableInit;
	UNUM32 *Dest = (void *) &PIE_VECT_PieVectTable;
		
	EALLOW;	
	for(i=(SNUM16)0; i < (SNUM16)128; i++)
	{
		*Dest = *Source;
		Dest++;
		Source++;
	}
	EDIS;

	/*Enable the PIE Vector Table*/
	PIE_CTRL_PieCtrlRegs.PIECTRL.bit.ENPIE = (UNUM16)1;
}

/***************************************************************************
End of file.
***************************************************************************/
