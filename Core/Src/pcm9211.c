/*
 * PCM9211 codec driver
 *
 * Copyright (C) 2023 PT. Hartono Istana Teknologi
 *
 * Author; Adrian B. Hartanto <adrian.b.hartanto@polytron.co.id>
 *
 */

#include "config.h"
#include "pcm9211.h"
#include "system.h"

extern I2C_HandleTypeDef hi2c2;
HAL_StatusTypeDef	pcm9211_i2c_ack;
uint8_t				pcm9211_i2c_buf;


#define PCM9211_MAX_SYSCLK 24576000

uint8_t ERR_OUT				= 0x00; 
uint8_t DIR_REG_1			= 0x00; 
uint8_t DIR_REG_2			= 0x01; 
uint8_t DIR_REG_3			= 0x04; 
uint8_t OSC_CTRL			= 0x00; 
uint8_t AUTO_SEL_CAUSE		= 0x81;
uint8_t DIR_FS_RANGE		= 0x00; 
uint8_t DIR_OUT_FMT			= 0x04; 
uint8_t DIR_RSCLK_RATIO		= 0x02; 
uint8_t XTI_SCLK_FREQ		= 0x1A;
uint8_t DIR_SOURCE_BIT2		= 0x22; 
uint8_t XTI_SOURCE_BIT2		= 0x22; 
uint8_t DIR_INP_BIPHASE		= 0xCC;
uint8_t FS_CALC_TARGET		= 0x00; 
uint8_t ADC_CTRL2			= 0x64;
uint8_t DIT_CTRL1			= 0x40;
uint8_t DIT_CTRL2			= 0x10; 
uint8_t MAIN_AUX_MUTE		= 0x00; 
uint8_t MAIN_OUT_SOURCE		= 0x22;
uint8_t MPIO_B_MAIN_HIZ		= 0x00; 
uint8_t MPIO_C_MPIO_A_HIZ	= 0x00;
uint8_t MPIO_GROUP			= 0x05;
uint8_t MPO_1_0_FUNC		= 0x00;
uint8_t ADC_L_CH_ATT		= 0xF2;	//0xDE;
uint8_t ADC_R_CH_ATT		= 0xF2;	//0xDE;



void pcm9211_reset(void)
{
	// pcm9211_i2c_buf = 0x33;
	// HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_SYS_RESET, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	pcm9211_i2c_buf = 0xC0;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_SYS_RESET, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
}

void pcm9211_clock(void)
{
	// XTI CLK source 12.288 and BCK 3.072, LRCK 48k = XTI/512
	pcm9211_i2c_buf = XTI_SCLK_FREQ;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_XTI_SCLK_FREQ, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	pcm9211_i2c_buf = XTI_SOURCE_BIT2;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_XTI_SOURCE_BIT2, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	pcm9211_i2c_buf = ERR_OUT;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_ERR_OUT, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	pcm9211_i2c_buf = OSC_CTRL;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_OSC_CTRL, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// ADC clock source is chosen by REG42
	pcm9211_i2c_buf = AUTO_SEL_CAUSE;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_AUTO_SEL_CAUSE, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// XTI Source, Secondary Bit/LR Clock (SBCK/SLRCK) Frequency Setting
	pcm9211_i2c_buf = XTI_SOURCE_BIT2;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_XTI_SOURCE_BIT2, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
}

void pcm9211_dir(void)
{
	// REG. 21h, DIR Receivable Incoming Biphase's Sampling Frequency Range Setting
	pcm9211_i2c_buf = DIR_REG_1;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_INITIAL1, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 22h, DIR CLKSTP and VOUT delay
	pcm9211_i2c_buf = DIR_REG_2;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_INITIAL2, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 23h, DIR OCS start up wait time and Process for Parity Error Detection and ERROR Release Wait Time Setting
	pcm9211_i2c_buf = DIR_REG_3;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_INITIAL3, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG 27h DIR Acceptable fs Range Setting & Mask
	pcm9211_i2c_buf = DIR_FS_RANGE;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_FS_RANGE, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG 2Fh, DIR Output Data Format, 24bit I2S mode
	pcm9211_i2c_buf = DIR_OUT_FMT;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_OUT_FMT, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 30h, DIR Recovered System Clock (SCK) Ratio Setting
	pcm9211_i2c_buf = DIR_RSCLK_RATIO;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_RSCLK_RATIO, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 32h, DIR Source, Secondary Bit/LR Clock (SBCK/SLRCK) Frequency Setting
	pcm9211_i2c_buf = DIR_SOURCE_BIT2;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_SOURCE_BIT2, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG 34h DIR Input Biphase Signal Source Select and RXIN01 Coaxial Amplifier
	pcm9211_i2c_buf = DIR_INP_BIPHASE;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIR_INP_BIPHASE, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 37h, Port Sampling Frequency Calculator Measurement Target Setting, Cal and DIR Fs
	pcm9211_i2c_buf = FS_CALC_TARGET;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_FS_CALC_TARGET, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
}

