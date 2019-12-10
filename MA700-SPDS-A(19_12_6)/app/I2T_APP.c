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
*     Module Description:  I2T_APP	algorithm           *
*     Module Name:         %name:     I2T.c %                                *
*     Module Version:      %version:  0 %                                 *
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
*				  %created_by:   yufangcheng %                                      *
*									                                          *
*     Date:       %date_modified:  Wed July  4 14:57:59 2015 %                 *
*                                                                             *
******************************************************************************/

/**** includes ***************************************************************/
#include "I2T_APP.h"
#include "GPIO.h"
#include "ADC.h"
#include "SPI.h"
#include "COMMON.h"
#include "GPIO_APP.h"


/**** Module functions declarations *************************************************/
static UNUM16 I2T_APP_Protection(UNUM16 channel,UNUM16 AD_value);
static UNUM16 I2T_APP_CalCurrent(UNUM16 channel,UNUM16 AD_value);
static UNUM16 I2T_APP_GetAcumCoef(UNUM16 channel,UNUM16 I2T_Y);
static void I2T_APP_SmoothFilter(UNUM16 lu16_ChannelSN);

/**** Module variables declarations *************************************************/
struct I2T_Structure I2T_Control[20];
/*static UNUM16 au16_CurTimes[20] = {(UNUM16)0};*/
static UNUM16 lu16_BoardType=(UNUM16)0;

static const UNUM16 DC_RC_TAB[20]=
{
		(UNUM16)20,		/*	CH01 Rated Current*10 1A */
		(UNUM16)20,		/*	CH02 Rated Current*10 1A */
		(UNUM16)20,		/*	CH03 Rated Current*10 1A */
		(UNUM16)20,		/*	CH04 Rated Current*10 1A */
		(UNUM16)20,		/*	CH05 Rated Current*10 1A */
		(UNUM16)20,		/*	CH06 Rated Current*10 1A */
		(UNUM16)20,		/*	CH07 Rated Current*10 1A */
		(UNUM16)20,		/*	CH08 Rated Current*10 1A */
		(UNUM16)20,		/*	CH09 Rated Current*10 1A */
		(UNUM16)20,		/*	CH10 Rated Current*10 1A */
		(UNUM16)35,		/*	CH11 Rated Current*10 2A */
		(UNUM16)35,		/*	CH12 Rated Current*10 2A */
		(UNUM16)35,		/*	CH13 Rated Current*10 2A */
		(UNUM16)35,		/*	CH14 Rated Current*10 2A */
		(UNUM16)35,		/*	CH15 Rated Current*10 2A */
		(UNUM16)50,		/*	CH16 Rated Current*10 5A */
		(UNUM16)50,		/*	CH17 Rated Current*10 5A */
		(UNUM16)75,		/*	CH18 Rated Current*10 7.5A */
		(UNUM16)100,	/*	CH19 Rated Current*10 10A */
		(UNUM16)150		/*	CH20 Rated Current*10 20A */
};


static const UNUM16 AC_RC_TAB[16]=
{
		(UNUM16)50,		/*	CH01 Rated Current*10 5A */
		(UNUM16)50,		/*	CH02 Rated Current*10 5A */
		(UNUM16)50,		/*	CH03 Rated Current*10 5A */
		(UNUM16)50,		/*	CH04 Rated Current*10 5A */
		(UNUM16)50,		/*	CH05 Rated Current*10 5A */
		(UNUM16)50,		/*	CH06 Rated Current*10 5A */
		(UNUM16)50,		/*	CH07 Rated Current*10 5A */
		(UNUM16)75,		/*	CH08 Rated Current*10 7.5A */
		(UNUM16)75,		/*	CH09 Rated Current*10 7.5A */
		(UNUM16)75,		/*	CH10 Rated Current*10 7.5A */
		(UNUM16)100,	/*	CH11 Rated Current*10 10A */
		(UNUM16)100,	/*	CH12 Rated Current*10 10A */
		(UNUM16)100,	/*	CH13 Rated Current*10 10A */
		(UNUM16)150,	/*	CH14 Rated Current*10 15A */
		(UNUM16)150,	/*	CH15 Rated Current*10 15A */
		(UNUM16)150		/*	CH16 Rated Current*10 15A */
};




/**** functions declarations *************************************************/

