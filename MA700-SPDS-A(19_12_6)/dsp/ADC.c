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
*     Module Description:  definition of the realtime scheduler callbacks     *
*     Module Name:         %name:     ADC.c %                                 *
*     Module Version:      %version:  2 %                                    *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	                                                              *
*                                                                             *
*     Controller:                                                             *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*                 %created_by:  maolei %                                       *
*                                                                             *
*     Datum:      %date_modified:  Tue Jan  8 14:15:17 2013 %                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     $Revision:: 603  $   embeddeers revision number                         *
******************************************************************************/

/**** includes ***************************************************************/
#include "ADC.h"
#include "ADC_cfg.h"
#include "DEVICE.h"
#include "DEVICE_cfg.h"

#pragma DATA_SECTION(ADC_AdcRegs,"AdcRegsFile");
volatile struct ADC_REGS ADC_AdcRegs;

#pragma DATA_SECTION(ADC_AdcMirror,"AdcMirrorFile");
volatile struct ADC_RESULT_MIRROR_REGS ADC_AdcMirror;
/**** functions **************************************************************/
/*---------------------------------------------------------------------------
ADC_Init:
-----------------------------------------------------------------------------
This function initializes ADC to a known state.
*/

void ADC_Init( UNUM16 au16_SampleNumber )
{
/* external void DSP28x_usDelay(UNUM32 Count); */
/* IMPORTANT */
/* The ADC_cal function, which  copies the ADC calibration values */
/* from TI reserved OTP into the ADCREFSEL and ADCOFFTRIM registers, */
/* occurs automatically in the Boot ROM. If the boot ROM code is bypassed */
/* during the debug process, the following function MUST be called for the */
/* ADC to function according to specification. The clocks to the ADC MUST */
/* be enabled before calling this function. */
/* See the device data manual and/or the ADC Reference */
/* Manual for more information. */

    EALLOW;
    SYS_SysCtrlRegs.PCLKCR0.bit.ADCENCLK = (UNUM16)1;
    ADC_cal(); 
    EDIS;

/* To power up the ADC the ADCENCLK bit should be set first to enable */
/* clocks, followed by powering up the bandgap, reference circuitry, */
/* and ADC core. Before the first conversion is performed a 5ms delay */
/* must be observed after power up to give all analog circuits time to */
/* power up and settle. */
/* Please note that for the delay function below to operate correctly */
/* the CPU_RATE define statement in the DSP2833x_Examples.h file must */
/* contain the correct CPU clock period in nanoseconds. */

    ADC_AdcRegs.ADCTRL3.all = (UNUM16)0x00E0; /* Power up bandgap/reference/ADC circuits */
    DELAY_US(ADC_usDELAY); /* Delay before converting ADC channels */

    ADC_AdcRegs.ADCTRL1.all = (UNUM16)0;
    ADC_AdcRegs.ADCTRL1.bit.ACQ_PS = (UNUM16)ADC_SHCLK; /* Set Sample Window Size */
    ADC_AdcRegs.ADCTRL1.bit.CPS = (UNUM16)BIT_SET; /* divide by 2 */

    ADC_AdcRegs.ADCTRL1.bit.CONT_RUN = (UNUM16)BIT_CLEAR; /* Start/Stop run */

	/* AdcRegs.ADCTRL1.bit.SEQ_OVRD = BIT_CLEAR; */	/* Unable Override */
    ADC_AdcRegs.ADCTRL1.bit.SEQ_CASC = (UNUM16)BIT_SET;	/* Sequencer Mode */
    ADC_AdcRegs.ADCTRL2.all = (UNUM16)0;

    ADC_AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = (UNUM16)BIT_SET; /* 1=enable SEQ1 interrupt */

	/* AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = BIT_CLEAR; */	/* 0= interrupt after every end of sequence */
    ADC_AdcRegs.ADCTRL3.bit.ADCCLKPS = (UNUM16)ADC_CKLPS;
    ADC_AdcRegs.ADCTRL3.bit.SMODE_SEL = (UNUM16)BIT_CLEAR; /* sequence sample */

    ADC_AdcRegs.ADCMAXCONV.all = (UNUM16)au16_SampleNumber - (UNUM16)1;
    /* 20140505 Laspide changed */
    /* Debug use internal voltage reference, this should be changed as required */
    ADC_AdcRegs.ADCREFSEL.bit.REF_SEL = (UNUM16)0;
}

