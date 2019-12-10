/******************************************************************************
*                                                                             *
*               COPYRIGHT (C)     SAEShanghai, China                          *
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
*     Module Name:         %name:     SCI.h %                                 *
*     Module Version:      %version:  3.1.6 %                                     *
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
*                 %created_by:   sunxiaopeng %                                   *
*                                                                             *
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 %                 *
*                                                                             *
*******************************************************************************/
#ifndef __SCI_H__
#define __SCI_H__

/****Includes ****************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"
/***************Definitions****************************************** *********/
/**** type definitions and macros *********************************************/
#define DSP_OK    0
#define CAN_LOST  1
#define DSP_ERROR 2
#define DSP_NOISE 3

/* SCICCR communication control register bit definitions: */

struct  SCICCR_BITS {        /* bit    description */
    UNUM16 SCICHAR:3;         /* 2:0    Character length control */
    UNUM16 ADDRIDLE_MODE:1;   /* 3      ADDR/IDLE Mode control*/
    UNUM16 LOOPBKENA:1;       /* 4      Loop Back enable*/
    UNUM16 PARITYENA:1;       /* 5      Parity enable   */
    UNUM16 PARITY:1;          /* 6      Even or Odd Parity*/
    UNUM16 STOPBITS:1;        /* 7      Number of Stop Bits*/
    UNUM16 rsvd1:8;           /* 15:8   reserved*/
};


union SCICCR_REG {
    UNUM16              all;
    struct SCICCR_BITS  bit;
};

/*-------------------------------------------*/
/* SCICTL1 control register 1 bit definitions:*/
struct  SCICTL1_BITS {       /* bit    description*/
    UNUM16 RXENA:1;           /* 0      SCI receiver enable*/
    UNUM16 TXENA:1;           /* 1      SCI transmitter enable*/
    UNUM16 SLEEP:1;           /* 2      SCI sleep  */
    UNUM16 TXWAKE:1;          /* 3      Transmitter wakeup method*/
    UNUM16 rsvd:1;            /* 4      reserved*/
    UNUM16 SWRESET:1;         /* 5      Software reset   */
    UNUM16 RXERRINTENA:1;     /* 6      Recieve interrupt enable*/
    UNUM16 rsvd1:9;           /* 15:7   reserved*/

};
union SCICTL1_REG {
    UNUM16               all;
    struct SCICTL1_BITS  bit;
};

/*---------------------------------------------*/
/* SCICTL2 control register 2 bit definitions:*/


struct  SCICTL2_BITS {       /* bit    description*/
    UNUM16 TXINTENA:1;        /* 0      Transmit interrupt enable*/
    UNUM16 RXBKINTENA:1;      /* 1      Receiver-buffer break enable*/
    UNUM16 rsvd:4;            /* 5:2    reserved*/
    UNUM16 TXEMPTY:1;         /* 6      Transmitter empty flag*/
    UNUM16 TXRDY:1;           /* 7      Transmitter ready flag  */
    UNUM16 rsvd1:8;           /* 15:8   reserved*/

};

union SCICTL2_REG {
    UNUM16               all;
    struct SCICTL2_BITS  bit;
};

/*---------------------------------------------------*/
/* SCIRXST Receiver status register bit definitions:*/


struct  SCIRXST_BITS {       /* bit    description*/
    UNUM16 rsvd:1;            /* 0      reserved*/
    UNUM16 RXWAKE:1;          /* 1      Receiver wakeup detect flag*/
    UNUM16 PE:1;              /* 2      Parity error flag*/
    UNUM16 OE:1;              /* 3      Overrun error flag*/
    UNUM16 FE:1;              /* 4      Framing error flag*/
    UNUM16 BRKDT:1;           /* 5      Break-detect flag */
    UNUM16 RXRDY:1;           /* 6      Receiver ready flag*/
    UNUM16 RXERROR:1;         /* 7      Receiver error flag*/

};

union SCIRXST_REG {
    UNUM16               all;
    struct SCIRXST_BITS  bit;
};

/*----------------------------------------------------*/
/* SCIRXBUF Receiver Data Buffer with FIFO bit definitions:*/


struct  SCIRXBUF_BITS {      /* bits   description*/
    UNUM16 RXDT:8;            /* 7:0    Receive word*/
    UNUM16 rsvd:6;            /* 13:8   reserved*/
    UNUM16 SCIFFPE:1;         /* 14     SCI PE error in FIFO mode*/
    UNUM16 SCIFFFE:1;         /* 15     SCI FE error in FIFO mode*/
};

union SCIRXBUF_REG {
    UNUM16                all;
    struct SCIRXBUF_BITS  bit;
};

/*--------------------------------------------------*/
/* SCIPRI Priority control register bit definitions:*/



