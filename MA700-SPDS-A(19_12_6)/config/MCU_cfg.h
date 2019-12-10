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
*     Module Name:         %name:     MCU_cfg.h %                            *
*     Module Version:      %version:  5 %                                     *
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

#ifndef __MCU_CFG_H__
#define __MCU_CFG_H__

/**** includes ***************************************************************/
#include "DEVICE.h"

/**** definitions*************************************************************/
/*CPU Timer*/
#define MCU_FRQ_150MHZ					 1
#define MCU_SAMPLE_PERIOD                5000 /* in mSec fix 50000 to 10000 yfc */

#ifdef  MCU_FRQ_150MHZ
#define MCU_FRQ_SYSCLK                   150  /* in MHz*/
#elif   MCU_FRQ_100MHZ
#define MCU_FRQ_SYSCLK                   100  /* in MHz*/
#endif

#define MCU_POWER_SUPPLY_DIGITAL_IO_ADDRESS     1
#define MCU_POWER_SUPPLY_HIGH_LEVEL				1
#define MCU_POWER_SUPPLY_LOW_LEVEL				0

typedef enum
{
	MCU_CYCLIC_TASKS_COUNT_MIN  = 0,
	MCU_CYCLIC_TASKS_COUNT_ONE	= 1,
	MCU_CYCLIC_TASKS_COUNT_TWO  = 2
} MCU_Cyclic_Tasks_Count_Enum;

typedef enum
{
	TASK_ALIVE_NOT_STARTED	= 0x00, 	/* status of tasks alive check not yet available */
	TASK_ALIVE_OK 			= 0x01, 	/* tasks alive check OK 		*/
	TASK_ALIVE_NOT_OK 		= 0x02		/* tasks alive check NOT OK 	*/
} Tasks_Alive_Status_Enum;

typedef enum
{
	LOW_POWER_MODES_IDLE = 0,
	LOW_POWER_MODES_STANDBY,
	LOW_POWER_MODES_HALT,
	LOW_POWER_MODES_NORMAL_RUN
} Low_Power_Modes_Enum;

#define MCU_LOW_POWER_HW_IDLE                   0u
#define MCU_LOW_POWER_HW_STANDBY                1u
#define MCU_LOW_POWER_HW_HALT                   2u

/**** functions declarations *************************************************/
/*---------------------------------------------------------------------------
Usefull Timer Operations:
Start Timer:
---------------------------------------------------------------------------*/
#define MCU_StartCpuTimer0( void )   (MCU_CpuTimer0Regs.TCR.bit.TSS = 0)

/* Stop Timer:*/
#define MCU_StopCpuTimer0( void )    (MCU_CpuTimer0Regs.TCR.bit.TSS = 1)

/* Reload Timer With period Value:*/
#define MCU_ReloadCpuTimer0( void )  (MCU_CpuTimer0Regs.TCR.bit.TRB = 1)

/* Read 32-Bit Timer Value:*/
#define MCU_ReadCpuTimer0Counter( void ) (MCU_CpuTimer0Regs.TIM.all)

/* Read 32-Bit Period Value:*/
#define MCU_ReadCpuTimer0Period( void )  (MCU_CpuTimer0Regs.PRD.all)

/* CpuTimer 1 and CpuTimer2 are reserved for DSP BIOS & other RTOS
Do not use these two timers if you ever plan on integrating
DSP-BIOS or another realtime OS.
For this reason, comment out the code to manipulate these two timers
if using DSP-BIOS or another realtime OS.
Start Timer:*/
#define MCU_StartCpuTimer1( void )   (MCU_CpuTimer1Regs.TCR.bit.TSS = 0)
#define MCU_StartCpuTimer2( void )   (MCU_CpuTimer2Regs.TCR.bit.TSS = 0)

/*Stop Timer:*/
#define MCU_StopCpuTimer1( void )   (MCU_CpuTimer1Regs.TCR.bit.TSS = 1)
#define MCU_StopCpuTimer2( void )   (MCU_CpuTimer2Regs.TCR.bit.TSS = 1)

/*Reload Timer With period Value:*/
#define MCU_ReloadCpuTimer1( void ) (MCU_CpuTimer1Regs.TCR.bit.TRB = 1)
#define MCU_ReloadCpuTimer2( void ) (MCU_CpuTimer2Regs.TCR.bit.TRB = 1)

/*Read 32-Bit Timer Value:*/
#define MCU_ReadCpuTimer1Counter( void ) (MCU_CpuTimer1Regs.TIM.all)
#define MCU_ReadCpuTimer2Counter( void ) (MCU_CpuTimer2Regs.TIM.all)

/*Read 32-Bit Period Value:*/
#define MCU_ReadCpuTimer1Period( void )  (MCU_CpuTimer1Regs.PRD.all)
#define MCU_ReadCpuTimer2Period( void )  (MCU_CpuTimer2Regs.PRD.all)

extern struct CPUTIMER_VARS MCU_ms_CpuTimer0;

extern struct CPUTIMER_VARS MCU_CpuTimer1;

extern struct CPUTIMER_VARS MCU_CpuTimer2;

void MCU_InitClock( void );

void MCU_ConfigClock( struct CPUTIMER_VARS *Timer, float Freq, float Period );

void MCU_SetTaskFlag( MCU_Cyclic_Tasks_Count_Enum ae_TaskCount, Tasks_Alive_Status_Enum au32_TaskFlag );

Tasks_Alive_Status_Enum MCU_GetTaskFlag( MCU_Cyclic_Tasks_Count_Enum ae_TaskCount );

extern UNUM16 MCU_CheckSelf( UNUM16 au16_LRU_mu16_ID );

#endif

/***************************************************************************
End of file.
***************************************************************************/
