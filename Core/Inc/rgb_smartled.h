/**
  ******************************************************************************
  * @file			: rgb_smartled.h
  * @brief			: Header for rgb_smartled.c file.
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
#ifndef __RGB_SMARTLED_H
#define __RGB_SMARTLED_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
// #define MAX_LED 11
#define WS2812_NUM_LEDS 15
// #define WS2812_SPI_HANDLE hspi2

#define WS2812_RESET_PULSE 60
#define WS2812_BUFFER_SIZE (WS2812_NUM_LEDS * 24 + WS2812_RESET_PULSE)
// #define USE_BRIGHTNESS 1


/* Exported macro ------------------------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/
#ifdef USE_WS2812_SPI
extern SPI_HandleTypeDef hspi2;
extern uint8_t ws2812_buffer[WS2812_BUFFER_SIZE];
#endif


/* Exported functions prototypes ---------------------------------------------*/
void ws2812_init(void);
void ws2812_setLED(int LEDnum, int Red, int Green, int Blue);
void ws2812_setBrightness(int brightness);
void ws2812_Send(void);
void ws2812_displayLevel(uint8_t lvl);
void ws2812_displayCutOff(uint8_t lvl);
void ws2812_displayPhase(uint8_t lvl);
void ws2812_displayPolar(uint8_t lvl);
void ws2812_displayMode(uint8_t lvl);
void ws2812_displayCenter(void);
void ws2812_clear_bar(void);


#ifdef __cplusplus
}
#endif

#endif /* __RGB_SMARTLED_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
