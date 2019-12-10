/******************************************************************************
*                                                                             *
*           COPYRIGHT (C)    SAE    *
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
*     Module Description:             *
*     Module Name:         %name:     spi.h %                           *
*     Module Version:      %version:  8 %                                     *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	  	                                          * 
*                                                                             * 
*     Controller:                                            *
*                                                                             * 
*-----------------------------------------------------------------------------*
*                                                                             *   
*     Author:                                   *
*                 %created_by:   wangjian %                                     *
*                                    									      *									  
*     Date:       %date_modified:  Tue Apr 10 11:48:07 2012 % 			      *
*                                                                             *  
*******************************************************************************/


#ifndef __SPI_H__
#define __SPI_H__

/**** include *************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"

/*	spi check state	*/
#define SPI_OK       0
#define SPI_ERROR    1

#define SPI_CH_BASE		0x1000U /*0x185A 0x4000*/
#define SPI_CH_OFFSET	0x0180U


/*---------------------------------------------------------------------------*/
/* SPI Individual Register Bit Definitions:*/

/* SPI FIFO Transmit register bit    definitions:*/
struct  SPIFFTX_BITS {       /* bit    description*/
   UNUM16 TXFFIL:5;          /* 4:0    Interrupt level*/
   UNUM16 TXFFIENA:1;        /* 5      Interrupt enable*/
   UNUM16 TXFFINTCLR:1;      /* 6      Clear INT flag*/
   UNUM16 TXFFINT:1;         /* 7      INT flag*/
   UNUM16 TXFFST:5;          /* 12:8   FIFO status*/
   UNUM16 TXFIFO:1;          /* 13     FIFO reset*/
   UNUM16 SPIFFENA:1;        /* 14     Enhancement enable*/
   UNUM16 SPIRST:1;          /* 15     Reset SPI*/
};

union SPIFFTX_REG {
   UNUM16               all;
   struct SPIFFTX_BITS  bit;
};

/*--------------------------------------------*/
/* SPI FIFO recieve register bit definitions:*/


struct  SPIFFRX_BITS {       /* bits   description*/
   UNUM16 RXFFIL:5;          /* 4:0    Interrupt level*/
   UNUM16 RXFFIENA:1;        /* 5      Interrupt enable*/
   UNUM16 RXFFINTCLR:1;      /* 6      Clear INT flag*/
   UNUM16 RXFFINT:1;         /* 7      INT flag*/
   UNUM16 RXFFST:5;          /* 12:8   FIFO status*/
   UNUM16 RXFIFORESET:1;     /* 13     FIFO reset*/
   UNUM16 RXFFOVFCLR:1;      /* 14     Clear overflow*/
   UNUM16 RXFFOVF:1;         /* 15     FIFO overflow*/

};

union SPIFFRX_REG {
   UNUM16               all;
   struct SPIFFRX_BITS  bit;
};

/*--------------------------------------------*/
/* SPI FIFO control register bit definitions:*/


struct  SPIFFCT_BITS {       /* bits   description*/
   UNUM16 TXDLY:8;           /* 7:0    FIFO transmit delay*/
   UNUM16 rsvd:8;            /* 15:8   reserved*/
};

union SPIFFCT_REG {
   UNUM16               all;
   struct SPIFFCT_BITS  bit;
};

/*---------------------------------------------*/
/* SPI configuration register bit definitions:*/


struct  SPICCR_BITS {        /* bits   description*/
   UNUM16 SPICHAR:4;         /* 3:0    Character length control*/
   UNUM16 SPILBK:1;          /* 4      Loop-back enable/disable*/
   UNUM16 rsvd1:1;           /* 5      reserved*/
   UNUM16 CLKPOLARITY:1;     /* 6      Clock polarity*/
   UNUM16 SPISWRESET:1;      /* 7      SPI SW Reset*/
   UNUM16 rsvd2:8;           /* 15:8   reserved*/
};

union SPICCR_REG {
   UNUM16              all;
   struct SPICCR_BITS  bit;
};

