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
*     Module Name:         %name:     PIE_CTRL.h %                            *
*     Module Version:      %version:  2 %                                 *
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
*                 %created_by:   maolei %                                      *
*                                    									      *									  
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 % 			      *
*                                                                             *  
******************************************************************************/

#ifndef __PIE_CTRL_H__
#define __PIE_CTRL_H__

/**** includes ***************************************************************/
#include "DEVICE.h"

/**** definitions*************************************************************/

/*---------------------------------------------------------------------------
PIE Control Register Bit Definitions:
---------------------------------------------------------------------------*/
/* PIECTRL: Register bit definitions:*/
struct PIECTRL_BITS
{ /* bits description*/
   UNUM16  ENPIE:1;        /* 0    Enable PIE block*/
   UNUM16  PIEVECT:15;     /* 15:1 Fetched vector address*/
};

union PIECTRL_REG
{
   UNUM16               all;
   struct PIECTRL_BITS  bit;
};  

/*PIEIER: Register bit definitions:*/
struct PIEIER_BITS
{ /* bits description*/
   UNUM16 INTx1:1;         /* 0    INTx.1*/
   UNUM16 INTx2:1;         /* 1    INTx.2*/
   UNUM16 INTx3:1;         /* 2    INTx.3*/
   UNUM16 INTx4:1;         /* 3    INTx.4*/
   UNUM16 INTx5:1;         /* 4    INTx.5*/
   UNUM16 INTx6:1;         /* 5    INTx.6*/
   UNUM16 INTx7:1;         /* 6    INTx.7*/
   UNUM16 INTx8:1;         /* 7    INTx.8*/
   UNUM16 rsvd:8;          /* 15:8 reserved*/
};

union PIEIER_REG
{
   UNUM16              all;
   struct PIEIER_BITS  bit;
}; 

/*PIEIFR: Register bit definitions:*/
struct PIEIFR_BITS
{ /* bits description*/
   UNUM16 INTx1:1;         /* 0    INTx.1*/
   UNUM16 INTx2:1;         /* 1    INTx.2*/
   UNUM16 INTx3:1;         /* 2    INTx.3*/
   UNUM16 INTx4:1;         /* 3    INTx.4*/
   UNUM16 INTx5:1;         /* 4    INTx.5*/
   UNUM16 INTx6:1;         /* 5    INTx.6*/
   UNUM16 INTx7:1;         /* 6    INTx.7*/
   UNUM16 INTx8:1;         /* 7    INTx.8*/
   UNUM16 rsvd:8;          /* 15:8 reserved*/
};

union PIEIFR_REG
{
   UNUM16              all;
   struct PIEIFR_BITS  bit;
};

/* PIEACK: Register bit definitions:*/
struct PIEACK_BITS
{ /* bits description*/
   UNUM16 ACK1:1;          /* 0    Acknowledge PIE interrupt group 1*/
   UNUM16 ACK2:1;          /* 1    Acknowledge PIE interrupt group 2*/
   UNUM16 ACK3:1;          /* 2    Acknowledge PIE interrupt group 3*/
   UNUM16 ACK4:1;          /* 3    Acknowledge PIE interrupt group 4*/
   UNUM16 ACK5:1;          /* 4    Acknowledge PIE interrupt group 5*/
   UNUM16 ACK6:1;          /* 5    Acknowledge PIE interrupt group 6*/
   UNUM16 ACK7:1;          /* 6    Acknowledge PIE interrupt group 7*/
   UNUM16 ACK8:1;          /* 7    Acknowledge PIE interrupt group 8*/
   UNUM16 ACK9:1;          /* 8    Acknowledge PIE interrupt group 9*/
   UNUM16 ACK10:1;         /* 9    Acknowledge PIE interrupt group 10*/
   UNUM16 ACK11:1;         /* 10   Acknowledge PIE interrupt group 11*/
   UNUM16 ACK12:1;         /* 11   Acknowledge PIE interrupt group 12*/
   UNUM16 rsvd:4;          /* 15:12 reserved*/
};

union PIEACK_REG
{
   UNUM16              all;
   struct PIEACK_BITS  bit;
};

/*---------------------------------------------------------------------------
PIE Control Register File:
---------------------------------------------------------------------------*/
struct PIE_CTRL_REGS
{
   union PIECTRL_REG PIECTRL;       /* PIE control register*/
   union PIEACK_REG  PIEACK;        /* PIE acknowledge*/
   union PIEIER_REG  PIEIER1;       /* PIE int1 IER register*/
   union PIEIFR_REG  PIEIFR1;       /* PIE int1 IFR register*/
   union PIEIER_REG  PIEIER2;       /* PIE INT2 IER register*/
   union PIEIFR_REG  PIEIFR2;       /* PIE INT2 IFR register*/
   union PIEIER_REG  PIEIER3;       /* PIE INT3 IER register*/
   union PIEIFR_REG  PIEIFR3;       /* PIE INT3 IFR register*/
   union PIEIER_REG  PIEIER4;       /* PIE INT4 IER register*/
   union PIEIFR_REG  PIEIFR4;       /* PIE INT4 IFR register*/
   union PIEIER_REG  PIEIER5;       /* PIE INT5 IER register*/
   union PIEIFR_REG  PIEIFR5;       /* PIE INT5 IFR register*/
   union PIEIER_REG  PIEIER6;       /* PIE INT6 IER register*/
   union PIEIFR_REG  PIEIFR6;       /* PIE INT6 IFR register*/
   union PIEIER_REG  PIEIER7;       /* PIE INT7 IER register*/
   union PIEIFR_REG  PIEIFR7;       /* PIE INT7 IFR register*/
   union PIEIER_REG  PIEIER8;       /* PIE INT8 IER register*/
   union PIEIFR_REG  PIEIFR8;       /* PIE INT8 IFR register*/
   union PIEIER_REG  PIEIER9;       /* PIE INT9 IER register*/
   union PIEIFR_REG  PIEIFR9;       /* PIE INT9 IFR register*/
   union PIEIER_REG  PIEIER10;      /* PIE int10 IER register*/
   union PIEIFR_REG  PIEIFR10;      /* PIE int10 IFR register*/
   union PIEIER_REG  PIEIER11;      /* PIE int11 IER register*/
   union PIEIFR_REG  PIEIFR11;      /* PIE int11 IFR register*/
   union PIEIER_REG  PIEIER12;      /* PIE int12 IER register*/
   union PIEIFR_REG  PIEIFR12;      /* PIE int12 IFR register*/
};     

extern volatile struct PIE_CTRL_REGS PIE_CTRL_PieCtrlRegs;

#endif

/***************************************************************************
End of file.
***************************************************************************/
