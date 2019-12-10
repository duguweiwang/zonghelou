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
*     Module Name:         %name:     ADC_cfg.h %                             *
*     Module Version:      %version:  3 %                                *
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
*                 %created_by:   maolei %                                       *
*                                    									      *									  
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 % 			      *
*                                                                             *  
******************************************************************************/

#ifndef __ADC_CFG_H__
#define __ADC_CFG_H__

/****includes ****************************************************************/
#include "DEVICE.h"
#include "COMMON.h"
/**** definitions*************************************************************/
#define ADC_usDELAY                 5000L
#define ADC_CKLPS	                3 /*ADC module clock = HSPCLK/2*ADC_CKPS = 25.0MHz/(1*2) = 12.5MHz*/
#define ADC_SHCLK	                7 /*S/H width in ADC module periods = 16 ADC clocks*/
#define ADC_MAX_WAIT_COUNTER	    1000
#define ADC_SAMPLE_NUMBER		    18 /* ADC_SAMPLE_NUMBER = ADC_SAMPLE_LOOP_NUMBER * ADC_CHANNEL_NUMBER */
#define ADC_SAMPLE_LOOP_NUMBER	    3
#define ADC_CHANNEL_NUMBER		    6
#define ADC_MAX_VALID_VALUE		    3412
#define ADC_MIN_INVALID_VALUE	    3591
#define ADC_OFF_ENCODE			    0xA
#define ADC_FAULT_MAX_NUMBER	    3
#define ADC_SN_MASK				    0xFFF0
#define ADC_MAX_INVALID_ENCODE	    0xFFFF

struct ADC_Structure
{
	UNUM16 mu16_ADC_Channel;				/* POT channel */
	UNUM16 mu16_ADC_FinalResult;            /* POT result*/
	UNUM16 mu16_ADC_Flag;			/* POT signal encode */
};



extern struct ADC_Structure ADC_Ref_Check[16];
/**** functions declarations *************************************************/
void ADC_Init( UNUM16 au16_SampleNumber );

void ADC_Reset_SEQ( void );

void ADC_HandleSEQINT( void );

void ADC_Check_SEQCNTR( void );

void ADC_ConfigChannel( UNUM16 au16_ChannelSN,
		                UNUM16 au16_SampleNumber );

UNUM16 ADC_GetADCResult ( UNUM16 au16_SampleNumber );

void ADC_GetFinalResult( struct ADC_Structure *ap_Status );
void ADC_GetResult( struct ADC_Structure *ap_Status );

UNUM32 ADC_GetAverageResult( const UNUM16 au16_Array[],
		                     SNUM16 as16_NumberCounter );

void ADC_Sort( UNUM16 au16_Array[],
		       SNUM16 as16_NumberCounter );

#endif

/***************************************************************************
End of file.
***************************************************************************/
