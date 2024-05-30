/**
  ******************************************************************************
  * @file           : spp.c
  * @brief          : Bridge for Android App and Microcontroler
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version        : v1.0.0
  * @date created   : 2024-04-02
  *
  * @author modified:
  * @date modified	:
  *
  * @copyright		  : (C) 2024, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spp_app_proc.h"
#include "string.h"
#include "type.h"
#include "config.h"


/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
uint8_t spp_resp_buff[0xFF];  //0x55 0xAA Len CMD_H CMD_L DATA
extern uint8_t bBLE_recv_final[0xFF];
uint8_t bSPP_data = 0;

/* Private function prototypes -----------------------------------------------*/
extern UART_HandleTypeDef huart1;


/* Private user code ---------------------------------------------------------*/
void SlaveSendResp(uint16_t Cmd, uint8_t* Buf, uint8_t Len)
{
	uint8_t CheckSum;
//	uint8_t RespHead[5];
	uint8_t LenTemp;
	uint8_t SppSendDataBuf[0xFF];
	uint16_t SppSendBufSize = 0;
	memset(SppSendDataBuf,0, 0xFF);
	CheckSum = Len + (BYTE1(Cmd) | 0x80) + BYTE0(Cmd);
	LenTemp = Len;

	while(LenTemp)
	{
		CheckSum += Buf[LenTemp - 1];
		LenTemp--;
	}
	CheckSum = 0 - CheckSum;
	SppSendDataBuf[0] = 0x55;
	SppSendDataBuf[1] = 0xAA;
	SppSendDataBuf[2] = Len;
	SppSendDataBuf[3] = (BYTE1(Cmd) | 0x80);
	SppSendDataBuf[4] = (BYTE0(Cmd));

	if(Len)
	{
		uint16_t i;
		for(i = 0; i < Len; i++)
		{
			SppSendDataBuf[5+i] = Buf[i];
		}
	}
	SppSendDataBuf[5+Len] = CheckSum;
	SppSendBufSize = 5+Len+1;
	HAL_UART_Transmit(&huart1, &SppSendDataBuf[0], SppSendBufSize, 500);
}

// void SlaveSysModeProcess(uint16_t Cmd);
// void SlaveFileSystemProcess(uint16_t Cmd);
// void SlavePlayCtrlProcess(uint16_t Cmd);
void SlaveAudioProcess(uint16_t Cmd)
{
	switch (Cmd)
	{
		// case SLAVE_VOLADD:
		// 	break;
		// case SLAVE_VOLSUB:
		// 	break;
		case SLAVE_SET_VOL:
		case SLAVE_GET_VOL:
		case SLAVE_SET_SWF_FREQ:
		case SLAVE_GET_SWF_FREQ:
		case SLAVE_SET_SWF_PHASE:
		case SLAVE_GET_SWF_PHASE:
		case SLAVE_SET_SWF_LFE:
		case SLAVE_GET_SWF_LFE:
			bSPP_data = (uint8_t) Cmd & 0x0F;
			bSPP_data -= 3;
			prc_handler_command_apk(bSPP_data, bBLE_recv_final[5]);
			break;
		// case SLAVE_SET_EQ:
		// 	break;
		// case SLAVE_GET_EQ:
		// 	break;
		// case SLAVE_MUTE:
		// 	break;
		// case SLAVE_UNMUTE:
		// 	break;
		// case SLAVE_SET_LINEIN_CHANNEL:
		//     break;
		// case SLAVE_SET_LINEIN_GAIN:
		// 	break;
		// case SLAVE_ENABLE_MIC:
		// 	break;
		// case SLAVE_DISABLE_MIC:
		// 	break;
		// case SLAVE_BASS_ADD:
		// 	break;
		// case SLAVE_BASS_SUB:
		// 	break;
		// case SLAVE_SET_BASS:
		// 	break;
		// case SLAVE_GET_BASS:
		// 	break;
		// case SLAVE_MIDD_ADD:
		// 	break;
		// case SLAVE_MIDD_SUB:
		// 	break;
		// case SLAVE_SET_MIDD:
		// 	break;
		// case SLAVE_GET_MIDD:
		// 	break;
		// case SLAVE_TREB_ADD:
		// 	break;
		// case SLAVE_TREB_SUB:
		// 	break;
		// case SLAVE_SET_TREB:
		// 	break;
		// case SLAVE_GET_TREB:
		// 	break;
		// case SLAVE_MICLV_ADD:
		// 	break;
		// case SLAVE_MICLV_SUB:
		// 	break;
		// case SLAVE_SET_MICLV:
		// 	break;
		// case SLAVE_GET_MICLV:
		// 	break;
		// case SLAVE_ECHOLV_ADD:
		// 	break;
		// case SLAVE_ECHOLV_SUB:
		// 	break;
		// case SLAVE_SET_ECHOLV:
		// 	break;
		// case SLAVE_GET_ECHOLV:
		// 	break;
		// case SLAVE_SBASS_ADD:
		// 	break;
		// case SLAVE_SBASS_SUB:
		// 	break;
		// case SLAVE_SET_SBASS:
		// 	break;
		// case SLAVE_GET_SBASS:
		// 	break;
		// case SLAVE_SET_KARAOKE:
		// 	break;
		// case SLAVE_GET_KARAOKE:
		// 	break;
		// case SLAVE_SET_BAZOKE1:
		// 	break;
		// case SLAVE_GET_BAZOKE:
		// 	break;
		// case SLAVE_SET_SURROUND:
		// 	break;
		// case SLAVE_GET_SURROUND:
		// 	break;
		// case SLAVE_SET_MIC_PRIORITY:
		// 	break;
		// case SLAVE_GET_MIC_PRIORITY:
		// 	break;
		// case SLAVE_SET_RECORD:
		// 	break;
		// case SLAVE_GET_RECORD:
		// 	break;
		// case SLAVE_REC_FILE_DEL:
		// 	break;
		// case SLAVE_REC_MUSIC_CTRL:
		// 	break;
		// case SLAVE_SET_MIC_EFFECT:
		// 	break;
		// case SLAVE_GET_MIC_EFFECT:
		// 	break;
		// case SLAVE_REVBLV_ADD:
		// 	break;
		// case SLAVE_REVBLV_SUB:
		// 	break;
		// case SLAVE_SET_REVBLV:
		// 	break;
		// case SLAVE_GET_REVBLV:
		// 	break;
		// case SLAVE_MIC_SET_EQ:
		// 	break;
		// case SLAVE_MIC_GET_EQ:
		// 	break;
		// case SLAVE_SET_BTPIN:
		// 	break;

		default:
			break;
	}
}
// void SlaveRtcProcess(uint16_t Cmd);
// void SlaveGpioProcess(uint16_t Cmd);
// void SlaveAdcProcess(uint16_t Cmd);
// void SlavePwmProcess(uint16_t Cmd);
// void SlaveDeepSleepProcess(uint16_t Cmd);
// void SlaveRadioProcess(uint16_t Cmd);
// void SlaveCustomProcess(uint16_t Cmd);
// void SlaveDvdProcess(uint16_t Cmd);
// void SlaveRemoteProcess(uint16_t Cmd);
// void SlaveWirelessMicProcess(uint16_t Cmd);
// void SlaveSpecialFunctionProcess(uint16_t Cmd);

