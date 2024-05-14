/**
  ******************************************************************************
  * @file			: adc_key.h
  * @brief			: Header for adc_key.c file.
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
#ifndef __ADC_KEY_H
#define __ADC_KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
extern sBIT_BYTE_ACCESS bAdcKey_flag;


/* Exported constants --------------------------------------------------------*/
#define fAdcKey_pressed 								bAdcKey_flag.bit_access.bit_0

#define cADCKEY_NOKEY									0xFF
// #define cLKEY_NOKEY_LIMIT			0x0C
// #define cLKEY_NOKEY_LIMIT			0x0B
// #define cADCKEY_NOKEY_LIMIT			0x07

// #define cADCKEY_KEY1_MASK			0x20
// #define cLKEY_KEY2_MASK				0x27
// #define cADCKEY_KEY2_MASK			0x2E

#define cADC_KEY_0_MIN									100
#define cADC_KEY_0_MAX									250
#define cADC_KEY_1_MIN									330
#define cADC_KEY_1_MAX									600
#define cADC_KEY_2_MIN									670
#define cADC_KEY_2_MAX									1100
#define cADC_KEY_3_MIN									1500
#define cADC_KEY_3_MAX									1950
#define cADC_KEY_4_MIN									2500
#define cADC_KEY_4_MAX									2800


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void adcKey_init(void);
uint8_t adcKey_getReceived_code(void);
uint8_t adcKey_getValue(void);
void adcKey_check(void);
uint8_t adcKey_softwareVersion(void);
uint8_t adcKey_task(void);


#ifdef __cplusplus
}
#endif

#endif /* __ADC_KEY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
