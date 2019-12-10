#ifndef __GPIO_APP_H__
#define __GPIO_APP_H__

#define SSPC_TYPE  (SSPC_AC)
#define SSPC_AC  1U
#define SSPC_DC  0U
#if SSPC_TYPE
#define APP_SETTYPE 1U
#define SHORT1 0U
#define AC_STATUS 1U
#else
#define APP_SETTYPE 0U
#define SHORT1 0U
#define DC_STATUS 0U
#endif


/* SSPC channel state define */
extern UNUM16 Channal_Status[20];
#define SSPC_ST_LOCK  1U
#define SSPC_ST_OFF  2U
#define SSPC_ST_ON   3U
#define SSPC_ST_TRIPPED 4U
#define SSPC_ST_SHORT 5U
#define SSPC_ST_ERROR 6U
#define SSPC_ST_CLOSE_FAILED (UNUM16)7U
#define SSPC_ST_OPEN_FAILED (UNUM16)8U
/* SSPC channel command define */
#define SSPC_CMD_OFF  1U
#define SSPC_CMD_ON   2U
#define SSPC_CMD_LCOK  1U
#define SSPC_CMD_UNLCOK  2U
#define SSPC_CMD_RESET 1U

extern void GPIO_APP_ChannelProcess(void);
extern void GPIO_APP_StateInit(void);
extern void GPIO_OverloadCtrl(UNUM16 au16_ChannelSN);
void GPIO_Short_Ctrl(UNUM16 au16_ChannelSN);
void GPIO_status_ON_Ctrl(UNUM16 au16_ChannelSN);
void GPIO_status_OFF_Ctrl(UNUM16 au16_ChannelSN);
void GPIO_Error_Ctrl(UNUM16 au16_ChannelSN);
void GPIO_OPEN_FAILED_Ctrl(UNUM16 au16_ChannelSN);
void GPIO_CLOSE_FAILED_Ctrl(UNUM16 au16_ChannelSN);
extern UNUM16 GPIO_GetCtrlStatus(UNUM16 au16_ChannelSN);



#endif  /* end of CHANNEL_APP_H definition*/
