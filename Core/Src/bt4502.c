/**
  ******************************************************************************
  * @file           : bt4502.c
  * @brief          : Driver for BLE BT4502
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

/* Includes ------------------------------------------------------------------*/
#include "bt4502.h"
#include "math.h"
#include "string.h"
#include "system.h"
#include "spp.h"

/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
uint8_t bBLE_recv_buffer[0xFF];
#ifdef USE_CIRCULAR_BUFF_EN
MCU_CIRCULAR_CONTEXT BLE_CircularCtx;
uint8_t bBLE_CircularBuff[MAX_DATA_BUFF];
uint8_t bBLE_recv_final[32];
#else
uint8_t bBLE_recv_final[0xFF];
#endif
uint8_t bBLE_recv_temp[1];
uint8_t bBLE_send_buffer[0xFF];
char cData_Buffer[0xFF];
uint8_t bBLE_recv_len = 0;
uint8_t bBLE_SPP_len = 0;
uint8_t bBLE_UART_len = 0;
uint8_t bBLE_temp_buffer[0xFF];	//ga kepake
sBIT_BYTE_ACCESS bBLE_flag;


/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
extern UART_HandleTypeDef huart1;

GPIO_PinState bt4502_read_int(void)
{
	return HAL_GPIO_ReadPin(BLE_INT_GPIO_Port, BLE_INT_Pin);
}

uint8_t bt4502_recv_check(void)
{
#ifdef USE_CIRCULAR_BUFF_EN
	uint8_t dataTemp;
	static int8_t recvIndex = -4;
	uint16_t dataSize = MCUCircular_GetDataLen(&BLE_CircularCtx);

	while(dataSize > 0)
	{
		if(MCUCircular_GetData(&BLE_CircularCtx, &dataTemp, 1) == 0)
		{
			return 0;
		}
		dataSize = MCUCircular_GetSpaceLen(&BLE_CircularCtx);
		if(recvIndex == -4)
		{
			if(dataTemp == 0x0D)
			{
				recvIndex = -1;
			}
			else if(dataTemp == 'T')
			{
				recvIndex = -3;
			}
		}
		else if(recvIndex == -3)
		{
			if(dataTemp == 'T')
			{
				recvIndex = -2;
			}
		}
		else if(recvIndex == -2)
		{
			if(dataTemp == 'M')
			{
				recvIndex = -1;
			}
		}
		else if(recvIndex == -1)
		{
			if(dataTemp == 0x0A)
			{
				recvIndex = 0;
			}
			else if(dataTemp == ':')
			{
				recvIndex = 0;
			}
		}
		else
		{
			bBLE_recv_final[recvIndex++] = dataTemp;
			if(bBLE_recv_final[recvIndex-1] == 0x0A)
			{
				recvIndex = -4;
				return 2;
			}
			if((bBLE_recv_final[recvIndex-1] == 0x00) && (bBLE_recv_final[recvIndex-2] == 0x0A) && (bBLE_recv_final[recvIndex-2] == 0x0D))
			{
				recvIndex = -4;
				return 1;
			}
		}
	}
	return 0;
#else		//USE_CIRCULAR_BUFF_EN
	if(fBLE_SPP_Flag)
	{
		if((bBLE_recv_temp[0] == '\n') && (bBLE_recv_len != 0))
		{
			memcpy(bBLE_recv_final, bBLE_recv_buffer, bBLE_recv_len);
			bBLE_SPP_len = bBLE_recv_len;
			bBLE_recv_len = 0;
			fBLE_SPP_Flag = 0;
			fBLE_UART_Flag = 0;
			memset(bBLE_recv_buffer, 0, sizeof(bBLE_recv_buffer));
			return 2;
		}
	}
	else if(fBLE_UART_Flag)
	{
		if(fBLE_wait_reply == 0)
		// if((bBLE_recv_temp[0] == '\n') && (bBLE_recv_len != 0))
		{
			memcpy(bBLE_recv_final, bBLE_recv_buffer, bBLE_recv_len);
			bBLE_UART_len = bBLE_recv_len;
			bBLE_recv_len = 0;
			fBLE_SPP_Flag = 0;
			fBLE_UART_Flag = 0;
			memset(bBLE_recv_buffer, 0, sizeof(bBLE_recv_buffer));
			return 1;
		}
	}
	return 0;
#endif		//USE_CIRCULAR_BUFF_EN
}

