/*******************************************************************
*                  SAE COPYRIGHT (C) SAEShanghai, China            *
*                                ALL RIGHTS RESERVED               *
* The copying, use, distribution or disclosure of the confidential *
* and proprietary information contained in this document(s) is     *
* strictly prohibited without prior written consent. Any breach    *
* shall subject the infringing party to remedies. The owner        *
* reserves all rights in the event of the grant of a patent or the *
* registration of a utility model or design.                       *
*------------------------------------------------------------------*
*                             MODULE DESCRIPTION                   *
* Module Name:         I2C                                         *
* Module Version:                                                  *
*------------------------------------------------------------------*
* Original Author: HuangLiling                                     *
* Date:20170303                                                    *
*------------------------------------------------------------------*
*                                CHANGE HISTORY                    *
* DATE         Modifier         DESCRIPTION                        *
*2017/04/05 huangliling Code optimization according to the SCS(CR452)*
*2017/04/10 huangliling update IIC code according to bootload IIC(CR455)*
* *****************************************************************/
#ifndef __I2C_H__
#define __I2C_H__

/*****************************Includes*****************************/
#include "DEVICE.h"

/*************Definitions******************************************/
#define au16_I2C_SlaveAddr  0x50

/* Error Messages */
#define I2C_ERROR               ((UNUM16)0xFFFFU)
#define I2C_ARB_LOST_ERROR      ((UNUM16)0x0001)
#define I2C_NACK_ERROR          ((UNUM16)0x0002)
#define I2C_BUS_BUSY_ERROR      ((UNUM16)0x1000)
#define I2C_STP_NOT_READY_ERROR ((UNUM16)0x5555)
#define I2C_NO_FLAGS            ((UNUM16)0xAAAA)
#define I2C_SUCCESS             ((UNUM16)0x0000)
#define EEPROM_BLOCK_LEN        ((UNUM16)128)

/* Clear Status Flags */
#define I2C_CLR_AL_BIT          ((UNUM16)0x0001)
#define I2C_CLR_NACK_BIT        ((UNUM16)0x0002)
#define I2C_CLR_ARDY_BIT        ((UNUM16)0x0004)
#define I2C_CLR_RRDY_BIT        ((UNUM16)0x0008)
#define I2C_CLR_SCD_BIT         ((UNUM16)0x0020)

/* Interrupt Source Messages */
#define I2C_NO_ISRC             ((UNUM16)0x0000)
#define I2C_ARB_ISRC            ((UNUM16)0x0001)
#define I2C_NACK_ISRC           ((UNUM16)0x0002)
#define I2C_ARDY_ISRC           ((UNUM16)0x0003)
#define I2C_RX_ISRC             ((UNUM16)0x0004)
#define I2C_TX_ISRC             ((UNUM16)0x0005)
#define I2C_SCD_ISRC            ((UNUM16)0x0006)
#define I2C_AAS_ISRC            ((UNUM16)0x0007)

/* I2CMSG structure defines */
#define I2C_NO_STOP             ((UNUM16)0)
#define I2C_YES_STOP            ((UNUM16)1)
#define I2C_RECEIVE             ((UNUM16)0)
#define I2C_TRANSMIT            ((UNUM16)1)
#define I2C_MAX_BUFFER_SIZE     ((UNUM16)10)

/* I2C Slave State defines */
#define I2C_NOTSLAVE            ((UNUM16)0)
#define I2C_ADDR_AS_SLAVE       ((UNUM16)1)
#define I2C_ST_MSG_READY        ((UNUM16)2)

/* I2C Slave Receiver messages defines */
#define I2C_SND_MSG1            ((UNUM16)1)
#define I2C_SND_MSG2            ((UNUM16)2)

/* I2C State defines*/
#define I2C_IDLE                ((UNUM16)0)
#define I2C_SLAVE_RECEIVER      ((UNUM16)1)
#define I2C_SLAVE_TRANSMITTER   ((UNUM16)2)
#define I2C_MASTER_RECEIVER     ((UNUM16)3)
#define I2C_MASTER_TRANSMITTER  ((UNUM16)4)

/* I2C  Message Commands for I2CMSG struct */
#define I2C_MSGSTAT_INACTIVE          ((UNUM16)0x000)
#define I2C_MSGSTAT_SEND_WITHSTOP     ((UNUM16)0x001)
#define I2C_MSGSTAT_WRITE_BUSY        ((UNUM16)0x001)
#define I2C_MSGSTAT_SEND_NOSTOP       ((UNUM16)0x002)
#define I2C_MSGSTAT_SEND_NOSTOP_BUSY  ((UNUM16)0x002)
#define I2C_MSGSTAT_RESTART           ((UNUM16)0x002)
#define I2C_MSGSTAT_READ_BUSY         ((UNUM16)0x0023)

