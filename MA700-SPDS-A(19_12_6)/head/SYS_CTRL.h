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
*     Module Description:                                                     *
*     Module Name:         %name:     SYS_CTRL.h %                            *
*     Module Version:      %version:  2 %                                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	 		                                                      *
*                                                                             * 
*     Controller:                                                             *
*                                                                             * 
*-----------------------------------------------------------------------------*
*                                                                             *   
*     Author:                                                                 *
*                 %created_by:   maolei %                                      *
*                                    									      *									  
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 % 			      *
*                                                                             *  
******************************************************************************/
#ifndef __SYS_CTRL_H__
#define __SYS_CTRL_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"

/**** definitions*************************************************************/

/*---------------------------------------------------------------------------
System Control Individual Register Bit Definitions:
---------------------------------------------------------------------------*/
/* PLL Status Register*/
struct PLLSTS_BITS
{ /* bits  description*/
   UNUM16 PLLLOCKS:1;     /* 0     PLL lock status*/
   UNUM16 rsvd1:1;        /* 1     reserved*/
   UNUM16 PLLOFF:1;       /* 2     PLL off bit*/
   UNUM16 MCLKSTS:1;      /* 3     Missing clock status bit*/
   UNUM16 MCLKCLR:1;      /* 4     Missing clock clear bit*/
   UNUM16 OSCOFF:1;       /* 5     Oscillator clock off*/
   UNUM16 MCLKOFF:1;      /* 6     Missing clock detect*/
   UNUM16 DIVSEL:2;       /* 7     Divide Select*/
   UNUM16 rsvd2:7;        /* 15:7  reserved*/
};

union PLLSTS_REG
{
   UNUM16              all;
   struct PLLSTS_BITS  bit;
};

/* High speed peripheral clock register bit definitions:*/
struct HISPCP_BITS
{ /* bits  description*/
   UNUM16 HSPCLK:3;     /* 2:0   Rate relative to SYSCLKOUT*/
   UNUM16 rsvd1:13;     /* 15:3  reserved*/
};

union HISPCP_REG
{
   UNUM16              all;
   struct HISPCP_BITS  bit;
};

/* Low speed peripheral clock register bit definitions:*/
struct LOSPCP_BITS
{ /* bits  description*/
   UNUM16 LSPCLK:3;     /* 2:0   Rate relative to SYSCLKOUT*/
   UNUM16 rsvd1:13;     /* 15:3  reserved*/
};

union LOSPCP_REG
{
   UNUM16              all;
   struct LOSPCP_BITS  bit;
};

/* Peripheral clock control register 0 bit definitions:*/
struct PCLKCR0_BITS
{ /* bits  description*/
   UNUM16 rsvd1:2;       /* 1:0   reserved*/
   UNUM16 TBCLKSYNC:1;   /* 2     EWPM Module TBCLK enable/sync*/
   UNUM16 ADCENCLK:1;    /* 3     Enable high speed clk to ADC*/
   UNUM16 I2CAENCLK:1;   /* 4     Enable SYSCLKOUT to I2C-A*/
   UNUM16 SCICENCLK:1;   /* 5     Enalbe low speed clk to SCI-C*/
   UNUM16 rsvd2:2;       /* 7:6   reserved*/
   UNUM16 SPIAENCLK:1;   /* 8     Enable low speed clk to SPI-A*/
   UNUM16 rsvd3:1;       /* 9     reserved*/
   UNUM16 SCIAENCLK:1;   /* 10    Enable low speed clk to SCI-A*/
   UNUM16 SCIBENCLK:1;   /* 11    Enable low speed clk to SCI-B*/
   UNUM16 MCBSPAENCLK:1; /* 12    Enable low speed clk to McBSP-A*/
   UNUM16 MCBSPBENCLK:1; /* 13    Enable low speed clk to McBSP-B*/
   UNUM16 ECANAENCLK:1;  /* 14    Enable system clk to eCAN-A*/
   UNUM16 ECANBENCLK:1;  /* 15    Enable system clk to eCAN-B*/
};

union PCLKCR0_REG
{
   UNUM16              all;
   struct PCLKCR0_BITS bit;
};