struct  SCIPRI_BITS {        /* bit    description*/
    UNUM16 rsvd:3;            /* 2:0    reserved*/
    UNUM16 FREE:1;            /* 3      Free emulation suspend mode*/
    UNUM16 SOFT:1;            /* 4      Soft emulation suspend mode*/
    UNUM16 rsvd1:3;           /* 7:5    reserved*/
};

union SCIPRI_REG {
    UNUM16              all;
    struct SCIPRI_BITS  bit;
};

/*-------------------------------------------------*/
/* SCI FIFO Transmit register bit definitions:*/



struct  SCIFFTX_BITS {       /* bit    description*/
    UNUM16 TXFFIL:5;          /* 4:0    Interrupt level*/
    UNUM16 TXFFIENA:1;        /* 5      Interrupt enable*/
    UNUM16 TXFFINTCLR:1;      /* 6      Clear INT flag*/
    UNUM16 TXFFINT:1;         /* 7      INT flag*/
    UNUM16 TXFFST:5;          /* 12:8   FIFO status*/
    UNUM16 TXFIFOXRESET:1;    /* 13     FIFO reset*/
    UNUM16 SCIFFENA:1;        /* 14     Enhancement enable*/
    UNUM16 SCIRST:1;          /* 15     SCI reset rx/tx channels */

};

union SCIFFTX_REG {
    UNUM16               all;
    struct SCIFFTX_BITS  bit;
};

/*------------------------------------------------*/
/* SCI FIFO recieve register bit definitions:*/


struct  SCIFFRX_BITS {       /* bits   description*/
    UNUM16 RXFFIL:5;          /* 4:0    Interrupt level*/
    UNUM16 RXFFIENA:1;        /* 5      Interrupt enable*/
    UNUM16 RXFFINTCLR:1;      /* 6      Clear INT flag*/
    UNUM16 RXFFINT:1;         /* 7      INT flag*/
    UNUM16 RXFFST:5;          /* 12:8   FIFO status*/
    UNUM16 RXFIFORESET:1;     /* 13     FIFO reset*/
    UNUM16 RXFFOVRCLR:1;      /* 14     Clear overflow*/
    UNUM16 RXFFOVF:1;         /* 15     FIFO overflow*/

};

union SCIFFRX_REG {
    UNUM16               all;
    struct SCIFFRX_BITS  bit;
};

/* SCI FIFO control register bit definitions:*/
struct  SCIFFCT_BITS {       /* bits   description*/
    UNUM16 FFTXDLY:8;         /* 7:0    FIFO transmit delay*/
    UNUM16 rsvd:5;            /* 12:8   reserved*/
    UNUM16 CDC:1;             /* 13     Auto baud mode enable*/
    UNUM16 ABDCLR:1;          /* 14     Auto baud clear*/
    UNUM16 ABD:1;             /* 15     Auto baud detect*/
};

union SCIFFCT_REG {
    UNUM16               all;
    struct SCIFFCT_BITS  bit;
};

/*--------------------------------------------*/
/* SCI Register File:*/

struct  SCI_REGS {
    union SCICCR_REG     SCICCR;     /* Communications control register*/
    union SCICTL1_REG    SCICTL1;    /* Control register 1*/
    UNUM16               SCIHBAUD;   /* Baud rate (high) register*/
    UNUM16               SCILBAUD;   /* Baud rate (low) register*/
    union SCICTL2_REG    SCICTL2;    /* Control register 2*/
    union SCIRXST_REG    SCIRXST;    /* Recieve status register*/
    UNUM16               SCIRXEMU;   /* Recieve emulation buffer register*/
    union SCIRXBUF_REG   SCIRXBUF;   /* Recieve data buffer  */
    UNUM16               rsvd1;      /* reserved*/
    UNUM16               SCITXBUF;   /* Transmit data buffer */
    union SCIFFTX_REG    SCIFFTX;    /* FIFO transmit register*/
    union SCIFFRX_REG    SCIFFRX;    /* FIFO recieve register*/
    union SCIFFCT_REG    SCIFFCT;    /* FIFO control register*/
    UNUM16               rsvd2;      /* reserved*/
    UNUM16               rsvd3;      /* reserved*/
    union SCIPRI_REG     SCIPRI;     /* FIFO Priority control  */
};

/**** Functions Declarations **************************************************/
/*---------------------------------------------------------------------------*/
/* SCI External References & Function Declarations:*/
extern volatile struct SCI_REGS SCI_SciaRegs;
extern volatile struct SCI_REGS SCI_ScibRegs;
extern volatile struct SCI_REGS SCI_ScicRegs;
/*** Function prototype for SCI-A ***/
extern void Sci_Init(void);                    /*This function must be called when power on*/
void SCI_Tx_Data(UNUM16 au16_data);
UNUM16 SCI_Rx_Data(void);
void SCI_Error_Process(void);

#endif  /* end of DSP2833x_SCI_H definition*/

/*===========================================================================*/
/* End of file.*/
/*===========================================================================*/