void bt4502_parse_reply(void)
{
	if((bBLE_recv_final[4] == 'C') && (bBLE_recv_final[5] == 'O') && (bBLE_recv_final[6] == 'N'))
	{
		//BLE Connect
		fBLE_connect = 1;
	}
	else if((bBLE_recv_final[4] == 'D') && (bBLE_recv_final[5] == 'I') && (bBLE_recv_final[6] == 'S'))
	{
		//BLE Disconnect
		fBLE_connect = 0;
	}
	else if((bBLE_recv_final[4] == 'O') && (bBLE_recv_final[5] == 'K'))
	{
		//BLE return OK
	}
	else if((bBLE_recv_final[4] == 'E') && (bBLE_recv_final[5] == 'R') && (bBLE_recv_final[6] == 'P'))
	{
		//BLE return ERROR
	}
	else if((bBLE_recv_final[4] == 'T') && (bBLE_recv_final[5] == 'I') && (bBLE_recv_final[6] == 'M'))
	{
		//BLE return TIMEOUT
	}
	else if((bBLE_recv_final[4] == 'N') && (bBLE_recv_final[5] == 'A') && (bBLE_recv_final[6] == 'M'))
	{
		//BLE return Module NAME
		for(uint8_t i = 8; i < bBLE_UART_len-3; i++)
		{
			cData_Buffer[i-8] = bBLE_recv_final[i];
		}
	}
	else if((bBLE_recv_final[4] == 'B') && (bBLE_recv_final[5] == 'P') && (bBLE_recv_final[6] == 'S') && (bBLE_recv_final[6] == '-'))
	{
		//BLE return Baud Rate
	}
	else if((bBLE_recv_final[4] == 'B') && (bBLE_recv_final[5] == 'P') && (bBLE_recv_final[6] == 'S'))
	{
		//BLE return Baud Rate Set
	}
	else if((bBLE_recv_final[4] == 'M') && (bBLE_recv_final[5] == 'A') && (bBLE_recv_final[6] == 'C'))
	{
		//BLE return MAC Address
	}
	else if((bBLE_recv_final[4] == 'R') && (bBLE_recv_final[5] == 'T') && (bBLE_recv_final[6] == 'C'))
	{
		//BLE retrun RTC
	}
}

void bt4502_task(void)
{
    uint8_t asdfgh = 0;

	if(MCUCircular_GetDataLen(&BLE_CircularCtx) != 0)
	{
		asdfgh = bt4502_recv_check();
		if(asdfgh == 1)
		{
			// saat UART selesai;
			bt4502_parse_reply();
		}
		else if(asdfgh == 2)
		{
			// saat SPP selesai
			SlaveStateCtrl();
		}
	}
}

void bt4502_test_send(uint8_t buff)
{
	bt4502_wakeup_low();
	bBLE_send_buffer[0] = bBLE_temp_buffer[buff];
	bBLE_send_buffer[1] = '\r';
	bBLE_send_buffer[2] = '\n';
	bBLE_send_buffer[3] = '\0';
	HAL_Delay(20);
	HAL_UART_Transmit(&huart1, &bBLE_send_buffer[0], 4, 500);
	bt4502_wakeup_high();
}

void bt4502_init(void)
{
	uint8_t waitReplyCount = 10;
#ifdef USE_CIRCULAR_BUFF_EN
	MCUCircular_Config(&BLE_CircularCtx, bBLE_CircularBuff, MAX_DATA_BUFF);
#endif
	HAL_UART_Receive_IT(&huart1, bBLE_recv_temp, 1);
	bt4502_get_moduleName();
	while(fBLE_wait_reply)
	{
		if(waitReplyCount)	waitReplyCount--;
		else fSys_BLE_error = 1;
		HAL_Delay(100);
	}
	bt4502_task();
	waitReplyCount = strcmp(cData_Buffer, "PHS WOOFER");
	if(waitReplyCount != 0)
	{
		bt4502_set_moduleName();
	}
//	bt4502_set_connectionInterval(200);
	bt4502_pdn_low();	//start advertisement
}

