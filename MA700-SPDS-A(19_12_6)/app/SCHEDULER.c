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
*     Module Name:         %name:     SCHEDULER.c %                           *
*     Module Version:      %version:  6 %                                     *
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
*                 %created_by:  lirunqing %                                      *
*                                                                             *
*     Datum:      %date_modified:  2019-11-26 16:38 %                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*     Author:     %mason                                                      *
*     datum:      %date_modified:                                             *
*     Description:  2019-11-30 lirunqing 摸底实验                         13,14通道保护值缩小                                *
*                                                                             *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     $Revision: 1.2 $   embeddeers revision number                           *
******************************************************************************/
/**** includes ***************************************************************/
#include "SCHEDULER.h"
#include "I2T_APP.h"
#include "SPI.h"

/*#include "MCU.h"
#include "MCU_cfg.h"
#include "PIE_CTRL.h"
#include "COMMON.h"
#include "INIT_APP.h"*/


/**** definitions*************************************************************/
/**** functions declarations *************************************************/
void SCHEDULER_InitSysCtrl( void );

void SCHEDULER_EnableGlobalInterrupts( void );

void SCHEDULER_MemCopy(  const UNUM16* SourceAddr, const UNUM16* SourceEndAddr,  UNUM16* DestAddr );

void SCHEDULER_InitTask( void );

UNUM16 lu16_i2cRead = (UNUM16)0;
UNUM16 lu16_BoardID = (UNUM16)0;

UNUM32 Channel_Status[20] = {(UNUM16)0};
UNUM16 Channel_Current[16] = {(UNUM16)0};
UNUM16 Sch_value = (UNUM16)0;

/**** functions **************************************************************/
/******************************************************************************
* Description:   SCHEDULER_Main
*
* Parameters:    -void
*
* Return values: -void
******************************************************************************/
int SCHEDULER_Main( void ){

	UNUM16 lu16_value = (UNUM16)0;

    SCHEDULER_InitTask();
    INIT_APP_Module();
	I2T_APP_SetType(APP_SETTYPE);
	/*GPIO_ChannelType((UNUM16)0);*/

	if(GPIO_ReadSSPC_ID());
	{

		while( 1 )
		{
    	/*SCI_Tx_Data(0x65U);*/
    	/*SCI_Rx_Data();*/
    	lu16_value = MCU_GetStatus_5ms();
        if(lu16_value == (UNUM16)1 )
        {
        	MCU_ClearStatus_5ms();
        	static UNUM16 lu16_SchTime = (UNUM16)0;
        	static UNUM16 au16_ch = (UNUM16)0;

        	ECAN_APP_ReceiveProcess();
        	GPIO_APP_ChannelProcess();

        	if(au16_ch)
        	{
        		I2T_APP_Process();
        	}
        	au16_ch++;
        	au16_ch &=(UNUM16)0x07;

        	ECAN_APP_TransmitProcess();

        	if(lu16_SchTime == (UNUM16)5)
        	{
        		/*CBIT_APP_Process();*/
        	}
        	else if(lu16_SchTime == (UNUM16)10)
        	{
        		/*lu16_i2cRead = CBIT_APP_Test();*/
        		lu16_i2cRead = lu16_i2cRead;
        	}
        	else
        	{

        	}

        	lu16_SchTime++;
        	if(lu16_SchTime > (UNUM16)49)
        	{
        		lu16_SchTime = (UNUM16)0;
        	}

        	/*test  parts*/

        	static UNUM16 au16_time = (UNUM16)0;
        	if(au16_time == (UNUM16)0)
        	{
        		UNUM16 lu16_ii=0;
				for(lu16_ii=0; lu16_ii< (UNUM16)16; lu16_ii++)
				{
					Channel_Status[lu16_ii]=GPIO_GetCtrlStatus(lu16_ii);
					Channel_Current[lu16_ii] = SPI_Rece_Current(lu16_ii);
				}
        	}
        	au16_time++;
        	if(au16_time > 200)
        	{
        		au16_time = 0;
        	}


        	Sch_value++;
        	EALLOW;
        	GPIO_GpioDataRegs.GPATOGGLE.all = GPIO_GpioDataRegs.GPATOGGLE.all|0x400000U;
        	EDIS;

        }


		}
	}
}

/******************************************************************************
* Description:   SCHEDULER_InitTask
*
* Parameters:    -void
*
* Return values: -void
******************************************************************************/
void SCHEDULER_InitTask( void )
{
	SCHEDULER_InitSysCtrl();
	INIT_APP_GPIO();
	MCU_InitClock();
	SCHEDULER_MemCopy( &RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart );
	I2C_InitGpio();
    I2C_Init();
	DINT;
	IER = (UNUM16)0x0000;
	IFR = (UNUM16)0x0000;
	PIE_CTRL_Init();
	PIE_VECT_Table_Init();
	SYS_Ctrl_Flash_Init();
	EALLOW;
	EDIS;
	PIE_CTRL_PieCtrlRegs.PIEIER8.bit.INTx1 = (UNUM16)1;
	IER = IER | (UNUM16)M_INT8;
	EINT;
	MCU_ConfigClock( &MCU_ms_CpuTimer0, (float)MCU_FRQ_SYSCLK, (float)MCU_SAMPLE_PERIOD );
	MCU_CpuTimer0Regs.TCR.bit.TSS = (UNUM16)0;
    SCHEDULER_EnableGlobalInterrupts();
}

/******************************************************************************
* Description:   SCHEDULER_InitSysCtrl
*
* Parameters:    -void
*
* Return values: -void
******************************************************************************/
void SCHEDULER_InitSysCtrl( void )
{
   /*Disable the watchdog*/
	WDG_DisableDog();
   /*Initialize the PLL control: PLLCR and DIVSEL*/
   /*DSP28_PLLCR and DSP28_DIVSEL are defined in DSP2833x_Examples.h*/
   SYS_Ctrl_InitPll( (UNUM16)DSP28_PLLCR,(UNUM16)DSP28_DIVSEL );
   /*Initialize the peripheral clocks*/
   SYS_Ctrl_PeripheralClocks_Init();
}

/******************************************************************************
* Description:   SCHEDULER_EnableGlobalInterrupts
*
* Parameters:    -void
*
* Return values: -void
******************************************************************************/
void SCHEDULER_EnableGlobalInterrupts( void )
{
	PIE_CTRL_PieCtrlRegs.PIEIER1.bit.INTx7 = (UNUM16)1; /*CPUtimer0 interrupt*/
    IER = IER | (UNUM16)M_INT1;
    EINT;
    ERTM;
}

/******************************************************************************
* Description:   SCHEDULER_MemCopy
*
* Parameters:    -UNUM16* SourceAddr
*		         -UNUM16* SourceEndAddr
*		         -UNUM16* DestAddr
*
* Return values: -void
******************************************************************************/
void SCHEDULER_MemCopy( const UNUM16* SourceAddr,  const UNUM16* SourceEndAddr, UNUM16* DestAddr )
{
    while( SourceAddr < SourceEndAddr )
    { 
       *DestAddr = *SourceAddr;
       DestAddr++;
       SourceAddr++;
    }
    return;
}

/***************************************************************************
End of file.
***************************************************************************/

