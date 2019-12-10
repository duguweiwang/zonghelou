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
*     Module Name:         %name:     ECAN_APP.c %                          *
*     Module Version:      %version:  3 %                                   *
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
*				  %created_by:       mason                                  *
*									                                        *
*     Date:       %date_modified:  2014-12-02 %                 			*
*                                                                           *
****************************************************************************/
/**** includes ***************************************************************/
#include "ECAN_APP.h"
#include "COMMON.h"
#include "GPIO_APP.h"

/**** definitions*************************************************************/
struct CAN_Re_Message ECAN_APP_ms_Msg_Re[3];


/*通道电流值状态报告*/
static UNUM32 CUR_STA_RPT[20] = {(UNUM32)0};

/*通道额定电流值*/
static UNUM32 CH_CUR_RAT[20] = {(UNUM32)0};

/*SSPC1 通道状态*/
static UNUM32 CH_STA_RPT[20] = {(UNUM32)0};

static UNUM32 lu32_Transmit_HigBytes[15] = {(UNUM32)0};
static UNUM32 lu32_Transmit_LowBytes[15] = {(UNUM32)0};
static UNUM32 lu32_Transmit_MsgID[15] = {(UNUM32)0};

static void ECAN_APP_Msg_Setting(UNUM16 lu16_frame_id);
void PHASE_Command(void);
void PHASE_JUDGE(void);

UNUM32 PHASE_JUDGE_FLAG[5] = {(UNUM32)0};/*三相通道命令若一致则该标志位为1*/
extern UNUM32 GROUP_FLAG[5];

/**** functions declarations *************************************************/

void ECAN_APP_ReceiveProcess(void)
{
	UNUM16 lu16_i = (UNUM16)0;

	for ( lu16_i =  (UNUM16)0; lu16_i <  (UNUM16)20; lu16_i++ )/* Read channel current*/
	{

		CH_CUR_RAT[lu16_i] = (UNUM32)I2T_APP_GetRateCurrent(lu16_i); /* 通道额定电流值读取   */
		CH_STA_RPT[lu16_i] = (UNUM32)GPIO_GetCtrlStatus(lu16_i) & (UNUM32)0xF; /* 通道状态读取   */
		if(CH_STA_RPT[lu16_i] == 2)
		{
			CUR_STA_RPT[lu16_i] = 0; /* set to current 0 if channel turn off*/
		}
		else
		{
			CUR_STA_RPT[lu16_i] = I2T_APP_GetCurrent(lu16_i); /* 通道电流值读取   */
		}
	}
	/*FLG_mu16_LRU_CAN_MailboxSN =*/
	ECAN_RecMsgAll( (UNUM16)0 );

	PHASE_Command();
	PHASE_JUDGE();
}

void ECAN_APP_TransmitProcess(void)
{
	UNUM32 tt1=(UNUM32)0;
	static UNUM16 lu16_loop_trans = (UNUM16)0;
	static UNUM16 lu16_loop_frame = (UNUM16)0;

	tt1=MCU_GetTMR0_5ms();


	if( tt1  % ((UNUM32)2) == (UNUM32)0 )
	{
		if(lu16_loop_frame > (UNUM16)15)
			{
				lu16_loop_frame = (UNUM16)0;
			}

			ECAN_APP_Msg_Setting(lu16_loop_frame);

			lu16_loop_frame++;
	}


	if( tt1  % ((UNUM32)4) == (UNUM32)0 )
	{
		if(lu16_loop_trans > (UNUM16)15)
		{
			lu16_loop_trans = (UNUM16)0;
		}

		if(lu32_Transmit_MsgID[lu16_loop_trans]!= (UNUM32)0)
		{
			ECAN_ConfigSendMsgBox( (UNUM16)ECAN_ECANA_SN, (UNUM32)15+lu16_loop_trans , lu32_Transmit_MsgID[lu16_loop_trans], 0, 8 );
			ECAN_SendMsg( (UNUM16)ECAN_ECANA_SN, (UNUM32)15+lu16_loop_trans, lu32_Transmit_HigBytes[lu16_loop_trans] , lu32_Transmit_LowBytes[lu16_loop_trans] );
			lu32_Transmit_MsgID[lu16_loop_trans] = (UNUM32)0;
		}
			lu16_loop_trans++;

	}



}


