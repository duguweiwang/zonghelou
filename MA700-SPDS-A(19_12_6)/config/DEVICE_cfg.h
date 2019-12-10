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
*     Module Name:         %name:     DEVICE_cfg.h %                          *
*     Module Version:      %version:  3 %                                     *
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
#ifndef __DEVICE_CFG_H__
#define __DEVICE_CFG_H__

/**** includes ***************************************************************/
#include "I2C.h"
#include "DEFAULT_ISR.h"

/**** definitions*************************************************************/
#define OK					    0x0000
#define SYSTEM_ERROR		    0xFFFF
#define CAN_BUSOFF_ERROR	    0x7788
/*-----------------------------------------------------------------------------
      Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
-----------------------------------------------------------------------------*/
/*#define DSP28_DIVSEL   0 */ /****Enable /4 for SYSCLKOUT****/
/*#define DSP28_DIVSEL   1 */ /****Enable /4 for SYSCLKOUT****/
#define DSP28_DIVSEL     2 /****Enable /2 for SYSCLKOUT****/
/*#define DSP28_DIVSEL   3 */ /****Enable /1 for SYSCLKOUT****/

#define DSP28_PLLCR     10
/*#define DSP28_PLLCR    9*/
/*#define DSP28_PLLCR    8*/
/*#define DSP28_PLLCR    7*/
/*#define DSP28_PLLCR    6*/
/*#define DSP28_PLLCR    5*/
/*#define DSP28_PLLCR    4*/
/*#define DSP28_PLLCR    3*/
/*#define DSP28_PLLCR    2*/
/*#define DSP28_PLLCR    1*/
/*#define DSP28_PLLCR    0*/ /****PLL is bypassed in this mode****/

/*-----------------------------------------------------------------------------
      Specify the clock rate of the CPU (SYSCLKOUT) in nS.

      Take into account the input clock frequency and the PLL multiplier
      selected in step 1.

      Use one of the values provided, or define your own.
      The trailing L is required tells the compiler to treat
      the number as a 64-bit value.

      Only one statement should be uncommented.

      Example 1:150 MHz devices:
                CLKIN is a 30MHz crystal.

                In step 1 the user specified PLLCR = 0xA for a
                150Mhz CPU clock (SYSCLKOUT = 150MHz).

                In this case, the CPU_RATE will be 6.667L
                Uncomment the line:  #define CPU_RATE  6.667L

      Example 2:  100 MHz devices:
                  CLKIN is a 20MHz crystal.

	              In step 1 the user specified PLLCR = 0xA for a
	              100Mhz CPU clock (SYSCLKOUT = 100MHz).

	              In this case, the CPU_RATE will be 10.000L
                  Uncomment the line:  #define CPU_RATE  10.000L
-----------------------------------------------------------------------------*/
#define CPU_RATE    6.667L /****for a 150MHz CPU clock speed (SYSCLKOUT)****/
/*#define CPU_RATE    7.143L*/   /****for a 140MHz CPU clock speed (SYSCLKOUT)****/
/*#define CPU_RATE    8.333L*/  /****for a 120MHz CPU clock speed (SYSCLKOUT)****/
/*#define CPU_RATE   10.000L*/   /****for a 100MHz CPU clock speed (SYSCLKOUT)****/
/*#define CPU_RATE   13.330L*/   /****for a 75MHz CPU clock speed  (SYSCLKOUT)****/
/*#define CPU_RATE   20.000L*/   /****for a 50MHz CPU clock speed  (SYSCLKOUT)****/
/*#define CPU_RATE   33.333L*/   /****for a 30MHz CPU clock speed  (SYSCLKOUT)****/
/*#define CPU_RATE   41.667L*/   /****for a 24MHz CPU clock speed  (SYSCLKOUT)****/
/*#define CPU_RATE   50.000L*/   /****for a 20MHz CPU clock speed  (SYSCLKOUT)****/
/*#define CPU_RATE   66.667L*/   /****for a 15MHz CPU clock speed  (SYSCLKOUT)****/
/*#define CPU_RATE  100.000L*/   /****for a 10MHz CPU clock speed  (SYSCLKOUT)****/

