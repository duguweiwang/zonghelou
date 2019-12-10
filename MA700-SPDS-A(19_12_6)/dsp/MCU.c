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
*     Module Description:  module to provide a realtime scheduler	          *
*     Module Name:         %name:     MCU.c %                                 *
*     Module Version:      %version:  5 %                                    *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	 	                                                          *
*                                                                             *
*     Controller:                                                             *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*				  %created_by:   maolei %                                     *
*									                                          *
*     Date:       %date_modified:  Wed Apr  4 14:57:59 2012 %                 *
*                                                                             *
******************************************************************************/

/**** includes ***************************************************************/
#include "MCU.h"
#include "MCU_cfg.h"
#include "PIE_CTRL.h"
#include "COMMON.h"
#include "INIT_APP.h"
#include "I2T_APP.h"
/**** definitions*************************************************************/

#pragma DATA_SECTION(MCU_CpuTimer0Regs,"CpuTimer0RegsFile");
volatile struct CPUTIMER_REGS MCU_CpuTimer0Regs;

#pragma DATA_SECTION(MCU_CpuTimer1Regs,"CpuTimer1RegsFile");
volatile struct CPUTIMER_REGS MCU_CpuTimer1Regs;

#pragma DATA_SECTION(MCU_CpuTimer2Regs,"CpuTimer2RegsFile");
volatile struct CPUTIMER_REGS MCU_CpuTimer2Regs;

/*Counter Variables of Timer0 Interrupt -- Start*/

UNUM16 FLG_mu16_LRU_CAN_MailboxSN = (UNUM16)0xFFFFU;

static UNUM16 Schedule_5ms = (UNUM16)0;
static UNUM32 MCU_mu32_cnt_TMR0_5ms = (UNUM32)0; /*50ms Timer0 Interrupt Counter*/


struct CPUTIMER_VARS MCU_ms_CpuTimer0;
static Tasks_Alive_Status_Enum MCU_ge_TaskOneStatus;
static Tasks_Alive_Status_Enum MCU_ge_TaskTwoStatus;


/**** functions **************************************************************/
/******************************************************************************
MCU_InitClock:
-------------------------------------------------------------------------------
This function initializes all three CPU timers to a known state.
*******************************************************************************/
void MCU_InitClock( void )
{
    /*CPU Timer 0*/
    /*Initialize address pointers to respective timer registers:*/
    MCU_ms_CpuTimer0.RegsAddr = &MCU_CpuTimer0Regs;
    /*Initialize timer period to maximum:*/
    MCU_CpuTimer0Regs.PRD.all  = (UNUM32)0xFFFFFFFFU;
    /*Initialize pre-scale counter to divide by 1 (SYSCLKOUT):*/
    MCU_CpuTimer0Regs.TPR.all  = (UNUM16)0;
    MCU_CpuTimer0Regs.TPRH.all = (UNUM16)0;
    /*Make sure timer is stopped:*/
    MCU_CpuTimer0Regs.TCR.bit.TSS = (UNUM16)1;
    /*Reload all counter register with period value:*/
    MCU_CpuTimer0Regs.TCR.bit.TRB = (UNUM16)1;
    /*Reset interrupt counters:*/
    MCU_ms_CpuTimer0.InterruptCount = (UNUM32)0;
}

/*---------------------------------------------------------------------------
MCU_ConfigClock:
---------------------------------------------------------------------------
This function initializes the selected timer to the period specified
by the "Freq" and "Period" parameters. The "Freq" is entered as "MHz"
and the period in "uSeconds". The timer is held in the stopped state
after configuration.**/

void MCU_ConfigClock( struct CPUTIMER_VARS *Timer, float Freq, float Period )
{
    UNUM32  temp;
    /*Initialize timer period:*/
    Timer->CPUFreqInMHz = Freq;
    Timer->PeriodInUSec = Period;
    temp = (UNUM32)Freq *(UNUM32) Period;
    Timer->RegsAddr->PRD.all = temp;
    /*Set pre-scale counter to divide by 1 (SYSCLKOUT):*/
    Timer->RegsAddr->TPR.all  = (UNUM16)0;
    Timer->RegsAddr->TPRH.all  = (UNUM16)0;
    /*Initialize timer control register:*/
    Timer->RegsAddr->TCR.bit.TSS = (UNUM16)1; /*1 = Stop timer, 0 = Start/Restart Timer*/
    Timer->RegsAddr->TCR.bit.TRB = (UNUM16)1; /*1 = reload timer*/
    Timer->RegsAddr->TCR.bit.SOFT = (UNUM16)1;
    Timer->RegsAddr->TCR.bit.FREE = (UNUM16)1; /*Timer Free Run*/
    Timer->RegsAddr->TCR.bit.TIE = (UNUM16)1; /*0 = Disable/ 1 = Enable Timer Interrupt*/
    /*Reset interrupt counter:*/
    Timer->InterruptCount = (UNUM32)0;
}

