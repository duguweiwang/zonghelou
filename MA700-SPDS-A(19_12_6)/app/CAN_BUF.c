/****************************************************************************
*                                                                           *
*                         COPYRIGHT (C)   SAE      							*
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
*     Module Name:         %name:     CAN_BUF.c %                           *
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
*				  %created_by:   maolei % Laspide                           *
*									                                        *
*     Date:       %date_modified:  2014-12-02 %                 			*
*                                                                           *
****************************************************************************/
/**** includes ***************************************************************/
#include "CAN_BUF.h"

/**** definitions*************************************************************/
UNUM16 gu16_InputPosition = (UNUM16)0;     /* the input position of CAN receive buffer */
UNUM16 gu16_OutputPosition = (UNUM16)0;    /* the output position of CAN receive buffer */
SNUM16 gs16_DataCount = (SNUM16)0;         /* the number of data in CAN receive buffer */
UNUM32 gu32_Array[CAN_BUF_MAX_SIZE];

/**** functions **************************************************************/
/*******************************************************************************
* Description:   CAN_BUF_Init
*
* Parameters:    -void
*
* Return values: -void
*******************************************************************************/
void CAN_BUF_Init( void )
{
	UNUM16 lu16_loop_i = (UNUM16)0;
	gu16_InputPosition = (UNUM16)0;
	gu16_OutputPosition = (UNUM16)0;
	gs16_DataCount = (SNUM16)0;
	for ( lu16_loop_i = (UNUM16)0; lu16_loop_i < (UNUM16)CAN_BUF_MAX_SIZE; lu16_loop_i ++ )
	{
		gu32_Array[lu16_loop_i] = (UNUM32)0;
	}
}

/*******************************************************************************
* Description:   CAN_BUF_GetData
*
* Parameters:    -void
*
* Return values: -void
*******************************************************************************/
UNUM32 CAN_BUF_GetData( void )
{
    UNUM16 lu16_CurrentPosition = (UNUM16)0;
    UNUM32 lu32_Data = (UNUM32)0;
    if ( gs16_DataCount > 0 )
    {
        lu16_CurrentPosition = gu16_OutputPosition;
        if( gu16_OutputPosition < (UNUM16)CAN_BUF_MAX_SIZE )
        {
            gu16_OutputPosition++;
        }
        if( gu16_OutputPosition == (UNUM16)CAN_BUF_MAX_SIZE )
        {
            gu16_OutputPosition = (UNUM16)0;
        }
        gs16_DataCount--;
        lu32_Data = gu32_Array[lu16_CurrentPosition];
        gu32_Array[lu16_CurrentPosition] = (UNUM16)0;
    }
    else
    {/* CAN Receive buffer is empty */
    	lu32_Data = 0xFFFFFFFFU;
    }
    return ( lu32_Data );
}

/*******************************************************************************
* Description:   CAN_BUF_PutData
*
* Parameters:    -void
*
* Return values: -void
*******************************************************************************/
void CAN_BUF_PutData( UNUM32 au32_REC_Data )
{
    if ( gs16_DataCount < CAN_BUF_MAX_SIZE )
    {
       	gu32_Array[gu16_InputPosition] = au32_REC_Data;
        if( gu16_InputPosition < (UNUM16)CAN_BUF_MAX_SIZE )
        {
            gu16_InputPosition++;
        }
        if( gu16_InputPosition == (UNUM16)CAN_BUF_MAX_SIZE )
        {
            gu16_InputPosition = (UNUM16)0;
        }
        gs16_DataCount++;
    }
    else if ( gs16_DataCount == CAN_BUF_MAX_SIZE )
    {
     	gu32_Array[gu16_InputPosition] = au32_REC_Data;
        if( gu16_InputPosition < (UNUM16)CAN_BUF_MAX_SIZE )
        {
            gu16_InputPosition++;
        }
        if( gu16_InputPosition == (UNUM16)CAN_BUF_MAX_SIZE )
        {
            gu16_InputPosition = (UNUM16)0;
        }
        gu16_OutputPosition = gu16_InputPosition;
    }
	else
	{
    }
}

/***************************************************************************
End of file.
***************************************************************************/
