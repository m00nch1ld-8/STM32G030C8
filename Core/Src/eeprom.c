#include "stm32g0xx_hal.h"
#include "eeprom.h"
#include "sound.h"
#include "system.h"


extern I2C_HandleTypeDef hi2c2;

sBIT_BYTE_ACCESS bEeprom_flag;

uint8_t bEep_buf[8];

#ifdef USE_BREAKPOINT_EN
void eeprom_init(void)
{
	HAL_StatusTypeDef	ack = HAL_BUSY;
	uint8_t i = 0;

	while (ack != HAL_OK)
	{
		ack = HAL_I2C_IsDeviceReady(&hi2c2,EEPROM_ADDR,10,50);
		if(ack == HAL_ERROR) i++;
		if(i > 9)
		{
			ack = HAL_OK;
			soundCt.bEepromFlag = I2C_STAT_TIMEOUT;
		}
	}

	if(ack == HAL_OK && soundCt.bEepromFlag != I2C_STAT_TIMEOUT) soundCt.bEepromFlag = I2C_STAT_OK;
}

void eeprom_read_byte(uint16_t addr, uint8_t num)
{
	HAL_StatusTypeDef ack = HAL_BUSY;
	uint16_t timeout = 400;

	if(num > 10) timeout = 1000;
	ack = HAL_I2C_Mem_Read(&hi2c2,EEPROM_ADDR+EEPROM_READ, addr,I2C_MEMADD_SIZE_8BIT,&bEep_buf[0],num,timeout);

}

void eeprom_write_byte(uint16_t addr,uint8_t ddata)
{
	HAL_StatusTypeDef ack = HAL_BUSY;

	ack = HAL_I2C_Mem_Write(&hi2c2,EEPROM_ADDR,addr,I2C_MEMADD_SIZE_8BIT,&ddata,1,100);

}
#endif	//USE_BREAKPOINT_EN
