void bt4502_deinit(void)
{
	bt4502_pdn_high();	//full sleep
}

void bt4502_sendAT(uint8_t len)
{
	bBLE_send_buffer[0] = 'T';
	bBLE_send_buffer[1] = 'T';
	bBLE_send_buffer[2] = 'M';
	bBLE_send_buffer[3] = ':';

	bt4502_wakeup_low();
	HAL_Delay(20);
	HAL_UART_Transmit(&huart1, &bBLE_send_buffer[0], len, 500);
	bt4502_wakeup_high();
}

void bt4502_receiveAT(void)
{
	HAL_UART_Receive(&huart1, &bBLE_recv_buffer[0], 0xFF, 500);
}

void bt4502_set_connectionInterval(uint16_t intr)
{
	uint16_t sq = 4;
	uint8_t len = 4, pos = 0, i = 3;
	uint8_t buff[4];

	while(i)
	{
		sq = pow(10,i);
		buff[i] = (intr/sq)%10;
		if(buff[i] != 0 && pos == 0) pos = i+1;
		i--;
	}
	bBLE_send_buffer[len++] = 'C';
	bBLE_send_buffer[len++] = 'I';
	bBLE_send_buffer[len++] = 'T';
	bBLE_send_buffer[len++] = '-';
	if(pos == 4)
	{
		bBLE_send_buffer[len++] = buff[3];
		bBLE_send_buffer[len++] = buff[2];
		bBLE_send_buffer[len++] = buff[1];
	}
	else if(pos == 3)
	{
		bBLE_send_buffer[len++] = buff[2];
		bBLE_send_buffer[len++] = buff[1];
	}
	else if(pos == 2)
	{
		bBLE_send_buffer[len++] = buff[1];
	}
	else return;
	bBLE_send_buffer[len++] = '0';
	bBLE_send_buffer[len++] = 'm';
	bBLE_send_buffer[len++] = 's';
	bt4502_sendAT(len);
}

void bt4502_get_moduleName(void)
{
	fBLE_wait_reply = 1;
	bBLE_send_buffer[4] = 'N';
	bBLE_send_buffer[5] = 'A';
	bBLE_send_buffer[6] = 'M';
	bBLE_send_buffer[7] = '-';
	bBLE_send_buffer[8] = '?';
	bBLE_send_buffer[9] = 0x0D;
	bBLE_send_buffer[10] = 0x0A;
	bBLE_send_buffer[11] = 0x00;
	bt4502_sendAT(12);
}

void bt4502_set_moduleName(void)
{
	bBLE_send_buffer[4] = 'R';
	bBLE_send_buffer[5] = 'E';
	bBLE_send_buffer[6] = 'N';
	bBLE_send_buffer[7] = '-';
	bBLE_send_buffer[8] = 'P';
	bBLE_send_buffer[9] = 'H';
	bBLE_send_buffer[10] = 'S';
	bBLE_send_buffer[11] = ' ';
	bBLE_send_buffer[12] = 'W';
	bBLE_send_buffer[13] = 'O';
	bBLE_send_buffer[14] = 'O';
	bBLE_send_buffer[15] = 'F';
	bBLE_send_buffer[16] = 'E';
	bBLE_send_buffer[17] = 'R';
	bBLE_send_buffer[18] = 0x0D;
	bBLE_send_buffer[19] = 0x0A;
	bBLE_send_buffer[20] = '\0';
	bt4502_sendAT(21);
}

void bt4502_get_baudRate(void)
{
	bBLE_send_buffer[4] = 'B';
	bBLE_send_buffer[5] = 'P';
	bBLE_send_buffer[6] = 'S';
	bBLE_send_buffer[7] = '-';
	bBLE_send_buffer[8] = '?';
	bt4502_sendAT(9);
}