/* Generic defines */
#define I2C_TRUE                ((UNUM16)1)
#define I2C_FALSE               ((UNUM16)0)
#define I2C_YES                 ((UNUM16)1)
#define I2C_NO                  ((UNUM16)0)
#define I2C_DUMMY_BYTE 0

#define I2C_SLAVE_ADDR          ((UNUM16)0x50)
#define I2C_NUMBYTES            ((UNUM16)8)
#define I2C_EEPROM_HIGH_ADDR    ((UNUM16)0x00)
#define I2C_EEPROM_LOW_ADDR     ((UNUM16)0x30)

/* I2C operation timeout defines */
#define I2C_TIMEOUT_PER_TX               ((UNUM32)15) /* 5ms timeout for per TX operation */
#define I2C_TIMEOUT_PER_RX               ((UNUM32)10) /* 5ms timeout for per RX operation */

/* I2C interrupt vector register bit definitions */
struct I2CISRC_BITS {         /* bits   description */
    UNUM16 INTCODE:3;          /* 2:0    Interrupt code */
    UNUM16 rsvd1:13;           /* 15:3   reserved */
};

union I2CISRC_REG {
    UNUM16                  all;
    struct I2CISRC_BITS     bit;
};

struct I2CIER_BITS {              /* bits    description*/
    UNUM16 ARBL :1;               /* 0        Arbitration lost interrupt*/
    UNUM16 NACK :1;               /* 1        No ack interrupt*/
    UNUM16 ARDY :1;               /* 2        Register access ready interrupt*/
    UNUM16 RRDY :1;               /* 3        Recieve data ready interrupt*/
    UNUM16 XRDY :1;               /* 4        Transmit data ready interrupt*/
    UNUM16 SCD  :1;               /* 5        Stop condition detection*/
    UNUM16 AAS  :1;               /* 6        Address as slave*/
    UNUM16 rsvd :9;               /* 15:7    reserved*/
};

union I2CIER_REG {
    UNUM16                   all;
    struct I2CIER_BITS       bit;
};

struct I2CSTR_BITS {              /* bits     description*/
    UNUM16 ARBL    :1;            /* 0        Arbitration lost interrupt*/
    UNUM16 NACK    :1;            /* 1        No ack interrupt*/
    UNUM16 ARDY    :1;            /* 2        Register access ready interrupt*/
    UNUM16 RRDY    :1;            /* 3        Recieve data ready interrupt*/
    UNUM16 XRDY    :1;            /* 4        Transmit data ready interrupt*/
    UNUM16 SCD     :1;            /* 5        Stop condition detection*/
    UNUM16 rsvd1   :2;            /* 7:6      reserved*/
    UNUM16 AD0     :1;            /* 8        Address Zero*/
    UNUM16 AAS     :1;            /* 9        Address as slave*/
    UNUM16 XSMT    :1;            /* 10       XMIT shift empty*/
    UNUM16 RSFULL  :1;            /* 11       Recieve shift full*/
    UNUM16 BB      :1;            /* 12       Bus busy*/
    UNUM16 NACKSNT :1;            /* 13       A no ack sent*/
    UNUM16 SDIR    :1;            /* 14       Slave direction*/
    UNUM16 rsvd2   :1;            /* 15       reserved*/
};

union I2CSTR_REG {
    UNUM16                   all;
    struct I2CSTR_BITS       bit;
};

struct I2CMDR_BITS {              /* bits     description*/
    UNUM16 BC       :3;           /* 2:0      Bit count*/
    UNUM16 FDF      :1;           /* 3        Free data format*/
    UNUM16 STB      :1;           /* 4        Start byte*/
    UNUM16 IRS      :1;           /* 5        I2C Reset not*/
    UNUM16 DLB      :1;           /* 6        Digital loopback*/
    UNUM16 RM       :1;           /* 7        Repeat mode*/
    UNUM16 XA       :1;           /* 8        Expand address*/
    UNUM16 TRX      :1;           /* 9        Transmitter/reciever*/
    UNUM16 MST      :1;           /* 10       Master/slave*/
    UNUM16 STP      :1;           /* 11       Stop condition*/
    UNUM16 rsvd1    :1;           /* 12       reserved*/
    UNUM16 STT      :1;           /* 13       Start condition*/
    UNUM16 FREE     :1;           /* 14       Emulation mode*/
    UNUM16 NACKMOD  :1;           /* 15       No Ack mode*/
};