static void ECAN_APP_Msg_Setting(UNUM16 lu16_frame_id)
{
	UNUM32 lu32_LowBytes_Blue = (UNUM32)0;
	UNUM32 lu32_HigBytes_Blue = (UNUM32)0;



	switch ( lu16_frame_id )
	{
	case (UNUM16)CAN_CUR_FRAME_0:

			break;
	case (UNUM16)CAN_CUR_FRAME_1:
		    lu32_HigBytes_Blue = (CH_STA_RPT[0]<<28)|(CH_STA_RPT[1]<<24)|(CH_STA_RPT[2]<<20)|(CH_STA_RPT[3]<<16)|(CH_STA_RPT[4]<<12)|
							     (CH_STA_RPT[5]<<8)|(CH_STA_RPT[6]<<4)|(CH_STA_RPT[7]<<0);
		    lu32_LowBytes_Blue = (CH_STA_RPT[8]<<28)|(CH_STA_RPT[9]<<24)|(CH_STA_RPT[10]<<20)|(CH_STA_RPT[11]<<16)|(CH_STA_RPT[12]<<12)|
							     (CH_STA_RPT[13]<<8)|(CH_STA_RPT[14]<<4)|(CH_STA_RPT[15]<<0);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_1] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_1] = lu32_LowBytes_Blue;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_1] = (UNUM32)0x11;
			break;
	case (UNUM16)CAN_CUR_FRAME_2:
			lu32_HigBytes_Blue = (CH_STA_RPT[16]<<28)|(CH_STA_RPT[17]<<24)|(CH_STA_RPT[18]<<20)|(CH_STA_RPT[19]<<16);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_2] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_2] = 0;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_2] = (UNUM32)0x12;
			break;
	case (UNUM16)CAN_CUR_FRAME_3:

			break;
	case (UNUM16)CAN_CUR_FRAME_4:
			lu32_HigBytes_Blue = (CUR_STA_RPT[0]<<24)|(CUR_STA_RPT[1]<<16)|(CUR_STA_RPT[2]<<8)|(CUR_STA_RPT[3]);
			lu32_LowBytes_Blue = (CUR_STA_RPT[4]<<24)|(CUR_STA_RPT[5]<<16)|(CUR_STA_RPT[6]<<8)|(CUR_STA_RPT[7]);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_4] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_4] = lu32_LowBytes_Blue;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_4] = (UNUM32)0x13;
			break;
	case (UNUM16)CAN_CUR_FRAME_5:
			lu32_HigBytes_Blue = (CUR_STA_RPT[8]<<24)|(CUR_STA_RPT[9]<<16)|(CUR_STA_RPT[10]<<8)|(CUR_STA_RPT[11]);
			lu32_LowBytes_Blue = (CUR_STA_RPT[12]<<24)|(CUR_STA_RPT[13]<<16)|(CUR_STA_RPT[14]<<8)|(CUR_STA_RPT[15]);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_5] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_5] = lu32_LowBytes_Blue;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_5] = (UNUM32)0x14;
			break;
	case (UNUM16)CAN_CUR_FRAME_6:
			lu32_HigBytes_Blue = (CUR_STA_RPT[16]<<24)|(CUR_STA_RPT[17]<<16)|(CUR_STA_RPT[18]<<8)|(CUR_STA_RPT[19]);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_6] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_6] = 0;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_6] = (UNUM32)0x15;

			break;
	case (UNUM16)CAN_CUR_FRAME_7:
			lu32_HigBytes_Blue = (CH_CUR_RAT[0]<<24)|(CH_CUR_RAT[1]<<16)|(CH_CUR_RAT[2]<<8)|(CH_CUR_RAT[3]);
			lu32_LowBytes_Blue = (CH_CUR_RAT[4]<<24)|(CH_CUR_RAT[5]<<16)|(CH_CUR_RAT[6]<<8)|(CH_CUR_RAT[7]);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_7] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_7] = lu32_LowBytes_Blue;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_7] = (UNUM32)0x18;
			break;
	case (UNUM16)CAN_CUR_FRAME_8:
			lu32_HigBytes_Blue = (CH_CUR_RAT[8]<<24)|(CH_CUR_RAT[9]<<16)|(CH_CUR_RAT[10]<<8)|(CH_CUR_RAT[11]);
			lu32_LowBytes_Blue = (CH_CUR_RAT[12]<<24)|(CH_CUR_RAT[13]<<16)|(CH_CUR_RAT[14]<<8)|(CH_CUR_RAT[15]);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_8] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_8] = lu32_LowBytes_Blue;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_8] = (UNUM32)0x19;
				break;
	case (UNUM16)CAN_CUR_FRAME_9:
			lu32_HigBytes_Blue = (CH_CUR_RAT[16]<<24)|(CH_CUR_RAT[17]<<16)|(CH_CUR_RAT[18]<<8)|(CH_CUR_RAT[19]);
			lu32_Transmit_HigBytes[CAN_CUR_FRAME_9] = lu32_HigBytes_Blue;
			lu32_Transmit_LowBytes[CAN_CUR_FRAME_9] = 0;
			lu32_Transmit_MsgID[CAN_CUR_FRAME_9] = (UNUM32)0x20;

				break;
	case (UNUM16)CAN_CUR_FRAME_10:

				break;
	case (UNUM16)CAN_CUR_FRAME_11:

				break;
	case (UNUM16)CAN_CUR_FRAME_12:

				break;
	case (UNUM16)CAN_CUR_FRAME_13:

				break;
	case (UNUM16)CAN_CUR_FRAME_14:

				break;

	default:
		break;
	}

}

