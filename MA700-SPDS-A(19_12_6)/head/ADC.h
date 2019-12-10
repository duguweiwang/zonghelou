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
*     Module Name:         %name:     ADC.h %                                 *
*     Module Version:      %version:  2 %                                     *
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
*                 %created_by:   maolei %                                     *
*                                    									      *									  
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 % 			      *
*                                                                             *  
******************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"
#include "SYS_CTRL.h"

/**** definitions*************************************************************/


/*---------------------------------------------------------------------------
ADC Individual Register Bit Definitions:
---------------------------------------------------------------------------*/
struct ADCTRL1_BITS
{ /* bits  description*/
    UNUM16  rsvd1:4; /* 3:0   reserved*/
    UNUM16  SEQ_CASC:1; /* 4     Cascaded sequencer mode*/
    UNUM16  SEQ_OVRD:1; /* 5     Sequencer override */
    UNUM16  CONT_RUN:1; /* 6     Continuous run*/
    UNUM16  CPS:1; /* 7     ADC core clock pre-scalar*/
    UNUM16  ACQ_PS:4; /* 11:8  Acquisition window size*/
    UNUM16  SUSMOD:2; /* 13:12 Emulation suspend mode*/
    UNUM16  RESET:1; /* 14    ADC reset*/
    UNUM16  rsvd2:1; /* 15    reserved*/
};

union ADCTRL1_REG
{
   UNUM16                all;
   struct ADCTRL1_BITS   bit;
};

struct ADCTRL2_BITS
{ /* bits  description*/
    UNUM16  EPWM_SOCB_SEQ2:1; /* 0     EPWM compare B SOC mask for SEQ2*/
    UNUM16  rsvd1:1; /* 1     reserved*/
    UNUM16  INT_MOD_SEQ2:1; /* 2     SEQ2 Interrupt mode*/
    UNUM16  INT_ENA_SEQ2:1; /* 3     SEQ2 Interrupt enable*/
    UNUM16  rsvd2:1; /* 4     reserved*/
    UNUM16  SOC_SEQ2:1; /* 5     Start of conversion for SEQ2*/
    UNUM16  RST_SEQ2:1; /* 6     Reset SEQ2*/
    UNUM16  EXT_SOC_SEQ1:1; /* 7     External start of conversion for SEQ1*/
    UNUM16  EPWM_SOCA_SEQ1:1; /* 8     EPWM compare B SOC mask for SEQ1*/
    UNUM16  rsvd3:1; /* 9     reserved*/
    UNUM16  INT_MOD_SEQ1:1; /* 10    SEQ1 Interrupt mode*/
    UNUM16  INT_ENA_SEQ1:1; /* 11    SEQ1 Interrupt enable*/
    UNUM16  rsvd4:1; /* 12    reserved*/
    UNUM16  SOC_SEQ1:1; /* 13    Start of conversion trigger for SEQ1*/
    UNUM16  RST_SEQ1:1; /* 14    Restart sequencer 1 */
    UNUM16  EPWM_SOCB_SEQ:1; /* 15    EPWM compare B SOC enable*/
};

union ADCTRL2_REG
{
   UNUM16                all;
   struct ADCTRL2_BITS   bit;
};

struct ADCASEQSR_BITS
{ /* bits   description*/
    UNUM16  SEQ1_STATE:4; /* 3:0    SEQ1 state*/
    UNUM16  SEQ2_STATE:3; /* 6:4    SEQ2 state*/
    UNUM16  rsvd1:1; /* 7      reserved*/
    UNUM16  SEQ_CNTR:4; /* 11:8   Sequencing counter status*/
    UNUM16  rsvd2:4; /* 15:12  reserved */
};

union ADCASEQSR_REG
{
   UNUM16                 all;
   struct ADCASEQSR_BITS  bit;
};

struct ADCMAXCONV_BITS
{ /* bits  description*/
    UNUM16  MAX_CONV1:4; /* 3:0   Max number of conversions*/
    UNUM16  MAX_CONV2:3; /* 6:4   Max number of conversions */
    UNUM16  rsvd1:9; /* 15:7  reserved */
};

union ADCMAXCONV_REG
{
   UNUM16                  all;
   struct ADCMAXCONV_BITS  bit;
};

