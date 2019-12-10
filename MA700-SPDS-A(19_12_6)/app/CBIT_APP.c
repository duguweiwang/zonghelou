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
*     Module Name:         %name:     CBIT_APP.c %                           *
*     Module Version:      %version:  7.2.1 %                                   *
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
*				  %created_by:       yfc                                  *
*									                                        *
*     Date:       %date_modified:  2016-03 %                 			*
*                                                                           *
****************************************************************************/
/**** includes ***************************************************************/
#include "CBIT_APP.h"
#include "SPI.h"
#include "COMMON.h"






static UNUM16 CBIT_APP_CheckCANRegister( void );

extern UNUM16 GPIO_CheckSSPCChannel( void );

/*void CBIT_APP_Init(void)
{


}*/


void CBIT_APP_Process(void)
{

	static UNUM16 lu16_time=(UNUM16)0;
	static UNUM16 lu16_I2cWriteValue[10]={(UNUM16)0};

	ECAN_GetBusoffError((UNUM16)0);
	GPIO_CheckSSPCChannel();
	CBIT_APP_CheckCANRegister();

	lu16_I2cWriteValue[0] = lu16_time;
	lu16_I2cWriteValue[1] = lu16_time + (UNUM16)1;

	I2C_Write( &lu16_I2cWriteValue[0], (UNUM16)0xE002U, (UNUM16)2U );

	lu16_time++;
	if(lu16_time>(UNUM16)200)
	{
		lu16_time = (UNUM16)0;
	}

}


UNUM16 CBIT_APP_Test(void)
{
	static UNUM16 lu16_I2cReadValue[10]={(UNUM16)0};

	I2C_Read( &lu16_I2cReadValue[0], (UNUM16)0xE002U, (UNUM16)2U );
	return lu16_I2cReadValue[0] + (lu16_I2cReadValue[1] << 8);
}



static UNUM16 CBIT_APP_CheckCANRegister( void )
{
	UNUM16 lu16_is_error = (UNUM16)TRUE;    /* initialize the CAN bus as error */
    if( ECAN_CheckRegister( (UNUM16)0 ) )
    {
    	/*gu16_CBITReport[0] = gu16_CBITReport[0] | (UNUM16)1;     set CBIT report */
    }
    else
    {
    	lu16_is_error = (UNUM16)FALSE;
    }
	return lu16_is_error;
}

UNUM16 GPIO_CheckSSPCChannel(void)
{
	UNUM32 lu32_HW_Status = (UNUM32)0;
	UNUM32 lu32_SW_Status = (UNUM32)0;
	UNUM16 lu16_Ret = (UNUM16)0;

	lu32_HW_Status = GPIO_ReadGPIOPort((UNUM16)0) & (UNUM32)0x000FFFFF;
	lu32_SW_Status = GPIO_ReadGPIOPort((UNUM16)2) & (UNUM32)0x000FFFFF;
	if(lu32_HW_Status == lu32_SW_Status)
	{
		lu16_Ret = (UNUM16)0;
	}
	else
	{
		lu16_Ret = (UNUM16)1;
	}


	return (lu16_Ret);
}


/***************************************************************************
End of file.
***************************************************************************/

