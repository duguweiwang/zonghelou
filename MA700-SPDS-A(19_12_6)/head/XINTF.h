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
*     Module Name:         %name:     XINTF.h %                               *
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
*                 %created_by:  maolei %                                       *
*                                                                             *                                      
*     Date:       %date_modified:  Tue Jun 26 18:04:37 2012 %                 *
*                                                                             *
******************************************************************************/

#ifndef __XINTF_H__
#define __XINTF_H__


/**** includes ***************************************************************/
#include "DEVICE.h"

/**** definitions*************************************************************/


/* XINTF timing register bit definitions:*/
struct XTIMING_BITS
{ /* bits  description*/
   UNUM16 XWRTRAIL:2;    /* 1:0   Write access trail timing*/
   UNUM16 XWRACTIVE:3;   /* 4:2   Write access active timing*/
   UNUM16 XWRLEAD:2;     /* 6:5   Write access lead timing*/
   UNUM16 XRDTRAIL:2;    /* 8:7   Read access trail timing*/
   UNUM16 XRDACTIVE:3;   /* 11:9  Read access active timing*/
   UNUM16 XRDLEAD:2;     /* 13:12 Read access lead timing*/
   UNUM16 USEREADY:1;    /* 14    Extend access using HW waitstates*/
   UNUM16 READYMODE:1;   /* 15    Ready mode*/
   UNUM16 XSIZE:2;       /* 17:16 XINTF bus width - must be written as 11b*/
   UNUM16 rsvd1:4;       /* 21:18 reserved*/
   UNUM16 X2TIMING:1;    /* 22    Double lead/active/trail timing*/
   UNUM16 rsvd3:9;       /* 31:23 reserved*/
};

union XTIMING_REG
{
   UNUM32               all;
   struct XTIMING_BITS  bit;
};

/* XINTF control register bit definitions:*/
struct XINTCNF2_BITS
{ /* bits  description*/
   UNUM16 WRBUFF:2;       /* 1:0   Write buffer depth*/
   UNUM16 CLKMODE:1;      /* 2     Ratio for XCLKOUT with respect to XTIMCLK*/
   UNUM16 CLKOFF:1;       /* 3     Disable XCLKOUT*/
   UNUM16 rsvd1:2;        /* 5:4   reserved*/
   UNUM16 WLEVEL:2;       /* 7:6   Current level of the write buffer*/
   UNUM16 rsvd2:1;        /* 8     reserved*/
   UNUM16 HOLD:1;         /* 9     Hold enable/disable*/
   UNUM16 HOLDS:1;        /* 10    Current state of HOLDn input*/
   UNUM16 HOLDAS:1;       /* 11    Current state of HOLDAn output*/
   UNUM16 rsvd3:4;        /* 15:12 reserved*/
   UNUM16 XTIMCLK:3;      /* 18:16 Ratio for XTIMCLK*/
   UNUM16 rsvd4:13;       /* 31:19 reserved*/
};

union XINTCNF2_REG
{
   UNUM32                all;
   struct XINTCNF2_BITS  bit;
};

/* XINTF bank switching register bit definitions:*/
struct XBANK_BITS
{ /* bits  description*/
   UNUM16  BANK:3;       /* 2:0   Zone for which banking is enabled*/
   UNUM16  BCYC:3;       /* 5:3   XTIMCLK cycles to add*/
   UNUM16  rsvd:10;      /* 15:6  reserved*/
};

union XBANK_REG
{
   UNUM16             all;
   struct XBANK_BITS  bit;
};

struct XRESET_BITS
{
    UNUM16  XHARDRESET:1;
    UNUM16  rsvd1:15;
};

union XRESET_REG
{
    UNUM16            all;
    struct XRESET_BITS bit;
};

/*---------------------------------------------------------------------------
XINTF Register File:
---------------------------------------------------------------------------*/
struct XINTF_REGS
{
   union XTIMING_REG XTIMING0;
   UNUM32  rsvd1[5];
   union XTIMING_REG XTIMING6;
   union XTIMING_REG XTIMING7;
   UNUM32  rsvd2[2];
   union XINTCNF2_REG XINTCNF2;
   UNUM32  rsvd3;
   union XBANK_REG    XBANK;
   UNUM16  rsvd4;
   UNUM16  XREVISION;
   UNUM16  rsvd5[2];
   union XRESET_REG   XRESET;
};

extern UNUM16 XINTF_XintffuncsLoadStart;
extern UNUM16 XINTF_XintffuncsLoadEnd;
extern UNUM16 XINTF_XintffuncsRunStart;

/**** functions declarations *************************************************/
extern void XINTF_InitXIntrupt( void );

extern void XINTF_XintfInit( void );

extern void XINTF_InitXintf16Gpio( void );

extern void XINTF_InitXintf32Gpio( void );

extern volatile struct XINTF_REGS XintfRegs;

#endif

/***************************************************************************
End of file.
***************************************************************************/
