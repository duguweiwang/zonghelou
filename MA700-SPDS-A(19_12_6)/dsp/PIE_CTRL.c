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
*     Module Name:         %name:     PIE_CTRL.c %                            *
*     Module Version:      %version:  2 %                                     *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	  	                                                          *
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
#include "PIE_CTRL.h"
#include "PIE_CTRL_cfg.h"
#include "DEVICE.h"     /* DSP2833x Headerfile Include File*/
#include "DEVICE_cfg.h"

/**** definitions*************************************************************/
#pragma DATA_SECTION(PIE_CTRL_PieCtrlRegs,"PieCtrlRegsFile");
volatile struct PIE_CTRL_REGS PIE_CTRL_PieCtrlRegs;

/**** functions **************************************************************/
/****-------------------------------------------------------------------------
PieCtrl_Init:
------------------------------------------------------------------------------
This function initializes the PIE control registers to a known state.
******************************************************************************/
void PIE_CTRL_Init( void )
{
    /* Disable Interrupts at the CPU level: */
    DINT;

    /* Disable the PIE */
    PIE_CTRL_PieCtrlRegs.PIECTRL.bit.ENPIE = (UNUM16)0;

	/* Clear all PIEIER registers: */
    PIE_CTRL_PieCtrlRegs.PIEIER1.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER2.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER3.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER4.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER5.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER6.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER7.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER8.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER9.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER10.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER11.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIER12.all = (UNUM16)0;

	/* Clear all PIEIFR registers: */
    PIE_CTRL_PieCtrlRegs.PIEIFR1.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR2.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR3.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR4.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR5.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR6.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR7.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR8.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR9.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR10.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR11.all = (UNUM16)0;
    PIE_CTRL_PieCtrlRegs.PIEIFR12.all = (UNUM16)0;

    /* Enable the PIE */
    PIE_CTRL_PieCtrlRegs.PIECTRL.bit.ENPIE = (UNUM16)1;
    		
	/* Enables PIE to drive a pulse into the CPU */
    PIE_CTRL_PieCtrlRegs.PIEACK.all = (UNUM16)0xFFFFU;
}	

/***************************************************************************
End of file.
***************************************************************************/
