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
*     Module Name:         %name:     CAN_BUF.h %                        *
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
*				  %created_by:   maolei % Laspide                      *
*									                                        *
*     Date:       %date_modified:  2014-12-03 %                 			*
*                                                                           *
****************************************************************************/
#ifndef __CAN_BUFFER_H__
#define __CAN_BUFFER_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"

/**** definitions*************************************************************/
/* For 500kbps, in 5ms, there are nearly 15 CAN messages, one message need 4 store room */
#define CAN_BUF_MAX_SIZE	64				            /* MAX size for CAN receive buffer */
extern UNUM16 gu16_InputPosition;               /* the input position of CAN receive buffer */
extern UNUM16 gu16_OutputPosition;              /* the output position of CAN receive buffer */
extern SNUM16 gs16_DataCount;                   /* the number of data in CAN receive buffer */
extern UNUM32 gu32_Array[CAN_BUF_MAX_SIZE];

/**** functions declarations *************************************************/
void CAN_BUF_Init( void );

UNUM32 CAN_BUF_GetData( void );

void CAN_BUF_PutData( UNUM32 au32_REC_Data );

#endif
/***************************************************************************
End of file.
***************************************************************************/
