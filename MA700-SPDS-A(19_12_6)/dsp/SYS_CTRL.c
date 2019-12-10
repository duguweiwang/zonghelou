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
*     Module Description:  	                                                  *
*     Module Name:         %name:     SYS_CTRL.c %                            *
*     Module Version:      %version:  2 %                                 *
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
*				  %created_by:   maolei %                                      *
*									                                          *
*     Date:       %date_modified:  Wed Apr  4 14:57:59 2012 %                 *
*                                                                             *
******************************************************************************/

/**** includes ***************************************************************/
#include "SYS_CTRL.h"
#include "SYS_CTRL_cfg.h"
#include "XINTF.h"
#include "WDG.h"
#include "WDG_cfg.h"

/**** definitions*************************************************************/
#pragma DATA_SECTION(SYS_CsmPwl,"CsmPwlFile");
volatile struct CSM_PWL SYS_CsmPwl;

#pragma DATA_SECTION(SYS_CsmRegs,"CsmRegsFile");
volatile struct CSM_REGS SYS_CsmRegs;

#pragma DATA_SECTION(SYS_SysCtrlRegs,"SysCtrlRegsFile");
volatile struct SYS_CTRL_REGS SYS_SysCtrlRegs;

#pragma DATA_SECTION(SYS_FlashRegs,"FlashRegsFile");
volatile struct FLASH_REGS SYS_FlashRegs;

/**** definitions*************************************************************/
/* Functions that will be run from RAM need to be assigned to
a different section.  This section will then be mapped to a load and
run address using the linker cmd file.*/
#pragma CODE_SECTION(SYS_Ctrl_Flash_Init, "ramfuncs");

/**** functions **************************************************************/
/**************************************************************************
Example: Sys_Flash_Init:
---------------------------------------------------------------------------
This function initializes the Flash Control registers
**************************************************************************/

/***************************************************************************
                     CAUTION
This function MUST be executed out of RAM. Executing it
out of OTP/Flash will yield unpredictable results
***************************************************************************/
void SYS_Ctrl_Flash_Init( void )
{
   /*Enable Flash Pipeline mode to improve performance*/
   /*of code executed from Flash.*/
   /*                CAUTION
   Minimum waitstates required for the flash operating
   at a given CPU rate must be characterized by TI.
   Refer to the datasheet for the latest information.*/

   EALLOW;
   SYS_FlashRegs.FOPT.bit.ENPIPE = (UNUM16)1;

   SYS_FlashRegs.FBANKWAIT.bit.PAGEWAIT = (UNUM16)5; /*Set the Paged Waitstate for the Flash*/
   SYS_FlashRegs.FBANKWAIT.bit.RANDWAIT = (UNUM16)5; /*Set the Random Waitstate for the Flash*/
   SYS_FlashRegs.FOTPWAIT.bit.OTPWAIT = (UNUM16)8; /*Set the Waitstate for the OTP*/

   SYS_FlashRegs.FSTDBYWAIT.bit.STDBYWAIT = (UNUM16)0x01FF;
   SYS_FlashRegs.FACTIVEWAIT.bit.ACTIVEWAIT = (UNUM16)0x01FF;
   EDIS;
   /*                CAUTION
   ONLY THE DEFAULT VALUE FOR THESE 2 REGISTERS SHOULD BE USED*/

   /*Force a pipeline flush to ensure that the write to
   the last register configured occurs before returning.*/
   /*asm(" RPT #7 || NOP");*/
}

/*---------------------------------------------------------------------------
Example: Sys_InitPll:
---------------------------------------------------------------------------
This function initializes the PLLCR register.*/

void SYS_Ctrl_InitPll( UNUM16 val,
		               UNUM16 divsel )
{
   /*Make sure the PLL is not running in limp mode*/
   if ( SYS_SysCtrlRegs.PLLSTS.bit.MCLKSTS )
   {
      /*Missing external clock has been detected
      Replace this line with a call to an appropriate
      SystemShutdown(); function.*/
      asm("        ESTOP0");
   }

   /*DIVSEL MUST be 0 before PLLCR can be changed from
   0x0000. It is set to 0 by an external reset XRSn
   This puts us in 1/4*/
   if ( SYS_SysCtrlRegs.PLLSTS.bit.DIVSEL )
   {
       EALLOW;
       SYS_SysCtrlRegs.PLLSTS.bit.DIVSEL = (UNUM16)0;
       EDIS;
   }

   /*Change the PLLCR*/
   if ((UNUM16)SYS_SysCtrlRegs.PLLCR.bit.DIV != (UNUM16)val)
   {
      EALLOW;
      /*Before setting PLLCR turn off missing clock detect logic*/
      SYS_SysCtrlRegs.PLLSTS.bit.MCLKOFF = (UNUM16)1;
      SYS_SysCtrlRegs.PLLCR.bit.DIV = (UNUM16)val;
      EDIS;

      /*Optional: Wait for PLL to lock.
      During this time the CPU will switch to OSCCLK/2 until
      the PLL is stable.  Once the PLL is stable the CPU will
      switch to the new PLL value.

      This time-to-lock is monitored by a PLL lock counter.

      Code is not required to sit and wait for the PLL to lock.
      However, if the code does anything that is timing critical,
      and requires the correct clock be locked, then it is best to
      wait until this switching has completed.

      Wait for the PLL lock bit to be set.

      The watchdog should be disabled before this loop, or fed within
      the loop via ServiceDog().

	  Uncomment to disable the watchdog*/
      WDG_DisableDog();

      while((UNUM16)SYS_SysCtrlRegs.PLLSTS.bit.PLLLOCKS != (UNUM16)1)
      {
	      /*Uncomment to service the watchdog*/
          /*ServiceDog();*/
      }

      EALLOW;
      SYS_SysCtrlRegs.PLLSTS.bit.MCLKOFF = (UNUM16)0;
      EDIS;
    }

    /*If switching to 1/2*/
	if((divsel == (UNUM16)1)||(divsel == (UNUM16)2))
	{
		EALLOW;
		SYS_SysCtrlRegs.PLLSTS.bit.DIVSEL = divsel;
	    EDIS;
	}
	/*NOTE: ONLY USE THIS SETTING IF PLL IS BYPASSED (I.E. PLLCR = 0) OR OFF
	If switching to 1/1
	First go to 1/2 and let the power settle
	The time required will depend on the system, this is only an example
	Then switch to 1/1*/
	/*if(divsel == (UNUM16)3)
	{
		EALLOW;
		SYS_SysCtrlRegs.PLLSTS.bit.DIVSEL = (UNUM16)2;
	    DELAY_US(50L);
	    SYS_SysCtrlRegs.PLLSTS.bit.DIVSEL = (UNUM16)3;
	    EDIS;
    }*/
}