Tasks_Alive_Status_Enum MCU_GetTaskFlag( MCU_Cyclic_Tasks_Count_Enum ae_TaskCount )
{
	Tasks_Alive_Status_Enum le_TaskStatus = TASK_ALIVE_NOT_OK;
	switch (ae_TaskCount)
	{
		case MCU_CYCLIC_TASKS_COUNT_ONE:
			le_TaskStatus = MCU_ge_TaskOneStatus;
			break;
		case MCU_CYCLIC_TASKS_COUNT_TWO:
			le_TaskStatus = MCU_ge_TaskTwoStatus;
			break;
		default:
			break;
	}
	return le_TaskStatus;
}

void MCU_SetTaskFlag( MCU_Cyclic_Tasks_Count_Enum ae_TaskCount, Tasks_Alive_Status_Enum au32_TaskFlag )
{
	switch (ae_TaskCount)
	{
		case MCU_CYCLIC_TASKS_COUNT_ONE:
			MCU_ge_TaskOneStatus = au32_TaskFlag;
			break;
		case MCU_CYCLIC_TASKS_COUNT_TWO:
			MCU_ge_TaskTwoStatus = au32_TaskFlag;
			break;
		default:
		    break;
	}
}

UNUM32 MCU_GetTMR0_5ms(void)
{
	return MCU_mu32_cnt_TMR0_5ms;
}

UNUM16 MCU_GetStatus_5ms(void)
{
	UNUM16 lu16_Status=(UNUM16)0;

	lu16_Status = Schedule_5ms;

	return lu16_Status;
}

void MCU_ClearStatus_5ms(void)
{
	Schedule_5ms = (UNUM16)0;
}

interrupt void TINT0_ISR( void ) /*CPU-Timer 0*/
{
	if(MCU_mu32_cnt_TMR0_5ms > (UNUM32)9999)
	{
	    MCU_mu32_cnt_TMR0_5ms = (UNUM32)0;
	}

	MCU_mu32_cnt_TMR0_5ms ++;
	Schedule_5ms = (UNUM16)1;

	MCU_CpuTimer0Regs.TCR.bit.TIF=(UNUM16)1;
	PIE_CTRL_PieCtrlRegs.PIEACK.bit.ACK1 = (UNUM16)1;
    EINT;
}

/***************************************************************************
End of file.
***************************************************************************/