void ADC_ConfigChannel( UNUM16 au16_ChannelSN, UNUM16 au16_SampleNumber )
{
	switch ( au16_SampleNumber )
	{
		case (UNUM16)0:
		    ADC_AdcRegs.ADCCHSELSEQ1.bit.CONV00 = au16_ChannelSN;
			break;
		case (UNUM16)1:
			ADC_AdcRegs.ADCCHSELSEQ1.bit.CONV01 = au16_ChannelSN;
			break;
		case (UNUM16)2:
			ADC_AdcRegs.ADCCHSELSEQ1.bit.CONV02 = au16_ChannelSN;
			break;
		case (UNUM16)3:
		    ADC_AdcRegs.ADCCHSELSEQ1.bit.CONV03 = au16_ChannelSN;
		    break;
		case (UNUM16)4:
			ADC_AdcRegs.ADCCHSELSEQ2.bit.CONV04 = au16_ChannelSN;
			break;
		case (UNUM16)5:
			ADC_AdcRegs.ADCCHSELSEQ2.bit.CONV05 = au16_ChannelSN;
			break;
		case (UNUM16)6:
			ADC_AdcRegs.ADCCHSELSEQ2.bit.CONV06 = au16_ChannelSN;
			break;
		case (UNUM16)7:
			ADC_AdcRegs.ADCCHSELSEQ2.bit.CONV07 = au16_ChannelSN;
			break;
		case (UNUM16)8:
			ADC_AdcRegs.ADCCHSELSEQ3.bit.CONV08 = au16_ChannelSN;
			break;
		case (UNUM16)9:
			ADC_AdcRegs.ADCCHSELSEQ3.bit.CONV09 = au16_ChannelSN;
			break;
		case (UNUM16)10:
			ADC_AdcRegs.ADCCHSELSEQ3.bit.CONV10 = au16_ChannelSN;
			break;
		case (UNUM16)11:
			ADC_AdcRegs.ADCCHSELSEQ3.bit.CONV11 = au16_ChannelSN;
			break;
		case (UNUM16)12:
			ADC_AdcRegs.ADCCHSELSEQ4.bit.CONV12 = au16_ChannelSN;
			break;
		case (UNUM16)13:
			ADC_AdcRegs.ADCCHSELSEQ4.bit.CONV13 = au16_ChannelSN;
			break;
		case (UNUM16)14:
			ADC_AdcRegs.ADCCHSELSEQ4.bit.CONV14 = au16_ChannelSN;
			break;
		case (UNUM16)15:
			ADC_AdcRegs.ADCCHSELSEQ4.bit.CONV15 = au16_ChannelSN;
			break;
		default:
			break;
	}
}

void ADC_Reset_SEQ( void )
{
    ADC_AdcRegs.ADCTRL2.bit.RST_SEQ1 = (UNUM16)BIT_SET;
    ADC_AdcRegs.ADCTRL2.bit.SOC_SEQ1 = (UNUM16)BIT_SET;
}

void ADC_HandleSEQINT( void )
{
	UNUM16 lu16_WaitCounter = (UNUM16)ADC_MAX_WAIT_COUNTER;

	while ( ((UNUM16)ADC_AdcRegs.ADCST.bit.INT_SEQ1 == (UNUM16)0) && (lu16_WaitCounter != (UNUM16)0) )
	{
		lu16_WaitCounter--;
	}

	ADC_AdcRegs.ADCST.bit.INT_SEQ1_CLR = (UNUM16)1;
}

void ADC_Check_SEQCNTR( void )
{
	UNUM16 lu16_WaitCounter = (UNUM16)ADC_MAX_WAIT_COUNTER;

	while ( ((UNUM16)ADC_AdcRegs.ADCASEQSR.bit.SEQ_CNTR != (UNUM16)0) && (lu16_WaitCounter != (UNUM16)0) )
	{
	    lu16_WaitCounter--;
	}

	ADC_AdcRegs.ADCST.bit.INT_SEQ1_CLR = (UNUM16)1;
}

UNUM16 ADC_GetADCResult( UNUM16 au16_SampleNumber )
{
	UNUM16  lu16_Result = (UNUM16)0;

	switch ( au16_SampleNumber )
	{
		case (UNUM16)0:
			lu16_Result = ADC_AdcRegs.ADCRESULT0;
			break;
		case (UNUM16)1:
			lu16_Result = ADC_AdcRegs.ADCRESULT1;
			break;
		case (UNUM16)2:
			lu16_Result = ADC_AdcRegs.ADCRESULT2;
			break;
		case (UNUM16)3:
			lu16_Result = ADC_AdcRegs.ADCRESULT3;
			break;
		case (UNUM16)4:
			lu16_Result = ADC_AdcRegs.ADCRESULT4;
			break;
		case (UNUM16)5:
			lu16_Result = ADC_AdcRegs.ADCRESULT5;
			break;
		case (UNUM16)6:
			lu16_Result = ADC_AdcRegs.ADCRESULT6;
			break;
		case (UNUM16)7:
			lu16_Result = ADC_AdcRegs.ADCRESULT7;
			break;
		case (UNUM16)8:
			lu16_Result = ADC_AdcRegs.ADCRESULT8;
			break;
		case (UNUM16)9:
			lu16_Result = ADC_AdcRegs.ADCRESULT9;
			break;
		case (UNUM16)10:
			lu16_Result = ADC_AdcRegs.ADCRESULT10;
			break;
		case (UNUM16)11:
			lu16_Result = ADC_AdcRegs.ADCRESULT11;
			break;
		case (UNUM16)12:
			lu16_Result = ADC_AdcRegs.ADCRESULT12;
			break;
		case (UNUM16)13:
			lu16_Result = ADC_AdcRegs.ADCRESULT13;
			break;
		case (UNUM16)14:
			lu16_Result = ADC_AdcRegs.ADCRESULT14;
			break;
		case (UNUM16)15:
			lu16_Result = ADC_AdcRegs.ADCRESULT15;
			break;
		default:
			break;
	}

	return(lu16_Result);
}

