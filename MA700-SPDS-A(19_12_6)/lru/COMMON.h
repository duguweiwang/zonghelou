/****************************************************************************
*                                                                           *
*                         COPYRIGHT (C)   SAE      	    					*
*                         ALL RIGHTS RESERVED                               *
*                                                                           *
*    The copying, use, distribution or disclosure of the confidential and   *
*    proprietary information contained in this document(s) is strictly      *
*    prohibited without prior written consent. Any breach shall subject     *
*    the infringing party to remedies. The owner reserves all rights in     *
*    the event of the grant of a patent or the registration of a utility    *
*    model or design.                                                       *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Module Description:  module to provide a realtime scheduler	        *
*     Module Name:         %name:     COMMON.h %                           *
*     Module Version:      %version:  5 %                                   *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Compiler:	  		                                          			*
*                                                                           *
*     Controller:                                             				*
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Author:                                  								*
*				  %created_by:        mason                                 *
*									                                        *
*     Date:       %date_modified:  2014-12-03 %                 			*
*                                                                           *
****************************************************************************/
#ifndef __COMMON_H__
#define __COMMON_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"
#include "ADC.h"
#include "ADC_cfg.h"
#include "ECAN.h"
#include "ECAN_cfg.h"
#include "GPIO.h"
#include "GPIO_cfg.h"
#include "I2C.h"
#include "I2C_cfg.h"
#include "I2T_APP.h"
#include "CAN_BUF.h"
#include "ECAN_APP.h"
#include "WDG.h"
#include "WDG_cfg.h"
#include "SPI.h"
#include "SCI.h"
#include "TLV5638.h"
#include "I2T_APP.h"
#include "GPIO_APP.h"

extern UNUM32 gu32_GPIO_PORTA_OUT_MASK;
extern UNUM32 gu32_GPIO_PORTB_OUT_MASK;
extern UNUM32 gu32_GPIO_PORTC_OUT_MASK;
extern UNUM32 gu32_GPIO_PORTA_IN_MASK;
extern UNUM32 gu32_GPIO_PORTB_IN_MASK;
extern UNUM32 gu32_GPIO_PORTC_IN_MASK;


extern UNUM16 I2T_ADC_Value[20];
extern UNUM16 ADC_START_FLAG;
extern UNUM16 ADC_FINISHED_FLAG;
extern UNUM32 MCU_GetTMR0_5ms(void);
extern UNUM16 MCU_GetStatus_5ms(void);
extern void MCU_ClearStatus_5ms(void);

#endif
/***************************************************************************
End of file.
***************************************************************************/
