#include "I2T_APP.h"
#include "GPIO.h"
#include "ADC.h"
#include "SPI.h"
#include "COMMON.h"


UNUM16 Channal_Status[20] = {(UNUM16)0};

/*static UNUM16 Reset_Command[20] = {(UNUM16)0};*/
static void GPIO_OutputCtrl(UNUM32 au32_HighBytes,UNUM32 au32_LowBytes);
static void GPIO_ResetCtrl(UNUM32 au32_HighBytes,UNUM32 au32_LowBytes);
static void Lock_CommandCtrl (UNUM32 au32_HighBytes,UNUM32 au32_LowBytes);
static void Channel_Output_Ctrl(void);
void Channel_PhaseState_Judge(void);
extern UNUM32 PHASE_JUDGE_FLAG[5];
extern UNUM32 GROUP_FLAG[5];
void GPIO_APP_StateInit(void)
{
	UNUM16 lu16_i = (UNUM16)0;

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)20; lu16_i++)
	{
		GPIO_ChannelTurnOff(lu16_i);
		Channal_Status[lu16_i] = SSPC_ST_OFF;
	}
	recHighBytes[0]=(UNUM32)0;
	recLowBytes[0]=(UNUM32)0;
	recHighBytes[1]=(UNUM32)0;
	recLowBytes[1]=(UNUM32)0;
	recHighBytes[2]=(UNUM32)0;
	recLowBytes[2]=(UNUM32)0;
	recLowBytes[3]=(UNUM32)0;
	recLowBytes[4]=(UNUM32)0;
}

void GPIO_APP_ChannelProcess(void)
{

	UNUM32 au32_HighBytes = (UNUM32)0;
	UNUM32 au32_LowBytes = (UNUM32)0;

		au32_HighBytes =recHighBytes[2];
		au32_LowBytes = recLowBytes[2];
		GPIO_ResetCtrl(au32_HighBytes,au32_LowBytes);/*重置*/

		au32_HighBytes =recHighBytes[1];
		au32_LowBytes = recLowBytes[1];
		Lock_CommandCtrl(au32_HighBytes,au32_LowBytes);/*锁定*/

		au32_HighBytes = recHighBytes[0];
		au32_LowBytes = recLowBytes[0];
		GPIO_OutputCtrl(au32_HighBytes,au32_LowBytes);/*开通*/


	Channel_Output_Ctrl();
}


static void Lock_CommandCtrl (UNUM32 au32_HighBytes,UNUM32 au32_LowBytes)
{
	UNUM16 lu16_i = (UNUM16)0;
	UNUM32 lu32_LockCommand = (UNUM32)0;

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)16; lu16_i++)
	{
		lu32_LockCommand = au32_LowBytes << ((UNUM16)2*lu16_i);
		lu32_LockCommand =  lu32_LockCommand >> 30;
		if( (Channal_Status[lu16_i] != SSPC_ST_SHORT) &&(Channal_Status[lu16_i] != SSPC_ST_TRIPPED) && (lu32_LockCommand == SSPC_CMD_LCOK))
		{
			Channal_Status[lu16_i] = SSPC_ST_LOCK;
		}
		else if( (Channal_Status[lu16_i] != SSPC_ST_SHORT) &&(Channal_Status[lu16_i] != SSPC_ST_TRIPPED) && (lu32_LockCommand == SSPC_CMD_UNLCOK))
		{
			Channal_Status[lu16_i] = SSPC_ST_OFF;
		}
		else
		{

		}
	}

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)4; lu16_i++)
	{
		lu32_LockCommand = au32_HighBytes << ((UNUM16)2*lu16_i);
		lu32_LockCommand =  lu32_LockCommand >> 30;
		if( (Channal_Status[lu16_i+(UNUM16)16] != SSPC_ST_SHORT) &&(Channal_Status[lu16_i + (UNUM16)16] != SSPC_ST_TRIPPED) && (lu32_LockCommand == SSPC_CMD_LCOK))
		{
			Channal_Status[lu16_i + (UNUM16)16] = SSPC_ST_LOCK;
		}
		else if( (Channal_Status[lu16_i] != SSPC_ST_SHORT) &&(Channal_Status[lu16_i+ (UNUM16)16] != SSPC_ST_TRIPPED) && (lu32_LockCommand == SSPC_CMD_UNLCOK))
		{
			Channal_Status[lu16_i+ (UNUM16)16] = SSPC_ST_OFF;
		}
		else
		{

		}
	}

}

