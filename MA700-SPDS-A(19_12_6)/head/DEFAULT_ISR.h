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
*     Module Description:  module to provide a realtime scheduler             *
*     Module Name:         %name:     DEFAULT_ISR.h %                         *
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
*                 %created_by:   maolei %                                      *
*                                    									      *									  
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 % 			      *
*                                                                             *  
******************************************************************************/
#ifndef __DEFAULT_ISR_H__
#define __DEFAULT_ISR_H__

/**** functions declarations *************************************************/
/******************************************************************************
Default Interrupt Service Routine Declarations:
The following function prototypes are for the
default ISR routines used with the default PIE vector table.
This default vector table is found in the DSP2833x_PieVect.h
file.
******************************************************************************/
/* Group 1 PIE Interrupt Service Routines:*/

interrupt void  ADCINT_ISR( void ); /* ADC*/

interrupt void  TINT0_ISR( void ); /* Timer 0*/

interrupt void  WAKEINT_ISR( void ); /* WD*/

/* Group 2 PIE Interrupt Service Routines:*/
interrupt void EPWM1_TZINT_ISR( void ); /* EPWM-1*/

interrupt void EPWM2_TZINT_ISR( void ); /* EPWM-2*/

interrupt void EPWM3_TZINT_ISR( void ); /* EPWM-3*/

interrupt void EPWM4_TZINT_ISR( void ); /* EPWM-4*/

interrupt void EPWM5_TZINT_ISR( void ); /* EPWM-5*/

interrupt void EPWM6_TZINT_ISR( void ); /* EPWM-6*/
      
/* Group 3 PIE Interrupt Service Routines:*/
interrupt void EPWM1_INT_ISR( void ); /* EPWM-1*/

interrupt void EPWM2_INT_ISR( void ); /* EPWM-2*/

interrupt void EPWM3_INT_ISR( void ); /* EPWM-3*/

interrupt void EPWM4_INT_ISR( void ); /* EPWM-4*/

interrupt void EPWM5_INT_ISR( void ); /* EPWM-5*/

interrupt void EPWM6_INT_ISR( void ); /* EPWM-6*/
      
/* Group 4 PIE Interrupt Service Routines:*/
interrupt void ECAP1_INT_ISR( void ); /* ECAP-1*/

interrupt void ECAP2_INT_ISR( void ); /* ECAP-2*/

interrupt void ECAP3_INT_ISR( void ); /* ECAP-3*/

interrupt void ECAP4_INT_ISR( void ); /* ECAP-4*/

interrupt void ECAP5_INT_ISR( void ); /* ECAP-5*/

interrupt void ECAP6_INT_ISR( void ); /* ECAP-6*/

/* Group 6 PIE Interrupt Service Routines:*/
interrupt void SPIRXINTA_ISR( void ); /* SPI-A*/

interrupt void SPITXINTA_ISR( void ); /* SPI-A*/

/* Group 8 PIE Interrupt Service Routines: */
interrupt void I2CINT1A_ISR( void ); /* I2C-A*/

interrupt void I2CINT2A_ISR( void ); /* I2C-A*/

interrupt void SCIRXINTC_ISR( void ); /* SCI-C*/

interrupt void SCITXINTC_ISR( void ); /* SCI-C*/
   
/* Group 9 PIE Interrupt Service Routines:*/
interrupt void SCIRXINTA_ISR( void ); /* SCI-A*/

interrupt void SCITXINTA_ISR( void ); /* SCI-A*/

interrupt void SCIRXINTB_ISR( void ); /* SCI-B*/

interrupt void SCITXINTB_ISR( void ); /* SCI-B*/

interrupt void ECAN0INTA_ISR( void ); /* eCAN-A*/

interrupt void ECAN1INTA_ISR( void ); /* eCAN-A*/

interrupt void ECAN0INTB_ISR( void ); /* eCAN-B*/

interrupt void ECAN1INTB_ISR( void ); /* eCAN-B*/

/* Group 10 PIE Interrupt Service Routines:*/
 
/* Group 11 PIE Interrupt Service Routines:*/

/* Group 12 PIE Interrupt Service Routines:*/

/* Catch-all for Reserved Locations For testing purposes:*/
interrupt void PIE_RESERVED( void ); /* Reserved for test*/

interrupt void rsvd_ISR( void ); /* for test*/

interrupt void INT_NOTUSED_ISR( void ); /* for unused interrupts*/

interrupt void XINT1_ISR( void );

interrupt void XINT2_ISR( void );

interrupt void XINT3_ISR( void );

interrupt void XINT4_ISR( void );

interrupt void XINT5_ISR( void );

interrupt void XINT6_ISR( void );

interrupt void XINT7_ISR( void );

#endif /*end of _DEFAULT_ISR_H definition*/

/***************************************************************************
End of file.
***************************************************************************/
