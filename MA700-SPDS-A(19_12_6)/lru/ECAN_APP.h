/****************************************************************************
*                                                                           *
*                         COPYRIGHT (C)   SAE      	    					*
*                         ALL RIGHTS RESERVED                               *
*                                                                           *
*    The copying, use, distribution or disclosure of the confidential and   *
*    proprietary information contained in this document(s) is strictly      *
*    prohibited without prior written consent. Any breach shall subject     *
*    the infringing party to remedies. The owner reserves all rights in     *
*    the event of the grant of a patent or the registration of a utility    *
*    model or design.                                                       *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Module Description:  module to provide a realtime scheduler	        *
*     Module Name:         %name:     ECAN_APP.h %                          *
*     Module Version:      %version:  2 %                                   *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Compiler:	  		                                          			*
*                                                                           *
*     Controller:                                             				*
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Author:                                  								*
*				  %created_by:        mason                                 *
*									                                        *
*     Date:       %date_modified:  2014-12-03 %                 			*
*                                                                           *
****************************************************************************/
#ifndef __ECAN_APP_H__
#define __ECAN_APP_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"
#include "COMMON.h"

/**** definitions*************************************************************/
#define CAN_DATA_SIZE                  4                /* the MIN size of a CAN message in CAN buffer */
#define CAN_REC_MSG_ID_MASK	           0x1FFFFFFF       /* the mask of CAN message ID */

#define CAN_CUR_FRAME_0 		0
#define CAN_CUR_FRAME_1 		1
#define CAN_CUR_FRAME_2			2
#define CAN_CUR_FRAME_3 		3
#define CAN_CUR_FRAME_4 		4
#define CAN_CUR_FRAME_5 		5
#define CAN_CUR_FRAME_6 		6
#define CAN_CUR_FRAME_7 		7
#define CAN_CUR_FRAME_8 		8
#define CAN_CUR_FRAME_9 		9
#define CAN_CUR_FRAME_10 		10
#define CAN_CUR_FRAME_11 		11
#define CAN_CUR_FRAME_12 		12
#define CAN_CUR_FRAME_13 		13
#define CAN_CUR_FRAME_14 		14




struct CAN_Re_Message
{
	UNUM32 mu32_ID;                         /* CAN message ID */
	UNUM16 mu16_Length;                     /* CAN message length */
	UNUM32 mu32_HighBytes;                  /* CAN message high bytes */
	UNUM32 mu32_LowBytes;                   /* CAN message low bytes */
	UNUM16 mu16_ReOKFlag;                   /* the flag of CAN message receive: TRUE receive successfully; FALSE receive failed */

	UNUM16 mu16_CBIT_FaultFlag;				/* fault flag */
	UNUM16 mu16_CBIT_FaultCounter;			/* fault counter */
	UNUM16 mu16_CBIT_FaultAddupCounter;		/* fault Add-up Counter */
	UNUM16 mu16_CBIT_FaultRecordFlag;		/* fault record flag */
	UNUM16 mu16_CBIT_FaultID;
	/*UNUM16 mu16_CBIT_FaultRecordAddress;*/	/* fault record address */
};

extern struct CAN_Re_Message ECAN_APP_ms_Msg_Re[3];               /* the received messages: CASM and ODCM PDCM IDCM */

/**** functions declarations *************************************************/
void ECAN_APP_Init( void );

void ECAN_APP_HandleRecBuffer( void );

extern void ECAN_APP_TransmitProcess(void);
extern void ECAN_APP_ReceiveProcess(void);

SNUM16 ECAN_APP_GetMessage( struct CAN_Re_Message* ap_CAN_Message, SNUM16 as16_DataNumber );

#endif
/***************************************************************************
End of file.
***************************************************************************/
