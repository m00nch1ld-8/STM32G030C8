/**
  ******************************************************************************
  * @file			: spp.h
  * @brief			: Header for spp.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version		    : v1.0.0
  * @date created	  : 2024-04-02
  *
  * @author modified:
  * @date modified	:
  *
  * @copyright		  : (C) 2024, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_SPP_H_
#define INC_SPP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
// void SlaveSysModeProcess(uint16_t Cmd);
// void SlaveFileSystemProcess(uint16_t Cmd);
// void SlavePlayCtrlProcess(uint16_t Cmd);
void SlaveAudioProcess(uint16_t Cmd);
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
uint8_t SppCheck(void);
void SlaveStateCtrl(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_SPP_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
