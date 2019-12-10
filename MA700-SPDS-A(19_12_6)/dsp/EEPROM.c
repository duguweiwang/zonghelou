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
*     Module Description:  definition of the realtime scheduler callbacks     *
*     Module Name:         %name:     EEPROM.c %                              *
*     Module Version:      %version:  2 %                                     *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	                                                              *
*                                                                             *
*     Controller:                                                             *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*                 %created_by:  maolei %                                      *
*                                                                             *
*     Datum:      %date_modified:  Tue Jan  8 14:15:17 2013 %                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     $Revision: 1.2 $   embeddeers revision number                           *
******************************************************************************/

/**** includes ***************************************************************/
#define  EEPROM_OWN
#include "EEPROM.h"
#include "EEPROM_cfg.h"
#include "DEVICE.h"
#include "DEVICE_cfg.h"
#include "I2C.h"
#include "I2C_cfg.h"

/**** functions **************************************************************/
void EEPROM_Init( void )
{

}

/******************************************************************************
* Description:   Write Configuration Data
*
* Parameters:    UNUM16 au16_Address
*			   UCHAR *ap_ConfigurationData
*                     UNUM32 au32_DataLength
*
* Return values: none
*******************************************************************************/
/*
void EEPROM_WriteUserData( UNUM16 au16_Address,
		                   UCHAR ap_ConfigurationData[],
		                   UNUM32 au16_DataLength )
{
	UNUM16 lu16_Number;
	for ( lu16_Number = (UNUM16)0; lu16_Number < (UNUM16)au16_DataLength; lu16_Number++ )
	{
		I2C_I2cMsgOut1.MsgBuffer[lu16_Number] = ap_ConfigurationData[lu16_Number];
	}

	I2C_WriteUserData( &I2C_I2cMsgOut1, au16_Address, (UNUM16)au16_DataLength );
}
*/