/*-------------------------------------------------*/
/* SPI operation control register bit definitions:*/


struct  SPICTL_BITS {        /* bits   description*/
   UNUM16 SPIINTENA:1;       /* 0      Interrupt enable*/
   UNUM16 TALK:1;            /* 1      Master/Slave transmit enable*/
   UNUM16 MASTER_SLAVE:1;    /* 2      Network control mode*/
   UNUM16 CLK_PHASE:1;       /* 3      Clock phase select*/
   UNUM16 OVERRUNINTENA:1;   /* 4      Overrun interrupt enable*/
   UNUM16 rsvd:11;           /* 15:5   reserved*/
};

union SPICTL_REG {
   UNUM16              all;
   struct SPICTL_BITS  bit;
};

/*--------------------------------------*/
/* SPI status register bit definitions:*/


struct  SPISTS_BITS {        /* bits   description*/
   UNUM16 rsvd1:5;           /* 4:0    reserved*/
   UNUM16 BUFFULL_FLAG:1;    /* 5      SPI transmit buffer full flag*/
   UNUM16 INT_FLAG:1;        /* 6      SPI interrupt flag*/
   UNUM16 OVERRUN_FLAG:1;    /* 7      SPI reciever overrun flag*/
   UNUM16 rsvd2:8;           /* 15:8   reserved*/
};

union SPISTS_REG {
   UNUM16              all;
   struct SPISTS_BITS  bit;
};

/*------------------------------------------------*/
/* SPI priority control register bit definitions:*/


struct  SPIPRI_BITS {        /* bits   description*/
   UNUM16 rsvd1:4;           /* 3:0    reserved*/
   UNUM16 FREE:1;            /* 4      Free emulation mode control*/
   UNUM16 SOFT:1;            /* 5      Soft emulation mode control*/
   UNUM16 rsvd2:1;           /* 6      reserved*/
   UNUM16 rsvd3:9;           /* 15:7   reserved*/
};

union SPIPRI_REG {
   UNUM16              all;
   struct SPIPRI_BITS  bit;
};

/*---------------------------------------------------------------------------*/
/* SPI Register File:*/

struct  SPI_REGS {
   union SPICCR_REG     SPICCR;      /* Configuration register*/
   union SPICTL_REG     SPICTL;      /* Operation control register*/
   union SPISTS_REG     SPISTS;      /* Status register*/
   UNUM16               rsvd1;       /* reserved*/
   UNUM16               SPIBRR;      /* Baud Rate*/
   UNUM16               rsvd2;       /* reserved*/
   UNUM16               SPIRXEMU;    /* Emulation buffer*/
   UNUM16               SPIRXBUF;    /* Serial input buffer*/
   UNUM16               SPITXBUF;    /* Serial output buffer*/
   UNUM16               SPIDAT;      /* Serial data*/
   union SPIFFTX_REG    SPIFFTX;     /* FIFO transmit register*/
   union SPIFFRX_REG    SPIFFRX;     /* FIFO recieve register*/
   union SPIFFCT_REG    SPIFFCT;     /* FIFO control register*/
   UNUM16               rsvd3[2];    /* reserved*/
   union SPIPRI_REG     SPIPRI;      /* FIFO Priority control*/
};

/**** functions declarations **************************************************/

static void SPI_TX_BUF(UNUM16 au16_Ch);
static void SPI_RX_BUF(UNUM16 au16_Ch);
extern void SPI_GetResult(void);
extern UNUM16 SPI_GetChannelData(UNUM16 lu16_ChannelSN);
extern void SPI_Gpio_Init(void);
extern void SPI_Init(void);
extern UNUM16 SPI_Rece_Current(UNUM16 lu16_ChannelSN);
extern UNUM16 SPI_Rece_State(UNUM16 lu16_ChannelSN);
/*---------------------------------------------------------------------------*/
/* SPI External References & Function Declarations:*/
extern volatile struct SPI_REGS SPI_SpiaRegs;


#endif  /* end of SPI_H definition*/

/*===========================================================================*/
/* End of file.*/
/*===========================================================================*/