void pcm9211_dit(void)
{
	// REG. 46h, ADC Function Control Register 2/3
// #ifdef SETTING_AUTRAN
	pcm9211_i2c_buf = ADC_L_CH_ATT;
// #else
// 	pcm9211_i2c_buf = ADC_L_CH_ATT;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_ADC_L_CH_ATT, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
// 	// REG. 47h, ADC Function Control Register 2/3
	pcm9211_i2c_buf = ADC_R_CH_ATT;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_ADC_R_CH_ATT, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
// #endif

	// REG. 48h, ADC Function Control Register 2/3
	// pcm9211_i2c_buf = ADC_CTRL2;
	// HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_ADC_CTRL2, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 60h, DIT Function Control Register 1/3
	pcm9211_i2c_buf = DIT_CTRL1;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIT_CTRL1, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 61h, DIT Function Control Register 2/3
	pcm9211_i2c_buf = DIT_CTRL2;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_DIT_CTRL2, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
}

void pcm9211_mainOutput(void)
{
	// REG. 6Ah, Main Output & AUXOUT Port Control
	pcm9211_i2c_buf = MAIN_AUX_MUTE;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MAIN_AUX_MUTE, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 6Bh, Main Output Port (SCKO/BCK/LRCK/DOUT) Source Setting
	pcm9211_i2c_buf = MAIN_OUT_SOURCE;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MAIN_OUT_SOURCE, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 6Dh, MPIO_B & Main Output Port Hi-Z Control
	pcm9211_i2c_buf = MPIO_B_MAIN_HIZ;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MPIO_B_MAIN_HIZ, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);

	// REG. 6Eh, MPIO_C and MPIO_A Hi-Z Control Register
	pcm9211_i2c_buf = MPIO_C_MPIO_A_HIZ;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MPIO_C_MPIO_A_HIZ, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 6Fh, MPIO_A, MPIO_B, MPIO_C Group Function Assign Register
	pcm9211_i2c_buf = MPIO_GROUP;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MPIO_GROUP, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
	
	// REG. 78h, MPO1, MPO0 Function Assign Setting Register
	pcm9211_i2c_buf = MPO_1_0_FUNC;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MPO_1_0_FUNC, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
}

void pcm9211_unMute_outPort(void)
{
	
	// REG. 6Dh, MPIO_B & Main Output Port Hi-Z Control
	pcm9211_i2c_buf = MPIO_B_MAIN_HIZ;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MPIO_B_MAIN_HIZ, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);

	// REG. 6Eh, MPIO_C and MPIO_A Hi-Z Control Register
	pcm9211_i2c_buf = MPIO_C_MPIO_A_HIZ;
	HAL_I2C_Mem_Write(&hi2c2, PCM9211_ADDR+PCM9211_WRITE, PCM9211_MPIO_C_MPIO_A_HIZ, I2C_MEMADD_SIZE_8BIT, &pcm9211_i2c_buf, 1, 100);
}

void pcm9211_init(void)
{
	HAL_StatusTypeDef	ack = HAL_BUSY;
	uint8_t i = 0;

	while (ack != HAL_OK)
	{
		ack = HAL_I2C_IsDeviceReady(&hi2c2,PCM9211_ADDR,10,50);
		if(ack == HAL_ERROR) i++;
		else if(ack == HAL_BUSY) i++;
		else if(ack == HAL_TIMEOUT) i++;
		if(i > 9)
		{
			fSys_PCM_error = 1;
		}
	}

	if(!fSys_PCM_error)
	{
		// System RST Control
		pcm9211_reset();
		// XTI Source, Clock (SCK/BCK/LRCK) Frequency Setting
		pcm9211_clock();
		// DIR settings
		pcm9211_dir();
		// DIT_CTRL Settings
		pcm9211_dit();
		// HAL_Delay(6969);
		// MainOutput Settings
		// pcm9211_mainOutput();	//dipindah setelah init finished
	}
}

void pcm9211_output_selector(bool selOut)
{
	HAL_StatusTypeDef	ack = HAL_BUSY;

	// fADC_CTRL1_ADDTRX7 = selOut;

	while (ack != HAL_OK)
	{
		// ack = HAL_I2C_IsDeviceReady(&hi2c2,cDEVID_EEP0_WRITE,10,50);
	}
	// ack = HAL_I2C_Mem_Write(&hi2c2,PCM9211_ADDR+PCM9211_WRITE,PCM9211_ADC_CTRL1,I2C_MEMADD_SIZE_8BIT,ADC_CTRL1,1,100);
}