/* Peripheral clock control register 1 bit definitions:*/
struct PCLKCR1_BITS
{ /* bits  description*/
   UNUM16 EPWM1ENCLK:1;   /* 0     Enable SYSCLKOUT to EPWM1*/
   UNUM16 EPWM2ENCLK:1;   /* 1     Enable SYSCLKOUT to EPWM2*/
   UNUM16 EPWM3ENCLK:1;   /* 2     Enable SYSCLKOUT to EPWM3*/
   UNUM16 EPWM4ENCLK:1;   /* 3     Enable SYSCLKOUT to EPWM4*/
   UNUM16 EPWM5ENCLK:1;   /* 4     Enable SYSCLKOUT to EPWM5*/
   UNUM16 EPWM6ENCLK:1;   /* 5     Enable SYSCLKOUT to EPWM6*/
   UNUM16 rsvd1:2;        /* 7:6   reserved*/
   UNUM16 ECAP1ENCLK:1;   /* 8     Enable SYSCLKOUT to ECAP1*/
   UNUM16 ECAP2ENCLK:1;   /* 9     Enable SYSCLKOUT to ECAP2*/
   UNUM16 ECAP3ENCLK:1;   /* 10    Enable SYSCLKOUT to ECAP3*/
   UNUM16 ECAP4ENCLK:1;   /* 11    Enable SYSCLKOUT to ECAP4*/
   UNUM16 ECAP5ENCLK:1;   /* 12    Enable SYSCLKOUT to ECAP5*/
   UNUM16 ECAP6ENCLK:1;   /* 13    Enable SYSCLKOUT to ECAP6*/
   UNUM16 EQEP1ENCLK:1;   /* 14    Enable SYSCLKOUT to EQEP1*/
   UNUM16 EQEP2ENCLK:1;   /* 15    Enable SYSCLKOUT to EQEP2*/
};

union PCLKCR1_REG
{
   UNUM16              all;
   struct PCLKCR1_BITS bit;
};

/* Peripheral clock control register 2 bit definitions:*/
struct PCLKCR3_BITS
{ /* bits  description*/
   UNUM16 rsvd1:8;            /* 7:0   reserved*/
   UNUM16 CPUTIMER0ENCLK:1;   /* 8     Enable SYSCLKOUT to CPU-Timer 0*/
   UNUM16 CPUTIMER1ENCLK:1;   /* 9     Enable SYSCLKOUT to CPU-Timer 1*/
   UNUM16 CPUTIMER2ENCLK:1;   /* 10    Enable SYSCLKOUT to CPU-Timer 2*/
   UNUM16 DMAENCLK:1;         /* 11    Enable the DMA clock*/
   UNUM16 XINTFENCLK:1;       /* 12    Enable SYSCLKOUT to XINTF*/
   UNUM16 GPIOINENCLK:1;      /*       Enable GPIO input clock*/
   UNUM16 rsvd2:2;            /* 15:14 reserved*/
};

union PCLKCR3_REG
{
   UNUM16              all;
   struct PCLKCR3_BITS bit;
};

/* PLL control register bit definitions:*/
struct PLLCR_BITS
{ /* bits  description*/
   UNUM16 DIV:4;         /* 3:0   Set clock ratio for the PLL*/
   UNUM16 rsvd1:12;      /* 15:4  reserved*/
};

union PLLCR_REG
{
   UNUM16             all;
   struct PLLCR_BITS  bit;
};

/* Low Power Mode 0 control register bit definitions:*/
struct LPMCR0_BITS
{ /* bits  description*/
   UNUM16 LPM:2;         /* 1:0   Set the low power mode*/
   UNUM16 QUALSTDBY:6;   /* 7:2   Qualification*/
   UNUM16 rsvd1:7;       /* 14:8  reserved*/
   UNUM16 WDINTE:1;      /* 15    Enables WD to wake the device from STANDBY*/
};

union LPMCR0_REG
{
   UNUM16              all;
   struct LPMCR0_BITS  bit;
};

/* Dual-mapping configuration register bit definitions:*/
struct MAPCNF_BITS
{ /* bits  description*/
    UNUM16 MAPEPWM:1;    /* 0     EPWM dual-map enable*/
    UNUM16 rsvd1:15;     /* 15:1  reserved*/
};

union MAPCNF_REG
{
	UNUM16             all;
	struct MAPCNF_BITS bit;
};