void PHASE_Command(void)
	{
		UNUM32 au32_LowBytes;
		au32_LowBytes = recLowBytes[4];

		if(((au32_LowBytes>>7)&(UNUM32)0x1)==1)
		{
			GROUP_FLAG[0]=1;
		}
		if(((au32_LowBytes>>6)&(UNUM32)0x1)==1)
		{
			GROUP_FLAG[1]=1;
		}
		if(((au32_LowBytes>>5)&(UNUM32)0x1)==1)
		{
			GROUP_FLAG[2]=1;
		}
		if(((au32_LowBytes>>4)&(UNUM32)0x1)==1)
		{
			GROUP_FLAG[3]=1;
		}
		if(((au32_LowBytes>>3)&(UNUM32)0x1)==1)
		{
			GROUP_FLAG[4]=1;
		}
	}

void PHASE_JUDGE(void)/*判断三个通道的CH_CTL_CMD是否一致*/
	{
	    UNUM16 i=0;UNUM16 a=0;UNUM16 b=0;UNUM16 c=0;

		for(;i<5;i++)
		{
			switch(i)
			{
			case 1:
				if(GROUP_FLAG[i]==1)
				{
					 a= recLowBytes[0]>>((UNUM32)(15*2)&(UNUM32)0x3);
				 	 b= recLowBytes[0]>>((UNUM32)(14*2)&(UNUM32)0x3);
				 	 c= recLowBytes[0]>>((UNUM32)(13*2)&(UNUM32)0x3);
				 	 if(((a-b)==(UNUM32)0)&&((a-c)==(UNUM32)0)&&((b-c)==(UNUM32)0))
				 	 {
				 		 PHASE_JUDGE_FLAG[i]=1;
				 	 }
				 	 else
				 	 {
				 		 PHASE_JUDGE_FLAG[i]=0;
				 	 }
				}break;
			case 2:
				if(GROUP_FLAG[i]==1)
				{
					a= recLowBytes[0]>>((UNUM32)(12*2)&(UNUM32)0x3);
					b= recLowBytes[0]>>((UNUM32)(11*2)&(UNUM32)0x3);
					c= recLowBytes[0]>>((UNUM32)(10*2)&(UNUM32)0x3);
					if(((a-b)==(UNUM32)0)&&((a-c)==(UNUM32)0)&&((b-c)==(UNUM32)0))
					{
						PHASE_JUDGE_FLAG[i]=1;
					}
					else
					{
						PHASE_JUDGE_FLAG[i]=0;
					}
				}break;
			case 3:
				if(GROUP_FLAG[i]==1)
				{
					a= recLowBytes[0]>>((UNUM32)(8*2)&(UNUM32)0x3);
					b= recLowBytes[0]>>((UNUM32)(7*2)&(UNUM32)0x3);
					c= recLowBytes[0]>>((UNUM32)(6*2)&(UNUM32)0x3);
					if(((a-b)==(UNUM32)0)&&((a-c)==(UNUM32)0)&&((b-c)==(UNUM32)0))
					{
						PHASE_JUDGE_FLAG[i]=1;
					}
					else
					{
						PHASE_JUDGE_FLAG[i]=0;
					}
				}break;
			case 4:
				if(GROUP_FLAG[i]==1)
				{
					a= recLowBytes[0]>>((UNUM32)(5*2)&(UNUM32)0x3);
					b= recLowBytes[0]>>((UNUM32)(4*2)&(UNUM32)0x3);
					c= recLowBytes[0]>>((UNUM32)(3*2)&(UNUM32)0x3);
					if(((a-b)==(UNUM32)0)&&((a-c)==(UNUM32)0)&&((b-c)==(UNUM32)0))
					{
						PHASE_JUDGE_FLAG[i]=1;
					}
					else
					{
						PHASE_JUDGE_FLAG[i]=0;
					}
				}break;
			case 5:
				if(GROUP_FLAG[i]==1)
				{
					a= recLowBytes[0]>>((UNUM32)(2*2)&(UNUM32)0x3);
					b= recLowBytes[0]>>((UNUM32)(1*2)&(UNUM32)0x3);
					c= recLowBytes[0]>>((UNUM32)(0*2)&(UNUM32)0x3);
					if(((a-b)==0)&&((a-c)==0)&&((b-c)==0))
					{
						PHASE_JUDGE_FLAG[i]=1;
					}
					else
					{
						PHASE_JUDGE_FLAG[i]=0;
					}
				}break;
			default:
				break;
			}
		}

	}




