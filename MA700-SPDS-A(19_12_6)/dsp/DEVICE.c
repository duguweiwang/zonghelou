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
*     Module Name:         %name:     DEVICE.c %                                 *
*     Module Version:      %version:  2 %                                    *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	 	                                                          *
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
#include "DEVICE.h"
#include "DEVICE_cfg.h"

/**** definitions*************************************************************/
#pragma DATA_SECTION(DevEmuRegs,"DevEmuRegsFile");
volatile struct DEV_EMU_REGS DevEmuRegs;

#pragma DATA_SECTION(PartIdRegs,"PartIdRegsFile");
volatile struct PARTID_REGS PartIdRegs;

/***************************************************************************
End of file.
***************************************************************************/
