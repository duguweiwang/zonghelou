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
*     Module Name:         %name:     SYS_CTRL_cfg.h %                            *
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

#ifndef __SYS_CTRL_CFG_H__
#define __SYS_CTRL_CFG_H__

/**** includes ***************************************************************/
#include "DEVICE.h"

/**** functions declarations *************************************************/

/*                 CAUTION
This function MUST be executed out of RAM. Executing it
out of OTP/Flash will yield unpredictable results
*/
void SYS_Ctrl_Flash_Init( void );

void SYS_Ctrl_PeripheralClocks_Init( void );

void SYS_Ctrl_InitPll( UNUM16 val, UNUM16 divsel );

UNUM16 SYS_Ctrl_CsmUnlock( void );

#endif

/***************************************************************************
End of file.
***************************************************************************/
