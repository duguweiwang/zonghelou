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
*     Module Description:  configuration of the realtime scheduler            *
*     Module Name:         %name:     MCU.h %                                 *
*     Module Version:      %version:  2 %                                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:                                                               *
*                                                                             * 
*     Controller:                                                             *
*                                                                             * 
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*                 %created_by:  maolei %                                        *
*                                    									      *									  
*     Datum:      %date_modified:  Fri Aug 17 14:11:11 2012 % 			      *
*                                                                             *  
******************************************************************************/
#ifndef __MCU_H__
#define __MCU_H__

/**** includes ***************************************************************/
#include "DEVICE.h"

/**** definitions*************************************************************/



/*---------------------------------------------------------------------------
CPU Timer Register Bit Definitions:
---------------------------------------------------------------------------*/

/* TCR: Control register bit definitions:*/
struct  TCR_BITS
{ /* bits  description*/
   UNUM16    rsvd1:4;       /* 3:0   reserved*/
   UNUM16    TSS:1;         /* 4     Timer Start/Stop*/
   UNUM16    TRB:1;         /* 5     Timer reload*/
   UNUM16    rsvd2:4;       /* 9:6   reserved*/
   UNUM16    SOFT:1;        /* 10    Emulation modes*/
   UNUM16    FREE:1;        /* 11*/
   UNUM16    rsvd3:2;       /* 12:13 reserved*/
   UNUM16    TIE:1;         /* 14    Output enable*/
   UNUM16    TIF:1;         /* 15    Interrupt flag*/
};

union TCR_REG
{
   UNUM16           all;
   struct TCR_BITS  bit;
};

/* TPR: Pre-scale low bit definitions:*/
struct  TPR_BITS
{ /* bits  description*/
   UNUM16     TDDR:8;     /* 7:0   Divide-down low*/
   UNUM16     PSC:8;      /* 15:8  Prescale counter low*/
};

union TPR_REG
{
   UNUM16           all;
   struct TPR_BITS  bit;
};

/* TPRH: Pre-scale high bit definitions:*/
struct  TPRH_BITS
{ /* bits  description*/
   UNUM16     TDDRH:8;      /* 7:0   Divide-down high*/
   UNUM16     PSCH:8;       /* 15:8  Prescale counter high*/
};

union TPRH_REG
{
   UNUM16           all;
   struct TPRH_BITS bit;
};

/* TIM, TIMH: Timer register definitions:*/
struct TIM_REG
{
   UNUM16  LSW;
   UNUM16  MSW;
};

union TIM_GROUP
{
   UNUM32          all;
   struct TIM_REG  half;
};

/* PRD, PRDH: Period register definitions:*/
struct PRD_REG
{
   UNUM16  LSW;
   UNUM16  MSW;
};

union PRD_GROUP
{
   UNUM32          all;
   struct PRD_REG  half;
};

/*---------------------------------------------------------------------------
CPU Timer Register File:
---------------------------------------------------------------------------*/

struct CPUTIMER_REGS
{
   union TIM_GROUP TIM;   /* Timer counter register*/
   union PRD_GROUP PRD;   /* Period register*/
   union TCR_REG   TCR;   /* Timer control register*/
   UNUM16          rsvd1; /* reserved*/
   union TPR_REG   TPR;   /* Timer pre-scale low*/
   union TPRH_REG  TPRH;  /* Timer pre-scale high*/
};

/*---------------------------------------------------------------------------
CPU Timer Support Variables:
---------------------------------------------------------------------------*/
struct CPUTIMER_VARS
{
   volatile struct  CPUTIMER_REGS  *RegsAddr;
   UNUM32                          InterruptCount;
   float                           CPUFreqInMHz;
   float                           PeriodInUSec;
};

extern volatile struct CPUTIMER_REGS MCU_CpuTimer0Regs;
extern volatile struct CPUTIMER_REGS MCU_CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS MCU_CpuTimer2Regs;
extern void interrupt_Main_CANoe(void);

#endif

/***************************************************************************
End of file.
***************************************************************************/
