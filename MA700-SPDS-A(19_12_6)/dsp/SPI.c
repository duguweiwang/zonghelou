
#include "SPI.h"
#include "gpio.h"


#pragma DATA_SECTION(SPI_SpiaRegs,"SpiaRegsFile");
volatile struct SPI_REGS SPI_SpiaRegs;
extern UNUM16 SPI_mu16_Rece[20]={(UNUM16)0};
extern UNUM16 SPI_mu16_State[20]={(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,
		(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2,(UNUM16)2};
extern UNUM16 SPI_mu16_Rece_gpio_temp[5000]={(UNUM16)0};

static void SPI_Set_CS(UNUM16 lu16_ChannelSN);
static void SPI_Clear_CS(void);
 UNUM16 SPI_DATA[1000]={(UNUM16)0};
 UNUM16 FLAG=0;

/*---------------------------------------------------------------------------*/
/* 初始化过程请看数据手册的P20 或者参考书28335原理及开发编程的P308
 * 单独赋值可合并成整体赋值
 * This function initializes the SPI(s) to a known state.*/
void SPI_Init(void)
{
	SPI_SpiaRegs.SPICCR.bit.SPISWRESET=(UNUM16)0;	/*	SPI	to reset condition	*/
	SPI_SpiaRegs.SPICCR.bit.SPICHAR=(UNUM16)0x0F;	/*	16 bits Data	*/
	SPI_SpiaRegs.SPICCR.bit.CLKPOLARITY=(UNUM16)0;	/*	change clk	*/

	SPI_SpiaRegs.SPICTL.bit.TALK=(UNUM16)1;			/*	enable transmission	*/
	SPI_SpiaRegs.SPICTL.bit.MASTER_SLAVE=(UNUM16)1;	/*	master mode	*/
	/*SPI_SpiaRegs.SPICTL.bit.CLK_PHASE=(UNUM16)1;		change clk	*/
	SPI_SpiaRegs.SPICTL.bit.CLK_PHASE=(UNUM16)1;	/*	fix 1 to 0, change clk	*/

	SPI_SpiaRegs.SPIBRR=(UCHAR)99; 				/*	baud rate=LSPCLK/(BRR+1)=37.5M/100=375kHz	*/

	SPI_SpiaRegs.SPICCR.bit.SPISWRESET=(UNUM16)1;	/*	configuration completed	*/



}
/*	send a word	*/
static void SPI_TX_BUF(UNUM16 au16_Ch)
{
	UNUM16 lu16_TxBuf = (UNUM16)0;
	UNUM16 lu16_TxDelay = (UNUM16)0;
    static UNUM16 lu16_test =  (UNUM16)0;
    static UNUM16 lu16_test_time =  (UNUM16)0;
   /* static UNUM16 lu16_test_init =  (UNUM16)0;*/

	if (au16_Ch < (UNUM16)20)
	{

		lu16_test_time++;
		if(lu16_test_time>10000)
		{
			lu16_test++;
			lu16_test_time=0;
		}
		if(lu16_test > (UNUM16)3)
		{
			lu16_test = (UNUM16)0;
		}

		SPI_Set_CS(au16_Ch);
		lu16_TxBuf=0x1810;



		lu16_TxDelay=(UNUM16)0;


		while( ((UNUM16)SPI_SpiaRegs.SPISTS.bit.BUFFULL_FLAG == (UNUM16)1) && (lu16_TxDelay < (UNUM16)50) )
		{
			DELAY_US(10);
			lu16_TxDelay++;
		}
		if ( lu16_TxDelay < (UNUM16)50 )
		{
			SPI_SpiaRegs.SPITXBUF =  lu16_TxBuf;
		}
	}

}

static void SPI_RX_BUF(UNUM16 au16_Ch)
{
	UNUM16 lu16_RxBuff=(UNUM16)0x2FFF;

	UNUM16 lu16_RxDelay = (UNUM16)0;


	if (au16_Ch < (UNUM16)20)
	{
		lu16_RxDelay=(UNUM16)0;
		while(((UNUM16)SPI_SpiaRegs.SPISTS.bit.INT_FLAG != (UNUM16)1) && (lu16_RxDelay < (UNUM16)50) )
		{

			DELAY_US(10);
			lu16_RxDelay++;
		}
		if ( lu16_RxDelay < (UNUM16)50 )
		{

			if(FLAG>1000)
			{
				lu16_RxBuff=SPI_SpiaRegs.SPIRXBUF;

				SPI_mu16_Rece[au16_Ch]=lu16_RxBuff;
				SPI_mu16_Rece[au16_Ch]&=(UNUM16)0x0fff;


				SPI_mu16_State[au16_Ch]=lu16_RxBuff;
				SPI_mu16_State[au16_Ch]=SPI_mu16_State[au16_Ch]>>12;
				FLAG=1000;

			}
			else
			{
				SPI_DATA[FLAG]=SPI_SpiaRegs.SPIRXBUF;
			}

			}




		}



}

UNUM16 SPI_Rece_Current(UNUM16 lu16_ChannelSN)
{
	return SPI_mu16_Rece[lu16_ChannelSN];
}
UNUM16 SPI_Rece_State(UNUM16 lu16_ChannelSN)
{
	return SPI_mu16_State[lu16_ChannelSN];
}


void SPI_GetResult(void)
{
	UNUM16 lu16_ChannelSN=(UNUM16)0;
	static UNUM16 lu16_ChannelFlag=(UNUM16)2;
	lu16_ChannelFlag++;
	if(lu16_ChannelFlag>19)
	{
		lu16_ChannelFlag=2;
	}
	lu16_ChannelSN=0;
	for ( lu16_ChannelSN=(UNUM16)0; lu16_ChannelSN < (UNUM16)20; lu16_ChannelSN++ )
	{

			SPI_TX_BUF(lu16_ChannelSN);
			SPI_RX_BUF(lu16_ChannelSN);
			SPI_Clear_CS();
			DELAY_US(15);
			FLAG++;
	}

}

static void SPI_Set_CS(UNUM16 lu16_ChannelSN)
{
	if(lu16_ChannelSN < (UNUM16)20 )
	{
		GPIO_GpioDataRegs.GPADAT.all &= ~((UNUM32)1 << lu16_ChannelSN);

	}
	else
	{

	}
}

static void SPI_Clear_CS(void)
{
	GPIO_GpioDataRegs.GPADAT.all |= (UNUM32)0xFFFFF;
}

/*	check spi send status	*/
UNUM16 SPI_GetChannelData(UNUM16 lu16_ChannelSN)
{
	UNUM16 lu16_Value_Ret = (UNUM16)0;

	if ( lu16_ChannelSN < (UNUM16)4)
	{
		lu16_Value_Ret = (UNUM16)(((UNUM32)SPI_mu16_Rece[lu16_ChannelSN] * (UNUM32)499) / (UNUM32)600);
	}
	if (lu16_Value_Ret > (UNUM16)3398)
	{
		lu16_Value_Ret = (UNUM16)3398;

	}
	return lu16_Value_Ret;
}

void SPI_Gpio_Init(void)
{
 EALLOW;
 	 GPIO_GpioCtrlRegs.GPBPUD.bit.GPIO54 = (UNUM16)0;   /* Enable pull-up on GPIO54 (SPISIMOA)*/
 	 GPIO_GpioCtrlRegs.GPBPUD.bit.GPIO55 = (UNUM16)0;   /* Enable pull-up on GPIO55 (SPISOMIA)*/
 	 GPIO_GpioCtrlRegs.GPBPUD.bit.GPIO56 = (UNUM16)0;   /* Enable pull-up on GPIO56 (SPICLKA)*/
 	 GPIO_GpioCtrlRegs.GPBPUD.bit.GPIO57 = (UNUM16)0;   /* Enable pull-up on GPIO57 (SPISTEA)*/

 	 GPIO_GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = (UNUM16)3; /* Asynch input GPIO54 (SPISIMOA)*/
 	 GPIO_GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = (UNUM16)3; /* Asynch input GPIO55 (SPISOMIA)*/
 	 GPIO_GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = (UNUM16)3; /* Asynch input GPIO56 (SPICLKA)*/
 	 GPIO_GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = (UNUM16)3; /* Asynch input GPIO57 (SPISTEA)*/

 	 GPIO_GpioCtrlRegs.GPBMUX2.bit.GPIO54 = (UNUM16)1; /* Configure GPIO54 as SPISIMOA*/
 	 GPIO_GpioCtrlRegs.GPBMUX2.bit.GPIO55 = (UNUM16)1; /* Configure GPIO55 as SPISOMIA*/
 	 GPIO_GpioCtrlRegs.GPBMUX2.bit.GPIO56 = (UNUM16)1; /* Configure GPIO56 as SPICLKA*/
 	 GPIO_GpioCtrlRegs.GPBMUX2.bit.GPIO57 = (UNUM16)1; /* Configure GPIO57 as SPISTEA*/

 	GPIO_GpioCtrlRegs.GPADIR.all &= (UNUM32)0x00FFFFFF; /*SET GPIO 0-20 as an input*/
 	GPIO_GpioDataRegs.GPADAT.all |= (UNUM32)0xFFFFF;


 EDIS;
}


/*===========================================================================*/
/* End of file.*/
/*===========================================================================*/
