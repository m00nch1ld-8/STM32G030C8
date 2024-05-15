/**
	******************************************************************************
	* @file			: remote.h
	* @brief			: Header for remote.c file.
	*					  This file contains the common defines of the application.
	******************************************************************************
	* @attention
	*
	* @author         : BeeHa
	* @version		: v1.0.0
	* @date created	: 2024-04-24
	*
	* @author modified: 
	* @date modified	: 
	* 
	* @copyright		: (C) 2024, PT. Hartono Istana Teknologi. All rights reserved.
	*
	******************************************************************************
	*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __REMOTE_H
#define __REMOTE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "type.h"


/* Exported types ------------------------------------------------------------*/
extern uint8_t bAddrHigh;
extern uint8_t bAddrLow;
extern uint8_t bCmdHigh;
extern uint8_t bCmdLow;
extern uint8_t bBitIndex;
extern uint32_t bRemote_temp;
extern uint32_t bRemote_received_code;
extern uint32_t bRemote_oldreceived_code;
extern sBIT_BYTE_ACCESS bRemote_flag;


/* Exported constants --------------------------------------------------------*/
#define IR_MAX_LEN										112
#define fRemote_pressed 								bRemote_flag.bit_access.bit_0
#define fRemote_processed								bRemote_flag.bit_access.bit_1

/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void remote_init(void);
uint8_t remote_getReceived_code(void);
void remote_check(void);
uint8_t remote_task(void);


#ifdef __cplusplus
}
#endif

#endif /* __REMOTE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