struct ADCCHSELSEQ1_BITS
{ /* bits   description*/
    UNUM16  CONV00:4; /* 3:0    Conversion selection 00*/
    UNUM16  CONV01:4; /* 7:4    Conversion selection 01*/
    UNUM16  CONV02:4; /* 11:8   Conversion selection 02*/
    UNUM16  CONV03:4; /* 15:12  Conversion selection 03*/
};

union  ADCCHSELSEQ1_REG
{
   UNUM16                    all;
   struct ADCCHSELSEQ1_BITS  bit;
};

struct ADCCHSELSEQ2_BITS
{ /* bits   description*/
    UNUM16  CONV04:4; /* 3:0    Conversion selection 04*/
    UNUM16  CONV05:4; /* 7:4    Conversion selection 05*/
    UNUM16  CONV06:4; /* 11:8   Conversion selection 06*/
    UNUM16  CONV07:4; /* 15:12  Conversion selection 07*/
};

union  ADCCHSELSEQ2_REG
{
   UNUM16                    all;
   struct ADCCHSELSEQ2_BITS  bit;
};

struct ADCCHSELSEQ3_BITS
{ /* bits   description*/
    UNUM16  CONV08:4; /* 3:0    Conversion selection 08*/
    UNUM16  CONV09:4; /* 7:4    Conversion selection 09*/
    UNUM16  CONV10:4; /* 11:8   Conversion selection 10*/
    UNUM16  CONV11:4; /* 15:12  Conversion selection 11*/
};

union  ADCCHSELSEQ3_REG
{
   UNUM16                    all;
   struct ADCCHSELSEQ3_BITS  bit;
};

struct ADCCHSELSEQ4_BITS
{ /* bits   description*/
    UNUM16  CONV12:4; /* 3:0    Conversion selection 12*/
    UNUM16  CONV13:4; /* 7:4    Conversion selection 13*/
    UNUM16  CONV14:4; /* 11:8   Conversion selection 14*/
    UNUM16  CONV15:4; /* 15:12  Conversion selection 15*/
};

union  ADCCHSELSEQ4_REG
{
   UNUM16                    all;
   struct ADCCHSELSEQ4_BITS  bit;
};

struct ADCTRL3_BITS
{ /* bits   description*/
    UNUM16   SMODE_SEL:1; /* 0      Sampling mode select*/
    UNUM16   ADCCLKPS:4; /* 4:1    ADC core clock divider*/
    UNUM16   ADCPWDN:1; /* 5      ADC powerdown*/
    UNUM16   ADCBGRFDN:2; /* 7:6    ADC bandgap/ref power down*/
    UNUM16   rsvd1:8; /* 15:8   reserved*/
}; 

union  ADCTRL3_REG
{
   UNUM16                all;
   struct ADCTRL3_BITS   bit;
};

struct ADCST_BITS
{ /* bits   description*/
    UNUM16   INT_SEQ1:1; /* 0      SEQ1 Interrupt flag  */
    UNUM16   INT_SEQ2:1; /* 1      SEQ2 Interrupt flag*/
    UNUM16   SEQ1_BSY:1; /* 2      SEQ1 busy status*/
    UNUM16   SEQ2_BSY:1; /* 3      SEQ2 busy status*/
    UNUM16   INT_SEQ1_CLR:1; /* 4      SEQ1 Interrupt clear*/
    UNUM16   INT_SEQ2_CLR:1; /* 5      SEQ2 Interrupt clear*/
    UNUM16   EOS_BUF1:1; /* 6      End of sequence buffer1*/
    UNUM16   EOS_BUF2:1; /* 7      End of sequence buffer2*/
    UNUM16   rsvd1:8; /* 15:8   reserved*/
};

union  ADCST_REG
{
   UNUM16             all;    
   struct ADCST_BITS  bit;    
};                           

struct ADCREFSEL_BITS
{ /* bits   description*/
	UNUM16   rsvd1:14; /* 13:0   reserved  */
	UNUM16   REF_SEL:2; /* 15:14  Reference select*/
};

union ADCREFSEL_REG
{
	UNUM16		all;
	struct ADCREFSEL_BITS bit;
};

struct ADCOFFTRIM_BITS
{ /* bits   description*/
	SNUM16	OFFSET_TRIM:9; /* 8:0    Offset Trim  */
	UNUM16	rsvd1:7; /* 15:9   reserved*/
};

union ADCOFFTRIM_REG
{
	UNUM16		all;
	struct ADCOFFTRIM_BITS bit;
};