/*
void EEPROM_ReadChecksum( UNUM16 au16_ChecksumAddress,
		                  UCHAR ap_Checksum[] )
{
	UNUM16 lu16_ReadNumber;

	for ( lu16_ReadNumber = (UNUM16)0; lu16_ReadNumber < (UNUM16)CHECKSUM_LENGTH; lu16_ReadNumber++ )
	{
		I2C_ReadUserData( &I2C_I2cMsgIn1, au16_ChecksumAddress, (UNUM16)CHECKSUM_LENGTH );
		DELAY_US(880);
		I2C_ReadUserData( &I2C_I2cMsgIn1, au16_ChecksumAddress, (UNUM16)CHECKSUM_LENGTH );
		DELAY_US(880);

		ap_Checksum[lu16_ReadNumber] = I2C_I2cMsgIn1.MsgBuffer[lu16_ReadNumber];
	}
}
*/
/*
UNUM16 EEPROM_CheckSelf( void )
{
	UNUM16   lb_Result = (UNUM16)TRUE;
	UNUM32 lu32_CountX = (UNUM32)0;
	UNUM32 lu32_CountY = (UNUM32)0;
	UNUM16 lu16_Checksum = (UNUM16)0;
	UNUM16 lu16_CalculateChecksum = (UNUM16)0;
	UNUM16 lu16_EepromChecksum = (UNUM16)0;
	UNUM16 lu16_MemoryAddress = (UNUM16)0;
	UNUM16 lu16_NumOfBytes = (UNUM16)0;
	UCHAR lu8_FillData[EEPROM_WRITE_FILL_LENGTH]={(UCHAR)0x55,(UCHAR)0xAA,(UCHAR)0x55,(UCHAR)0xAA};
	UCHAR lu8_TotalData[EEPROM_CHECKSUM_ADDRESS - EEPROM_BASE_ADDRESS+CHECKSUM_LENGTH+EEPROM_ALL_CHECKSUM_LENGTH] = {(UCHAR)0};
	UNUM32 lu32_TotalNumber = (UNUM32)((UNUM32)EEPROM_CHECKSUM_ADDRESS - (UNUM32)EEPROM_BASE_ADDRESS+(UNUM32)EEPROM_ALL_CHECKSUM_LENGTH) / ((UNUM32)EEPROM_WRITE_FILL_LENGTH);

	I2C_I2cMsgOut1.NumOfBytes = (UNUM16)EEPROM_WRITE_FILL_LENGTH;

	for ( lu32_CountY = (UNUM32)0; lu32_CountY < lu32_TotalNumber; lu32_CountY++ )
	{
		for (lu32_CountX = (UNUM32)0; lu32_CountX < (UNUM32)EEPROM_WRITE_FILL_LENGTH; lu32_CountX++)
		{
			lu8_TotalData[lu32_CountX+lu32_CountY*((UNUM32)EEPROM_WRITE_FILL_LENGTH)] = lu8_FillData[lu32_CountX];
		}
	}

	for (lu32_CountX = (UNUM32)0; lu32_CountX < (UNUM32)EEPROM_WRITE_FILL_LENGTH; lu32_CountX++)
	{
		I2C_I2cMsgOut1.MsgBuffer[lu32_CountX] = lu8_FillData[lu32_CountX];
	}

	for (lu32_CountY = (UNUM32)0; lu32_CountY < lu32_TotalNumber; lu32_CountY++)
	{
		I2C_WriteUserData( &I2C_I2cMsgOut1, (UNUM16)((UNUM32)EEPROM_BASE_ADDRESS+lu32_CountY*((UNUM32)EEPROM_WRITE_FILL_LENGTH)), (UNUM16)EEPROM_WRITE_FILL_LENGTH );
	}

	lu16_Checksum = CHECK_SUM_crc16_ccitt( lu8_TotalData, (UNUM32)(EEPROM_CHECKSUM_ADDRESS - EEPROM_BASE_ADDRESS +EEPROM_ALL_CHECKSUM_LENGTH) );

	I2C_I2cMsgOut1.NumOfBytes = (UNUM16)2;
	I2C_I2cMsgOut1.MsgBuffer[0] = (UCHAR)(lu16_Checksum>>8);
	I2C_I2cMsgOut1.MsgBuffer[1] = (UCHAR)(lu16_Checksum&((UNUM16)0x00FF));

	lu16_MemoryAddress = (UNUM16)( EEPROM_CHECKSUM_ADDRESS + EEPROM_ALL_CHECKSUM_LENGTH);
	lu16_NumOfBytes = I2C_I2cMsgOut1.NumOfBytes;

	I2C_WriteUserData( &I2C_I2cMsgOut1, lu16_MemoryAddress, lu16_NumOfBytes );
	
	for (lu32_CountY = (UNUM32)0; lu32_CountY < lu32_TotalNumber; lu32_CountY++)
	{
		for (lu32_CountX = (UNUM32)0; lu32_CountX < (UNUM32)EEPROM_WRITE_FILL_LENGTH; lu32_CountX++)
		{
			I2C_ReadUserData( &I2C_I2cMsgIn1, (UNUM16)((UNUM32)EEPROM_BASE_ADDRESS+lu32_CountY*((UNUM32)EEPROM_WRITE_FILL_LENGTH)), (UNUM16)EEPROM_WRITE_FILL_LENGTH );
			DELAY_US(211);
			I2C_ReadUserData( &I2C_I2cMsgIn1, (UNUM16)((UNUM32)EEPROM_BASE_ADDRESS+lu32_CountY*((UNUM32)EEPROM_WRITE_FILL_LENGTH)), (UNUM16)EEPROM_WRITE_FILL_LENGTH );
			DELAY_US(211);

			lu8_TotalData[lu32_CountX+lu32_CountY*((UNUM32)EEPROM_WRITE_FILL_LENGTH)] = I2C_I2cMsgIn1.MsgBuffer[lu32_CountX];
		}
	}

	lu16_CalculateChecksum = CHECK_SUM_crc16_ccitt( lu8_TotalData, (UNUM32)(EEPROM_CHECKSUM_ADDRESS - EEPROM_BASE_ADDRESS + EEPROM_ALL_CHECKSUM_LENGTH) );

	lu16_MemoryAddress = (UNUM16)(EEPROM_CHECKSUM_ADDRESS+EEPROM_ALL_CHECKSUM_LENGTH);
	lu16_NumOfBytes = I2C_I2cMsgIn1.NumOfBytes;

	I2C_ReadUserData( &I2C_I2cMsgIn1, lu16_MemoryAddress, lu16_NumOfBytes );
	DELAY_US(211);
	lu16_MemoryAddress = (UNUM16)(EEPROM_CHECKSUM_ADDRESS+EEPROM_ALL_CHECKSUM_LENGTH);
	lu16_NumOfBytes = I2C_I2cMsgIn1.NumOfBytes;

	I2C_ReadUserData( &I2C_I2cMsgIn1, lu16_MemoryAddress, lu16_NumOfBytes );
	DELAY_US(211);
	lu8_TotalData[EEPROM_CHECKSUM_ADDRESS- EEPROM_BASE_ADDRESS+EEPROM_ALL_CHECKSUM_LENGTH] = I2C_I2cMsgIn1.MsgBuffer[0];
	lu8_TotalData[EEPROM_CHECKSUM_ADDRESS- EEPROM_BASE_ADDRESS+EEPROM_ALL_CHECKSUM_LENGTH+1] = I2C_I2cMsgIn1.MsgBuffer[1];

	lu16_EepromChecksum = (((UNUM16)lu8_TotalData[EEPROM_CHECKSUM_ADDRESS- EEPROM_BASE_ADDRESS+EEPROM_ALL_CHECKSUM_LENGTH])<<8)
					| (UNUM16)lu8_TotalData[EEPROM_CHECKSUM_ADDRESS- EEPROM_BASE_ADDRESS+EEPROM_ALL_CHECKSUM_LENGTH+1];

	if (lu16_CalculateChecksum == lu16_EepromChecksum)
	{
		lb_Result = (UNUM16)TRUE;
	}
	else
	{
		lb_Result = (UNUM16)FALSE;
	}

	return lb_Result;
}
*/
/***************************************************************************
End of file.
***************************************************************************/

