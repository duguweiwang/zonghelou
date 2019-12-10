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
*     Module Description:  configuration of the realtime scheduler            *
*     Module Name:         %name:     SCHEDULER.h %                       *
*     Module Version:      %version:  2 %                                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:                                                               *
*                                                                             * 
*     Controller:                                                             *
*                                                                             * 
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*                 %created_by:  maolei %                                       *
*                                    									      *									  
*     Datum:      %date_modified:                             			      *
*                                                                             *  
******************************************************************************/

#ifndef __SCHEDULER_CFG_H__
#define __SCHEDULER_CFG_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"
#include "GPIO.h"
#include "GPIO_cfg.h"
#include "I2C.h"
#include "I2C_cfg.h"
#include "MCU.h"
#include "MCU_cfg.h"
#include "SYS_CTRL.h"
#include "SYS_CTRL_cfg.h"
#include "WDG.h"
#include "WDG_cfg.h"
#include "ADC.h"
#include "ADC_cfg.h"
#include "ECAN.h"
#include "ECAN_cfg.h"
#include "EEPROM.h"
#include "EEPROM_cfg.h"
#include "PIE_CTRL.h"
#include "PIE_CTRL_cfg.h"
#include "PIE_VECT.h"
#include "PIE_VECT_cfg.h"
#include "INIT_APP.h"
#include "ECAN_APP.h"
#include "GPIO_APP.h"
#include "CBIT_APP.h"

extern int SCHEDULER_Main(void );
extern UNUM16 lu16_BoardType;

#endif

/***************************************************************************
End of file.
***************************************************************************/