struct ADC_REGS
{
    union ADCTRL1_REG      ADCTRL1; /* ADC Control 1*/
    union ADCTRL2_REG      ADCTRL2; /* ADC Control 2*/
    union ADCMAXCONV_REG   ADCMAXCONV; /* Max conversions*/
    union ADCCHSELSEQ1_REG ADCCHSELSEQ1; /* Channel select sequencing control 1*/
    union ADCCHSELSEQ2_REG ADCCHSELSEQ2; /* Channel select sequencing control 2*/
    union ADCCHSELSEQ3_REG ADCCHSELSEQ3; /* Channel select sequencing control 3*/
    union ADCCHSELSEQ4_REG ADCCHSELSEQ4; /* Channel select sequencing control 4*/
    union ADCASEQSR_REG    ADCASEQSR; /* Autosequence status register*/
    UNUM16                 ADCRESULT0; /* Conversion Result Buffer 0*/
    UNUM16                 ADCRESULT1; /* Conversion Result Buffer 1*/
    UNUM16                 ADCRESULT2; /* Conversion Result Buffer 2*/
    UNUM16                 ADCRESULT3; /* Conversion Result Buffer 3*/
    UNUM16                 ADCRESULT4; /* Conversion Result Buffer 4*/
    UNUM16                 ADCRESULT5; /* Conversion Result Buffer 5*/
    UNUM16                 ADCRESULT6; /* Conversion Result Buffer 6*/
    UNUM16                 ADCRESULT7; /* Conversion Result Buffer 7*/
    UNUM16                 ADCRESULT8; /* Conversion Result Buffer 8*/
    UNUM16                 ADCRESULT9; /* Conversion Result Buffer 9*/
    UNUM16                 ADCRESULT10; /* Conversion Result Buffer 10*/
    UNUM16                 ADCRESULT11; /* Conversion Result Buffer 11*/
    UNUM16                 ADCRESULT12; /* Conversion Result Buffer 12*/
    UNUM16                 ADCRESULT13; /* Conversion Result Buffer 13*/
    UNUM16                 ADCRESULT14; /* Conversion Result Buffer 14*/
    UNUM16                 ADCRESULT15; /* Conversion Result Buffer 15*/
    union ADCTRL3_REG      ADCTRL3; /* ADC Control 3  */
    union ADCST_REG        ADCST; /* ADC Status Register*/
    UNUM16				   rsvd1;
    UNUM16                 rsvd2;
    union ADCREFSEL_REG    ADCREFSEL; /* Reference Select Register*/
    union ADCOFFTRIM_REG   ADCOFFTRIM; /* Offset Trim Register*/
};

struct ADC_RESULT_MIRROR_REGS
{
    UNUM16                 ADCRESULT0; /* Conversion Result Buffer 0*/
    UNUM16                 ADCRESULT1; /* Conversion Result Buffer 1*/
    UNUM16                 ADCRESULT2; /* Conversion Result Buffer 2*/
    UNUM16                 ADCRESULT3; /* Conversion Result Buffer 3*/
    UNUM16                 ADCRESULT4; /* Conversion Result Buffer 4*/
    UNUM16                 ADCRESULT5; /* Conversion Result Buffer 5*/
    UNUM16                 ADCRESULT6; /* Conversion Result Buffer 6*/
    UNUM16                 ADCRESULT7; /* Conversion Result Buffer 7*/
    UNUM16                 ADCRESULT8; /* Conversion Result Buffer 8*/
    UNUM16                 ADCRESULT9; /* Conversion Result Buffer 9*/
    UNUM16                 ADCRESULT10; /* Conversion Result Buffer 10*/
    UNUM16                 ADCRESULT11; /* Conversion Result Buffer 11*/
    UNUM16                 ADCRESULT12; /* Conversion Result Buffer 12*/
    UNUM16                 ADCRESULT13; /* Conversion Result Buffer 13*/
    UNUM16                 ADCRESULT14; /* Conversion Result Buffer 14*/
    UNUM16                 ADCRESULT15; /* Conversion Result Buffer 15*/
};

extern volatile struct ADC_REGS ADC_AdcRegs;
extern volatile struct ADC_RESULT_MIRROR_REGS ADC_AdcMirror;

#endif

/***************************************************************************
End of file.
***************************************************************************/
