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
*     Module Description:  module to provide a realtime scheduler	          *
*     Module Name:         %name:     GPIO.c %                                *
*     Module Version:      %version:  2 %                                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:	  	                                                          *
*                                                                             *
*     Controller:                                                             *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*				  %created_by:   maolei %                                      *
*									                                          *
*     Date:       %date_modified:  Wed Apr  4 14:57:59 2012 %                 *
*                                                                             *
******************************************************************************/

/**** includes ***************************************************************/
#include "GPIO.h"
#include "COMMON.h"
#include "GPIO_cfg.h"
#include "DEVICE.h"
#include "DEVICE_cfg.h"
#include "I2T_APP.h"

/**** definitions*************************************************************/
#pragma DATA_SECTION(GPIO_GpioCtrlRegs,"GpioCtrlRegsFile");
volatile struct GPIO_CTRL_REGS GPIO_GpioCtrlRegs;

#pragma DATA_SECTION(GPIO_GpioDataRegs,"GpioDataRegsFile");
volatile struct GPIO_DATA_REGS GPIO_GpioDataRegs;

#pragma DATA_SECTION(GPIO_GpioIntRegs,"GpioIntRegsFile");
volatile struct GPIO_INT_REGS GPIO_GpioIntRegs;


UNUM32 SOURCE_FID=0;

/**** functions **************************************************************/



void GPIO_Init(void)
{
   /* GPIO_GpioCtrlRegs.GPCMUX1.all = (UNUM32)0x00000000; //SET GPIO 64-79
   // GPIO_GpioCtrlRegs.GPCMUX2.all &= (UNUM32)0xFFFFFF00; //SET GPIO 80-83
    GPIO_GpioCtrlRegs.GPCDIR.all |= (UNUM32)0x000FFFFF; //SET GPIO DIR64-83
    GPIO_GpioDataRegs.GPCDAT.all  |=  (UNUM32)0x000FFFF; //SET GPIO VALUE 64-83


    GPIO_GpioCtrlRegs.GPAMUX1.all = (UNUM32)0x00000000; //SET GPIO 0-15 General purpose I/O
   // GPIO_GpioCtrlRegs.GPAMUX2.all &= (UNUM32)0xFFFFFF00; //SET GPIO 16-19 General purpose I/O
    GPIO_GpioCtrlRegs.GPADIR.all &= (UNUM32)0x000F0000; //SET GPIO 0-20 as an input
*/
	EALLOW;
	GPIO_GpioCtrlRegs.GPBDIR.bit.GPIO58=0;
	GPIO_GpioCtrlRegs.GPBDIR.bit.GPIO59=0;
	GPIO_GpioCtrlRegs.GPBDIR.bit.GPIO60=0;
	GPIO_GpioCtrlRegs.GPBDIR.bit.GPIO61=0;
	GPIO_GpioCtrlRegs.GPBDIR.bit.GPIO62=0;
	GPIO_GpioCtrlRegs.GPBDIR.bit.GPIO63=0;
	EDIS;
}



/* Operation GPIO Grouping */
void GPIO_InitGPIOPort( UNUM16 au16_PortSN,const UNUM32 au32_PortRegPara[7] )