/*-----------------------------------------------------------------------------
      Target device (in DSP2833x_Device.h) determines CPU frequency
      (for examples) - either 150 MHz (for 28335 and 28334) or 100 MHz
      (for 28332). User does not have to change anything here.
-----------------------------------------------------------------------------*/
#define CPU_FRQ_100MHZ    0 /****DSP28_28335||DSP28_28334****/
#define CPU_FRQ_150MHZ    1 /****150 MHz CPU Freq (30 MHz input freq) by DEFAULT****/
#define PARTNO_28335      0xEF
#define DEVICE_DATETYPE_UNUM16_MAX_VALUE		65535
/****Include files not used with DSP/BIOS****/
/****-----------------------------------------------------------------
External symbols created by the linker cmd file
DSP28 examples will use these to relocate code from one LOAD location
in either Flash or XINTF to a different RUN location in internal
RAM****/
extern UNUM16 RamfuncsLoadStart;
extern UNUM16 RamfuncsLoadEnd;
extern UNUM16 RamfuncsRunStart;
/*extern volatile struct SYS_CTRL_REGS SysCtrlRegs;*/
#ifndef DSP28_BIOS

#endif

/*---------------------------------------------------------------------------
Common CPU Definitions:
---------------------------------------------------------------------------*/
extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int IER;

/**** functions declarations **************************************************/
extern void DMAInitialize( void );
/****DMA Channel 1****/
extern void DMACH1AddrConfig( volatile UNUM16 *DMA_Dest,
		                      volatile UNUM16 *DMA_Source );

extern void DMACH1BurstConfig( UNUM16 bsize,
		                       SNUM16 srcbstep,
		                       SNUM16 desbstep );

extern void DMACH1TransferConfig( UNUM16 tsize,
		                          SNUM16 srctstep,
		                          SNUM16 deststep );

extern void DMACH1WrapConfig( UNUM16 srcwsize,
		                      SNUM16 srcwstep,
		                      UNUM16 deswsize,
		                      SNUM16 deswstep );

extern void DMACH1ModeConfig( UNUM16 persel,
		                      UNUM16 perinte,
		                      UNUM16 oneshot,
		                      UNUM16 cont,
		                      UNUM16 synce,
		                      UNUM16 syncsel,
		                      UNUM16 ovrinte,
		                      UNUM16 datasize,
		                      UNUM16 chintmode,
		                      UNUM16 chinte );

extern void StartDMACH1( void );
/****DMA Channel 2****/
extern void DMACH2AddrConfig( volatile UNUM16 *DMA_Dest,
		                      volatile UNUM16 *DMA_Source );

extern void DMACH2BurstConfig( UNUM16 bsize,
		                       SNUM16 srcbstep,
		                       SNUM16 desbstep );

extern void DMACH2TransferConfig( UNUM16 tsize,
		                          SNUM16 srctstep,
		                          SNUM16 deststep );

extern void DMACH2WrapConfig( UNUM16 srcwsize,
		                      SNUM16 srcwstep,
		                      UNUM16 deswsize,
		                      SNUM16 deswstep );

extern void DMACH2ModeConfig( UNUM16 persel,
		                      UNUM16 perinte,
		                      UNUM16 oneshot,
		                      UNUM16 cont,
		                      UNUM16 synce,
		                      UNUM16 syncsel,
		                      UNUM16 ovrinte,
		                      UNUM16 datasize,
		                      UNUM16 chintmode,
		                      UNUM16 chinte );

extern void StartDMACH2( void );
/****DMA Channel 3****/
extern void DMACH3AddrConfig( volatile UNUM16 *DMA_Dest,
		                      volatile UNUM16 *DMA_Source );

extern void DMACH3BurstConfig( UNUM16 bsize,
		                       SNUM16 srcbstep,
		                       SNUM16 desbstep );

extern void DMACH3TransferConfig( UNUM16 tsize,
		                          SNUM16 srctstep,
		                          SNUM16 deststep );

extern void DMACH3WrapConfig( UNUM16 srcwsize,
		                      SNUM16 srcwstep,
		                      UNUM16 deswsize,
		                      SNUM16 deswstep );

extern void DMACH3ModeConfig( UNUM16 persel,
		                      UNUM16 perinte,
		                      UNUM16 oneshot,
		                      UNUM16 cont,
		                      UNUM16 synce,
		                      UNUM16 syncsel,
		                      UNUM16 ovrinte,
		                      UNUM16 datasize,
		                      UNUM16 chintmode,
		                      UNUM16 chinte );