void bt4502_set_baudRate(uint8_t baud)
{
	uint16_t sq = 4;
	uint8_t len = 4, pos = 0, i = 5;
	uint8_t buff[6];

	while(i)
	{
		sq = pow(10,i);
		buff[i] = (baud/sq)%10;
		if(buff[i] != 0 && pos == 0) pos = i+1;
		i--;
	}
	bBLE_send_buffer[len++] = 'B';
	bBLE_send_buffer[len++] = 'P';
	bBLE_send_buffer[len++] = 'S';
	bBLE_send_buffer[len++] = '-';
	if(pos == 6)
	{
		bBLE_send_buffer[len++] = buff[5];
		bBLE_send_buffer[len++] = buff[4];
		bBLE_send_buffer[len++] = buff[3];
		bBLE_send_buffer[len++] = buff[2];
	}
	else if(pos == 5)
	{
		bBLE_send_buffer[len++] = buff[4];
		bBLE_send_buffer[len++] = buff[3];
		bBLE_send_buffer[len++] = buff[2];
	}
	else if(pos == 4)
	{
		bBLE_send_buffer[len++] = buff[3];
		bBLE_send_buffer[len++] = buff[2];
	}
	else return;
	bBLE_send_buffer[len++] = '0';
	bBLE_send_buffer[len++] = '0';
	bt4502_sendAT(len);
}

void bt4502_get_macAddress(void)
{
	bBLE_send_buffer[4] = 'M';
	bBLE_send_buffer[5] = 'A';
	bBLE_send_buffer[6] = 'C';
	bBLE_send_buffer[7] = '-';
	bBLE_send_buffer[8] = '?';
	bt4502_sendAT(9);
}

void bt4502_set_macAddress(uint8_t addr)
{
	bBLE_send_buffer[4] = 'M';
	bBLE_send_buffer[5] = 'A';
	bBLE_send_buffer[6] = 'C';
	bBLE_send_buffer[7] = '-';
//	bBLE_send_buffer[8] = '';
//	bBLE_send_buffer[9] = '';
	bt4502_sendAT(10);
}

void bt4502_reset(void)
{
	bBLE_send_buffer[4] = 'R';
	bBLE_send_buffer[5] = 'S';
	bBLE_send_buffer[6] = 'T';
	bBLE_send_buffer[7] = '-';
	bBLE_send_buffer[8] = 'S';
	bBLE_send_buffer[9] = 'Y';
	bBLE_send_buffer[10] = 'S';
	bBLE_send_buffer[11] = 'T';
	bBLE_send_buffer[12] = 'E';
	bBLE_send_buffer[13] = 'M';
	bBLE_send_buffer[14] = 'R';
	bBLE_send_buffer[15] = 'E';
	bBLE_send_buffer[16] = 'S';
	bBLE_send_buffer[17] = 'E';
	bBLE_send_buffer[18] = 'T';
	bt4502_sendAT(19);
}

void bt4502_set_advertisePeriod(uint8_t adv)
{
	uint16_t sq = 4;
	uint8_t len = 4, pos = 0, i = 1;
	uint8_t buff[2];

	while(i)
	{
		sq = pow(10,i);
		buff[i] = (adv/sq)%10;
		if(buff[i] != 0 && pos == 0) pos = i+1;
		i--;
	}
	bBLE_send_buffer[len++] = 'A';
	bBLE_send_buffer[len++] = 'D';
	bBLE_send_buffer[len++] = 'P';
	bBLE_send_buffer[len++] = '-';
	bBLE_send_buffer[len++] = '(';
	if(pos == 2)
	{
		bBLE_send_buffer[len++] = buff[1];
		bBLE_send_buffer[len++] = buff[0];
	}
	else
	{
		bBLE_send_buffer[len++] = buff[0];
	}
	bBLE_send_buffer[len++] = ')';
	bt4502_sendAT(len);
}

void bt4502_set_advertiseContent(uint8_t cont)
{
//	bBLE_send_buffer[4] = '';
//	bBLE_send_buffer[5] = '';
//	bBLE_send_buffer[6] = '';
//	bBLE_send_buffer[7] = '';
//	bBLE_send_buffer[8] = '';
//	bBLE_send_buffer[9] = '';
//	bt4502_sendAT();
}