void I2T_APP_Init(void)
{
	UNUM16 lu16_CH =  (UNUM16)0;

	for(lu16_CH =  (UNUM16)0; lu16_CH < (UNUM16)20; lu16_CH++)
	{
		I2T_Control[lu16_CH].Period = (UNUM16)10;
		I2T_Control[lu16_CH].AcumCoef = (UNUM16)0;
		I2T_Control[lu16_CH].Current = (UNUM32)0;
		I2T_Control[lu16_CH].CurHeat = (UNUM32)0;
		I2T_Control[lu16_CH].Times = (UNUM32)0;
	}
}

void I2T_APP_I2tClear(UNUM16 channel)
{
	I2T_Control[channel].Times = (UNUM32)0;
	I2T_Control[channel].Current = (UNUM32)0;
	I2T_Control[channel].CurHeat = (UNUM32)0;
	I2T_Control[channel].AcumCoef = (UNUM16)0;
}


/*void I2T_APP_SetType(void)
{
	UNUM32 temp=0;
	temp=GPIO_ReadSSPC_ID();
	if(temp>=(UNUM32)98)
	{
		lu16_BoardType = 1;
	}
	else
	{
		lu16_BoardType = 0;
	}


}*/
void I2T_APP_SetType(UNUM16 lu16_BoardID)
{
	lu16_BoardType = lu16_BoardID;
}


UNUM16 I2T_APP_GetRateCurrent(UNUM16 channelSN)
{
	UNUM16 lu16_ret = (UNUM16)0;

	if(channelSN < (UNUM16)20)
	{
		if(lu16_BoardType == (UNUM16)1)
		{
			lu16_ret = AC_RC_TAB[channelSN] / (UNUM16)10;
		}
		else
		{
			lu16_ret = DC_RC_TAB[channelSN] / (UNUM16)10;
		}
	}
	else
	{
		lu16_ret = (UNUM16)I2T_ERROR;
	}

	return lu16_ret;
}

static UNUM16 I2T_APP_CalCurrent(UNUM16 channel,UNUM16 AD_value)
{

	/*	DC CH01-CH20 RC1A R_mΩ*100 */
	/*static const UNUM16 CH_R_TAB[20]=
	{
			(UNUM16)2500, (UNUM16)2500, (UNUM16)2500, (UNUM16)2500, (UNUM16)2500,
			(UNUM16)2500, (UNUM16)2500, (UNUM16)2500, (UNUM16)2500, (UNUM16)2500,
			(UNUM16)1250, (UNUM16)1250, (UNUM16)1250, (UNUM16)1250, (UNUM16)1250,
			(UNUM16)500, (UNUM16)485, (UNUM16)342, (UNUM16)260, (UNUM16)141
	};*/
	static const UNUM16 CH_R_TAB[20]=
		{
				(UNUM16)2625, (UNUM16)2625, (UNUM16)2625, (UNUM16)2625, (UNUM16)2625,
				(UNUM16)2625, (UNUM16)2625, (UNUM16)2625, (UNUM16)2625, (UNUM16)2625,
				(UNUM16)1500, (UNUM16)1500, (UNUM16)1500, (UNUM16)1500, (UNUM16)1500,
				(UNUM16)1050, (UNUM16)1050, (UNUM16)735, (UNUM16)525, (UNUM16)350
		};
	static const UNUM16 AC_R_TAB[16]=
		{
				(UNUM16)150, (UNUM16)150,(UNUM16)150, (UNUM16)150, (UNUM16)150,
				(UNUM16)150, (UNUM16)150, (UNUM16)105, (UNUM16)105, (UNUM16)105,
				(UNUM16)75, (UNUM16)75, (UNUM16)75, (UNUM16)50, (UNUM16)50,
				(UNUM16)50
		};
	/*	AC CH01-CH16 5A */
	/*static const UNUM16 AC_R_TAB[16]=
	{
			(UNUM16)760, (UNUM16)760, (UNUM16)760, (UNUM16)760,

			(UNUM16)565, (UNUM16)565, (UNUM16)445, (UNUM16)445,
			(UNUM16)445, (UNUM16)333, (UNUM16)277, (UNUM16)277
	};*/

	UNUM32 lu32_Current_Ret = (UNUM16)0;
	UNUM16 lu16_ret = (UNUM16)0;

	if(channel < (UNUM16)20)
	{
		if(lu16_BoardType == (UNUM16)1)
		{
			/*lu32_Current_Ret = ((UNUM32)2033 * (UNUM32)10000 - (UNUM32)I2T_VREF * (UNUM32)AD_value) / (UNUM32)AC_R_TAB[channel];*/
			/*lu32_Current_Ret = (UNUM32)2 * lu32_Current_Ret;*/
			lu32_Current_Ret =(UNUM32)AD_value*(UNUM32)15*(UNUM32)2500*10/((UNUM32)6*(UNUM32)4096*(UNUM32)AC_R_TAB[channel]);
			
		}
		else
		{
			/*lu32_Current_Ret =(UNUM32)AD_value*(UNUM32)105*(UNUM32)2500*10/((UNUM32)4*(UNUM32)4096*(UNUM32)CH_R_TAB[channel]);*/
			lu32_Current_Ret =(UNUM32)AD_value*(UNUM32)105*(UNUM32)250/((UNUM32)4*(UNUM32)41*(UNUM32)CH_R_TAB[channel]);

		}
		/*	lu32_Current_Ret = ((UNUM32)I2T_VMAX * (UNUM32)10000 - (UNUM32)I2T_VREF * (UNUM32)AD_value) / (UNUM32)760;*/


		I2T_Control[channel].Current = lu32_Current_Ret*100;/*因为不能进行浮点运算，乘以100使和后面额定电流比的倍数为整数*/
	}
	else
	{
		lu16_ret = I2T_ERROR;
	}

	return lu16_ret;
}

