/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern TIM_HandleTypeDef htim14;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BLE_WAKEUP_Pin GPIO_PIN_13
#define BLE_WAKEUP_GPIO_Port GPIOC
#define ADC_KEY_Pin GPIO_PIN_0
#define ADC_KEY_GPIO_Port GPIOA
#define LED_WS_Pin GPIO_PIN_4
#define LED_WS_GPIO_Port GPIOA
#define ROT_ENC1_Pin GPIO_PIN_6
#define ROT_ENC1_GPIO_Port GPIOA
#define ROT_ENC2_Pin GPIO_PIN_7
#define ROT_ENC2_GPIO_Port GPIOA
#define LED_R_Pin GPIO_PIN_10
#define LED_R_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_11
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_12
#define LED_B_GPIO_Port GPIOB
#define PA_FAULT_Pin GPIO_PIN_15
#define PA_FAULT_GPIO_Port GPIOB
#define PA_FAULT_EXTI_IRQn EXTI4_15_IRQn
#define PA_OTW_Pin GPIO_PIN_8
#define PA_OTW_GPIO_Port GPIOA
#define PA_OTW_EXTI_IRQn EXTI4_15_IRQn
#define PA_CLIP_Pin GPIO_PIN_9
#define PA_CLIP_GPIO_Port GPIOA
#define PA_CLIP_EXTI_IRQn EXTI4_15_IRQn
#define IRM_Pin GPIO_PIN_6
#define IRM_GPIO_Port GPIOC
#define IRM_EXTI_IRQn EXTI4_15_IRQn
#define I2C_SCL_Pin GPIO_PIN_11
#define I2C_SCL_GPIO_Port GPIOA
#define I2C_SDA_Pin GPIO_PIN_12
#define I2C_SDA_GPIO_Port GPIOA
#define AMP_RST_Pin GPIO_PIN_15
#define AMP_RST_GPIO_Port GPIOA
#define PWM_MUTE_Pin GPIO_PIN_0
#define PWM_MUTE_GPIO_Port GPIOD
#define PWM_PDN_Pin GPIO_PIN_1
#define PWM_PDN_GPIO_Port GPIOD
#define PWM_RST_Pin GPIO_PIN_2
#define PWM_RST_GPIO_Port GPIOD
#define ADAU_DET_Pin GPIO_PIN_3
#define ADAU_DET_GPIO_Port GPIOD
#define BLE_TX_Pin GPIO_PIN_6
#define BLE_TX_GPIO_Port GPIOB
#define BLE_RX_Pin GPIO_PIN_7
#define BLE_RX_GPIO_Port GPIOB
#define BLE_INT_Pin GPIO_PIN_8
#define BLE_INT_GPIO_Port GPIOB
#define BLE_PDN_Pin GPIO_PIN_9
#define BLE_PDN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
