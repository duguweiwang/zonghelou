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
*     Module Description:  module to provide a real time scheduler	          *
*     Module Name:         %name:     EEPROM_cfg.h %                            *
*     Module Version:      %version:  3 %                                     *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	  		                                          			  *
*                                                                             *
*     Controller:                                             				  *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                  								  *
*				  %created_by:   maolei %                                     *
*									                                          *
*     Date:       %date_modified:  2013-10-14 %                 			  *
*                                                                             *
******************************************************************************/

#ifndef __EEPROM_CFG_H__
#define __EEPROM_CFG_H__

/**** includes ***************************************************************/
#include "DEVICE.h"
#include "DEVICE_cfg.h"
/**** definitions*************************************************************/
#define EEPROM_BASE_ADDRESS									       0x0400
#define EEPROM_CHECKSUM_ADDRESS								       0x0484/*0x048C*/
#define EEPROM_FAULT_INFORMATION_ADDRESS 					       0x0
#define EEPROM_FLIGHT_STATE_INFO_ADDR                              0x0585
#define EEPROM_READ_ADDRESS(INDEX)                			(EEPROM_BASE_ADDRESS+(INDEX))
#define EEPROM_WRITE_FAULT_INFORMATION_ADDRESS(INDEX)       ((INDEX)+EEPROM_FAULT_INFORMATION_ADDRESS)
#define EEPROM_CAN_REC_LOST_ADDRESS					        (EEPROM_WRITE_FAULT_INFORMATION_ADDRESS(0x15E))
#define EEPROM_CAN_BUS_OFF_ADDRESS					        (EEPROM_WRITE_FAULT_INFORMATION_ADDRESS(0x276))
#define EEPROM_WRITE_CONTROL_BYTE_LENGTH					        8
#define EEPROM_WRITE_FILL_LENGTH							        4
#define EEPROM_ALL_CHECKSUM_LENGTH							        22
#define EEPROM_MESSAGE_CONFIGURATION_CONSTRUCTURE_LENGTH			0x08
#define EEPROM_MESSAGE_HARDWARE_PART_NUMBER_LENGTH					0x14
#define EEPROM_MESSAGE_HARDWARE_PART_DESCRIPTION_LENGTH			    0x05
#define EEPROM_MESSAGE_HARDWARE_SERIAL_NUMBER_LENGTH				0x0B
#define EEPROM_MESSAGE_HARDWARE_MOD_STATUS_LENGTH				    0x04
#define EEPROM_MESSAGE_SOFTWARE_LOCAL_ID_LENGTH					    0x0F
#define EEPROM_MESSAGE_SOFTWARE_LOCAL_DESCRIPTION_LENGTH			0x0A
#define EEPROM_MESSAGE_SOFTWARE_PART_NUMBER_LENGTH					0x14
#define EEPROM_MESSAGE_SOFTWARE_PART_DESCRIPTION_LENGTH			    0x0E
#define EEPROM_MESSAGE_BL_SW_PART_NUMBER_LENGTH					    0x14
#define EEPROM_MESSAGE_BL_SW_PART_DESCRIPTION_LENGTH			    0x0D

#define EEPROM_SW_PART_NUMBER_ADDRESS						(EEPROM_READ_ADDRESS(EEPROM_MESSAGE_CONFIGURATION_CONSTRUCTURE_LENGTH+  	\
															EEPROM_MESSAGE_HARDWARE_PART_NUMBER_LENGTH+EEPROM_MESSAGE_HARDWARE_PART_DESCRIPTION_LENGTH+  \
															EEPROM_MESSAGE_HARDWARE_SERIAL_NUMBER_LENGTH+EEPROM_MESSAGE_HARDWARE_MOD_STATUS_LENGTH+	   \
															EEPROM_MESSAGE_SOFTWARE_LOCAL_ID_LENGTH+EEPROM_MESSAGE_SOFTWARE_LOCAL_DESCRIPTION_LENGTH))

/**** functions declarations *************************************************/
UNUM16 EEPROM_CheckSelf( void );

void EEPROM_WriteUserData( UNUM16 au16_Address,
		                   UCHAR ap_ConfigurationData[],
		                   UNUM32 au16_DataLength );

void EEPROM_ReadChecksum(UNUM16 au16_ChecksumAddress,
		                 UCHAR ap_Checksum[] );

void EEPROM_Init( void );

#endif

/***************************************************************************
End of file.
***************************************************************************/
