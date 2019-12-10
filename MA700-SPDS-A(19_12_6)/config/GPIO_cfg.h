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
*     Module Name:         %name:     GPIO_cfg.h %                            *
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

#ifndef __GPIO_CFG_H__
#define __GPIO_CFG_H__

/**** includes ***************************************************************/
#include "DEVICE.h"

/**** definitions*************************************************************/
/****** GPIO Used Macros Definitions *****************************************/
#define GPIO_PORTA_SN	0
#define GPIO_PORTB_SN	1
#define GPIO_PORTC_SN	2

#define GPIO_SET_BIT 	1
#define GPIO_CLEAR_BIT	2
/* #define GPIO_TOGGLE_BIT	3 */

#define GPIO_DIR_OUTPUT	1
#define GPIO_DIR_INPUT	0

#define GPIO_SELECT_ZERO	((UNUM32)0)
#define GPIO_SELECT_ONE		((UNUM32)1)
#define GPIO_SELECT_TWO		((UNUM32)2)
#define GPIO_SELECT_THREE	((UNUM32)3)

#define GPIO_PULLUP_ENABLE	0
#define GPIO_PULLUP_UNABLE	1

/* IO MASK for detecting the status of switch*/
#define GPIO_DPB   0x000C0000  /* GPIO19-18 for Dimming Push Button*/
#define GPIO_LTSW  0x00F00000  /* GPIO25-24 for Lamp Toggle Switch*/
#define GPIO_SPBA  0x03000000  /* GPIO23-20 for STORM PBA*/
/*(5个引脚确定的硬件地址)SSPC_ID:00010,00100,00111,01000,01011,01101,01110,10000,10011,10101,10110,11001,11010,11100*/
#define SSPC_ID1  2
#define SSPC_ID2  4
#define SSPC_ID3  7
#define SSPC_ID4  8
#define SSPC_ID5  11
#define SSPC_ID6  13
#define SSPC_ID7  14
#define SSPC_ID8  16
#define SSPC_ID9  19
#define SSPC_ID10  21
#define SSPC_ID11  22
#define SSPC_ID12  25
#define SSPC_ID13  26
#define SSPC_ID14  28

/**** functions declarations *************************************************/
/* Operation GPIO Individually */
extern void GPIO_InitGPIOSingle( SNUM16 as16_SerialNumber,
		                         UNUM16 au16_DIRSelect,
								 UNUM32 au32_SyncSysClkSelect,
								 UNUM16 au16_PullUpSelect );

extern UNUM16 GPIO_ReadGPIOSingle( SNUM16 as16_SerialNumber );

extern void GPIO_SetGPIOSingle( SNUM16 as16_SerialNumber );

extern void GPIO_ClearGPIOSingle( SNUM16 as16_SerialNumber );

extern void GPIO_ToggleGPIOSingle( SNUM16 as16_SerialNumber );

/* Operation GPIO Grouping */
extern void GPIO_InitGPIOPort( UNUM16 au16_PortSN,
		                       const UNUM32 au32_PortRegPara[7] );

extern UNUM32 GPIO_ReadGPIOPort( UNUM16 au16_PortSN );

extern UNUM32 GPIO_ReadSSPC_ID(void);/*lirunqing!!!!!!!!!!!!!!!!!!!!!!!*/

extern void GPIO_SetGPIOPort ( UNUM16 au16_PortSN,
		                       UNUM32 au32_SetValue );

extern void GPIO_ClearGPIOPort( UNUM16 au16_PortSN,
		                        UNUM32 au32_ClearValue );

extern void GPIO_ToggleGPIOPort( UNUM16 au16_PortSN,
		                         UNUM32 au32_ToggleValue );

extern void GPIO_HandleSingleGPIO( UNUM16 au16_PortSN,
		                           UNUM16 au16_GPIOAction,
		                           UNUM32 au32_GPIOSerialNumberInPORT );

extern void GPIO_WriteGPIOPort( UNUM16 au16_PortSN,
		                        UNUM32 au32_WriteData );

extern void GPIO_Init(void);
extern void GPIO_ChannelTurnOn( UNUM16 au16_ChannelSN);
extern void GPIO_ChannelTurnOff( UNUM16 au16_ChannelSN);
extern UNUM32 GPIO_GetChannelStatus( UNUM16 au16_ChannelSN);
extern void GPIO_ChannelType(UNUM16 au16_ChannelType);


UNUM16 GPIOGet_LRU_ID( UNUM16 *pu16_LRU_ID );

#endif

/***************************************************************************
End of file.
***************************************************************************/
