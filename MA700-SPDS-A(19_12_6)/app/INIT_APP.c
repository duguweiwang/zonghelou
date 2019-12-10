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
*     Module Name:         %name:     LRU.c %                               *
*     Module Version:      %version:   5 %                                    *
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
*				  %created_by:     mason                                    *
*									                                        *
*     Date:       %date_modified:   %                 			            *
*                                                                           *
****************************************************************************/
/**** includes *************************************************************/
#include "INIT_APP.h"

/**** functions **************************************************************/

/*******************************************************************************
* Description:   INIT_APP_GPIO
*
* Parameters:    -void
*
* Return values: -void
*******************************************************************************/
void INIT_APP_GPIO( void )
{
    /*UNUM32 lu32_GPIOInitParameter[7] = { (UNUM32)1,(UNUM32)1,(UNUM32)1,(UNUM32)1,(UNUM32)1,(UNUM32)1,(UNUM32)1 };*/
    UNUM32 lu32_GPIOInitParameter[7] = { (UNUM32)0,(UNUM32)0,(UNUM32)0,(UNUM32)0,(UNUM32)0,(UNUM32)0,(UNUM32)0 };
    gu32_GPIO_PORTA_OUT_MASK = (UNUM32)0xFFFFFFFFU;
    gu32_GPIO_PORTB_OUT_MASK = (UNUM32)0xFFFFFFFFU;
    gu32_GPIO_PORTC_OUT_MASK = (UNUM32)0xFFFFFFFFU;

    gu32_GPIO_PORTA_IN_MASK = (UNUM32)0x00000000U;
    gu32_GPIO_PORTB_IN_MASK = (UNUM32)0xF8000000U;
    gu32_GPIO_PORTC_IN_MASK = (UNUM32)0x00000000U;

    lu32_GPIOInitParameter[4] = gu32_GPIO_PORTA_OUT_MASK;
    lu32_GPIOInitParameter[5] = (~gu32_GPIO_PORTA_IN_MASK);
    GPIO_InitGPIOPort( (UNUM16)GPIO_PORTA_SN, lu32_GPIOInitParameter );

    lu32_GPIOInitParameter[4] = gu32_GPIO_PORTB_OUT_MASK;
    lu32_GPIOInitParameter[5] = (~gu32_GPIO_PORTB_IN_MASK);
    GPIO_InitGPIOPort( (UNUM16)GPIO_PORTB_SN, lu32_GPIOInitParameter );

    lu32_GPIOInitParameter[4] = gu32_GPIO_PORTC_OUT_MASK;
    lu32_GPIOInitParameter[5] = (~gu32_GPIO_PORTC_IN_MASK);
    GPIO_InitGPIOPort( (UNUM16)GPIO_PORTC_SN, lu32_GPIOInitParameter );

    /***Set all lamps off***/
    GPIO_ClearGPIOPort( (UNUM16)GPIO_PORTA_SN,(UNUM32)gu32_GPIO_PORTA_OUT_MASK );
    GPIO_ClearGPIOPort( (UNUM16)GPIO_PORTB_SN,(UNUM32)gu32_GPIO_PORTB_OUT_MASK );
    GPIO_ClearGPIOPort( (UNUM16)GPIO_PORTC_SN,(UNUM32)gu32_GPIO_PORTC_OUT_MASK );

    /***initialize the ECAN GPIOs***/
    ECAN_InitECanGPIO();
    SPI_Gpio_Init();
}

/*******************************************************************************
* Description:   INIT_APP_Module
*
* Parameters:    -void
*
* Return values: -void
*******************************************************************************/
void INIT_APP_Module( void )
{
	ECAN_InitModule();
	if( ECAN_SelfTest((UNUM16)ECAN_ECANA_SN) == (UNUM32)0xFFFFFFFFU )
	{
	    ECAN_InitModule();
	    ECAN_EnterNormalMode( (UNUM16)ECAN_ECANA_SN );
	    ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)0, (UNUM32)0x13, 0, 8 );
	    ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)2, (UNUM32)0xA520401, 0, 8 );

	    ECAN_ConfigRecMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)3, (UNUM32)0x86A040A, (UNUM32)0, 8 );/*ON/OFF*/
	    ECAN_ConfigRecMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)4, (UNUM32)0x186A040A, (UNUM32)0, 8 );/*Lock/Unlock*/
	    ECAN_ConfigRecMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)5, (UNUM32)0x186A040E, (UNUM32)0, 8 );/*Reset*/
	    ECAN_ConfigRecMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)6, (UNUM32)0x186A040B, (UNUM32)0, 8 );/*Flight/Ground*/
	    ECAN_ConfigRecMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)7, (UNUM32)0x186A040C, (UNUM32)0, 8 );/*Single/Three Phase*/
	    ECAN_ConfigRecMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)8, (UNUM32)0x186A040D, (UNUM32)0, 8 );/*Rate Current 1*/
	    CAN_BUF_Init();
    }
	 /***initialize Module for ADC***/

	SPI_Init();
	Sci_Init();
	I2T_APP_Init();
	TLV5638_Init();
	GPIO_Init();
	GPIO_APP_StateInit();

}

/***************************************************************************
End of file.
***************************************************************************/

