;******************************************************************************
;*                                                                             *
;*           COPYRIGHT (C)    SAE   *
;*                         ALL RIGHTS RESERVED                                 *
;*                                                                             *
;*    The copying, use, distribution or disclosure of the confidential and     *
;*    proprietary information contained in this document(s) is strictly        *
;*    prohibited without prior written consent. Any breach shall subject       *
;*    the infringing party to remedies. The owner reserves all rights in       *
;*    the event of the grant of a patent or the registration of a utility      *
;*    model or design.                                                         *
;*                                                                             *
;*-----------------------------------------------------------------------------*
;*                                                                             *
;*     Module Description:  module handles 32 bit integer division             *
;*     Module Name:         %name:      l_div.asm %                                     *
;*     Module Version:      %version:   1 %                                     *
;*                                                                             *
;*-----------------------------------------------------------------------------*
;*                                                                             *
;*     Compiler:    CCS 5.4                                                    *
;*                                                                             *
;*     Controller:  TMS320F28335                                               *
;*                                                                             *
;*-----------------------------------------------------------------------------*
;*                                                                             *
;*     Creator:    ZYR 2014-1-4                                                *
;*     Author:                                                                 *
;*                 %created_by:  maolei %                                         *
;*                                                                             *
;*     Date:       %date_modified:  Fri Apr 20 13:01:31 2012 %                 *
;*                                                                             *
;*******************************************************************************/


******************************************************************************
* This module contains the functions for 32-bit divide and modulus, signed and
* unsigned.  This stack map and these defines apply to all the routines in
* this module.
*
* SYMBOL DEFINITIONS:
*
* DEN   - denominator
*
******************************************************************************
; Numerator passed in ACC, denominator is on stack
;


******************************************************************************
* SET UP ALIASES FOR STACK REFERENCES AND REGISTERS USED
******************************************************************************
	.asg	*-SP[2],DEN	; denominator

	.page
******************************************************************************
* 32-bit SIGNED DIVIDE, CALCULATE NUM / DEN AND RETURN IN ACCUMULATOR
******************************************************************************
	.global	L$$DIV

L$$DIV:		.asmfunc
******************************************************************************
* DETERMINE SIGN OF RESULT, TAKE ABSOLUTE VALUE OF OPERANDS
******************************************************************************
	CLRC	OVM		; Clear the OVM bit to get desired effect on
				; the ABS instruction.
	CLRC	TC		; Clear TC flag, used to store sign
	ABSTC	ACC		; Take absolute value, TC = sign ^ TC
	MOVL	P, ACC		; Load P register with the numerator
	MOVL	ACC, DEN	; Load the denominator
	ABSTC	ACC		; Take absolute value, TC = sign ^ TC
	MOVL	DEN, ACC	; Move |denomiator| to DEN

******************************************************************************
* PERFORM DIVIDE
******************************************************************************
	MOVB	ACC, #0		; Clear ACC to perform the division.
	RPT	#31		;
     || SUBCUL	ACC, DEN	; Divide numerator by the denominator; the
				; quotient is in P and the remainder is in ACC

	MOVL	ACC, @P		; Load the quotient into ACC
	NEGTC	ACC		; Negate ACC if TC = 1

	CLRC	OVM		; Clear the OVM bit
	FFCRET	*XAR7		; return
	.endasmfunc



	.page
******************************************************************************
* 32-bit SIGNED MODULUS, CALCULATE NUM % DEN AND RETURN IN ACCUMULATOR
******************************************************************************
	.global	L$$MOD

L$$MOD:		.asmfunc
******************************************************************************
* DETERMINE SIGN OF RESULT, TAKE ABSOLUTE VALUE OF OPERANDS
******************************************************************************
        CLRC    OVM             ; Clear the OVM bit to get desired effect on
                                ; the ABS instruction.
        CLRC    TC              ; Clear TC flag, used to store sign
        ABSTC   ACC             ; Take absolute value, TC = sign ^ TC
        MOVL    P, ACC          ; Load P register with the numerator
        MOVL    ACC, DEN        ; Load the denominator
        ABS     ACC             ; Take absolute value, TC = sign ^ TC
        MOVL    DEN, ACC        ; Move |denomiator| to DEN.

******************************************************************************
* PERFORM DIVIDE
******************************************************************************
        MOVB    ACC, #0         ; Clear ACC to perform the division.
        RPT     #31             ;
     || SUBCUL	ACC, DEN	; Divide numerator by the denominator; the
				; quotient is in P and the remainder is in ACC

        NEGTC   ACC             ; Negate ACC if TC = 1

        CLRC    OVM             ; Clear the OVM bit
	FFCRET	*XAR7		; return
	.endasmfunc



	.page
******************************************************************************
* 32-bit UNSIGNED DIVIDE, CALCULATE NUM / DEN AND RETURN IN ACCUMULATOR
******************************************************************************
	.global	UL$$DIV

UL$$DIV:	.asmfunc
	MOVL	P, ACC		; Load the numerator into P

******************************************************************************
* PERFORM DIVIDE
******************************************************************************
        MOVB    ACC, #0         ; Clear ACC to perform the division.
        RPT     #31             ;
     || SUBCUL	ACC, DEN	; Divide numerator by the denominator; the
				; quotient is in P and the remainder is in ACC

	MOVL	ACC, P		; Load the quotient into return register.
	FFCRET	*XAR7		; return
	.endasmfunc

******************************************************************************
* 32-bit UNSIGNED MODULUS, CALCULATE NUM % DEN AND RETURN IN ACCUMULATOR
******************************************************************************
	.global	UL$$MOD

UL$$MOD:	.asmfunc
	MOVL	P, ACC		; Load the numerator into P

******************************************************************************
* PERFORM DIVIDE
******************************************************************************
        MOVB    ACC, #0         ; Clear ACC to perform the division.
        RPT     #31             ;
     || SUBCUL	ACC, DEN	; Divide numerator by the denominator; the
				; quotient is in P and the remainder is in ACC

	FFCRET	*XAR7		; return
	.endasmfunc
