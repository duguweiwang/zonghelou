#include "tlv5638.h"
/****	extern includes	********************************************************/
#include "spi.h"
#include "gpio.h"

/****	variable definitions	**************************************************/
static TLV5638_SettingsT  TLV5638_ms_Settings;
const TLV5638_SettingsT	TLV5638_ms_DefaultSettings = {
													  (UNUM16)TLV5638_SPEED_FAST,
													  (UNUM16)TLV5638_POWER_NORMAL,
													  (UNUM16)TLV5638_REF_IN2048,
													 };

/****	function declarations	**************************************************/
UNUM16 TLV5638_VoltageCheck(UNUM16 au16_OutputVoltage);
void TLV5638_Delay(void);


/******************************************************************************
*	Description: This function Initialize TLV5638 to a specific state
******************************************************************************/
void TLV5638_Init(void)
{
	/*SPI_CLOCK							SPI clock <	20MHz	*/
	TLV5638_SettingsT	ls_TLV5638_Settings;

	ls_TLV5638_Settings.Speed = (UNUM16)TLV5638_SPEED_FAST;
	ls_TLV5638_Settings.PowerMode = (UNUM16)TLV5638_POWER_NORMAL;
	ls_TLV5638_Settings.RefVoltage = (UNUM16)TLV5638_REF_IN2048;

	if((UNUM16)TLV5638_OK != (UNUM16)TLV5638_Set_Up(ls_TLV5638_Settings))		/*	handle error	*/
	{
		/*	add error handle function: go into default TLV5638 Settings	*/
		ls_TLV5638_Settings = TLV5638_ms_DefaultSettings;
		TLV5638_Set_Up(ls_TLV5638_Settings);
	}
	else
	{
	}
}

/******************************************************************************
*	Description: This function  config TLV5638
*	Parameters:  TLV5638_Settings			-
*	Return values:  TLV5638_OK:       if success
*	                TLV5638_ERROR:    if failed	-
******************************************************************************/
UNUM16 TLV5638_Set_Up(TLV5638_SettingsT as_TLV5638_Settings)
{
	static TLV5638_ControlRegisterT 	TLV5638_ms_ControlRegister;
	UNUM16 Temp_Return = (UNUM16)TLV5638_OK;
	UNUM16 Flag=(UNUM16)1;
	UNUM16 Flag_1=(UNUM16)1;
	UNUM16 Flag_2=(UNUM16)1;
	if(((UNUM16)as_TLV5638_Settings.Speed == (UNUM16)TLV5638_SPEED_SLOW)||((UNUM16)as_TLV5638_Settings.Speed == (UNUM16)TLV5638_SPEED_FAST))	/*	speed mode	*/
	{
		TLV5638_ms_ControlRegister.sBit.SPD = as_TLV5638_Settings.Speed;		/*	类型转换问题	*/
	}
	else
	{
		/*return (UNUM16)TLV5638_ERROR_INVALID_PARAMETERS; */
		Temp_Return = (UNUM16)TLV5638_ERROR_INVALID_PARAMETERS;
		Flag=(UNUM16)0;
	}
	
	if (Flag)
	{
		if(((UNUM16)as_TLV5638_Settings.PowerMode == (UNUM16)TLV5638_POWER_NORMAL)||((UNUM16)as_TLV5638_Settings.PowerMode == (UNUM16)TLV5638_POWER_DOWN))	/*	power mode	*/
		{
			TLV5638_ms_ControlRegister.sBit.PWR = as_TLV5638_Settings.PowerMode;
		}
		else
		{
			/*return (UNUM16)TLV5638_ERROR_INVALID_PARAMETERS;*/
			Temp_Return = (UNUM16)TLV5638_ERROR_INVALID_PARAMETERS;
			Flag_1=(UNUM16)0;
		}

		if (Flag_1)
		{
			switch(as_TLV5638_Settings.RefVoltage)		/*	ref voltage mode	*/
			{
				case (UNUM16)TLV5638_REF_EXTERNAL:					/*	ref voltage external	*/
					TLV5638_ms_ControlRegister.sBit.REF1 = (UNUM16)TLV5638_LOW;
					TLV5638_ms_ControlRegister.sBit.REF0 = (UNUM16)TLV5638_LOW;
					break;
				case (UNUM16)TLV5638_REF_IN1024:						/*	ref voltage internal 1024 mv	*/
					TLV5638_ms_ControlRegister.sBit.REF1 = (UNUM16)TLV5638_LOW;
					TLV5638_ms_ControlRegister.sBit.REF0 = (UNUM16)TLV5638_HIGH;
					break;
				case (UNUM16)TLV5638_REF_IN2048:						/*	ref voltage internal 2048 mv	*/
					TLV5638_ms_ControlRegister.sBit.REF1 = (UNUM16)TLV5638_HIGH;
					TLV5638_ms_ControlRegister.sBit.REF0 = (UNUM16)TLV5638_LOW;
					break;
				default:
				{
					/*return (UNUM16)TLV5638_ERROR_INVALID_PARAMETERS;	return error	*/
					Temp_Return = (UNUM16)TLV5638_ERROR_INVALID_PARAMETERS;
					Flag_2=(UNUM16)0;
					break;
				}
			}
            if (Flag_2)
            {
            	/*	set R0,R1 to HIGH; force TLV5638 into configutation mode	*/
            	TLV5638_ms_ControlRegister.sBit.R0 = (UNUM16)TLV5638_HIGH;
            	TLV5638_ms_ControlRegister.sBit.R1 = (UNUM16)TLV5638_HIGH;

            	/*	save TLV5638 settings	*/
            	TLV5638_ms_Settings = as_TLV5638_Settings;

            	/*	send to TLV5638 via SPI	*/
            	TLV5638_ms_ControlRegister.mu16_Word = (UNUM16)TLV5638_ms_ControlRegister.mu16_Word &(UNUM16)TLV5638_MASK_CONTROL_REGISTER;		/*	definition	*/
            	/*SPI_Send_Word(TLV5638_ms_ControlRegister.mu16_Word);*/
            	TLV5638_Delay();

            	/*	Delay to make sure data transfer completely	*/
            }
		}
	}
	return (UNUM16)Temp_Return;
}