/*---------------------------------------------------------------------------
System Control Register File:
---------------------------------------------------------------------------*/
struct SYS_CTRL_REGS
{
   UNUM16              rsvd1;     /* 0*/
   union   PLLSTS_REG  PLLSTS;    /* 1*/
   UNUM16              rsvd2[8];  /* 2-9*/
   union   HISPCP_REG  HISPCP;    /* 10: High-speed peripheral clock pre-scaler*/
   union   LOSPCP_REG  LOSPCP;    /* 11: Low-speed peripheral clock pre-scaler*/
   union   PCLKCR0_REG PCLKCR0;   /* 12: Peripheral clock control register*/
   union   PCLKCR1_REG PCLKCR1;   /* 13: Peripheral clock control register*/
   union   LPMCR0_REG  LPMCR0;    /* 14: Low-power mode control register 0*/
   UNUM16              rsvd3;     /* 15: reserved*/
   union   PCLKCR3_REG PCLKCR3;   /* 16: Peripheral clock control register*/
   union   PLLCR_REG   PLLCR;     /* 17: PLL control register*/
   /* No bit definitions are defined for SCSR because*/
   /* a read-modify-write instruction can clear the WDOVERRIDE bit*/
   UNUM16              SCSR;      /* 18: System control and status register*/
   UNUM16              WDCNTR;    /* 19: WD counter register*/
   UNUM16              rsvd4;     /* 20*/
   UNUM16              WDKEY;     /* 21: WD reset key register*/
   UNUM16              rsvd5[3];  /* 22-24*/
   /* No bit definitions are defined for WDCR because*/
   /* the proper value must be written to the WDCHK field*/
   /* whenever writing to this register.*/
   UNUM16              WDCR;      /* 25: WD timer control register*/
   UNUM16              rsvd6[4];  /* 26-29*/
   union   MAPCNF_REG  MAPCNF;    /* 30: Dual-mapping configuration register*/
   UNUM16              rsvd7[1];  /* 31*/
};

/* --------------------------------------------------- */
/* CSM Registers                                       */
/* ----------------------------------------------------*/

/* CSM Status & Control register bit definitions */
struct  CSMSCR_BITS
{ /* bit   description*/
   UNUM16     SECURE:1;    /* 0     Secure flag*/
   UNUM16     rsvd1:14;    /* 14-1  reserved*/
   UNUM16     FORCESEC:1;  /* 15    Force Secure control bit*/
};

/* Allow access to the bit fields or entire register */
union CSMSCR_REG
{
   UNUM16             all;
   struct CSMSCR_BITS bit;
};

/* CSM Register File */
struct  CSM_REGS
{
   UNUM16           KEY0;    /* KEY reg bits 15-0*/
   UNUM16           KEY1;    /* KEY reg bits 31-16*/
   UNUM16           KEY2;    /* KEY reg bits 47-32*/
   UNUM16           KEY3;    /* KEY reg bits 63-48*/
   UNUM16           KEY4;    /* KEY reg bits 79-64*/
   UNUM16           KEY5;    /* KEY reg bits 95-80*/
   UNUM16           KEY6;    /* KEY reg bits 111-96*/
   UNUM16           KEY7;    /* KEY reg bits 127-112*/
   UNUM16           rsvd1;   /* reserved*/
   UNUM16           rsvd2;   /* reserved*/
   UNUM16           rsvd3;   /* reserved*/
   UNUM16           rsvd4;   /* reserved*/
   UNUM16           rsvd5;   /* reserved*/
   UNUM16           rsvd6;   /* reserved*/
   UNUM16           rsvd7;   /* reserved*/
   union CSMSCR_REG CSMSCR;  /* CSM Status & Control register*/
};

/* Password locations */
struct  CSM_PWL
{
   UNUM16   PSWD0;  /* PSWD bits 15-0*/
   UNUM16   PSWD1;  /* PSWD bits 31-16*/
   UNUM16   PSWD2;  /* PSWD bits 47-32*/
   UNUM16   PSWD3;  /* PSWD bits 63-48*/
   UNUM16   PSWD4;  /* PSWD bits 79-64*/
   UNUM16   PSWD5;  /* PSWD bits 95-80*/
   UNUM16   PSWD6;  /* PSWD bits 111-96*/
   UNUM16   PSWD7;  /* PSWD bits 127-112*/
};

/* Flash Registers */

/*#define FLASH_SLEEP       0x0000*/
/*#define FLASH_STANDBY     0x0001*/
/*#define FLASH_ACTIVE      0x0003*/

/* Flash Option Register bit definitions */
struct  FOPT_BITS
{ /* bit   description*/
   UNUM16     ENPIPE:1;   /* 0     Enable Pipeline Mode*/
   UNUM16     rsvd:15;    /* 1-15  reserved*/
};

/* Allow access to the bit fields or entire register */
union FOPT_REG
{
   UNUM16           all;
   struct FOPT_BITS bit;
};