{
	EALLOW;
	switch ( au16_PortSN )
	{
	    case (UNUM16)GPIO_PORTA_SN:
	        GPIO_GpioCtrlRegs.GPAMUX1.all = GPIO_GpioCtrlRegs.GPAMUX1.all & au32_PortRegPara[0]; /* Configure GPIO0-GPIO15 are GPIO ports */

	        GPIO_GpioCtrlRegs.GPAMUX2.all = GPIO_GpioCtrlRegs.GPAMUX2.all & au32_PortRegPara[1]; /* Configure GPIO16-GPIO31 are GPIO ports */
	        GPIO_GpioCtrlRegs.GPAQSEL1.all = GPIO_GpioCtrlRegs.GPAQSEL1.all & au32_PortRegPara[2];	/* Configure GPIO0-GPIO15 are Sync with system clock */
	        GPIO_GpioCtrlRegs.GPAQSEL2.all = GPIO_GpioCtrlRegs.GPAQSEL2.all & au32_PortRegPara[3];	/* Configure GPIO16-GPIO31 are Sync with system clock */
	        GPIO_GpioCtrlRegs.GPADIR.all = GPIO_GpioCtrlRegs.GPADIR.all | au32_PortRegPara[4];	/* Configure GPIO0-GPIO31 are Output ports */
	        GPIO_GpioCtrlRegs.GPADIR.all = GPIO_GpioCtrlRegs.GPADIR.all & au32_PortRegPara[5]; /* Configure GPIO0-GPIO31 are Input ports */
	        GPIO_GpioCtrlRegs.GPAPUD.all = GPIO_GpioCtrlRegs.GPAPUD.all & au32_PortRegPara[6]; /* Enable GPIO0-GPIO31 and GPIO8-GPIO15 internal pull-up */
	        GPIO_GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;
	    	break;
	    case (UNUM16)GPIO_PORTB_SN:
	    	GPIO_GpioCtrlRegs.GPBMUX1.all = GPIO_GpioCtrlRegs.GPBMUX1.all & au32_PortRegPara[0]; /* Configure GPIO32-GPIO47 are GPIO ports */
	        GPIO_GpioCtrlRegs.GPBMUX2.all = GPIO_GpioCtrlRegs.GPBMUX2.all & au32_PortRegPara[1]; /* Configure GPIO48-GPIO63 are GPIO ports */
	        GPIO_GpioCtrlRegs.GPBQSEL1.all = GPIO_GpioCtrlRegs.GPBQSEL1.all & au32_PortRegPara[2];	/* Configure GPIO32-GPIO47 are Sync with system clock */
	        GPIO_GpioCtrlRegs.GPBQSEL2.all = GPIO_GpioCtrlRegs.GPBQSEL2.all & au32_PortRegPara[3];	/* Configure GPIO48-GPIO63 are Sync with system clock */
	        GPIO_GpioCtrlRegs.GPBDIR.all = GPIO_GpioCtrlRegs.GPBDIR.all | au32_PortRegPara[4]; /* Configure GPIO32-GPIO63 are Output ports */
	        GPIO_GpioCtrlRegs.GPBDIR.all = GPIO_GpioCtrlRegs.GPBDIR.all & au32_PortRegPara[5]; /* Configure GPIO32-GPIO63 are Input ports */
	        GPIO_GpioCtrlRegs.GPBPUD.all = GPIO_GpioCtrlRegs.GPBPUD.all & au32_PortRegPara[6]; /* Enable GPIO32-GPIO63 and GPIO8-GPIO15 internal pull-up */
	    	break;
	    case (UNUM16)GPIO_PORTC_SN:
	        GPIO_GpioCtrlRegs.GPCMUX1.all = GPIO_GpioCtrlRegs.GPCMUX1.all & au32_PortRegPara[0]; /* Configure GPIO64-GPIO79 are GPIO ports */
	        GPIO_GpioCtrlRegs.GPCMUX2.all = GPIO_GpioCtrlRegs.GPCMUX2.all & au32_PortRegPara[1]; /* Configure GPIO79-GPIO87 are GPIO ports */
	        GPIO_GpioCtrlRegs.GPCDIR.all = GPIO_GpioCtrlRegs.GPCDIR.all | au32_PortRegPara[4];	/* Configure GPIO64-GPIO87 is Output ports */
	        GPIO_GpioCtrlRegs.GPCDIR.all = GPIO_GpioCtrlRegs.GPCDIR.all & au32_PortRegPara[5];	/* Configure GPIO64-GPIO87 is Input ports */
	        GPIO_GpioCtrlRegs.GPCPUD.all = GPIO_GpioCtrlRegs.GPCPUD.all & au32_PortRegPara[6];	/* Enable GPIO64-GPIO87 internal pull-up */
	    	break;
	    default:
	    	break;
	}
	EDIS;
}

void GPIO_ClearGPIOPort( UNUM16 au16_PortSN,
		                 UNUM32 au32_ClearValue )
{
	switch ( au16_PortSN )
	{
	    case (UNUM16)GPIO_PORTA_SN:
	    	GPIO_GpioDataRegs.GPACLEAR.all = GPIO_GpioDataRegs.GPACLEAR.all | au32_ClearValue;
	    	break;
	    case (UNUM16)GPIO_PORTB_SN:
	    	GPIO_GpioDataRegs.GPBCLEAR.all = GPIO_GpioDataRegs.GPBCLEAR.all | au32_ClearValue;
	    	break;
	    case (UNUM16)GPIO_PORTC_SN:
	    	GPIO_GpioDataRegs.GPCCLEAR.all = GPIO_GpioDataRegs.GPCCLEAR.all | au32_ClearValue;
	    	break;
	    default:
	    	break;
	}
}