/*--------------------------------------------------------------------------
Example: Sys_PeripheralClocks_Init:
---------------------------------------------------------------------------
This function initializes the clocks to the peripheral modules.
First the high and low clock prescalers are set
Second the clocks are enabled to each peripheral.
To reduce power, leave clocks to unused peripherals disabled
Note: If a peripherals clock is not enabled then you cannot
read or write to the registers for that peripheral
 ---------------------------------------------------------------------------*/
void SYS_Ctrl_PeripheralClocks_Init( void )
{

   EALLOW;

/* HISPCP/LOSPCP prescale register settings, normally it will be set to default values*/
   SYS_SysCtrlRegs.HISPCP.all = (UNUM16)0x0001;
   SYS_SysCtrlRegs.LOSPCP.all = (UNUM16)0x0002;

/* XCLKOUT to SYSCLKOUT ratio.  By default XCLKOUT = 1/4 SYSCLKOUT*/
   /* XTIMCLK = SYSCLKOUT/2*/
   /*
   XintfRegs.XINTCNF2.bit.XTIMCLK = (UNUM16)1;*/
   /* XCLKOUT = XTIMCLK/2*/
   /*XintfRegs.XINTCNF2.bit.CLKMODE = (UNUM16)1;*/
   /* Enable XCLKOUT*/
 /* XintfRegs.XINTCNF2.bit.CLKOFF = (UNUM16)1;*/

/* Peripheral clock enables set for the selected peripherals.
   If you are not using a peripheral leave the clock off
   to save on power.

   Note: not all peripherals are available on all 2833x derivates.
   Refer to the datasheet for your particular device.

   This function is not written to be an example of efficient code.*/

   SYS_SysCtrlRegs.PCLKCR0.bit.ADCENCLK = (UNUM16)1; /* ADC*/

   /* *IMPORTANT*
   The ADC_cal function, which  copies the ADC calibration values from TI reserved
   OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
   Boot ROM. If the boot ROM code is bypassed during the debug process, the
   following function MUST be called for the ADC to function according
   to specification. The clocks to the ADC MUST be enabled before calling this
   function.
   See the device data manual and/or the ADC Reference
   Manual for more information.*/



   SYS_SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = (UNUM16)1; /* I2C*/
   SYS_SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = (UNUM16)1; /* SCI-A*/
   SYS_SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = (UNUM16)1; /* SCI-B*/
   SYS_SysCtrlRegs.PCLKCR0.bit.SCICENCLK = (UNUM16)1; /* SCI-C*/
   SYS_SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = (UNUM16)1; /* SPI-A*/
   SYS_SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = (UNUM16)1; /* McBSP-A*/
   SYS_SysCtrlRegs.PCLKCR0.bit.MCBSPBENCLK = (UNUM16)1; /* McBSP-B*/
   SYS_SysCtrlRegs.PCLKCR0.bit.ECANAENCLK= (UNUM16)1; /* eCAN-A*/
   SYS_SysCtrlRegs.PCLKCR0.bit.ECANBENCLK= (UNUM16)1; /* eCAN-B*/

   SYS_SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = (UNUM16)0; /* Disable TBCLK within the ePWM*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = (UNUM16)1; /* ePWM1*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = (UNUM16)1; /* ePWM2*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = (UNUM16)1; /* ePWM3*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = (UNUM16)1; /* ePWM4*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = (UNUM16)1; /* ePWM5*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = (UNUM16)1; /* ePWM6*/
   SYS_SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = (UNUM16)1; /* Enable TBCLK within the ePWM*/

   SYS_SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = (UNUM16)1; /* eCAP3*/
   SYS_SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = (UNUM16)1; /* eCAP4*/
   SYS_SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = (UNUM16)1; /* eCAP5*/
   SYS_SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = (UNUM16)1; /* eCAP6*/
   SYS_SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = (UNUM16)1; /* eCAP1*/
   SYS_SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = (UNUM16)1; /* eCAP2*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = (UNUM16)1; /* eQEP1*/
   SYS_SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = (UNUM16)1; /* eQEP2*/

   SYS_SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = (UNUM16)1; /*CPU Timer 0*/
   SYS_SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = (UNUM16)1; /*CPU Timer 1*/
   SYS_SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = (UNUM16)1; /*CPU Timer 2*/

   SYS_SysCtrlRegs.PCLKCR3.bit.DMAENCLK = (UNUM16)1; /*DMA Clock*/
   SYS_SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = (UNUM16)1; /*XTIMCLK*/
   SYS_SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = (UNUM16)1; /*GPIO input clock*/

   EDIS;
}

/***************************************************************************
End of file.
***************************************************************************/