static UNUM16 I2T_APP_GetAcumCoef(UNUM16 channel,UNUM16 I2T_Y)
{
	UNUM16 lu16_ret = (UNUM16)0;
	UNUM16 lu16_mod = (UNUM16)0;
	UNUM32 lu32_Acct = (UNUM16)0;

	if (channel < (UNUM16)20)
	{
		lu32_Acct = ((UNUM32)I2T_Y * (UNUM32)I2T_Y) -  ((UNUM32)4 * (UNUM32)I2T_Y) - (UNUM32)11600;
		lu16_mod =  (UNUM16)(lu32_Acct % (UNUM32)23);
		if(lu16_mod > (UNUM16)11)
		{
			I2T_Control[channel].AcumCoef = (UNUM16)(lu32_Acct / (UNUM32)23) + (UNUM16)1;
		}
		else
		{
			I2T_Control[channel].AcumCoef = (UNUM16)(lu32_Acct / (UNUM32)23);
		}

	}
	else
	{
		lu16_ret = I2T_ERROR;
	}

	return lu16_ret;
}

/*
void I2T_APP_SmoothReset(void)
{
	UNUM16 lu16_i = (UNUM16)0;

	for ( lu16_i = (UNUM16)0; lu16_i < (UNUM16)20; lu16_i++ )
	{
		au16_CurTimes[lu16_i] = (UNUM16)0;
	}
}
*/
/*static void I2T_APP_SmoothFilter(UNUM16 lu16_ChannelSN)
{
    static UNUM16 au16_CurC[20] = {(UNUM16)0};
    static UNUM32 au32_CurS[20] = {(UNUM16)0};
    static UNUM16 au16_CurN = (UNUM16)60;

    if(au16_CurTimes[lu16_ChannelSN] > (au16_CurN-(UNUM16)1))
    {
        au32_CurS[lu16_ChannelSN] = (au32_CurS[lu16_ChannelSN] + (UNUM32)ADC_Ref_Check[lu16_ChannelSN].mu16_ADC_FinalResult) - (UNUM32)au16_CurC[lu16_ChannelSN];
        au16_CurC[lu16_ChannelSN] = (UNUM16)(au32_CurS[lu16_ChannelSN]/(UNUM32)au16_CurN);
        I2T_ADC_Value[lu16_ChannelSN] = au16_CurC[lu16_ChannelSN];
        au16_CurTimes[lu16_ChannelSN] = au16_CurN;
    }
    else
    {
        if(au16_CurTimes[lu16_ChannelSN] == (UNUM16)0)
        {
            au32_CurS[lu16_ChannelSN] = (UNUM32)ADC_Ref_Check[lu16_ChannelSN].mu16_ADC_FinalResult;
        }
        else
        {
            au32_CurS[lu16_ChannelSN] = au32_CurS[lu16_ChannelSN] + (UNUM32)ADC_Ref_Check[lu16_ChannelSN].mu16_ADC_FinalResult;
        }
        au16_CurC[lu16_ChannelSN] = (UNUM16)(au32_CurS[lu16_ChannelSN]/((UNUM32)(au16_CurTimes[lu16_ChannelSN]) + (UNUM16)1 ));
        I2T_ADC_Value[lu16_ChannelSN] = au16_CurC[lu16_ChannelSN];
        au16_CurTimes[lu16_ChannelSN]++;
    }
}
*/