extern void StartDMACH3( void );
/****DMA Channel 4****/
extern void DMACH4AddrConfig( volatile UNUM16 *DMA_Dest,
		                      volatile UNUM16 *DMA_Source );

extern void DMACH4BurstConfig( UNUM16 bsize,
		                       SNUM16 srcbstep,
		                       SNUM16 desbstep );

extern void DMACH4TransferConfig( UNUM16 tsize,
		                          SNUM16 srctstep,
		                          SNUM16 deststep );

extern void DMACH4WrapConfig( UNUM16 srcwsize,
		                      SNUM16 srcwstep,
		                      UNUM16 deswsize,
		                      SNUM16 deswstep );

extern void DMACH4ModeConfig( UNUM16 persel,
		                      UNUM16 perinte,
		                      UNUM16 oneshot,
		                      UNUM16 cont,
		                      UNUM16 synce,
		                      UNUM16 syncsel,
		                      UNUM16 ovrinte,
		                      UNUM16 datasize,
		                      UNUM16 chintmode,
		                      UNUM16 chinte );

extern void StartDMACH4( void );
/****DMA Channel 5****/
extern void DMACH5AddrConfig( volatile UNUM16 *DMA_Dest,
		                      volatile UNUM16 *DMA_Source );

extern void DMACH5BurstConfig( UNUM16 bsize,
		                       SNUM16 srcbstep,
		                       SNUM16 desbstep );

extern void DMACH5TransferConfig( UNUM16 tsize,
		                          SNUM16 srctstep,
		                          SNUM16 deststep );

extern void DMACH5WrapConfig( UNUM16 srcwsize,
		                      SNUM16 srcwstep,
		                      UNUM16 deswsize,
		                      SNUM16 deswstep );

extern void DMACH5ModeConfig( UNUM16 persel,
		                      UNUM16 perinte,
		                      UNUM16 oneshot,
		                      UNUM16 cont,
		                      UNUM16 synce,
		                      UNUM16 syncsel,
		                      UNUM16 ovrinte,
		                      UNUM16 datasize,
		                      UNUM16 chintmode,
		                      UNUM16 chinte );

extern void StartDMACH5( void );
/****DMA Channel 6****/
extern void DMACH6AddrConfig( volatile UNUM16 *DMA_Dest,
		                      volatile UNUM16 *DMA_Source );

extern void DMACH6BurstConfig( UNUM16 bsize,
		                       UNUM16 srcbstep,
		                       SNUM16 desbstep );

extern void DMACH6TransferConfig( UNUM16 tsize,
		                          SNUM16 srctstep,
		                          SNUM16 deststep );

extern void DMACH6WrapConfig( UNUM16 srcwsize,
		                      SNUM16 srcwstep,
		                      UNUM16 deswsize,
		                      SNUM16 deswstep );

extern void DMACH6ModeConfig( UNUM16 persel,
		                      UNUM16 perinte,
		                      UNUM16 oneshot,
		                      UNUM16 cont,
		                      UNUM16 synce,
		                      UNUM16 syncsel,
		                      UNUM16 ovrinte,
		                      UNUM16 datasize,
		                      UNUM16 chintmode,
		                      UNUM16 chinte );

extern void StartDMACH6( void );

extern void InitPeripherals( void );

#if DSP28_EQEP1

extern void InitEQep( void );

extern void InitEQepGpio( void );

extern void InitEQep1Gpio( void );

#endif /****if DSP28_EQEP1****/

#if DSP28_EQEP2

extern void InitEQep2Gpio( void );

#endif /****endif DSP28_EQEP2****/

extern void InitGpio( void );

extern void EnableInterrupts( void );

/*#define KickDog ServiceDog*/ /**** For compatiblity with previous versions****/
/****DSP28_DBGIER.asm****/
extern void SetDBGIER( UNUM16 dbgier );

extern void DSP28x_usDelay( UNUM32 Count );
/****DO NOT MODIFY THIS LINE.****/
/*#define DELAY_US(A)  (DSP28x_usDelay(((((FLOAT64) (A) * 1000.0L) / (FLOAT64)CPU_RATE) - 9.0L) / 5.0L))*/
#define DELAY_US(A)  (DSP28x_usDelay(((((UNUM32) (A) * 1000U *1000U) / 6667U) - 9U) / 5U))
void ADC_cal( void );

#endif

/***************************************************************************
End of file.
***************************************************************************/
