/**
  ******************************************************************************
  * @file			: rotary_encoder.h
  * @brief			: Header for rotary_encoder.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version		: v1.0.0
  * @date created	: 2023-07-26
  *
  * @author modified: 
  * @date modified	: 2023-07-26
  * 
  * @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ROTARY_ENCODER_H
#define __ROTARY_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "input_process.h"
#include "config.h"


/* Exported types ------------------------------------------------------------*/
extern sBIT_BYTE_ACCESS	bRotEnc_flag;

extern uint8_t bRotEnc_code;
extern uint8_t bRotaryEnc_tasktick;


/* Exported constants --------------------------------------------------------*/
#define fRotEnc_changed									bRotEnc_flag.bit_access.bit_0
#define fRotEnc_count 									bRotEnc_flag.bit_access.bit_1

#define cROTENC_STATE_IDLE								0
#define cROTENC_STATE_PRELEFT							1
#define	cROTENC_STATE_LEFT								2
#define cROTENC_STATE_PRERIGHT							3
#define	cROTENC_STATE_RIGHT								4

#define	cROTENC_CODE_UP									0xB0
#define cROTENC_CODE_DOWN								0xB1

#define cROTENC_OFFSET_CODE								0xB0


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void rotaryEncoder_init(void);
uint8_t rotaryEncoder_getReceived_code(void);
void rotaryEncoder_check(void);
uint8_t rotaryEncoder_task(void);


#ifdef __cplusplus
}
#endif

#endif /* __ROTARY_ENCODER_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
