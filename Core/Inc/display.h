/**
	******************************************************************************
	* @file			: display.h
	* @brief			: Header for display.c file.
	*					  This file contains the common defines of the application.
	******************************************************************************
	* @attention
	*
	* @author         : BeeHa
	* @version		: v1.0.0
	* @date created	: 2023-08-02
	*
	* @author modified: 
	* @date modified	: 2023-08-02
	* 
	* @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
	*
	******************************************************************************
	*/
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "type.h"


/* Exported types ------------------------------------------------------------*/
extern sBIT_BYTE_ACCESS bDisplay_flag;


/* Exported constants --------------------------------------------------------*/
#define fDisplay_MenuUpdate							bDisplay_flag.bit_access.bit_0
#define fDisplay_Level 								bDisplay_flag.bit_access.bit_1
#define fDisplay_CutOff								bDisplay_flag.bit_access.bit_2
#ifdef USE_SOUND_SHIFT_EN
#define fDisplay_Phase 								bDisplay_flag.bit_access.bit_3
#else
#define fDisplay_Polar 								bDisplay_flag.bit_access.bit_3
#endif
#define fDisplay_Mode								bDisplay_flag.bit_access.bit_4
#define fDisplay_Center								bDisplay_flag.bit_access.bit_5
#define fDisplay_SmartRGB							bDisplay_flag.bit_access.bit_6

#define bPos_Led_Level				14
#define bPos_Led_CutOff				13
#ifdef USE_SOUND_SHIFT_EN
#define bPos_Led_Phase				12
#else
#define bPos_Led_Polar				12
#endif
#define bPos_Led_Mode				11


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void display_softwareVersion(void);
void display_init(void);
void display_task(void);
void finished_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