uint8_t SppCheck(void)
{
	uint8_t compare = 0;
	uint8_t lenTemp;
#ifdef USE_CIRCULAR_BUFF_EN
// bBLE_recv_final[0]	: data length
// bBLE_recv_final[1]	: CMD High
// bBLE_recv_final[2]	: CMD Low
// bBLE_recv_final[3]	: data jika ada, jika tidak checksum
	compare = bBLE_recv_final[0] + bBLE_recv_final[1] + bBLE_recv_final[2];
	lenTemp = bBLE_recv_final[0];

	while(lenTemp)
	{
		compare += bBLE_recv_final[2 + lenTemp];
		lenTemp--;
	}

	compare = 0 - compare;
	lenTemp = bBLE_recv_final[2];

	if(compare == bBLE_recv_final[3+lenTemp])
	{
		return 1;
	}
	else
	{
		return 0;
	}
#else		//USE_CIRCULAR_BUFF_EN
// bBLE_recv_final[0]	: 0x55
// bBLE_recv_final[1]	: 0xAA
// bBLE_recv_final[2]	: data length
// bBLE_recv_final[3]	: CMD High
// bBLE_recv_final[4]	: CMD Low
// bBLE_recv_final[5]	: data jika ada, jika tidak checksum
	compare = bBLE_recv_final[2] + bBLE_recv_final[3] + bBLE_recv_final[4];
	lenTemp = bBLE_recv_final[2];

	while(lenTemp)
	{
		compare += bBLE_recv_final[4 + lenTemp];
		lenTemp--;
	}

	compare = 0 - compare;
	lenTemp = bBLE_recv_final[2];

	if(compare == bBLE_recv_final[5+lenTemp])
	{
		return 1;
	}
	else
	{
		return 0;
	}
#endif		//USE_CIRCULAR_BUFF_EN
}

void SlaveStateCtrl(void)
{
  uint16_t cmdCode;
  
  if(!SppCheck()) return;

  memset(spp_resp_buff, 0, 0xFF);
  cmdCode = ((bBLE_recv_final[3] << 8) + bBLE_recv_final[4]);

  switch(bBLE_recv_final[3])
  {
	case 0x01:
	  // SlaveSysModeProcess(cmdCode);
	  break;

	case 0x02:
	  // SlaveFileSystemProcess(cmdCode);
	  break;

	case 0x03:
	  // SlavePlayCtrlProcess(cmdCode);
	  break;

	case 0x04:
	  SlaveAudioProcess(cmdCode);
	  break;

	case 0x05:
	  // SlaveRtcProcess(cmdCode);
	  break;

	case 0x06:
	  // SlaveGpioProcess(cmdCode);
	  break;

	case 0x07:
	  // SlaveAdcProcess(cmdCode);
	  break;

	case 0x08:
	  // SlavePwmProcess(cmdCode);
	  break;

	case 0x09:
	  // SlaveDeepSleepProcess(cmdCode);
	  break;

	case 0x0A:
	  // SlaveRadioProcess(cmdCode);
	  break;

	case 0x0B:
	  // SlaveCustomProcess(cmdCode);
	  break;

	case 0x0C:
	  // SlaveDvdProcess(cmdCode);
	  break;

	case 0x0D:
	  // SlaveRemoteProcess(cmdCode);
	  break;

	case 0x0E:
	  // SlaveWirelessMicProcess(cmdCode);
	  break;

	case 0x70:
	  // SlaveSpecialFunctionProcess(cmdCode);
	  break;

	default:
	  break;
  }
}

