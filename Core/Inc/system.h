/**
	******************************************************************************
	* @file			: system.h
	* @brief			: Header for system.c file.
	*					  This file contains the common defines of the application.
	******************************************************************************
	* @attention
	*
	* @author         : BeeHa
	* @version		: v1.0.0
	* @date created	: 2023-07-28
	*
	* @author modified: BeeHa
	* @date modified	: 2023-07-28
	* 
	* @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
	*
	******************************************************************************
	*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_H
#define __SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "stdint.h"
#include "type.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{	
	uint8_t	index;
	uint8_t	press_state;
}	sSystem_input;


/* Exported constants --------------------------------------------------------*/
extern sBIT_BYTE_ACCESS bSystem_flag;

#define fSys_PCM_error									bSystem_flag.bit_access.bit_0
#define fSys_TAS_error									bSystem_flag.bit_access.bit_1
#define fSys_ADAU_error									bSystem_flag.bit_access.bit_2
#define fSys_BLE_error									bSystem_flag.bit_access.bit_3
// #define fSys_								bSystem_flag.bit_access.bit_4
// #define fSys_								bSystem_flag.bit_access.bit_5
// #define fSys_								bSystem_flag.bit_access.bit_6
#define fSystem_flag									bSystem_flag.byte_access

#define I2C_STAT_OK			0x00
#define I2C_STAT_ERROR		0x01
#define I2C_STAT_BUSY		0x02
#define I2C_STAT_TIMEOUT	0x03
#define I2C_STAT_NONE		0xFF


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void system_timer20ms_handler(void);
void system_main(void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
