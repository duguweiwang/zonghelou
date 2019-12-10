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
*     Module Name:         %name:     DEVICE.h %                              *
*     Module Version:      %version:  2 %                                     *
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
#ifndef __DEVICE_H__
#define __DEVICE_H__

/**** definitions*************************************************************/
#ifndef FALSE
#define FALSE     0
#endif

#ifndef TRUE
#define TRUE      1
#endif

#ifndef BIT_SET
#define BIT_SET   1
#endif

#ifndef BIT_CLEAR
#define BIT_CLEAR 0
#endif

#define  EINT  do {asm(" clrc INTM ");} while(0)
#define  DINT   do {asm(" setc INTM ");} while(0)
#define  ERTM   do {asm(" clrc DBGM ");} while(0)
#define  DRTM   do {asm(" setc DBGM ");} while(0)
#define  EALLOW do {asm(" EALLOW ");} while(0)
#define  EDIS   do {asm(" EDIS ");} while(0)
#define  ESTOP0 do {asm(" ESTOP0 ");} while(0)

#define  SCHEDULER_Main    (main)
#define STATIC
#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

/*---------------------------------------------------------------------------
For Portability, User Is Recommended To Use Following Data Type Size
Definitions For 16-bit and 32-Bit Signed/Unsigned Integers:
---------------------------------------------------------------------------*/
typedef unsigned char       UCHAR;
typedef int                 SNUM16;
typedef long                SNUM32;
typedef long long           SNUM64;
typedef unsigned int        UNUM16;
typedef unsigned long       UNUM32;
typedef unsigned long long  UNUM64;
typedef float               FLOAT32;
typedef long double         FLOAT64;

#define DSP28_EQEP1  1
#define DSP28_EQEP2  1
#define DSP28_MCBSPA 1
#define DSP28_MCBSPB 1
#define DSP28_SPIA   1
#define DSP28_SCIA   1
#define DSP28_SCIB   1
#define DSP28_SCIC   1
#define DSP28_I2CA   1

/*---------------------------------------------------------------------------
Device Emulation Register Bit Definitions:
Device Configuration Register Bit Definitions
---------------------------------------------------------------------------*/
struct DEVICECNF_BITS
{ /* bits  description*/
   UNUM16 rsvd1:3; /* 2:0   reserved*/
   UNUM16 VMAPS:1; /* 3     VMAP Status*/
   UNUM16 rsvd2:1; /* 4     reserved*/
   UNUM16 XRSn:1; /* 5     XRSn Signal Status*/
   UNUM16 rsvd3:10; /* 15:6*/
   UNUM16 rsvd4:3; /* 18:16*/
   UNUM16 ENPROT:1; /* 19    Enable/Disable pipeline protection*/
   UNUM16 rsvd5:7; /* 26:20 reserved*/
   UNUM16 TRSTN:1; /* 27    Status of TRSTn signal*/
   UNUM16 rsvd6:4; /* 31:28 reserved*/
};

union DEVICECNF_REG
{
   UNUM32                 all;
   struct DEVICECNF_BITS  bit;
};

/* CLASSID*/
struct CLASSID_BITS
{ /* bits  description */
   UNUM16 CLASSNO:8; /* 7:0   Class Number */
   UNUM16 PARTTYPE:8; /* 15:8  Part Type */
};

union CLASSID_REG
{
   UNUM16               all;
   struct CLASSID_BITS  bit;
};

struct DEV_EMU_REGS
{
   union DEVICECNF_REG DEVICECNF; /* device configuration */
   union CLASSID_REG   CLASSID; /* Class ID */
   UNUM16              REVID; /* Device ID */
   UNUM16              PROTSTART; /* Write-Read protection start */
   UNUM16              PROTRANGE; /* Write-Read protection range */
   UNUM16              rsvd2[202];
};

/* PARTID*/
struct PARTID_BITS
{ /* bits  description */
   UNUM16 PARTNO:8; /* 7:0   Part Number */
   UNUM16 PARTTYPE:8; /* 15:8  Part Type */
};

union PARTID_REG
{
   UNUM16               all;
   struct PARTID_BITS   bit;
};

struct PARTID_REGS
{
   union PARTID_REG PARTID; /* Part ID */
};

extern volatile struct DEV_EMU_REGS DevEmuRegs;
extern volatile struct PARTID_REGS PartIdRegs;

#endif

/***************************************************************************
End of file.
***************************************************************************/