void I2T_APP_Process(void)
{
	UNUM16 lu16_ChannelSN = (UNUM16)0;
	UNUM16 lu16_I2tStatus = (UNUM16)0;
	UNUM16 lu16_CtrlStatus = (UNUM16)0;

	GPIO_GpioCtrlRegs.GPADIR.all &= (UNUM32)0xFFFFF; /*SET GPIO 0-20 as an input*/
	GPIO_GpioDataRegs.GPADAT.all |= (UNUM32)0xFFFFF;
	SPI_GetResult();



	for ( lu16_ChannelSN = (UNUM16)0; lu16_ChannelSN < (UNUM16)20; lu16_ChannelSN++ )
	{
		if ( lu16_ChannelSN < (UNUM16)20 )
		{

			I2T_ADC_Value[lu16_ChannelSN] =  SPI_Rece_Current(lu16_ChannelSN) & (UNUM16)0xFFF;
		 }

		I2T_APP_Short(lu16_ChannelSN);
		if((Channal_Status[lu16_ChannelSN] != SSPC_ST_SHORT)&&(Channal_Status[lu16_ChannelSN] != SSPC_ST_TRIPPED))
		{
			I2T_APP_ChannelStatus(lu16_ChannelSN);
		}

		lu16_CtrlStatus = GPIO_GetCtrlStatus(lu16_ChannelSN);
		if ( lu16_CtrlStatus == (UNUM16)3)
		{
			lu16_I2tStatus = I2T_APP_Protection(lu16_ChannelSN,I2T_ADC_Value[lu16_ChannelSN]);
			if ( lu16_I2tStatus == I2T_STS_TRIGGER)
			{
				I2T_Control[lu16_ChannelSN].Times = I2T_Control[lu16_ChannelSN].Times + (UNUM32)10;
				GPIO_OverloadCtrl(lu16_ChannelSN);
			}
			if ( lu16_I2tStatus == I2T_STS_PROTECTCAL)
			{
					I2T_Control[lu16_ChannelSN].Times = I2T_Control[lu16_ChannelSN].Times + (UNUM32)10;
			}
		}
		else
		{
			I2T_Control[lu16_ChannelSN].Current = (UNUM32)0;

			if(I2T_Control[lu16_ChannelSN].CurHeat!=0)
			{
				I2T_Control[lu16_ChannelSN].CurHeat = I2T_Control[lu16_ChannelSN].CurHeat - I2T_DECAY_T;
			}
		}
	}
	ADC_FINISHED_FLAG = (UNUM16)1;

}