UNUM32 GPIO_GetChannelStatus( UNUM16 au16_ChannelSN)
{
	UNUM32 lu32_status = (UNUM32)0;

	lu32_status = GPIO_GpioDataRegs.GPADAT.all & (UNUM32)0xFFFFFF;

	return lu32_status;
}

void GPIO_ChannelType(UNUM16 au16_ChannelType)
{

}

void GPIO_ChannelTurnOn( UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN <  (UNUM16)20)
	{
		GPIO_GpioDataRegs.GPCDAT.all |= (UNUM32)1 << au16_ChannelSN;
	}
}

void GPIO_ChannelTurnOff( UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN < (UNUM16)20 )
	{
		GPIO_GpioDataRegs.GPCDAT.all &= ~((UNUM32)1 << au16_ChannelSN);
	}
}


UNUM32 GPIO_ReadGPIOPort( UNUM16 au16_PortSN )
{
	UNUM32 GPIO_mu32_Data;

	switch ( au16_PortSN )
	{
	    case (UNUM16)GPIO_PORTA_SN:
	    	GPIO_mu32_Data = GPIO_GpioDataRegs.GPADAT.all;
	    	break;
	    case (UNUM16)GPIO_PORTB_SN:
	    	GPIO_mu32_Data = GPIO_GpioDataRegs.GPBDAT.all;
	    	break;
	    case (UNUM16)GPIO_PORTC_SN:
	    	GPIO_mu32_Data = GPIO_GpioDataRegs.GPCDAT.all;
	    	break;
	    default:
	    	break;
	}

	return (GPIO_mu32_Data);
}


UNUM32 GPIO_ReadSSPC_ID(void)
{
	UNUM32 GPIO_mu32_Data;

	GPIO_mu32_Data = GPIO_GpioDataRegs.GPBDAT.all;
	GPIO_mu32_Data = (UNUM32)GPIO_mu32_Data & (UNUM32)0xFC000000U;
	GPIO_mu32_Data = (UNUM32)GPIO_mu32_Data>>(UNUM32)24;
	switch ( GPIO_mu32_Data )
	{

	    case (UNUM32)SSPC_ID1:
	    	SOURCE_FID=(UNUM32)0x52;
	    	break;
	    case (UNUM32)SSPC_ID2:
	    	SOURCE_FID=(UNUM32)0x53;
	    	break;
	    case (UNUM32)SSPC_ID3:
	    	SOURCE_FID=(UNUM32)0x54;
	  		break;
	  	case (UNUM32)SSPC_ID4:
	  		SOURCE_FID=(UNUM32)0x55;
	  		break;
	    case (UNUM32)SSPC_ID5:
	    	SOURCE_FID=(UNUM32)0x56;
	  		break;
	  	case (UNUM32)SSPC_ID6:
	  		SOURCE_FID=(UNUM32)0x57;
	  		break;
	  	case (UNUM32)SSPC_ID7:
	  		SOURCE_FID=(UNUM32)0x58;
	  		break;
	  	case (UNUM32)SSPC_ID8:
	  		SOURCE_FID=(UNUM32)0x59;
	  		break;
	  	case (UNUM32)SSPC_ID9:
	  		SOURCE_FID=(UNUM32)0x5A;
	  		break;
	  	case (UNUM32)SSPC_ID10:
	  		SOURCE_FID=(UNUM32)0x5B;
	  		break;
	  	case (UNUM32)SSPC_ID11:
	  		SOURCE_FID=(UNUM32)0x62;
	  	   	break;
	  	case (UNUM32)SSPC_ID12:
	  		SOURCE_FID=(UNUM32)0x63;
	  	   	break;
	  	case (UNUM32)SSPC_ID13:
	  		SOURCE_FID=(UNUM32)0x64;
	  	    break;
	  	case (UNUM32)SSPC_ID14:
	  		SOURCE_FID=(UNUM32)0x65;
	  	    break;
	    default:
	    	break;
	}

	return (SOURCE_FID);
}

/***************************************************************************
End of file.
***************************************************************************/
