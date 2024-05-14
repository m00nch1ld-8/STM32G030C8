/**
  ******************************************************************************
  * @file			: eeprom.h
  * @brief			: Header for eeprom.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version		: v1.0.0
  * @date created	: 2023-09-27
  *
  * @author modified: 
  * @date modified	: 2023-09-27
  * 
  * @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_H
#define __EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "type.h"


/* Exported types ------------------------------------------------------------*/
extern uint8_t bEep_buf[8];
extern sBIT_BYTE_ACCESS bEeprom_flag;


/* Exported constants --------------------------------------------------------*/
#define fEeprom_Level 							bEeprom_flag.bit_access.bit_0
#define fEeprom_CutOff 							bEeprom_flag.bit_access.bit_1
#ifdef USE_SOUND_SHIFT_EN
#define fEeprom_Phase 							bEeprom_flag.bit_access.bit_2
#else
#define fEeprom_Polar 							bEeprom_flag.bit_access.bit_2
#endif
#define fEeprom_Mode   							bEeprom_flag.bit_access.bit_3

#define EEPROM_ADDR	  0xA0	//0x36 when ASEL pin = '1', 0x34 when ASEL pin = '0'
#define EEPROM_WRITE	0x00
#define EEPROM_READ 	0x01

#define EPPROM_ADR_LEVEL    0x00
#define EPPROM_ADR_FREQ     0x01
#ifdef USE_SOUND_SHIFT_EN
#define EPPROM_ADR_PHASE    0x02
#else
#define EPPROM_ADR_POLAR    0x02
#endif
#define EPPROM_ADR_MODE     0x03


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void eeprom_init(void);
void eeprom_read_byte(uint16_t addr, uint8_t num);
void eeprom_write_byte(uint16_t addr,uint8_t ddata);


#ifdef __cplusplus
}
#endif

#endif /* __EEPROM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
