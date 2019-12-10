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
*     Module Name:         %name:     WDG.c %                                 *
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
#include "WDG.h"
#include "WDG_cfg.h"
#include "SYS_CTRL.h"
#include "XINTF.h"

/**** definitions*************************************************************/
#pragma DATA_SECTION(XintfRegs,"XintfRegsFile");
volatile struct XINTF_REGS XintfRegs;

/**** functions **************************************************************/
void WDG_InitInterruptMode( void )
{
	EALLOW;
	SYS_SysCtrlRegs.SCSR = (UNUM16)WDG_INTERRUPT_MODE; /*watchdog Interrupt Mode*/
	EDIS;

	EALLOW;
	SYS_SysCtrlRegs.WDCR = (UNUM16)WDG_CONTROL;
	EDIS;
}

void WDG_InitResetMode( void )
{
	EALLOW;
	SYS_SysCtrlRegs.SCSR = (UNUM16)WDG_RESET_MODE; /*watchdog Reset Mode*/
	EDIS;

	EALLOW;
	SYS_SysCtrlRegs.WDCR = (UNUM16)WDG_CONTROL;
	EDIS;
}

/*-------------------------------------------------------------------------
Example: ServiceDog:
---------------------------------------------------------------------------
This function resets the watchdog timer.
Enable this function for using ServiceDog in the application
---------------------------------------------------------------------------*/
void WDG_ServiceDog( void )
{
    EALLOW;
    SYS_SysCtrlRegs.WDKEY = (UNUM16)WDG_SERVICE_KEY1;
    SYS_SysCtrlRegs.WDKEY = (UNUM16)WDG_SERVICE_KEY2;
    EDIS;
}


void WDG_ResetSys( void )
{
    EALLOW;
    SYS_SysCtrlRegs.WDKEY = (UNUM16)0;
    SYS_SysCtrlRegs.WDKEY = (UNUM16)WDG_SERVICE_KEY2;
    EDIS;
}
/*-------------------------------------------------------------------------
Example: DisableDog:
---------------------------------------------------------------------------
This function disables the watchdog timer.
---------------------------------------------------------------------------*/
void WDG_DisableDog( void )
{
    EALLOW;
    SYS_SysCtrlRegs.WDCR= (UNUM16)WDG_DISABLE;
    EDIS;
}

/***************************************************************************
End of file.
***************************************************************************/