static void GPIO_OutputCtrl(UNUM32 au32_HighBytes,UNUM32 au32_LowBytes)
{
	UNUM16 lu16_i = (UNUM16)0;
	UNUM32 lu32_OutputCommand = (UNUM32)0;

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)16; lu16_i++)
	{
		if( (Channal_Status[lu16_i] != SSPC_ST_SHORT) &&(Channal_Status[lu16_i] != SSPC_ST_LOCK) && (Channal_Status[lu16_i] != SSPC_ST_TRIPPED) )
		{
			lu32_OutputCommand = au32_LowBytes << ((UNUM16)2*lu16_i);
			lu32_OutputCommand =  lu32_OutputCommand >> 30;

			if( lu32_OutputCommand  == SSPC_CMD_OFF)
			{
				Channal_Status[lu16_i] = SSPC_ST_OFF;
			}
			else if( lu32_OutputCommand  == SSPC_CMD_ON)
			{
				Channal_Status[lu16_i] = SSPC_ST_ON;
			}
			else
			{
				Channal_Status[lu16_i]=SSPC_ST_OFF;
			}
		}

	}

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)4; lu16_i++)
	{
		if( (Channal_Status[lu16_i+(UNUM16)16] != SSPC_ST_SHORT) &&(Channal_Status[lu16_i+ (UNUM16)16] != SSPC_ST_LOCK) && (Channal_Status[lu16_i+ (UNUM16)16] != SSPC_ST_TRIPPED))
		{
			lu32_OutputCommand = au32_HighBytes << ((UNUM16)2*lu16_i);
			lu32_OutputCommand =  lu32_OutputCommand >> 30;

			if( lu32_OutputCommand  == SSPC_CMD_OFF)
			{
				Channal_Status[lu16_i + (UNUM16)16] = SSPC_ST_OFF;
			}
			else if( lu32_OutputCommand  == SSPC_CMD_ON)
			{
				Channal_Status[lu16_i + (UNUM16)16] = SSPC_ST_ON;

			}
			else
			{

			}
		}

	}

}


static void GPIO_ResetCtrl(UNUM32 au32_HighBytes,UNUM32 au32_LowBytes)/*主要给给通道状态赋值*/
{
	UNUM16 lu16_i = (UNUM16)0;
	UNUM32 lu32_ResetCommand = (UNUM32)0;

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)16; lu16_i++)
	{
		lu32_ResetCommand = au32_LowBytes << ((UNUM16)2*lu16_i);
		lu32_ResetCommand =  lu32_ResetCommand >> 30;

		if( lu32_ResetCommand  == SSPC_CMD_RESET)
		{
			Channal_Status[lu16_i] = SSPC_ST_OFF;
			I2T_APP_I2tClear(lu16_i);
		}
	}

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)4; lu16_i++)
	{
		lu32_ResetCommand = au32_HighBytes << ((UNUM16)2*lu16_i);
		lu32_ResetCommand =  lu32_ResetCommand >> 30;

		if( lu32_ResetCommand  == SSPC_CMD_RESET)
		{
			Channal_Status[lu16_i + (UNUM16)16] = SSPC_ST_OFF;
			I2T_APP_I2tClear(lu16_i + (UNUM16)16);
		}
	}

}

