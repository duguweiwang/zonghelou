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
*     Module Description:  module to provide a real time scheduler	          *
*     Module Name:         %name:     ECAN_cfg.h %                            *
*     Module Version:      %version:  3 %                                     *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	  		                                          			  *
*                                                                             *
*     Controller:                                             				  *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                  								  *
*				  %created_by:   maolei %                                     *
*									                                          *
*     Date:       %date_modified:  2013-10-14 %                 			  *
*                                                                             *
******************************************************************************/

#ifndef __ECAN_CFG_H__
#define __ECAN_CFG_H__
/**** own include *************************************************************/
/**** external includes *******************************************************/
#include "DEVICE.h"
#include "CAN_BUF.h"

/****** ECAN Module Used Macros Definitions ***********************************/
#define DSP28_ECANA  1U
#define DSP28_ECANB  0U

/* Two ECAN Module SN */
#define	ECAN_ECANA_SN 0U /* Select eCAN module A */
#define	ECAN_ECANB_SN 1U	/* Select eCAN module B */
/* ECAN Module Pins Function Selected */
                              /* for GPASEL Register		for GPAMUX Register 	for GPAPUD register	*/
#define	ECAN_GPIO_SET_ZERO	0U /* Sync System Clock		Peripheral Func One 	Enable internal pull up	*/
#define	ECAN_GPIO_SET_ONE	1U /* Sample Period Three		Peripheral Func Two     Disable internal pull up */
#define	ECAN_GPIO_SET_TWO	2U /* Sample Period Six		Peripheral Func Three */
#define	ECAN_GPIO_SET_THREE	3U /* Non Sync					Peripheral Func Four */
/* ECAN Module Pins Selected */
#define	ECAN_ECANA_PINSSELONE	0U
#define	ECAN_ECANA_PINSSELTWO	1U
#define	ECAN_ECANB_PINSSELONE	0U
#define	ECAN_ECANB_PINSSELTWO	1U
#define	ECAN_ECANB_PINSSELTHREE	0U
#define	ECAN_ECANB_PINSSELFOUR	0U
/* ECAN Module Baud Rate Selected */
#define ECAN_CAN_BAUDRATE_50KBPS	0U
#define ECAN_CAN_BAUDRATE_100KBPS	0U
#define ECAN_CAN_BAUDRATE_125KBPS	0U
#define ECAN_CAN_BAUDRATE_250KBPS	0U
#define ECAN_CAN_BAUDRATE_500KBPS	1U
#define ECAN_CAN_BAUDRATE_1000KBPS	0U
/* ECAN Module Sample Point Selected */
                                      /* SysClk=150MHz,BT=15;		SysClk=100MHz,BT=10; */
#define ECAN_CAN_SAMPLEPOINTONE 	1 /*		80%						85%				 */
#define ECAN_CAN_SAMPLEPOINTTWO 	0 /*		73%						80%				 */
#define ECAN_CAN_SAMPLEPOINTTHREE 	0 /*		66%						75%				 */
#define ECAN_CAN_SAMPLEPOINTFOUR 	0 /*		60%						70%				 */
#define ECAN_CAN_SAMPLEPOINTFIVE 	0 /*		 -						65%				 */
#define ECAN_CAN_SAMPLEPOINTSIX 	0 /*		 -						60%				 */

#define ECAN_CAN_SJWVALUE	1 /* this value will be 0 thru 3 */

#define ECAN_MBOX_NUM	32U

/* Self-test */
/* the default ID for Mailbox #0, other mailbox id is decreased*/
#define ECAN_MBOX_DEF_ID		  0x9FFFFFFFU /* the MSB is 1, means extend frame */
#define ECAN_DEF_SEND_DATA_HIGH	  0xAA55AA55U /* the self test data, it is a constant */
#define ECAN_DEF_SEND_DATA_LOW	  0x9FFFFFFFU /* the self test data, it is the same as frame ID */
#define ECAN_SELF_TEST_MAX_NUM	  10U /* the max number for self test */
#define ECAN_MAX_WAIT_COUNTER	  1000U

/**** user data type declarations **************************************************/
struct ECAN_Msg
{
	UNUM32 ECAN_mu32_Msg_ID;
	UNUM16 ECAN_mu16_Msg_Data_Length;
	UNUM32 ECAN_mu32_Msg_Data_High;
	UNUM32 ECAN_mu32_Msg_Data_Low;
};
/**** user functions declarations **************************************************/
void ECAN_InitECan( UNUM16 au16_ECanModuleSN );

void ECAN_InitModule( void );

void ECAN_InitECanGPIO( void );

void ECAN_ConfigSendMsgBox( UNUM16 au16_ECanModuleSN,
                            UNUM32 au32_ECanMailbox_SN,
                            UNUM32 au32_MsgID,
                            SNUM16 as16_SendPriority,
                            SNUM16 as16_DataLength );

void ECAN_ConfigRecMsgBox( UNUM16 au16_ECanModuleSN,
                           UNUM32 au32_ECanMailbox_SN,
                           UNUM32 au32_MsgID,
                           UNUM32 au32_MsgIDMask,
                           SNUM16 as16_DataLength );

void ECAN_SendMsg( UNUM16 au16_ECanModuleSN,
                   UNUM32 au32_ECanMailbox_SN,
                   UNUM32 au32_MsgHighBytes,
                   UNUM32 au32_MsgLowBytes );

UNUM16 ECAN_RecMsgAll( UNUM16 au16_ECanModuleSN );

UNUM32 ECAN_SelfTest( UNUM16 au16_ECanModuleSN );

void ECAN_EnterNormalMode( UNUM16 au16_ECanModuleSN );

void ECAN_ResetCAN( UNUM16 au16_ECanModuleSN);

extern UNUM16 ECAN_GetBusoffError( UNUM16 au16_ECanModuleSN );
extern UNUM16 ECAN_CheckRegister( UNUM16 au16_ECanModuleSN );
#endif

/***************************************************************************
End of file.
***************************************************************************/