/*
void interrupt_Main_CANoe(void)
{
	UNUM16 lu_i = (UNUM16)0;


	FLG_mu16_LRU_CAN_MailboxSN = ECAN_RecMsgAll( (UNUM16)0 );
	ECAN_APP_HandleRecBuffer();
	GPIO_ResetCtrl(recHighBytes[2],recLowBytes[2]);
	Lock_CommandCtrl(recHighBytes[1],recLowBytes[1]);
	GPIO_OutputCtrl(recHighBytes[0],recLowBytes[0]);
	I2T_APP_Process();

	if( tt1 % ((UNUM32)10) == (UNUM32)0 )
	{
		ADC_GetFinalResult( &ADC_Ref_Check[0] );
		ADC_GetFinalResult( &ADC_Ref_Check[1] );
		ADC_GetFinalResult( &ADC_Ref_Check[2] );
		ADC_GetFinalResult( &ADC_Ref_Check[3] );
		ADC_GetFinalResult( &ADC_Ref_Check[4] );
		ADC_GetFinalResult( &ADC_Ref_Check[5] );
		ADC_GetFinalResult( &ADC_Ref_Check[6] );
		ADC_GetFinalResult( &ADC_Ref_Check[7] );
		ADC_GetFinalResult( &ADC_Ref_Check[8] );
		ADC_GetFinalResult( &ADC_Ref_Check[9] );
		ADC_GetFinalResult( &ADC_Ref_Check[10] );
		ADC_GetFinalResult( &ADC_Ref_Check[11] );
		ADC_GetFinalResult( &ADC_Ref_Check[12] );
		ADC_GetFinalResult( &ADC_Ref_Check[13] );
		ADC_GetFinalResult( &ADC_Ref_Check[14] );
		ADC_GetFinalResult( &ADC_Ref_Check[15] );
		ADC_FINISHED_FLAG = (UNUM16)1;

		//Channel Status Sent to ESC CANID:A520446
		lu32_LowBytes = Channel_Status_LowBytes();
		lu32_High_Bytes = Channel_Status_HighBytes();
		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)17, (UNUM32)0xA520446, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM16)17, lu32_High_Bytes, lu32_LowBytes );

		//Channel Current Rate 0 Sent to ESC CANID:A520462
		lu32_LowBytes = (UNUM32)0;
		for ( lu_i =  (UNUM16)0; lu_i <  (UNUM16)5; lu_i++ )
		{
			lu32_LowBytes += (UNUM32)I2T_APP_GetRateCurrent(lu_i) << (lu_i * (UNUM16)5);
		}

		lu32_High_Bytes = (UNUM32)0;
		for ( lu_i =  (UNUM16)5; lu_i <  (UNUM16)10; lu_i++ )
		{
			lu32_High_Bytes += (UNUM32)I2T_APP_GetRateCurrent(lu_i) << ((lu_i - (UNUM16)5) * (UNUM16)5);
		}
		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)15, (UNUM32)0xA520462, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM16)15, lu32_High_Bytes, lu32_LowBytes );

		//Channel Current Rate 1 Sent to ESC CANID:A520466
		lu32_LowBytes = (UNUM32)0;
		for ( lu_i =  (UNUM16)10; lu_i <  (UNUM16)15; lu_i++ )
		{
			lu32_LowBytes += (UNUM32)I2T_APP_GetRateCurrent(lu_i) << ((lu_i -  (UNUM16)10) * (UNUM16)5);
		}

		lu32_High_Bytes = (UNUM32)0;
		for ( lu_i =  (UNUM16)15; lu_i <  (UNUM16)20; lu_i++ )
		{
			lu32_High_Bytes += (UNUM32)I2T_APP_GetRateCurrent(lu_i) << ((lu_i - (UNUM16)15) * (UNUM16)5);
		}
		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)16, (UNUM32)0xA520466, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM16)16, lu32_High_Bytes, lu32_LowBytes );


	}

	//Sent current to ESC Period:2S A52044E A520452 A520456 A52045A A52045E
	if(  (tt1 + (UNUM32)5) % ((UNUM32)100) == (UNUM32)0 )
	{
		lu32_adc_test[0] = (UNUM32)0;
		for ( lu_i =  (UNUM16)0; lu_i <  (UNUM16)20; lu_i++ )
		{
			lu32_adc_test[lu_i] = I2T_APP_GetdCurrent(lu_i);
			//if(lu32_adc_test[lu_i] > (UNUM32)1600)
			//{
				//lu32_adc_test[lu_i] = (UNUM32)1600;
			//}
		}
		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)10, (UNUM32)0xA52044E, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM32)10, (lu32_adc_test[3] << (UNUM32)16) + lu32_adc_test[2],  (lu32_adc_test[1] << (UNUM32)16) + lu32_adc_test[0]);

		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)11, (UNUM32)0xA520452, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM32)11, (lu32_adc_test[7] << (UNUM32)16) + lu32_adc_test[6],  (lu32_adc_test[5] << (UNUM32)16) + lu32_adc_test[4]);

		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)12, (UNUM32)0xA520456, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM32)12, (lu32_adc_test[11] << (UNUM32)16) + lu32_adc_test[10],  (lu32_adc_test[9] << (UNUM32)16) + lu32_adc_test[8]);

		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)13, (UNUM32)0xA52045A, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM32)13, (lu32_adc_test[15] << (UNUM32)16) + lu32_adc_test[14],  (lu32_adc_test[13] << (UNUM32)16) + lu32_adc_test[12]);

		ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)14, (UNUM32)0xA52045E, 0, 8 );
		ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM32)14, (lu32_adc_test[19] << (UNUM32)16) + lu32_adc_test[18],  (lu32_adc_test[17] << (UNUM32)16) + lu32_adc_test[16]);



		ADC_FINISHED_FLAG =(UNUM16)0;
	}

	//lu32_LowBytes = ADC_Ref_Check[1].mu16_ADC_FinalResult;
}
*/