void GPIO_OverloadCtrl(UNUM16 au16_ChannelSN)
{

		if((au16_ChannelSN<=2))/*因为是无符号整数所以肯定大于0，和0比较无意义，和0比较可以省掉*/
		{
			if(GROUP_FLAG[0]==1)
			{
				Channal_Status[0] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[1] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[2] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
			else
			{
				Channal_Status[au16_ChannelSN] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}

		}
		else if((au16_ChannelSN>=3)&&(au16_ChannelSN<=5))
		{
			if(GROUP_FLAG[1]==1)
			{
				Channal_Status[3] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[4] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[5] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
			else
			{
				Channal_Status[au16_ChannelSN] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
		}
		else if((au16_ChannelSN>=7)&&(au16_ChannelSN<=9))
		{
			if(GROUP_FLAG[2]==1)
			{
				Channal_Status[7] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[8] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[9] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
			else
			{
				Channal_Status[au16_ChannelSN] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
		}
		else if((au16_ChannelSN>=10)&&(au16_ChannelSN<=12))
		{
			if(GROUP_FLAG[3]==1)
			{
				Channal_Status[10] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[11] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[12] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
			else
			{
				Channal_Status[au16_ChannelSN] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
		}
		else if((au16_ChannelSN>=13)&&(au16_ChannelSN<=15))
		{
			if(GROUP_FLAG[4]==1)
			{
				Channal_Status[13] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[14] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
				Channal_Status[15] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
			else
			{
				Channal_Status[au16_ChannelSN] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
			}
		}
		else
		{
			Channal_Status[au16_ChannelSN] = (UNUM16)4;/*SSPC_ST_TRIPPED=4*/
		}
}
void GPIO_Short_Ctrl(UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN < (UNUM16)20 )
	{
		Channal_Status[au16_ChannelSN] = SSPC_ST_SHORT;
	}
}
void GPIO_status_ON_Ctrl(UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN < (UNUM16)20 )
	{
		Channal_Status[au16_ChannelSN] = SSPC_ST_ON;
	}
}
void GPIO_status_OFF_Ctrl(UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN < (UNUM16)20 )
	{
		Channal_Status[au16_ChannelSN] = SSPC_ST_OFF;
	}
}
void GPIO_CLOSE_FAILED_Ctrl(UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN < (UNUM16)20 )
	{
		Channal_Status[au16_ChannelSN] = SSPC_ST_CLOSE_FAILED;
	}
}
void GPIO_OPEN_FAILED_Ctrl(UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN < (UNUM16)20 )
	{
		Channal_Status[au16_ChannelSN] = SSPC_ST_OPEN_FAILED;
	}
}

void GPIO_Error_Ctrl(UNUM16 au16_ChannelSN)
{
	if ( au16_ChannelSN < (UNUM16)20 )
	{
		Channal_Status[au16_ChannelSN] = SSPC_ST_ERROR;
	}
}

UNUM16 GPIO_GetCtrlStatus(UNUM16 au16_ChannelSN)
{
	return Channal_Status[au16_ChannelSN];

}

static void Channel_Output_Ctrl(void)/*根据GPIO_OutputCtrl赋的值对寄存器进行操作*/
{
	UNUM16 lu16_i = (UNUM16)0;
	/*static UNUM16 lu16_time = (UNUM16)0;
	lu16_time++;
	GPIO_ChannelTurnOn(0);
	if(lu16_time==600)
	{
		GPIO_ChannelTurnOn(0);
		GPIO_ChannelTurnOn(1);
	}

	if(lu16_time==1200)
	{
		GPIO_ChannelTurnOff(0);
		GPIO_ChannelTurnOff(1);
		lu16_time=0;
	}*/

	for (lu16_i = (UNUM16)0; lu16_i < (UNUM16)20; lu16_i++)
	{

		if( Channal_Status[lu16_i] == SSPC_ST_ON )
		{
			GPIO_ChannelTurnOn(lu16_i);
		}
		else
		{
			GPIO_ChannelTurnOff(lu16_i);
		}
	}

}
void Channel_PhaseState_Judge(void)/*判断三相通道状态知否一致!!!!!!!!!!*/
{
	UNUM16 i=0;UNUM16 a=0;UNUM16 b=0;UNUM16 c=0;UNUM16 lu16_ChannelSN=0;
	UNUM16 temp[20]={0};
	for(lu16_ChannelSN=0;lu16_ChannelSN<20;lu16_ChannelSN++)
	{
		temp[lu16_ChannelSN]=SPI_Rece_State(lu16_ChannelSN);
		temp[lu16_ChannelSN] &=(UNUM16)0x0001;
	}





	for(i=0;i<5;i++)
	{
		switch(i)
		{
		case 1:
			if(GROUP_FLAG[i]==1)
			{
				a=temp[0];b=temp[1];c=temp[2];
			 	 if(((a-b)!=(UNUM32)0)||((a-c)!=(UNUM32)0)||((b-c)!=(UNUM32)0))
			 	 {

			 		GPIO_Error_Ctrl(0);
			 		GPIO_Error_Ctrl(1);
			 		GPIO_Error_Ctrl(2);
			 	 }
			 	 else
			 	 {
			 		 PHASE_JUDGE_FLAG[i]=0;
			 	 }
			}break;
		case 2:
			if(GROUP_FLAG[i]==1)
			{
				a=temp[3];b=temp[4];c=temp[5];
				if(((a-b)!=(UNUM32)0)||((a-c)!=(UNUM32)0)||((b-c)!=(UNUM32)0))
				{

			 		GPIO_Error_Ctrl(3);
			 		GPIO_Error_Ctrl(4);
			 		GPIO_Error_Ctrl(5);
				}
				else
				{

				}
			}break;
		case 3:
			if(GROUP_FLAG[i]==1)
			{
				a=temp[7];b=temp[8];c=temp[9];
				if(((a-b)!=(UNUM32)0)||((a-c)!=(UNUM32)0)||((b-c)!=(UNUM32)0))
				{

			 		GPIO_Error_Ctrl(7);
			 		GPIO_Error_Ctrl(8);
			 		GPIO_Error_Ctrl(9);
				}
				else
				{

				}
			}break;
		case 4:
			if(GROUP_FLAG[i]==1)
			{
				a=temp[10];b=temp[11];c=temp[12];
				if(((a-b)!=(UNUM32)0)||((a-c)!=(UNUM32)0)||((b-c)!=(UNUM32)0))
				{

			 		GPIO_Error_Ctrl(10);
			 		GPIO_Error_Ctrl(11);
			 		GPIO_Error_Ctrl(12);
				}
				else
				{

				}
			}break;
		case 5:
			if(GROUP_FLAG[i]==1)
			{
				a=temp[13];b=temp[14];c=temp[15];
				if(((a-b)!=(UNUM32)0)||((a-c)!=(UNUM32)0)||((b-c)!=(UNUM32)0))
				{

			 		GPIO_Error_Ctrl(14);
			 		GPIO_Error_Ctrl(15);
			 		GPIO_Error_Ctrl(16);
				}
				else
				{

				}
			}break;
		default:
			break;
		}
	}

}

