/**
  ******************************************************************************
  * @file			: process.h
  * @brief			: Header for process.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version		: v1.0.0
  * @date created	: 2023-07-31
  *
  * @author modified: 
  * @date modified	: 2023-07-31
  * 
  * @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PROCESS_H
#define __PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "system.h"


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void prc_manager(sSystem_input *sManager);


#ifdef __cplusplus
}
#endif

#endif /* __PROCESS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