UNUM32 ADC_GetAverageResult( const UNUM16 au16_Array[], SNUM16 as16_NumberCounter )
{
	SNUM16 ls16_Loop_i = (SNUM16)0;
	UNUM32 lu32_TempResult = (UNUM32)0;

	for ( ls16_Loop_i = as16_NumberCounter - (SNUM16)2; ls16_Loop_i > 0; ls16_Loop_i-- )
	{
		lu32_TempResult += (UNUM32)au16_Array[ls16_Loop_i];
	}

	lu32_TempResult = (UNUM32)(lu32_TempResult / ( (UNUM32)as16_NumberCounter - (UNUM32)2 ));

	return( lu32_TempResult );
}

void ADC_GetFinalResult( struct ADC_Structure *ap_Status )
{
	UNUM16 lu16_Loop_ChannelSN = (UNUM16)0;
	UNUM16 lu16_Loop_LoopNumber = (UNUM16)0;
	UNUM16 lu16_SampleResult[ADC_SAMPLE_NUMBER];

	for( lu16_Loop_LoopNumber = (UNUM16)0; lu16_Loop_LoopNumber < (UNUM16)ADC_SAMPLE_NUMBER; lu16_Loop_LoopNumber++ )
	{
		lu16_SampleResult[lu16_Loop_LoopNumber] = (UNUM16)0;
	}

	for( lu16_Loop_LoopNumber = (UNUM16)0; lu16_Loop_LoopNumber < (UNUM16)ADC_SAMPLE_LOOP_NUMBER; lu16_Loop_LoopNumber++ )
	{
		for( lu16_Loop_ChannelSN = (UNUM16)0; lu16_Loop_ChannelSN < (UNUM16)ADC_CHANNEL_NUMBER; lu16_Loop_ChannelSN++ )
		{
			ADC_ConfigChannel( ap_Status->mu16_ADC_Channel, lu16_Loop_ChannelSN );
		}

		ADC_Reset_SEQ();

		ADC_HandleSEQINT();
		/*ADC_Check_SEQCNTR();*/

		for( lu16_Loop_ChannelSN = (UNUM16)0; lu16_Loop_ChannelSN < (UNUM16)ADC_CHANNEL_NUMBER; lu16_Loop_ChannelSN++ )
		{
			lu16_SampleResult[(lu16_Loop_LoopNumber * ((UNUM16)ADC_CHANNEL_NUMBER)) + lu16_Loop_ChannelSN] = ADC_GetADCResult ( lu16_Loop_ChannelSN ) >> 4;
		}
	}
	ADC_Sort( lu16_SampleResult, ADC_SAMPLE_NUMBER );
    /* return 12bit ADC converter result */
	ap_Status->mu16_ADC_FinalResult = (UNUM16)ADC_GetAverageResult( lu16_SampleResult, (SNUM16)ADC_SAMPLE_NUMBER );
}

void ADC_GetResult( struct ADC_Structure *ap_Status )
{
	ADC_ConfigChannel( ap_Status->mu16_ADC_Channel, ap_Status->mu16_ADC_Channel );
	ADC_Reset_SEQ();
	ADC_HandleSEQINT();
	ap_Status->mu16_ADC_FinalResult = ADC_GetADCResult ( ap_Status->mu16_ADC_Channel ) >> 4;

}

void ADC_Sort( UNUM16 au16_Array[], SNUM16 as16_NumberCounter )
{
    SNUM16 ls16_Loop_i,ls16_Loop_j;
    UNUM16 lu16_Temp;

    for( ls16_Loop_i = 0; ls16_Loop_i < as16_NumberCounter; ls16_Loop_i++)
    {
        for( ls16_Loop_j = ls16_Loop_i+1; ls16_Loop_j < as16_NumberCounter; ls16_Loop_j++)
        {
            if(au16_Array[ls16_Loop_i] > au16_Array[ls16_Loop_j])
            {
                lu16_Temp = au16_Array[ls16_Loop_i];
                au16_Array[ls16_Loop_i] = au16_Array[ls16_Loop_j];
                au16_Array[ls16_Loop_j] = lu16_Temp;
            }
        }
    }
}



/***************************************************************************
End of file.
***************************************************************************/
