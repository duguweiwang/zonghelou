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
*     Module Description:  module to provide a real time scheduler            *
*     Module Name:         %name:     ECAN.h %                                *
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
*                 %created_by:   maolei %                                      *
*                                    									      *									  
*     Date:       %date_modified:  2013-10-08 %                 			  *
*                                                                             *  
******************************************************************************/

#ifndef __ECAN_H__
#define __ECAN_H__

/**** definitions*************************************************************/

/* -----------------------------------------------------*/
/* eCAN Control & Status Registers                      */
/* -----------------------------------------------------*/
/* eCAN Mailbox enable register (CANME) bit definitions */
struct  CANME_BITS
{ /* bit  description */
   UNUM16      ME0:1; /* 0   Enable Mailbox 0 */
   UNUM16      ME1:1; /* 1   Enable Mailbox 1 */
   UNUM16      ME2:1; /* 2   Enable Mailbox 2 */
   UNUM16      ME3:1; /* 3   Enable Mailbox 3 */
   UNUM16      ME4:1; /* 4   Enable Mailbox 4 */
   UNUM16      ME5:1; /* 5   Enable Mailbox 5 */
   UNUM16      ME6:1; /* 6   Enable Mailbox 6 */
   UNUM16      ME7:1; /* 7   Enable Mailbox 7 */
   UNUM16      ME8:1; /* 8   Enable Mailbox 8 */
   UNUM16      ME9:1; /* 9   Enable Mailbox 9 */
   UNUM16      ME10:1; /* 10  Enable Mailbox 10 */
   UNUM16      ME11:1; /* 11  Enable Mailbox 11 */
   UNUM16      ME12:1; /* 12  Enable Mailbox 12 */
   UNUM16      ME13:1; /* 13  Enable Mailbox 13 */
   UNUM16      ME14:1; /* 14  Enable Mailbox 14 */
   UNUM16      ME15:1; /* 15  Enable Mailbox 15 */
   UNUM16      ME16:1; /* 16  Enable Mailbox 16 */
   UNUM16      ME17:1; /* 17  Enable Mailbox 17 */
   UNUM16      ME18:1; /* 18  Enable Mailbox 18 */
   UNUM16      ME19:1; /* 19  Enable Mailbox 19 */
   UNUM16      ME20:1; /* 20  Enable Mailbox 20 */
   UNUM16      ME21:1; /* 21  Enable Mailbox 21 */
   UNUM16      ME22:1; /* 22  Enable Mailbox 22 */
   UNUM16      ME23:1; /* 23  Enable Mailbox 23 */
   UNUM16      ME24:1; /* 24  Enable Mailbox 24 */
   UNUM16      ME25:1; /* 25  Enable Mailbox 25 */
   UNUM16      ME26:1; /* 26  Enable Mailbox 26 */
   UNUM16      ME27:1; /* 27  Enable Mailbox 27 */
   UNUM16      ME28:1; /* 28  Enable Mailbox 28 */
   UNUM16      ME29:1; /* 29  Enable Mailbox 29 */
   UNUM16      ME30:1; /* 30  Enable Mailbox 30 */
   UNUM16      ME31:1; /* 31  Enable Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANME_REG
{
   UNUM32             all;
   struct CANME_BITS  bit;
};

/* eCAN Mailbox direction register (CANMD) bit definitions */
struct  CANMD_BITS
{ /* bit  description */
   UNUM16      MD0:1; /* 0   0 -> Tx 1 -> Rx */
   UNUM16      MD1:1; /* 1   0 -> Tx 1 -> Rx */
   UNUM16      MD2:1; /* 2   0 -> Tx 1 -> Rx */
   UNUM16      MD3:1; /* 3   0 -> Tx 1 -> Rx */
   UNUM16      MD4:1; /* 4   0 -> Tx 1 -> Rx */
   UNUM16      MD5:1; /* 5   0 -> Tx 1 -> Rx */
   UNUM16      MD6:1; /* 6   0 -> Tx 1 -> Rx */
   UNUM16      MD7:1; /* 7   0 -> Tx 1 -> Rx */
   UNUM16      MD8:1; /* 8   0 -> Tx 1 -> Rx */
   UNUM16      MD9:1; /* 9   0 -> Tx 1 -> Rx */
   UNUM16      MD10:1; /* 10  0 -> Tx 1 -> Rx */
   UNUM16      MD11:1; /* 11  0 -> Tx 1 -> Rx */
   UNUM16      MD12:1; /* 12  0 -> Tx 1 -> Rx */
   UNUM16      MD13:1; /* 13  0 -> Tx 1 -> Rx */
   UNUM16      MD14:1; /* 14  0 -> Tx 1 -> Rx */
   UNUM16      MD15:1; /* 15  0 -> Tx 1 -> Rx */
   UNUM16      MD16:1; /* 16  0 -> Tx 1 -> Rx */
   UNUM16      MD17:1; /* 17  0 -> Tx 1 -> Rx */
   UNUM16      MD18:1; /* 18  0 -> Tx 1 -> Rx */
   UNUM16      MD19:1; /* 19  0 -> Tx 1 -> Rx */
   UNUM16      MD20:1; /* 20  0 -> Tx 1 -> Rx */
   UNUM16      MD21:1; /* 21  0 -> Tx 1 -> Rx */
   UNUM16      MD22:1; /* 22  0 -> Tx 1 -> Rx */
   UNUM16      MD23:1; /* 23  0 -> Tx 1 -> Rx */
   UNUM16      MD24:1; /* 24  0 -> Tx 1 -> Rx */
   UNUM16      MD25:1; /* 25  0 -> Tx 1 -> Rx */
   UNUM16      MD26:1; /* 26  0 -> Tx 1 -> Rx */
   UNUM16      MD27:1; /* 27  0 -> Tx 1 -> Rx */
   UNUM16      MD28:1; /* 28  0 -> Tx 1 -> Rx */
   UNUM16      MD29:1; /* 29  0 -> Tx 1 -> Rx */
   UNUM16      MD30:1; /* 30  0 -> Tx 1 -> Rx */
   UNUM16      MD31:1; /* 31  0 -> Tx 1 -> Rx */
};

/* Allow access to the bit fields or entire register */
union CANMD_REG
{
   UNUM32             all;
   struct CANMD_BITS  bit;
};

/* eCAN Transmit Request Set register (CANTRS) bit definitions */
struct  CANTRS_BITS
{ /* bit  description */
   UNUM16      TRS0:1; /* 0   TRS for Mailbox 0 */
   UNUM16      TRS1:1; /* 1   TRS for Mailbox 1 */
   UNUM16      TRS2:1; /* 2   TRS for Mailbox 2 */
   UNUM16      TRS3:1; /* 3   TRS for Mailbox 3 */
   UNUM16      TRS4:1; /* 4   TRS for Mailbox 4 */
   UNUM16      TRS5:1; /* 5   TRS for Mailbox 5 */
   UNUM16      TRS6:1; /* 6   TRS for Mailbox 6 */
   UNUM16      TRS7:1; /* 7   TRS for Mailbox 7 */
   UNUM16      TRS8:1; /* 8   TRS for Mailbox 8 */
   UNUM16      TRS9:1; /* 9   TRS for Mailbox 9 */
   UNUM16      TRS10:1; /* 10  TRS for Mailbox 10 */
   UNUM16      TRS11:1; /* 11  TRS for Mailbox 11 */
   UNUM16      TRS12:1; /* 12  TRS for Mailbox 12 */
   UNUM16      TRS13:1; /* 13  TRS for Mailbox 13 */
   UNUM16      TRS14:1; /* 14  TRS for Mailbox 14 */
   UNUM16      TRS15:1; /* 15  TRS for Mailbox 15 */
   UNUM16      TRS16:1; /* 16  TRS for Mailbox 16 */
   UNUM16      TRS17:1; /* 17  TRS for Mailbox 17 */
   UNUM16      TRS18:1; /* 18  TRS for Mailbox 18 */
   UNUM16      TRS19:1; /* 19  TRS for Mailbox 19 */
   UNUM16      TRS20:1; /* 20  TRS for Mailbox 20 */
   UNUM16      TRS21:1; /* 21  TRS for Mailbox 21 */
   UNUM16      TRS22:1; /* 22  TRS for Mailbox 22 */
   UNUM16      TRS23:1; /* 23  TRS for Mailbox 23 */
   UNUM16      TRS24:1; /* 24  TRS for Mailbox 24 */
   UNUM16      TRS25:1; /* 25  TRS for Mailbox 25 */
   UNUM16      TRS26:1; /* 26  TRS for Mailbox 26 */
   UNUM16      TRS27:1; /* 27  TRS for Mailbox 27 */
   UNUM16      TRS28:1; /* 28  TRS for Mailbox 28 */
   UNUM16      TRS29:1; /* 29  TRS for Mailbox 29 */
   UNUM16      TRS30:1; /* 30  TRS for Mailbox 30 */
   UNUM16      TRS31:1; /* 31  TRS for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANTRS_REG
{
   UNUM32              all;
   struct CANTRS_BITS  bit;
};

/* eCAN Transmit Request Reset register (CANTRR) bit definitions */
struct  CANTRR_BITS
{ /* bit  description */
   UNUM16      TRR0:1; /* 0   TRR for Mailbox 0 */
   UNUM16      TRR1:1; /* 1   TRR for Mailbox 1 */
   UNUM16      TRR2:1; /* 2   TRR for Mailbox 2 */
   UNUM16      TRR3:1; /* 3   TRR for Mailbox 3 */
   UNUM16      TRR4:1; /* 4   TRR for Mailbox 4 */
   UNUM16      TRR5:1; /* 5   TRR for Mailbox 5 */
   UNUM16      TRR6:1; /* 6   TRR for Mailbox 6 */
   UNUM16      TRR7:1; /* 7   TRR for Mailbox 7 */
   UNUM16      TRR8:1; /* 8   TRR for Mailbox 8 */
   UNUM16      TRR9:1; /* 9   TRR for Mailbox 9 */
   UNUM16      TRR10:1; /* 10  TRR for Mailbox 10 */
   UNUM16      TRR11:1; /* 11  TRR for Mailbox 11 */
   UNUM16      TRR12:1; /* 12  TRR for Mailbox 12 */
   UNUM16      TRR13:1; /* 13  TRR for Mailbox 13 */
   UNUM16      TRR14:1; /* 14  TRR for Mailbox 14 */
   UNUM16      TRR15:1; /* 15  TRR for Mailbox 15 */
   UNUM16      TRR16:1; /* 16  TRR for Mailbox 16 */
   UNUM16      TRR17:1; /* 17  TRR for Mailbox 17 */
   UNUM16      TRR18:1; /* 18  TRR for Mailbox 18 */
   UNUM16      TRR19:1; /* 19  TRR for Mailbox 19 */
   UNUM16      TRR20:1; /* 20  TRR for Mailbox 20 */
   UNUM16      TRR21:1; /* 21  TRR for Mailbox 21 */
   UNUM16      TRR22:1; /* 22  TRR for Mailbox 22 */
   UNUM16      TRR23:1; /* 23  TRR for Mailbox 23 */
   UNUM16      TRR24:1; /* 24  TRR for Mailbox 24 */
   UNUM16      TRR25:1; /* 25  TRR for Mailbox 25 */
   UNUM16      TRR26:1; /* 26  TRR for Mailbox 26 */
   UNUM16      TRR27:1; /* 27  TRR for Mailbox 27 */
   UNUM16      TRR28:1; /* 28  TRR for Mailbox 28 */
   UNUM16      TRR29:1; /* 29  TRR for Mailbox 29 */
   UNUM16      TRR30:1; /* 30  TRR for Mailbox 30 */
   UNUM16      TRR31:1; /* 31  TRR for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANTRR_REG
{
   UNUM32              all;
   struct CANTRR_BITS  bit;
};

/* eCAN Transmit Acknowledge register (CANTA) bit definitions */
struct  CANTA_BITS
{ /* bit  description */
   UNUM16      TA0:1; /* 0   TA for Mailbox 0 */
   UNUM16      TA1:1; /* 1   TA for Mailbox 1 */
   UNUM16      TA2:1; /* 2   TA for Mailbox 2 */
   UNUM16      TA3:1; /* 3   TA for Mailbox 3 */
   UNUM16      TA4:1; /* 4   TA for Mailbox 4 */
   UNUM16      TA5:1; /* 5   TA for Mailbox 5 */
   UNUM16      TA6:1; /* 6   TA for Mailbox 6 */
   UNUM16      TA7:1; /* 7   TA for Mailbox 7 */
   UNUM16      TA8:1; /* 8   TA for Mailbox 8 */
   UNUM16      TA9:1; /* 9   TA for Mailbox 9 */
   UNUM16      TA10:1; /* 10  TA for Mailbox 10 */
   UNUM16      TA11:1; /* 11  TA for Mailbox 11 */
   UNUM16      TA12:1; /* 12  TA for Mailbox 12 */
   UNUM16      TA13:1; /* 13  TA for Mailbox 13 */
   UNUM16      TA14:1; /* 14  TA for Mailbox 14 */
   UNUM16      TA15:1; /* 15  TA for Mailbox 15 */
   UNUM16      TA16:1; /* 16  TA for Mailbox 16 */
   UNUM16      TA17:1; /* 17  TA for Mailbox 17 */
   UNUM16      TA18:1; /* 18  TA for Mailbox 18 */
   UNUM16      TA19:1; /* 19  TA for Mailbox 19 */
   UNUM16      TA20:1; /* 20  TA for Mailbox 20 */
   UNUM16      TA21:1; /* 21  TA for Mailbox 21 */
   UNUM16      TA22:1; /* 22  TA for Mailbox 22 */
   UNUM16      TA23:1; /* 23  TA for Mailbox 23 */
   UNUM16      TA24:1; /* 24  TA for Mailbox 24 */
   UNUM16      TA25:1; /* 25  TA for Mailbox 25 */
   UNUM16      TA26:1; /* 26  TA for Mailbox 26 */
   UNUM16      TA27:1; /* 27  TA for Mailbox 27 */
   UNUM16      TA28:1; /* 28  TA for Mailbox 28 */
   UNUM16      TA29:1; /* 29  TA for Mailbox 29 */
   UNUM16      TA30:1; /* 30  TA for Mailbox 30 */
   UNUM16      TA31:1; /* 31  TA for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANTA_REG
{
   UNUM32             all;
   struct CANTA_BITS  bit;
};

/* eCAN Transmit Abort Acknowledge register (CANAA) bit definitions */
struct  CANAA_BITS
{ /* bit  description */
   UNUM16      AA0:1; /* 0   AA for Mailbox 0 */
   UNUM16      AA1:1; /* 1   AA for Mailbox 1 */
   UNUM16      AA2:1; /* 2   AA for Mailbox 2 */
   UNUM16      AA3:1; /* 3   AA for Mailbox 3 */
   UNUM16      AA4:1; /* 4   AA for Mailbox 4 */
   UNUM16      AA5:1; /* 5   AA for Mailbox 5 */
   UNUM16      AA6:1; /* 6   AA for Mailbox 6 */
   UNUM16      AA7:1; /* 7   AA for Mailbox 7 */
   UNUM16      AA8:1; /* 8   AA for Mailbox 8 */
   UNUM16      AA9:1; /* 9   AA for Mailbox 9 */
   UNUM16      AA10:1; /* 10  AA for Mailbox 10 */
   UNUM16      AA11:1; /* 11  AA for Mailbox 11 */
   UNUM16      AA12:1; /* 12  AA for Mailbox 12 */
   UNUM16      AA13:1; /* 13  AA for Mailbox 13 */
   UNUM16      AA14:1; /* 14  AA for Mailbox 14 */
   UNUM16      AA15:1; /* 15  AA for Mailbox 15 */
   UNUM16      AA16:1; /* 16  AA for Mailbox 16 */
   UNUM16      AA17:1; /* 17  AA for Mailbox 17 */
   UNUM16      AA18:1; /* 18  AA for Mailbox 18 */
   UNUM16      AA19:1; /* 19  AA for Mailbox 19 */
   UNUM16      AA20:1; /* 20  AA for Mailbox 20 */
   UNUM16      AA21:1; /* 21  AA for Mailbox 21 */
   UNUM16      AA22:1; /* 22  AA for Mailbox 22 */
   UNUM16      AA23:1; /* 23  AA for Mailbox 23 */
   UNUM16      AA24:1; /* 24  AA for Mailbox 24 */
   UNUM16      AA25:1; /* 25  AA for Mailbox 25 */
   UNUM16      AA26:1; /* 26  AA for Mailbox 26 */
   UNUM16      AA27:1; /* 27  AA for Mailbox 27 */
   UNUM16      AA28:1; /* 28  AA for Mailbox 28 */
   UNUM16      AA29:1; /* 29  AA for Mailbox 29 */
   UNUM16      AA30:1; /* 30  AA for Mailbox 30 */
   UNUM16      AA31:1; /* 31  AA for Mailbox 31 */
};
/* Allow access to the bit fields or entire register */
union CANAA_REG
{
   UNUM32             all;
   struct CANAA_BITS  bit;
};

/* eCAN Received Message Pending register (CANRMP) bit definitions */
struct  CANRMP_BITS
{ /* bit  description */
   UNUM16      RMP0:1; /* 0   RMP for Mailbox 0 */
   UNUM16      RMP1:1; /* 1   RMP for Mailbox 1 */
   UNUM16      RMP2:1; /* 2   RMP for Mailbox 2 */
   UNUM16      RMP3:1; /* 3   RMP for Mailbox 3 */
   UNUM16      RMP4:1; /* 4   RMP for Mailbox 4 */
   UNUM16      RMP5:1; /* 5   RMP for Mailbox 5 */
   UNUM16      RMP6:1; /* 6   RMP for Mailbox 6 */
   UNUM16      RMP7:1; /* 7   RMP for Mailbox 7 */
   UNUM16      RMP8:1; /* 8   RMP for Mailbox 8 */
   UNUM16      RMP9:1; /* 9   RMP for Mailbox 9 */
   UNUM16      RMP10:1; /* 10  RMP for Mailbox 10 */
   UNUM16      RMP11:1; /* 11  RMP for Mailbox 11 */
   UNUM16      RMP12:1; /* 12  RMP for Mailbox 12 */
   UNUM16      RMP13:1; /* 13  RMP for Mailbox 13 */
   UNUM16      RMP14:1; /* 14  RMP for Mailbox 14 */
   UNUM16      RMP15:1; /* 15  RMP for Mailbox 15 */
   UNUM16      RMP16:1; /* 16  RMP for Mailbox 16 */
   UNUM16      RMP17:1; /* 17  RMP for Mailbox 17 */
   UNUM16      RMP18:1; /* 18  RMP for Mailbox 18 */
   UNUM16      RMP19:1; /* 19  RMP for Mailbox 19 */
   UNUM16      RMP20:1; /* 20  RMP for Mailbox 20 */
   UNUM16      RMP21:1; /* 21  RMP for Mailbox 21 */
   UNUM16      RMP22:1; /* 22  RMP for Mailbox 22 */
   UNUM16      RMP23:1; /* 23  RMP for Mailbox 23 */
   UNUM16      RMP24:1; /* 24  RMP for Mailbox 24 */
   UNUM16      RMP25:1; /* 25  RMP for Mailbox 25 */
   UNUM16      RMP26:1; /* 26  RMP for Mailbox 26 */
   UNUM16      RMP27:1; /* 27  RMP for Mailbox 27 */
   UNUM16      RMP28:1; /* 28  RMP for Mailbox 28 */
   UNUM16      RMP29:1; /* 29  RMP for Mailbox 29 */
   UNUM16      RMP30:1; /* 30  RMP for Mailbox 30 */
   UNUM16      RMP31:1; /* 31  RMP for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANRMP_REG
{
   UNUM32              all;
   struct CANRMP_BITS  bit;
};

/* eCAN Received Message Lost register (CANRML) bit definitions */
struct  CANRML_BITS
{ /* bit  description */
   UNUM16      RML0:1; /* 0   RML for Mailbox 0 */
   UNUM16      RML1:1; /* 1   RML for Mailbox 1 */
   UNUM16      RML2:1; /* 2   RML for Mailbox 2 */
   UNUM16      RML3:1; /* 3   RML for Mailbox 3 */
   UNUM16      RML4:1; /* 4   RML for Mailbox 4 */
   UNUM16      RML5:1; /* 5   RML for Mailbox 5 */
   UNUM16      RML6:1; /* 6   RML for Mailbox 6 */
   UNUM16      RML7:1; /* 7   RML for Mailbox 7 */
   UNUM16      RML8:1; /* 8   RML for Mailbox 8 */
   UNUM16      RML9:1; /* 9   RML for Mailbox 9 */
   UNUM16      RML10:1; /* 10  RML for Mailbox 10 */
   UNUM16      RML11:1; /* 11  RML for Mailbox 11 */
   UNUM16      RML12:1; /* 12  RML for Mailbox 12 */
   UNUM16      RML13:1; /* 13  RML for Mailbox 13 */
   UNUM16      RML14:1; /* 14  RML for Mailbox 14 */
   UNUM16      RML15:1; /* 15  RML for Mailbox 15 */
   UNUM16      RML16:1; /* 16  RML for Mailbox 16 */
   UNUM16      RML17:1; /* 17  RML for Mailbox 17 */
   UNUM16      RML18:1; /* 18  RML for Mailbox 18 */
   UNUM16      RML19:1; /* 19  RML for Mailbox 19 */
   UNUM16      RML20:1; /* 20  RML for Mailbox 20 */
   UNUM16      RML21:1; /* 21  RML for Mailbox 21 */
   UNUM16      RML22:1; /* 22  RML for Mailbox 22 */
   UNUM16      RML23:1; /* 23  RML for Mailbox 23 */
   UNUM16      RML24:1; /* 24  RML for Mailbox 24 */
   UNUM16      RML25:1; /* 25  RML for Mailbox 25 */
   UNUM16      RML26:1; /* 26  RML for Mailbox 26 */
   UNUM16      RML27:1; /* 27  RML for Mailbox 27 */
   UNUM16      RML28:1; /* 28  RML for Mailbox 28 */
   UNUM16      RML29:1; /* 29  RML for Mailbox 29 */
   UNUM16      RML30:1; /* 30  RML for Mailbox 30 */
   UNUM16      RML31:1; /* 31  RML for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANRML_REG
{
   UNUM32              all;
   struct CANRML_BITS  bit;
};

/* eCAN Remote Frame Pending register (CANRFP) bit definitions */
struct  CANRFP_BITS
{ /* bit  description */
   UNUM16      RFP0:1; /* 0   RFP for Mailbox 0 */
   UNUM16      RFP1:1; /* 1   RFP for Mailbox 1 */
   UNUM16      RFP2:1; /* 2   RFP for Mailbox 2 */
   UNUM16      RFP3:1; /* 3   RFP for Mailbox 3 */
   UNUM16      RFP4:1; /* 4   RFP for Mailbox 4 */
   UNUM16      RFP5:1; /* 5   RFP for Mailbox 5 */
   UNUM16      RFP6:1; /* 6   RFP for Mailbox 6 */
   UNUM16      RFP7:1; /* 7   RFP for Mailbox 7 */
   UNUM16      RFP8:1; /* 8   RFP for Mailbox 8 */
   UNUM16      RFP9:1; /* 9   RFP for Mailbox 9 */
   UNUM16      RFP10:1; /* 10  RFP for Mailbox 10 */
   UNUM16      RFP11:1; /* 11  RFP for Mailbox 11 */
   UNUM16      RFP12:1; /* 12  RFP for Mailbox 12 */
   UNUM16      RFP13:1; /* 13  RFP for Mailbox 13 */
   UNUM16      RFP14:1; /* 14  RFP for Mailbox 14 */
   UNUM16      RFP15:1; /* 15  RFP for Mailbox 15 */
   UNUM16      RFP16:1; /* 16  RFP for Mailbox 16 */
   UNUM16      RFP17:1; /* 17  RFP for Mailbox 17 */
   UNUM16      RFP18:1; /* 18  RFP for Mailbox 18 */
   UNUM16      RFP19:1; /* 19  RFP for Mailbox 19 */
   UNUM16      RFP20:1; /* 20  RFP for Mailbox 20 */
   UNUM16      RFP21:1; /* 21  RFP for Mailbox 21 */
   UNUM16      RFP22:1; /* 22  RFP for Mailbox 22 */
   UNUM16      RFP23:1; /* 23  RFP for Mailbox 23 */
   UNUM16      RFP24:1; /* 24  RFP for Mailbox 24 */
   UNUM16      RFP25:1; /* 25  RFP for Mailbox 25 */
   UNUM16      RFP26:1; /* 26  RFP for Mailbox 26 */
   UNUM16      RFP27:1; /* 27  RFP for Mailbox 27 */
   UNUM16      RFP28:1; /* 28  RFP for Mailbox 28 */
   UNUM16      RFP29:1; /* 29  RFP for Mailbox 29 */
   UNUM16      RFP30:1; /* 30  RFP for Mailbox 30 */
   UNUM16      RFP31:1; /* 31  RFP for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANRFP_REG
{
   UNUM32              all;
   struct CANRFP_BITS  bit;
};

/* eCAN Global Acceptance Mask register (CANGAM) bit definitions */
struct  CANGAM_BITS
{ /* bits  description */
   UNUM16 GAM150:16; /* 15:0  Global acceptance mask bits 0-15 */
   UNUM16 GAM2816:13; /* 28:16 Global acceptance mask bits 16-28 */
   UNUM16 rsvd:2; /* 30:29 reserved */
   UNUM16 AMI:1; /* 31    AMI bit */
};

/* Allow access to the bit fields or entire register */
union CANGAM_REG
{
   UNUM32              all;
   struct CANGAM_BITS  bit;
};


/* eCAN Master Control register (CANMC) bit definitions */
struct  CANMC_BITS
{ /* bits  description */
   UNUM16      MBNR:5; /* 4:0   MBX # for CDR bit */
   UNUM16      SRES:1; /* 5     Soft reset */
   UNUM16      STM:1; /* 6     Self-test mode */
   UNUM16      ABO:1; /* 7     Auto bus-on */
   UNUM16      CDR:1; /* 8     Change data request */
   UNUM16      WUBA:1; /* 9     Wake-up on bus activity */
   UNUM16      DBO:1; /* 10    Data-byte order */
   UNUM16      PDR:1; /* 11    Power-down mode request */
   UNUM16      CCR:1; /* 12    Change configuration request */
   UNUM16      SCB:1; /* 13    SCC compatibility bit */
   UNUM16      TCC:1; /* 14    TSC MSB clear bit */
   UNUM16      MBCC:1; /* 15    TSC clear bit thru mailbox 16 */
   UNUM16      SUSP:1; /* 16    SUSPEND free/soft bit */
   UNUM16      rsvd:15; /* 31:17  reserved */
};

/* Allow access to the bit fields or entire register */
union CANMC_REG
{
   UNUM32             all;
   struct CANMC_BITS  bit;
};

/* eCAN Bit -timing configuration register (CANBTC) bit definitions */
struct  CANBTC_BITS
{ /* bits  description */
   UNUM16  TSEG2REG:3; /* 2:0   TSEG2 register value */
   UNUM16  TSEG1REG:4; /* 6:3   TSEG1 register value */
   UNUM16  SAM:1; /* 7     Sample-point setting */
   UNUM16  SJWREG:2; /* 9:8   Synchroniztion Jump Width register value */
   UNUM16  rsvd1:6; /* 15:10 reserved */
   UNUM16  BRPREG:8; /* 23:16 Baudrate prescaler register value */
   UNUM16  rsvd2:8; /* 31:24 reserved */
};

/* Allow access to the bit fields or entire register */
union CANBTC_REG
{
   UNUM32              all;
   struct CANBTC_BITS  bit;
};

/* eCAN Error & Status register (CANES) bit definitions */
struct  CANES_BITS
{ /* bits  description */
   UNUM16   TM:1; /* 0     Transmit Mode */
   UNUM16   RM:1; /* 1     Receive Mode */
   UNUM16   rsvd1:1; /* 2     reserved */
   UNUM16   PDA:1; /* 3     Power-down acknowledge */
   UNUM16   CCE:1; /* 4     Change Configuration Enable */
   UNUM16   SMA:1; /* 5     Suspend Mode Acknowledge */
   UNUM16   rsvd2:10; /* 15:6  reserved */
   UNUM16   EW:1; /* 16    Warning status */
   UNUM16   EP:1; /* 17    Error Passive status */
   UNUM16   BO:1; /* 18    Bus-off status */
   UNUM16   ACKE:1; /* 19    Acknowledge error */
   UNUM16   SE:1; /* 20    Stuff error */
   UNUM16   CRCE:1; /* 21    CRC error */
   UNUM16   SA1:1; /* 22    Stuck at Dominant error */
   UNUM16   BE:1; /* 23    Bit error */
   UNUM16   FE:1; /* 24    Framing error */
   UNUM16   rsvd3:7; /* 31:25 reserved */
};

/* Allow access to the bit fields or entire register */
union CANES_REG
{
   UNUM32             all;
   struct CANES_BITS  bit;
};


/* eCAN Transmit Error Counter register (CANTEC) bit definitions */
struct  CANTEC_BITS
{ /* bits  description */
   UNUM16 TEC:8; /* 7:0   TEC */
   UNUM16 rsvd1:8; /* 15:8  reserved */
   UNUM16 rsvd2:16; /* 31:16  reserved */
};

/* Allow access to the bit fields or entire register */
union CANTEC_REG
{
   UNUM32              all;
   struct CANTEC_BITS  bit;
};

/* eCAN Receive Error Counter register (CANREC) bit definitions */
struct  CANREC_BITS
{ /* bits  description */
   UNUM16 REC:8; /* 7:0   REC */
   UNUM16 rsvd1:8; /* 15:8  reserved */
   UNUM16 rsvd2:16; /* 31:16 reserved */
};

/* Allow access to the bit fields or entire register */
union CANREC_REG
{
   UNUM32              all;
   struct CANREC_BITS  bit;
};

/* eCAN Global Interrupt Flag 0 (CANGIF0) bit definitions */
struct  CANGIF0_BITS
{ /* bits  description */
   UNUM16   MIV0:5; /* 4:0   Mailbox Interrupt Vector */
   UNUM16   rsvd1:3; /* 7:5   reserved */
   UNUM16   WLIF0:1; /* 8     Warning level interrupt flag */
   UNUM16   EPIF0:1; /* 9     Error-passive interrupt flag */
   UNUM16   BOIF0:1; /* 10    Bus-off interrupt flag */
   UNUM16   RMLIF0:1; /* 11    Received message lost interrupt flag */
   UNUM16   WUIF0:1; /* 12    Wakeup interrupt flag */
   UNUM16   WDIF0:1; /* 13    Write denied interrupt flag */
   UNUM16   AAIF0:1; /* 14    Abort Ack interrupt flag */
   UNUM16   GMIF0:1; /* 15    Global MBX interrupt flag */
   UNUM16   TCOF0:1; /* 16    TSC Overflow flag */
   UNUM16   MTOF0:1; /* 17    Mailbox Timeout flag */
   UNUM16   rsvd2:14; /* 31:18 reserved */
};

/* Allow access to the bit fields or entire register */
union CANGIF0_REG
{
   UNUM32               all;
   struct CANGIF0_BITS  bit;
};

/* eCAN Global Interrupt Mask register (CANGIM) bit definitions */
struct  CANGIM_BITS
{ /* bits  description */
   UNUM16  I0EN:1; /* 0      Interrupt 0 enable */
   UNUM16  I1EN:1; /* 1      Interrupt 1 enable */
   UNUM16  GIL:1; /* 2      Global Interrupt Level */
   UNUM16  rsvd1:5; /* 7:3    reserved */
   UNUM16  WLIM:1; /* 8      Warning level interrupt mask */
   UNUM16  EPIM:1; /* 9      Error-passive interrupt mask */
   UNUM16  BOIM:1; /* 10     Bus-off interrupt mask */
   UNUM16  RMLIM:1; /* 11     Received message lost interrupt mask */
   UNUM16  WUIM:1; /* 12     Wakeup interrupt mask */
   UNUM16  WDIM:1; /* 13     Write denied interrupt mask */
   UNUM16  AAIM:1; /* 14     Abort Ack interrupt mask */
   UNUM16  rsvd2:1; /* 15     reserved */
   UNUM16  TCOM:1; /* 16     TSC overflow interrupt mask */
   UNUM16  MTOM:1; /* 17     MBX Timeout interrupt mask */
   UNUM16  rsvd3:14; /* 31:18  reserved */
};

/* Allow access to the bit fields or entire register */
union CANGIM_REG
{
   UNUM32              all;
   struct CANGIM_BITS  bit;
};


/* eCAN Global Interrupt Flag 1 (eCANGIF1) bit definitions */
struct  CANGIF1_BITS
{ /* bits  description */
   UNUM16      MIV1:5; /* 4:0   Mailbox Interrupt Vector */
   UNUM16      rsvd1:3; /* 7:5   reserved */
   UNUM16      WLIF1:1; /* 8     Warning level interrupt flag */
   UNUM16      EPIF1:1; /* 9     Error-passive interrupt flag */
   UNUM16      BOIF1:1; /* 10    Bus-off interrupt flag */
   UNUM16      RMLIF1:1; /* 11    Received message lost interrupt flag */
   UNUM16      WUIF1:1; /* 12    Wakeup interrupt flag */
   UNUM16      WDIF1:1; /* 13    Write denied interrupt flag */
   UNUM16      AAIF1:1; /* 14    Abort Ack interrupt flag */
   UNUM16      GMIF1:1; /* 15    Global MBX interrupt flag */
   UNUM16      TCOF1:1; /* 16    TSC Overflow flag */
   UNUM16      MTOF1:1; /* 17    Mailbox Timeout flag */
   UNUM16      rsvd2:14; /* 31:18 reserved */
};

/* Allow access to the bit fields or entire register */
union CANGIF1_REG
{
   UNUM32               all;
   struct CANGIF1_BITS  bit;
};


/* eCAN Mailbox Interrupt Mask register (CANMIM) bit definitions */
struct  CANMIM_BITS
{ /* bit  description */
   UNUM16      MIM0:1; /* 0   MIM for Mailbox 0 */
   UNUM16      MIM1:1; /* 1   MIM for Mailbox 1 */
   UNUM16      MIM2:1; /* 2   MIM for Mailbox 2 */
   UNUM16      MIM3:1; /* 3   MIM for Mailbox 3 */
   UNUM16      MIM4:1; /* 4   MIM for Mailbox 4 */
   UNUM16      MIM5:1; /* 5   MIM for Mailbox 5 */
   UNUM16      MIM6:1; /* 6   MIM for Mailbox 6 */
   UNUM16      MIM7:1; /* 7   MIM for Mailbox 7 */
   UNUM16      MIM8:1; /* 8   MIM for Mailbox 8 */
   UNUM16      MIM9:1; /* 9   MIM for Mailbox 9 */
   UNUM16      MIM10:1; /* 10  MIM for Mailbox 10 */
   UNUM16      MIM11:1; /* 11  MIM for Mailbox 11 */
   UNUM16      MIM12:1; /* 12  MIM for Mailbox 12 */
   UNUM16      MIM13:1; /* 13  MIM for Mailbox 13 */
   UNUM16      MIM14:1; /* 14  MIM for Mailbox 14 */
   UNUM16      MIM15:1; /* 15  MIM for Mailbox 15 */
   UNUM16      MIM16:1; /* 16  MIM for Mailbox 16 */
   UNUM16      MIM17:1; /* 17  MIM for Mailbox 17 */
   UNUM16      MIM18:1; /* 18  MIM for Mailbox 18 */
   UNUM16      MIM19:1; /* 19  MIM for Mailbox 19 */
   UNUM16      MIM20:1; /* 20  MIM for Mailbox 20 */
   UNUM16      MIM21:1; /* 21  MIM for Mailbox 21 */
   UNUM16      MIM22:1; /* 22  MIM for Mailbox 22 */
   UNUM16      MIM23:1; /* 23  MIM for Mailbox 23 */
   UNUM16      MIM24:1; /* 24  MIM for Mailbox 24 */
   UNUM16      MIM25:1; /* 25  MIM for Mailbox 25 */
   UNUM16      MIM26:1; /* 26  MIM for Mailbox 26 */
   UNUM16      MIM27:1; /* 27  MIM for Mailbox 27 */
   UNUM16      MIM28:1; /* 28  MIM for Mailbox 28 */
   UNUM16      MIM29:1; /* 29  MIM for Mailbox 29 */
   UNUM16      MIM30:1; /* 30  MIM for Mailbox 30 */
   UNUM16      MIM31:1; /* 31  MIM for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANMIM_REG
{
   UNUM32              all;
   struct CANMIM_BITS  bit;
};

/* eCAN Mailbox Interrupt Level register (CANMIL) bit definitions */
struct  CANMIL_BITS
{ /* bit  description */
   UNUM16      MIL0:1; /* 0   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL1:1; /* 1   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL2:1; /* 2   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL3:1; /* 3   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL4:1; /* 4   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL5:1; /* 5   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL6:1; /* 6   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL7:1; /* 7   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL8:1; /* 8   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL9:1; /* 9   0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL10:1; /* 10  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL11:1; /* 11  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL12:1; /* 12  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL13:1; /* 13  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL14:1; /* 14  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL15:1; /* 15  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL16:1; /* 16  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL17:1; /* 17  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL18:1; /* 18  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL19:1; /* 19  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL20:1; /* 20  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL21:1; /* 21  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL22:1; /* 22  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL23:1; /* 23  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL24:1; /* 24  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL25:1; /* 25  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL26:1; /* 26  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL27:1; /* 27  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL28:1; /* 28  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL29:1; /* 29  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL30:1; /* 30  0 -> Int 9.5   1 -> Int 9.6 */
   UNUM16      MIL31:1; /* 31  0 -> Int 9.5   1 -> Int 9.6 */
};

/* Allow access to the bit fields or entire register */
union CANMIL_REG
{
   UNUM32              all;
   struct CANMIL_BITS  bit;
};


/* eCAN Overwrite Protection Control register (CANOPC) bit definitions */
struct  CANOPC_BITS
{ /* bit  description */
   UNUM16      OPC0:1; /* 0   OPC for Mailbox 0 */
   UNUM16      OPC1:1; /* 1   OPC for Mailbox 1 */
   UNUM16      OPC2:1; /* 2   OPC for Mailbox 2 */
   UNUM16      OPC3:1; /* 3   OPC for Mailbox 3 */
   UNUM16      OPC4:1; /* 4   OPC for Mailbox 4 */
   UNUM16      OPC5:1; /* 5   OPC for Mailbox 5 */
   UNUM16      OPC6:1; /* 6   OPC for Mailbox 6 */
   UNUM16      OPC7:1; /* 7   OPC for Mailbox 7 */
   UNUM16      OPC8:1; /* 8   OPC for Mailbox 8 */
   UNUM16      OPC9:1; /* 9   OPC for Mailbox 9 */
   UNUM16      OPC10:1; /* 10  OPC for Mailbox 10 */
   UNUM16      OPC11:1; /* 11  OPC for Mailbox 11 */
   UNUM16      OPC12:1; /* 12  OPC for Mailbox 12 */
   UNUM16      OPC13:1; /* 13  OPC for Mailbox 13 */
   UNUM16      OPC14:1; /* 14  OPC for Mailbox 14 */
   UNUM16      OPC15:1; /* 15  OPC for Mailbox 15 */
   UNUM16      OPC16:1; /* 16  OPC for Mailbox 16 */
   UNUM16      OPC17:1; /* 17  OPC for Mailbox 17 */
   UNUM16      OPC18:1; /* 18  OPC for Mailbox 18 */
   UNUM16      OPC19:1; /* 19  OPC for Mailbox 19 */
   UNUM16      OPC20:1; /* 20  OPC for Mailbox 20 */
   UNUM16      OPC21:1; /* 21  OPC for Mailbox 21 */
   UNUM16      OPC22:1; /* 22  OPC for Mailbox 22 */
   UNUM16      OPC23:1; /* 23  OPC for Mailbox 23 */
   UNUM16      OPC24:1; /* 24  OPC for Mailbox 24 */
   UNUM16      OPC25:1; /* 25  OPC for Mailbox 25 */
   UNUM16      OPC26:1; /* 26  OPC for Mailbox 26 */
   UNUM16      OPC27:1; /* 27  OPC for Mailbox 27 */
   UNUM16      OPC28:1; /* 28  OPC for Mailbox 28 */
   UNUM16      OPC29:1; /* 29  OPC for Mailbox 29 */
   UNUM16      OPC30:1; /* 30  OPC for Mailbox 30 */
   UNUM16      OPC31:1; /* 31  OPC for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANOPC_REG
{
   UNUM32              all;
   struct CANOPC_BITS  bit;
};


/* eCAN TX I/O Control Register (CANTIOC) bit definitions */
struct  CANTIOC_BITS
{ /* bits  description */
   UNUM16  rsvd1:3;    /* 2:0   reserved */
   UNUM16  TXFUNC:1;   /* 3     TXFUNC */
   UNUM16  rsvd2:12;   /* 15:4  reserved */
   UNUM16  rsvd3:16;   /* 31:16 reserved */
};

/* Allow access to the bit fields or entire register */
union CANTIOC_REG
{
   UNUM32               all;
   struct CANTIOC_BITS  bit;
};

/* eCAN RX I/O Control Register (CANRIOC) bit definitions */
struct  CANRIOC_BITS
{ /* bits  description */
   UNUM16  rsvd1:3; /* 2:0   reserved */
   UNUM16  RXFUNC:1; /* 3     RXFUNC */
   UNUM16  rsvd2:12; /* 15:4  reserved */
   UNUM16  rsvd3:16; /* 31:16 reserved */
};

/* Allow access to the bit fields or entire register */
union CANRIOC_REG
{
   UNUM32               all;
   struct CANRIOC_BITS  bit;
};


/* eCAN Time-out Control register (CANTOC) bit definitions */
struct  CANTOC_BITS
{ /* bit  description */
   UNUM16      TOC0:1; /* 0   TOC for Mailbox 0 */
   UNUM16      TOC1:1; /* 1   TOC for Mailbox 1 */
   UNUM16      TOC2:1; /* 2   TOC for Mailbox 2 */
   UNUM16      TOC3:1; /* 3   TOC for Mailbox 3 */
   UNUM16      TOC4:1; /* 4   TOC for Mailbox 4 */
   UNUM16      TOC5:1; /* 5   TOC for Mailbox 5 */
   UNUM16      TOC6:1; /* 6   TOC for Mailbox 6 */
   UNUM16      TOC7:1; /* 7   TOC for Mailbox 7 */
   UNUM16      TOC8:1; /* 8   TOC for Mailbox 8 */
   UNUM16      TOC9:1; /* 9   TOC for Mailbox 9 */
   UNUM16      TOC10:1; /* 10  TOC for Mailbox 10 */
   UNUM16      TOC11:1; /* 11  TOC for Mailbox 11 */
   UNUM16      TOC12:1; /* 12  TOC for Mailbox 12 */
   UNUM16      TOC13:1; /* 13  TOC for Mailbox 13 */
   UNUM16      TOC14:1; /* 14  TOC for Mailbox 14 */
   UNUM16      TOC15:1; /* 15  TOC for Mailbox 15 */
   UNUM16      TOC16:1; /* 16  TOC for Mailbox 16 */
   UNUM16      TOC17:1; /* 17  TOC for Mailbox 17 */
   UNUM16      TOC18:1; /* 18  TOC for Mailbox 18 */
   UNUM16      TOC19:1; /* 19  TOC for Mailbox 19 */
   UNUM16      TOC20:1; /* 20  TOC for Mailbox 20 */
   UNUM16      TOC21:1; /* 21  TOC for Mailbox 21 */
   UNUM16      TOC22:1; /* 22  TOC for Mailbox 22 */
   UNUM16      TOC23:1; /* 23  TOC for Mailbox 23 */
   UNUM16      TOC24:1; /* 24  TOC for Mailbox 24 */
   UNUM16      TOC25:1; /* 25  TOC for Mailbox 25 */
   UNUM16      TOC26:1; /* 26  TOC for Mailbox 26 */
   UNUM16      TOC27:1; /* 27  TOC for Mailbox 27 */
   UNUM16      TOC28:1; /* 28  TOC for Mailbox 28 */
   UNUM16      TOC29:1; /* 29  TOC for Mailbox 29 */
   UNUM16      TOC30:1; /* 30  TOC for Mailbox 30 */
   UNUM16      TOC31:1; /* 31  TOC for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANTOC_REG
{
   UNUM32              all;
   struct CANTOC_BITS  bit;
};


/* eCAN Time-out Status register (CANTOS) bit definitions */
struct  CANTOS_BITS
{ /* bit  description */
   UNUM16      TOS0:1; /* 0   TOS for Mailbox 0 */
   UNUM16      TOS1:1; /* 1   TOS for Mailbox 1 */
   UNUM16      TOS2:1; /* 2   TOS for Mailbox 2 */
   UNUM16      TOS3:1; /* 3   TOS for Mailbox 3 */
   UNUM16      TOS4:1; /* 4   TOS for Mailbox 4 */
   UNUM16      TOS5:1; /* 5   TOS for Mailbox 5 */
   UNUM16      TOS6:1; /* 6   TOS for Mailbox 6 */
   UNUM16      TOS7:1; /* 7   TOS for Mailbox 7 */
   UNUM16      TOS8:1; /* 8   TOS for Mailbox 8 */
   UNUM16      TOS9:1; /* 9   TOS for Mailbox 9 */
   UNUM16      TOS10:1; /* 10  TOS for Mailbox 10 */
   UNUM16      TOS11:1; /* 11  TOS for Mailbox 11 */
   UNUM16      TOS12:1; /* 12  TOS for Mailbox 12 */
   UNUM16      TOS13:1; /* 13  TOS for Mailbox 13 */
   UNUM16      TOS14:1; /* 14  TOS for Mailbox 14 */
   UNUM16      TOS15:1; /* 15  TOS for Mailbox 15 */
   UNUM16      TOS16:1; /* 16  TOS for Mailbox 16 */
   UNUM16      TOS17:1; /* 17  TOS for Mailbox 17 */
   UNUM16      TOS18:1; /* 18  TOS for Mailbox 18 */
   UNUM16      TOS19:1; /* 19  TOS for Mailbox 19 */
   UNUM16      TOS20:1; /* 20  TOS for Mailbox 20 */
   UNUM16      TOS21:1; /* 21  TOS for Mailbox 21 */
   UNUM16      TOS22:1; /* 22  TOS for Mailbox 22 */
   UNUM16      TOS23:1; /* 23  TOS for Mailbox 23 */
   UNUM16      TOS24:1; /* 24  TOS for Mailbox 24 */
   UNUM16      TOS25:1; /* 25  TOS for Mailbox 25 */
   UNUM16      TOS26:1; /* 26  TOS for Mailbox 26 */
   UNUM16      TOS27:1; /* 27  TOS for Mailbox 27 */
   UNUM16      TOS28:1; /* 28  TOS for Mailbox 28 */
   UNUM16      TOS29:1; /* 29  TOS for Mailbox 29 */
   UNUM16      TOS30:1; /* 30  TOS for Mailbox 30 */
   UNUM16      TOS31:1; /* 31  TOS for Mailbox 31 */
};

/* Allow access to the bit fields or entire register */
union CANTOS_REG
{
   UNUM32              all;
   struct CANTOS_BITS  bit;
};

/********************************************************************/
/* eCAN Control & Status register file                              */
/********************************************************************/

struct ECAN_REGS
{
   union CANME_REG   CANME; /* Mailbox Enable */
   union CANMD_REG   CANMD; /* Mailbox Direction */
   union CANTRS_REG  CANTRS; /* Transmit Request Set */
   union CANTRR_REG  CANTRR; /* Transmit Request Reset */
   union CANTA_REG   CANTA; /* Transmit Acknowledge */
   union CANAA_REG   CANAA; /* Abort Acknowledge */
   union CANRMP_REG  CANRMP; /* Received Message Pending */
   union CANRML_REG  CANRML; /* Received Message Lost */
   union CANRFP_REG  CANRFP; /* Remote Frame Pending */
   union CANGAM_REG  CANGAM; /* Global Acceptance Mask */
   union CANMC_REG   CANMC; /* Master Control */
   union CANBTC_REG  CANBTC; /* Bit Timing */
   union CANES_REG   CANES; /* Error Status */
   union CANTEC_REG  CANTEC; /* Transmit Error Counter */
   union CANREC_REG  CANREC; /* Receive Error Counter */
   union CANGIF0_REG CANGIF0; /* Global Interrupt Flag 0 */
   union CANGIM_REG  CANGIM; /* Global Interrupt Mask 0 */
   union CANGIF1_REG CANGIF1; /* Global Interrupt Flag 1 */
   union CANMIM_REG  CANMIM; /* Mailbox Interrupt Mask */
   union CANMIL_REG  CANMIL; /* Mailbox Interrupt Level */
   union CANOPC_REG  CANOPC; /* Overwrite Protection Control */
   union CANTIOC_REG CANTIOC; /* TX I/O Control */
   union CANRIOC_REG CANRIOC; /* RX I/O Control */
   UNUM32            CANTSC; /* Time-stamp counter */
   union CANTOC_REG  CANTOC; /* Time-out Control */
   union CANTOS_REG  CANTOS; /* Time-out Status */
};

/********************************************************************/
/* eCAN Mailbox Registers                                           */
/********************************************************************/

/* eCAN Message ID (MSGID) bit definitions */
struct  CANMSGID_BITS
{ /* bits  description */
   UNUM16      EXTMSGID_L:16; /* 0:15 */
   UNUM16      EXTMSGID_H:2; /* 16:17 */
   UNUM16      STDMSGID:11; /* 18:28 */
   UNUM16      AAM:1; /* 29 */
   UNUM16      AME:1; /* 30 */
   UNUM16      IDE:1; /* 31 */
};

/* Allow access to the bit fields or entire register */
union CANMSGID_REG
{
   UNUM32                all;
   struct CANMSGID_BITS  bit;
};

/* eCAN Message Control Register (MSGCTRL) bit definitions */
struct  CANMSGCTRL_BITS
{ /* bits  description */
   UNUM16 DLC:4; /* 0:3 */
   UNUM16 RTR:1; /* 4 */
   UNUM16 rsvd1:3; /* 7:5   reserved */
   UNUM16 TPL:5; /* 12:8 */
   UNUM16 rsvd2:3; /* 15:13 reserved */
   UNUM16 rsvd3:16; /* 31:16 reserved */
};

/* Allow access to the bit fields or entire register */
union CANMSGCTRL_REG
{
   UNUM32                  all;
   struct CANMSGCTRL_BITS  bit;
};

/* eCAN Message Data Register low (MDR_L) word definitions */
struct  CANMDL_WORDS
{ /* bits  description */
   UNUM16      LOW_WORD:16; /* 0:15 */
   UNUM16      HI_WORD:16; /* 31:16 */
};

/* eCAN Message Data Register low (MDR_L) byte definitions */
struct  CANMDL_BYTES
{ /* bits   description */
   UNUM16      BYTE3:8; /* 31:24 */
   UNUM16      BYTE2:8; /* 23:16 */
   UNUM16      BYTE1:8; /* 15:8 */
   UNUM16      BYTE0:8; /* 7:0 */
};


/* Allow access to the bit fields or entire register */

union CANMDL_REG
{
   UNUM32                all;
   struct CANMDL_WORDS   word;
   struct CANMDL_BYTES   byte;
};



/* eCAN Message Data Register high  (MDR_H) word definitions */
struct  CANMDH_WORDS
{ /* bits  description */
   UNUM16      LOW_WORD:16; /* 0:15 */
   UNUM16      HI_WORD:16; /* 31:16 */
};

/* eCAN Message Data Register low (MDR_H) byte definitions */
struct  CANMDH_BYTES
{ /* bits   description */
   UNUM16      BYTE7:8; /* 63:56 */
   UNUM16      BYTE6:8; /* 55:48 */
   UNUM16      BYTE5:8; /* 47:40 */
   UNUM16      BYTE4:8; /* 39:32 */
};

/* Allow access to the bit fields or entire register */
union CANMDH_REG
{
   UNUM32                  all;
   struct CANMDH_WORDS     word;
   struct CANMDH_BYTES     byte;
};


struct MBoxT
{
   union CANMSGID_REG     MSGID;
   union CANMSGCTRL_REG   MSGCTRL;
   union CANMDL_REG       MDL;
   union CANMDH_REG       MDH;
};

/********************************************************************/
/*          eCAN Mailboxes                                          */
/********************************************************************/

struct ECAN_MBOXES
{
   struct MBoxT MBOX[32];
};

/* eCAN Local Acceptance Mask (LAM) bit definitions */
struct  CANLAM_BITS
{ /* bits  description */
   UNUM16      LAM_L:16; /* 0:15 */
   UNUM16      LAM_H:13; /* 16:28 */
   UNUM16      rsvd1:2; /* 29:30   reserved */
   UNUM16      LAMI:1; /* 31 */
};

/* Allow access to the bit fields or entire register */
union CANLAM_REG
{
   UNUM32        all;
   struct CANLAM_BITS  bit;
};


/**************************************/
/*    eCAN Local Acceptance Masks      */
/**************************************/

/* eCAN LAM File */

struct LAM_REGS
{
   union CANLAM_REG LAM[32];
};

/* Mailbox MOTS File */

struct MOTS_REGS
{
   UNUM32 MOTS0;
   UNUM32 MOTS1;
   UNUM32 MOTS2;
   UNUM32 MOTS3;
   UNUM32 MOTS4;
   UNUM32 MOTS5;
   UNUM32 MOTS6;
   UNUM32 MOTS7;
   UNUM32 MOTS8;
   UNUM32 MOTS9;
   UNUM32 MOTS10;
   UNUM32 MOTS11;
   UNUM32 MOTS12;
   UNUM32 MOTS13;
   UNUM32 MOTS14;
   UNUM32 MOTS15;
   UNUM32 MOTS16;
   UNUM32 MOTS17;
   UNUM32 MOTS18;
   UNUM32 MOTS19;
   UNUM32 MOTS20;
   UNUM32 MOTS21;
   UNUM32 MOTS22;
   UNUM32 MOTS23;
   UNUM32 MOTS24;
   UNUM32 MOTS25;
   UNUM32 MOTS26;
   UNUM32 MOTS27;
   UNUM32 MOTS28;
   UNUM32 MOTS29;
   UNUM32 MOTS30;
   UNUM32 MOTS31;
};

/* Mailbox MOTO File */

struct MOTO_REGS
{
   UNUM32 MOTO0;
   UNUM32 MOTO1;
   UNUM32 MOTO2;
   UNUM32 MOTO3;
   UNUM32 MOTO4;
   UNUM32 MOTO5;
   UNUM32 MOTO6;
   UNUM32 MOTO7;
   UNUM32 MOTO8;
   UNUM32 MOTO9;
   UNUM32 MOTO10;
   UNUM32 MOTO11;
   UNUM32 MOTO12;
   UNUM32 MOTO13;
   UNUM32 MOTO14;
   UNUM32 MOTO15;
   UNUM32 MOTO16;
   UNUM32 MOTO17;
   UNUM32 MOTO18;
   UNUM32 MOTO19;
   UNUM32 MOTO20;
   UNUM32 MOTO21;
   UNUM32 MOTO22;
   UNUM32 MOTO23;
   UNUM32 MOTO24;
   UNUM32 MOTO25;
   UNUM32 MOTO26;
   UNUM32 MOTO27;
   UNUM32 MOTO28;
   UNUM32 MOTO29;
   UNUM32 MOTO30;
   UNUM32 MOTO31;
};

extern volatile struct ECAN_REGS ECAN_ECanaRegs;
extern volatile struct ECAN_MBOXES ECAN_ECanaMboxes;
extern volatile struct LAM_REGS ECAN_ECanaLAMRegs;
extern volatile struct MOTS_REGS ECAN_ECanaMOTSRegs;
extern volatile struct MOTO_REGS ECAN_ECanaMOTORegs;
extern volatile struct ECAN_REGS ECAN_ECanbRegs;
extern volatile struct ECAN_MBOXES ECAN_ECanbMboxes;
extern volatile struct LAM_REGS ECAN_ECanbLAMRegs;
extern volatile struct MOTS_REGS ECAN_ECanbMOTSRegs;
extern volatile struct MOTO_REGS ECAN_ECanbMOTORegs;

extern UNUM32 recHighBytes[10];
extern UNUM32 recLowBytes[10];

#endif

/***************************************************************************
End of file.
***************************************************************************/
