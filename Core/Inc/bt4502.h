/**
  ******************************************************************************
  * @file			: bt452.h
  * @brief			: Header for bt4502.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version		: v1.0.0
  * @date created	: 2024-03-25
  *
  * @author modified:
  * @date modified	:
  *
  * @copyright		: (C) 2024, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_BT4502_H_
#define INC_BT4502_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "system.h"
#include "main.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
extern uint8_t bBLE_SPP_Flag;
extern uint8_t bBLE_UART_Flag;

extern uint8_t bBLE_recv_buffer[0xFF];
extern uint8_t bBLE_recv_temp[2];
extern uint8_t bBLE_recv_len;


/* Exported macro ------------------------------------------------------------*/
#define bt4502_pdn_high()		  		HAL_GPIO_WritePin(BLE_PDN_GPIO_Port, BLE_PDN_Pin, GPIO_PIN_SET);
#define bt4502_pdn_low()			  	HAL_GPIO_WritePin(BLE_PDN_GPIO_Port, BLE_PDN_Pin, GPIO_PIN_RESET);
#define bt4502_wakeup_high()			HAL_GPIO_WritePin(BLE_WAKEUP_GPIO_Port, BLE_WAKEUP_Pin, GPIO_PIN_SET);
#define bt4502_wakeup_low()				HAL_GPIO_WritePin(BLE_WAKEUP_GPIO_Port, BLE_WAKEUP_Pin, GPIO_PIN_RESET);
//#define bt4502_read_int()				return HAL_GPIO_ReadPin(BLE_INT_GPIO_Port, BLE_INT_Pin);

/* Exported functions prototypes ---------------------------------------------*/
GPIO_PinState bt4502_read_int(void);
void bt4502_task(void);
uint8_t bt4502_recv_check(void);
void bt4502_test_send(uint8_t buff);
void bt4502_init(void);
void bt4502_deinit(void);
void bt4502_sendAT(uint8_t len);
void bt4502_receiveAT(void);
void bt4502_set_connectionInterval(uint16_t intr);
void bt4502_get_moduleName(void);
void bt4502_set_moduleName(char name[25]);
void bt4502_get_baudRate(void);
void bt4502_set_baudRate(uint8_t baud);
void bt4502_get_macAddress(void);
void bt4502_set_macAddress(uint8_t addr);
void bt4502_reset(void);
void bt4502_set_advertisePeriod(uint8_t adv);
void bt4502_set_advertiseContent(uint8_t cont);
void bt4502_set_productIdentification(uint8_t prod);
void bt4502_set_txPower(uint8_t pow);
void bt4502_set_rssi(uint8_t rssi);
void bt4502_rtc(uint8_t set);
void bt4502_set_delay(uint8_t delay);
void bt4502_battery(uint8_t batt);


#ifdef __cplusplus
}
#endif

#endif /* INC_BT4502_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/