void bt4502_set_productIdentification(uint8_t prod)
{
//	bBLE_send_buffer[4] = '';
//	bBLE_send_buffer[5] = '';
//	bBLE_send_buffer[6] = '';
//	bBLE_send_buffer[7] = '';
//	bBLE_send_buffer[8] = '';
//	bBLE_send_buffer[9] = '';
//	bt4502_sendAT();
}

void bt4502_set_txPower(uint8_t pow)
{
	uint8_t len = 4;
	bBLE_send_buffer[len++] = 'T';
	bBLE_send_buffer[len++] = 'P';
	bBLE_send_buffer[len++] = 'L';
	bBLE_send_buffer[len++] = '-';
	bBLE_send_buffer[len++] = '(';
	if(pow == 0)
	{
		bBLE_send_buffer[len++] = '-';
		bBLE_send_buffer[len++] = '2';
		bBLE_send_buffer[len++] = '0';
	}
	if(pow == 1)
	{
		bBLE_send_buffer[len++] = '-';
		bBLE_send_buffer[len++] = '6';
	}
	if(pow == 2)
	{
		bBLE_send_buffer[len++] = '0';
	}
	if(pow == 3)
	{
		bBLE_send_buffer[len++] = '6';
	}
	if(pow == 4)
	{
		bBLE_send_buffer[len++] = '+';
		bBLE_send_buffer[len++] = '1';
		bBLE_send_buffer[len++] = '0';
	}
	bBLE_send_buffer[len++] = ')';
	bt4502_sendAT(len);
}

void bt4502_set_rssi(uint8_t rssi)
{
	uint8_t len = 4;
	bBLE_send_buffer[len++] = 'R';
	bBLE_send_buffer[len++] = 'S';
	bBLE_send_buffer[len++] = 'I';
	bBLE_send_buffer[len++] = '-';
	bBLE_send_buffer[len++] = 'O';
	if(rssi)
	{
		bBLE_send_buffer[len++] = 'N';
	}
	else
	{
		bBLE_send_buffer[len++] = 'F';
		bBLE_send_buffer[len++] = 'F';
	}
	bt4502_sendAT(len);
}

void bt4502_rtc(uint8_t set)	// 1: set, 0: get
{
	uint8_t len = 4;
	bBLE_send_buffer[len++] = 'R';
	bBLE_send_buffer[len++] = 'T';
	bBLE_send_buffer[len++] = 'C';
	bBLE_send_buffer[len++] = '-';
	if(set)
	{
//		bBLE_send_buffer[4] = '';
//		bBLE_send_buffer[5] = '';
//		bBLE_send_buffer[6] = '';
//		bBLE_send_buffer[7] = '';
//		bBLE_send_buffer[8] = '';
//		bBLE_send_buffer[9] = '';
	}
	else
	{
		bBLE_send_buffer[len++] = '?';
	}
	bt4502_sendAT(len);
}

void bt4502_set_delay(uint8_t delay)
{
//	bBLE_send_buffer[4] = '';
//	bBLE_send_buffer[5] = '';
//	bBLE_send_buffer[6] = '';
//	bBLE_send_buffer[7] = '';
//	bBLE_send_buffer[8] = '';
//	bBLE_send_buffer[9] = '';
//	bt4502_sendAT();
}

void bt4502_battery(uint8_t batt)
{
	uint16_t sq = 4;
	uint8_t len = 4, pos = 0, i = 2;
	uint8_t buff[3];

	while(i)
	{
		sq = pow(10,i);
		buff[i] = (batt/sq)%10;
		if(buff[i] != 0 && pos == 0) pos = i+1;
		i--;
	}
	bBLE_send_buffer[len++] = 'B';
	bBLE_send_buffer[len++] = 'S';
	bBLE_send_buffer[len++] = 'T';
	bBLE_send_buffer[len++] = '-';
	if(pos == 3)
	{
		bBLE_send_buffer[len++] = buff[2];
		bBLE_send_buffer[len++] = buff[1];
		bBLE_send_buffer[len++] = buff[0];
	}
	if(pos == 2)
	{
		bBLE_send_buffer[len++] = buff[1];
		bBLE_send_buffer[len++] = buff[0];
	}
	if(pos == 1)
	{
		bBLE_send_buffer[len++] = buff[0];
	}
	bt4502_sendAT(len);
}
