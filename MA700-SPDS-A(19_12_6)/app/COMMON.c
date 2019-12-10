/****************************************************************************
*                                                                           *
*                         COPYRIGHT (C)   SAE      							*
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
*     Module Name:         %name:     COMMON.c %                            *
*     Module Version:      %version:  3 %                                   *
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
*				  %created_by:       mason                                  *
*									                                        *
*     Date:       %date_modified:  2014-12-02 %                 			*
*                                                                           *
****************************************************************************/
/**** includes ***************************************************************/
#include "COMMON.h"

/**** definitions*************************************************************/

UNUM32 gu32_GPIO_PORTA_OUT_MASK = (UNUM32)0x00000000;
UNUM32 gu32_GPIO_PORTB_OUT_MASK = (UNUM32)0x00000000;
UNUM32 gu32_GPIO_PORTC_OUT_MASK = (UNUM32)0x00000000;
UNUM32 gu32_GPIO_PORTA_IN_MASK = (UNUM32)0x00000000;
UNUM32 gu32_GPIO_PORTB_IN_MASK = (UNUM32)0x00000000;
UNUM32 gu32_GPIO_PORTC_IN_MASK = (UNUM32)0x00000000;

struct ADC_Structure ADC_Ref_Check[16] =
{
	{(UNUM16)0, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)1, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)2, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)3, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)4, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)5, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)6, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)7, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)8, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)9, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)10, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)11, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)12, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)13, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)14, (UNUM16)0x0FFF, (UNUM16)0},
	{(UNUM16)15, (UNUM16)0x0FFF, (UNUM16)0}
};

UNUM16 I2T_ADC_Value[20] = {(UNUM16)0};

extern struct ADC_Structure ADC_Ref_Check[16];
UNUM16 ADC_START_FLAG = (UNUM16)0;
UNUM16 ADC_FINISHED_FLAG = (UNUM16)0;
/***************************************************************************
End of file.
***************************************************************************/