static UNUM16 I2T_APP_Protection(UNUM16 channel,UNUM16 AD_value)
{
	UNUM16 lu16_I2T_Y = (UNUM16)0;
	UNUM16 lu16_I2T_Y_Mod = (UNUM16)0;
	UNUM16 lu16_I2T_Status = (UNUM16)0;
	UNUM16 lu16_RET_Value = (UNUM16)0;

	I2T_Control[channel].Period = (UNUM16)10;
	I2T_APP_CalCurrent(channel,AD_value);

	/*I2T_Control[13].Current=I2T_Control[13].Current*2/3;/*13,14通道保护值缩小*/
	/*I2T_Control[14].Current=I2T_Control[14].Current*2/3;*/
	/*I2T_Control[10].Current=I2T_Control[10].Current*2/3;/*12,13通道保护值缩小*/
	/*I2T_Control[11].Current=I2T_Control[11].Current*2/3;*/
	if(lu16_BoardType == (UNUM16)1)
	{
		lu16_I2T_Y = (UNUM16)(I2T_Control[channel].Current  / (UNUM32)AC_RC_TAB[channel]); /*(Current(mA)/RC(A))%*/
		lu16_I2T_Y_Mod = (UNUM16)((I2T_Control[channel].Current) % ((UNUM32)AC_RC_TAB[channel]));
	}
	else
	{
		lu16_I2T_Y = (UNUM16)(I2T_Control[channel].Current  / (UNUM32)DC_RC_TAB[channel]); /*(Current(mA)/RC(A))%*/
		lu16_I2T_Y_Mod = (UNUM16)((I2T_Control[channel].Current) % ((UNUM32)DC_RC_TAB[channel]));
	}
	if(lu16_I2T_Y_Mod > (UNUM16)4)
	{
		lu16_I2T_Y++;
	}


	if (lu16_I2T_Y >= I2T_MAX_VALUE)
	{
		lu16_I2T_Status = I2T_STS_TRIGGER;
	}

	else if ( (lu16_I2T_Y > I2T_START_VALUE) && (lu16_I2T_Y < I2T_MAX_VALUE))
	{

		lu16_RET_Value = I2T_APP_GetAcumCoef(channel,lu16_I2T_Y);
		if(lu16_RET_Value != I2T_ERROR )
		{
			I2T_Control[channel].CurHeat = I2T_Control[channel].CurHeat + (UNUM32)I2T_Control[channel].AcumCoef;

			if (I2T_Control[channel].CurHeat > (UNUM32)I2T_HEAT_TRIGGER)
			{
				lu16_I2T_Status = I2T_STS_TRIGGER;
			}
			else
			{
				lu16_I2T_Status = I2T_STS_PROTECTCAL;
			}

		}
		else
		{
			lu16_I2T_Status = I2T_STS_ERROR;
		}
	}

	else if (lu16_I2T_Y > I2T_STOP_DECAY)
	{
		if (I2T_Control[channel].CurHeat < I2T_HEAT_BALANCE )
		{
			I2T_Control[channel].CurHeat = I2T_Control[channel].CurHeat + I2T_DECAY_T;
			if (I2T_Control[channel].CurHeat > I2T_HEAT_BALANCE)
			{
				I2T_Control[channel].CurHeat = I2T_HEAT_BALANCE;
			}
			lu16_I2T_Status = I2T_STS_NORMAL;

		}
		else if ( I2T_Control[channel].CurHeat > I2T_HEAT_BALANCE )
		{
			I2T_Control[channel].CurHeat = I2T_Control[channel].CurHeat - I2T_DECAY_T;
			if( I2T_Control[channel].CurHeat > I2T_HEAT_BALANCE)
			{

				lu16_I2T_Status = I2T_STS_PROTECTCAL;
			}
			else
			{
				lu16_I2T_Status = I2T_STS_NORMAL;
				I2T_Control[channel].CurHeat = I2T_HEAT_BALANCE;
			}
		}
		else
		{

		}
	}
	else
	{
		if (I2T_Control[channel].CurHeat < I2T_HEAT_BALANCE )
		{
			I2T_Control[channel].CurHeat = I2T_Control[channel].CurHeat + I2T_DECAY_T;
			if (I2T_Control[channel].CurHeat > I2T_HEAT_BALANCE)
			{
				I2T_Control[channel].CurHeat = I2T_HEAT_BALANCE;
			}
		}
		else
		{
			I2T_Control[channel].CurHeat = I2T_HEAT_BALANCE;
		}
		lu16_I2T_Status = I2T_STS_NORMAL;
	}

	return lu16_I2T_Status;
}

void I2T_APP_Short(UNUM16 channel)
{
	UNUM16 temp=0;
	temp=SPI_Rece_State(channel);
	temp &=(UNUM16)0x0002;
	if(temp==(UNUM16)SHORT1)
	{
	/*	GPIO_ChannelTurnOff(channel);*/
		GPIO_Short_Ctrl(channel);
	}

}
void I2T_APP_ChannelStatus(UNUM16 channel)
{
	UNUM16 temp=0;
	UNUM16 status=0;
	temp=SPI_Rece_State(channel);
	temp &=(UNUM16)0x0001;
	status=GPIO_GetCtrlStatus(channel);
	if(temp==(UNUM16)SSPC_TYPE)
	{
		if(status==3)
		{
			GPIO_CLOSE_FAILED_Ctrl(channel);
		}
		else
		{
			/*GPIO_status_OFF_Ctrl(channel);*/
		}
	}
	else if(temp==(~SSPC_TYPE))
	{

		if(status==2)
		{
			GPIO_OPEN_FAILED_Ctrl(channel) ;
		}
		else
		{
			/*GPIO_status_ON_Ctrl(channel);*//*此步骤可以省略*/
		}
	}
	else
	{

	}
}

UNUM32 I2T_APP_GetCurrent(UNUM16 channelSN)
{
	return I2T_Control[channelSN].Current/((UNUM32)100);

}

