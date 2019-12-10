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
*     Module Name:         %name:     WDG_cfg.h %                            *
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
*                 %created_by:   maolei %                                     *
*                                    									      *									  
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 % 			      *
*                                                                             *  
******************************************************************************/
#ifndef __WDG_CFG_H__
#define __WDG_CFG_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"

/**** definitions*************************************************************/
#define WDG_RESET_MODE            4
#define WDG_INTERRUPT_MODE        2
#define WDG_CONTROL               0x002F
#define WDG_SERVICE_KEY1          0x0055
#define WDG_SERVICE_KEY2          0x00AA
#define WDG_DISABLE               0x0068
/**** functions declarations *************************************************/
void WDG_DisableDog( void );

void WDG_ServiceDog( void );

void WDG_ResetSys( void );

void WDG_InitResetMode( void );

void WDG_InitInterruptMode( void );

#endif

/***************************************************************************
End of file.
***************************************************************************/