union I2CMDR_REG {
    UNUM16                   all;
    struct I2CMDR_BITS       bit;
};

struct I2CPSC_BITS {
    UNUM16 IPSC    :8;              /* 7:0     pre-scaler*/
    UNUM16 rsvd1   :8;              /* 15:8    reserved*/
};

union I2CPSC_REG {
    UNUM16                   all;
    struct I2CPSC_BITS       bit;
};

struct I2CFFTX_BITS {
    UNUM16 TXFFIL       :5;             /* 4:0     FIFO interrupt level*/
    UNUM16 TXFFIENA     :1;             /* 5        FIFO interrupt enable/disable*/
    UNUM16 TXFFINTCLR   :1;             /* 6        FIFO clear*/
    UNUM16 TXFFINT      :1;             /* 7        FIFO interrupt flag*/
    UNUM16 TXFFST       :5;             /* 12:8    FIFO level status*/
    UNUM16 TXFFRST      :1;             /* 13       FIFO reset*/
    UNUM16 I2CFFEN      :1;             /* 14       enable/disable TX & RX FIFOs*/
    UNUM16 rsvd1        :1;             /* 15       reserved*/

};

union I2CFFTX_REG {
    UNUM16                  all;
    struct I2CFFTX_BITS     bit;
};

struct I2CFFRX_BITS {
    UNUM16 RXFFIL       :5;               /* 4:0      FIFO interrupt level*/
    UNUM16 RXFFIENA     :1;               /* 5        FIFO interrupt enable/disable*/
    UNUM16 RXFFINTCLR   :1;               /* 6        FIFO clear*/
    UNUM16 RXFFINT      :1;               /* 7        FIFO interrupt flag*/
    UNUM16 RXFFST       :5;               /* 12:8     FIFO level*/
    UNUM16 RXFFRST      :1;               /* 13       FIFO reset*/
    UNUM16 rsvd1        :2;               /* 15:14    reserved*/
};

union I2CFFRX_REG {
    UNUM16                  all;
    struct I2CFFRX_BITS     bit;
};

struct I2C_REGS {
    UNUM16                    I2COAR;     /* Own address register*/
    union  I2CIER_REG         I2CIER;     /* Interrupt enable*/
    union  I2CSTR_REG         I2CSTR;     /* Interrupt status*/
    UNUM16                    I2CCLKL;    /* Clock divider low*/
    UNUM16                    I2CCLKH;    /* Clock divider high*/
    UNUM16                    I2CCNT;     /* Data count*/
    UNUM16                    I2CDRR;     /* Data recieve*/
    UNUM16                    I2CSAR;     /* Slave address*/
    UNUM16                    I2CDXR;     /* Data transmit*/
    union  I2CMDR_REG         I2CMDR;     /* Mode*/
    union  I2CISRC_REG        I2CISRC;    /* Interrupt source*/
    UNUM16                    rsvd1;      /* reserved*/
    union  I2CPSC_REG         I2CPSC;     /* Pre-scaler*/
    UNUM16                    rsvd2[19];  /* reserved */
    union  I2CFFTX_REG        I2CFFTX;    /* Transmit FIFO */
    union  I2CFFRX_REG        I2CFFRX;    /* Recieve FIFO */
};

typedef enum
{
    I2C_WR_STA_ADDR = 0,
    I2C_WR_STA_W4DATA,
    I2C_WR_STA_DATA,
    I2C_WR_STA_W4_END
}I2C_WR_STATE;

typedef enum
{
    I2C_RD_STA_ADDR = 0,
    I2C_RD_STA_W4DATA,
    I2C_RD_STA_DATA,
    I2C_RD_STA_W4_END
}I2C_RD_STATE;

/*************Variable Declarations********************************/
extern volatile struct I2C_REGS I2caRegs;

/*************Functions Declarations*******************************/
void  I2C_Init(void);
void  I2C_InitGpio(void);
UNUM16 I2C_CheckRegister( void );
UNUM16  I2C_Read(UNUM16 *ap_I2C_Buffer,UNUM16 au16_I2C_Address,UNUM16 au16_DataLen);
UNUM16  I2C_Write( UNUM16 *ap_I2C_Buffer,UNUM16 au16_I2C_Address,UNUM16 au16_DataLen);

#endif
/****************end of file***************************************/