/******************************************************************************
*	Description: This function output voltage on channel A
*	Parameters:  output voltage	: 0~4095		-
*	Return values: TLV5638_OK:       if success
*	               TLV5638_ERROR:    if failed	-
******************************************************************************/
UNUM16 TLV5638_Output_Channel_A(UNUM16 au16_OutputVoltage)
{
	/*	voltage range shall be check	*/
	UNUM16 Temp_Return = (UNUM16)TLV5638_OK;
	UNUM16 			lu16_TLV5638_Output_A = (UNUM16)TLV5638_MAX_OUTPUT_VLOTAGE;
	
	lu16_TLV5638_Output_A = TLV5638_VoltageCheck(au16_OutputVoltage);
	
	if((UNUM16)lu16_TLV5638_Output_A >= (UNUM16)TLV5638_MAX_OUTPUT_VLOTAGE)	/*	 || (lu16_TLV5638_Output_A < 0)	*/
	{
		/*return TLV5638_ERROR_INVALID_PARAMETERS;	return error	*/
		Temp_Return = (UNUM16)TLV5638_ERROR_INVALID_PARAMETERS;
	}
	else
	{
		/*	channel configed shall be same with one selected	*/
		lu16_TLV5638_Output_A |= TLV5638_MASK_BIT_SET_CHANNEL_A;
		/*SPI_Send_Word(lu16_TLV5638_Output_A);			change to SPI_Send()	*/
		TLV5638_Delay();
	}
	return Temp_Return;
}


/******************************************************************************
*	Description: This function check the legality of voltage value
*	Parameters:  output voltage	: 0~4095		-
*	Return values:
*	                output voltage(0~4095): if success
*	                error:					if failed	-
******************************************************************************/

UNUM16 TLV5638_VoltageCheck(UNUM16 au16_OutputVoltage)
{
	UNUM16 lu16_CheckResult = (UNUM16)TLV5638_MAX_OUTPUT_VLOTAGE;
	
	/*	voltage range shall be check	*/
	if((UNUM16)au16_OutputVoltage >= (UNUM16)TLV5638_MAX_OUTPUT_VLOTAGE)				/*	depend on RefVoltage, replace by a function	*/
	{
		/*return TLV5638_MAX_OUTPUT_IN2048;		return error	*/
	}
	else if((UNUM16)au16_OutputVoltage >= (UNUM16)TLV5638_MAX_OUTPUT_IN1024)
	{
		if((UNUM16)TLV5638_ms_Settings.RefVoltage == (UNUM16)TLV5638_REF_IN1024)
		{
			/*return TLV5638_MAX_OUTPUT_IN2048;		return error	*/
		}
		else if((UNUM16)TLV5638_ms_Settings.RefVoltage == (UNUM16)TLV5638_REF_IN2048)
		{
			lu16_CheckResult = au16_OutputVoltage;
		}
		else
		{
			/*return TLV5638_MAX_OUTPUT_IN2048;		return error	*/
		}
	}
	else	/* if(au16_OutputVoltage >= 0)*/
	{
		if((UNUM16)TLV5638_ms_Settings.RefVoltage == (UNUM16)TLV5638_REF_IN1024)
		{
			lu16_CheckResult = au16_OutputVoltage << 1;		/*	replace by macro or function	*/
		}
		else if((UNUM16)TLV5638_ms_Settings.RefVoltage == (UNUM16)TLV5638_REF_IN2048)
		{
			lu16_CheckResult = au16_OutputVoltage;
		}
		else
		{
			/*return TLV5638_MAX_OUTPUT_IN2048;		return error	*/
		}
	}
	
	return lu16_CheckResult;
}

/******************************************************************************
*	Description: This function delay 2500 system clk cycle
******************************************************************************/
void TLV5638_Delay(void)
{
	UNUM16 lu16_DelayCycle = (UNUM16)2500;

	while((UNUM16)lu16_DelayCycle>(UNUM16)1)
	{
		lu16_DelayCycle--;
	}
}

/****	end of file	************************************************************/
