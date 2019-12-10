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
*     Module Description:  I2T 	algorithm           *
*     Module Name:         %name:     I2T.h %                                *
*     Module Version:      %version:  0 %                                 *
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
*				  %created_by:   yufangcheng %                                      *
*									                                          *
*     Date:       %date_modified:  Wed July  4 14:57:59 2015 %                 *
*                                                                             *
******************************************************************************/


#ifndef __I2T_APP__
#define __I2T_APP__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"

#define I2T_ERROR	0xF555U	/*	error*/
#define I2T_VMAX	2490U		/*	ADC MAX 2.49V*/
#define I2T_VREF	7324U		/*	ADC REF 3.000V 3000*10000/4096*/

#define I2T_STS_ERROR		0U	/*	I2T SCAN error*/
#define I2T_STS_NORMAL		1U	/*	Working Normal*/
#define I2T_STS_PROTECTCAL	2U	/*	Working Overload & Protect Calculating */
#define I2T_STS_TRIGGER		3U/*	Protect Trigger*/
#define I2T_START_VALUE		119U	/*	I2T Start Calculating value*/
#define I2T_MAX_VALUE		900U/*	When I2T_Y > 800% Protect Trigger immediately*/
#define I2T_DECAY_T			400U	/*	I2T Decay value*/
#define I2T_HEAT_TRIGGER	1000000U	/*	I2T Calculate Trigger value*/
#define I2T_HEAT_BALANCE	330000U	/*	I2T Calculate Trigger value*/
#define I2T_STOP_DECAY		33U	/*	Protect Trigger*/


struct I2T_Structure
{
	UNUM16 Period;
	UNUM16 AcumCoef;
	UNUM32 Times;
	UNUM32 Current;
	UNUM32 CurHeat;
};


extern struct I2T_Structure I2T_Control[20];

/**** functions declarations *************************************************/
extern void I2T_APP_Init(void);
extern void I2T_APP_Process(void);
extern UNUM16 I2T_APP_GetRateCurrent(UNUM16 channelSN);
extern UNUM32 I2T_APP_GetCurrent(UNUM16 channelSN);
extern void I2T_APP_I2tClear(UNUM16 channel);
extern void I2T_APP_SetType(UNUM16 lu16_BoardID);
extern void I2T_APP_SmoothReset(void);
extern void I2T_APP_Short(UNUM16 channel);
extern void I2T_APP_ChannelStatus(UNUM16 channel);

#endif  /* end of I2T_H definition*/

/*===========================================================================*/
/* End of file. */
/*===========================================================================*/
