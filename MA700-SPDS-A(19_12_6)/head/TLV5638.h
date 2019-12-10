/******************************************************************************
*                                                                             *
*           COPYRIGHT (C)   SAE    *
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
*																																							*
*			Module Description:		module handles the dimming voltage via control		*
*														spi output signal																	*
*			Module Name:					%name:		tlv5638.h %															*
*			Module Version:				%version:	10 %													*
*																																							*
*-----------------------------------------------------------------------------*
*																																							*
*			Compiler:																													*
*																																							*
*			Controller:																										*
*																																							*
*-----------------------------------------------------------------------------*
*																																							*
*			Author:									*
*									%created_by:	wangjian %																*
*																																							*
*			Date:				%date_modified:		*
*																																							*
******************************************************************************/

#ifndef	__TLV5638_H_
#define	__TLV5638_H_

/****	includes	**************************************************************/

#include	"device.h"


/*	TLV5638 high and low definitions	*/
#define TLV5638_LOW										0
#define TLV5638_HIGH									1

/*	TLV5638 control mode	*/
#define TLV5638_SPEED_SLOW						0
#define TLV5638_SPEED_FAST						1

#define TLV5638_POWER_NORMAL					0
#define TLV5638_POWER_DOWN						1

#define TLV5638_REF_EXTERNAL					0
#define TLV5638_REF_IN1024						1						/*	output voltage range: 0~2048 mv	*/
#define TLV5638_REF_IN2048						2						/*	output voltage range: 0~4096 mv	*/

/*	TLV5638 state	*/

#define TLV5638_OK								0
#define TLV5638_ERROR_INVALID_PARAMETERS		1
#define TLV5638_ERROR_SPI_SEND_FAILED           2

/*	bit mask	*/
#define TLV5638_MASK_CONTROL_REGISTER			0xF003U

#define TLV5638_MASK_BIT_SET_CHANNEL_A			0xC000U	/*	only for FAST MODE	*/

#define TLV5638_MASK_BIT_SET_CHANNEL_B			0x4000U	/*	only for FAST MODE	*/

#define TLV5638_MASK_BIT_SET_CHANNEL_AB_A		0x1000U	/*	only for FAST MODE	*/

#define TLV5638_MASK_BIT_SET_CHANNEL_AB_B		0x8000U	/*	only for FAST MODE	*/

/*	max output voltage	*/
#define TLV5638_MAX_OUTPUT_IN1024			2048U
#define TLV5638_MAX_OUTPUT_IN2048			4096U
#define TLV5638_MAX_OUTPUT_VLOTAGE			4096U  /*TLV5638_MAX_OUTPUT_IN2048*/

/*	TLV5638 control register definitions 	*/


typedef union
{
	UNUM16				mu16_Word;
	struct
	{
		UNUM16		REF0:1;				/*	Reference voltage if internal reference selected	*/
		UNUM16		REF1:1;				/*	Reference voltage if internal reference selected	*/
		UNUM16		rsvd:10;			/*	reserved	*/
		UNUM16		R0:1;					/*	R0 and R1 are registered select bits	*/
		UNUM16		PWR:1;				/*	Power control bit:	1 -> fast mode, 0 -> slow mode */
		UNUM16		SPD:1;				/*	Speed control bit:	1 -> power down, 0 -> normal operation*/
		UNUM16		R1:1;					/*	R0 and R1 are registered select bits	*/
	}sBit;
}TLV5638_ControlRegisterT;

/*	TLV5638 settings definitions*/
typedef struct
{
	UNUM16			Speed;
	UNUM16			PowerMode;
	UNUM16			RefVoltage;
}TLV5638_SettingsT;


/****	functions declarations	************************************************/
/*	initialize	*/
extern void TLV5638_Init(void);		/*	Power on reset	*/
extern UNUM16 TLV5638_Set_Up(TLV5638_SettingsT as_TLV5638_Settings);
extern UNUM16 TLV5638_Output_Channel_A(UNUM16 au16_OutputVoltage);



#endif	/*	__TLV5638_H_	*/