/* Flash Power Modes Register bit definitions */
struct  FPWR_BITS
{ /* bit   description*/
   UNUM16     PWR:2;      /* 0-1   Power Mode bits*/
   UNUM16     rsvd:14;    /* 2-15  reserved*/
};

/* Allow access to the bit fields or entire register */
union FPWR_REG
{
   UNUM16           all;
   struct FPWR_BITS bit;
};

/* Flash Status Register bit definitions */
struct  FSTATUS_BITS
{ /* bit   description*/
   UNUM16     PWRS:2;        /* 0-1   Power Mode Status bits*/
   UNUM16     STDBYWAITS:1;  /* 2     Bank/Pump Sleep to Standby Wait Counter Status bits*/
   UNUM16     ACTIVEWAITS:1; /* 3     Bank/Pump Standby to Active Wait Counter Status bits*/
   UNUM16     rsvd1:4;       /* 4-7   reserved*/
   UNUM16     V3STAT:1;      /* 8     VDD3V Status Latch bit*/
   UNUM16     rsvd2:7;       /* 9-15  reserved*/
};

/* Allow access to the bit fields or entire register */
union FSTATUS_REG
{
   UNUM16              all;
   struct FSTATUS_BITS bit;
};

/* Flash Sleep to Standby Wait Counter Register bit definitions */
struct  FSTDBYWAIT_BITS
{    /* bit   description*/
   UNUM16     STDBYWAIT:9;   /* 0-8   Bank/Pump Sleep to Standby Wait Count bits*/
   UNUM16     rsvd:7;        /* 9-15  reserved*/
};

/* Allow access to the bit fields or entire register */
union FSTDBYWAIT_REG
{
   UNUM16                 all;
   struct FSTDBYWAIT_BITS bit;
};

/* Flash Standby to Active Wait Counter Register bit definitions */
struct  FACTIVEWAIT_BITS
{ /* bit   description*/
   UNUM16     ACTIVEWAIT:9;  /* 0-8   Bank/Pump Standby to Active Wait Count bits*/
   UNUM16     rsvd:7;        /* 9-15  reserved*/
};

/* Allow access to the bit fields or entire register */
union FACTIVEWAIT_REG
{
   UNUM16                  all;
   struct FACTIVEWAIT_BITS bit;
};

/* Bank Read Access Wait State Register bit definitions */
struct  FBANKWAIT_BITS
{ /* bit   description*/
   UNUM16     RANDWAIT:4;    /* 0-3   Flash Random Read Wait State bits*/
   UNUM16     rsvd1:4;       /* 4-7   reserved*/
   UNUM16     PAGEWAIT:4;    /* 8-11  Flash Paged Read Wait State bits*/
   UNUM16     rsvd2:4;       /* 12-15 reserved*/
};

/* Allow access to the bit fields or entire register */
union FBANKWAIT_REG
{
   UNUM16                all;
   struct FBANKWAIT_BITS bit;
};

/* OTP Read Access Wait State Register bit definitions */
struct  FOTPWAIT_BITS
{ /* bit   description*/
   UNUM16     OTPWAIT:5;     /* 0-4   OTP Read Wait State bits*/
   UNUM16     rsvd:11;       /* 5-15  reserved*/
};

/* Allow access to the bit fields or entire register */
union FOTPWAIT_REG
{
   UNUM16               all;
   struct FOTPWAIT_BITS bit;
};

struct FLASH_REGS
{
   union FOPT_REG        FOPT;        /* Option Register*/
   UNUM16                rsvd1;       /* reserved*/
   union FPWR_REG        FPWR;        /* Power Modes Register*/
   union FSTATUS_REG     FSTATUS;     /* Status Register*/
   union FSTDBYWAIT_REG  FSTDBYWAIT;  /* Pump/Bank Sleep to Standby Wait State Register*/
   union FACTIVEWAIT_REG FACTIVEWAIT; /* Pump/Bank Standby to Active Wait State Register*/
   union FBANKWAIT_REG   FBANKWAIT;   /* Bank Read Access Wait State Register*/
   union FOTPWAIT_REG    FOTPWAIT;    /* OTP Read Access Wait State Register*/
};

extern volatile struct CSM_PWL SYS_CsmPwl;
extern volatile struct CSM_REGS SYS_CsmRegs;
extern volatile struct SYS_CTRL_REGS SYS_SysCtrlRegs;
extern volatile struct FLASH_REGS SYS_FlashRegs;

#endif

/***************************************************************************
End of file.
***************************************************************************/

