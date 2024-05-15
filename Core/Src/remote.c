/**
	******************************************************************************
	* @file           : main.c
	* @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "sound.h"
#include "display.h"
#include "remote.h"
#include "input_process.h"


/* Private typedef -----------------------------------------------------------*/
uint8_t bAddrHigh = 0;
uint8_t bAddrLow = 0;
uint8_t bCmdHigh = 0;
uint8_t bCmdLow = 0;
uint8_t bBitIndex = 0;
uint32_t bRemote_temp = 0;
uint32_t bRemote_received_code = 0;
uint32_t bRemote_oldreceived_code = 0;
sBIT_BYTE_ACCESS bRemote_flag;


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/
extern TIM_HandleTypeDef htim16;

// uint8_t bRemoteKeyFunction[IR_MAX_LEN] = {
// 	0x00,/*0*/
// 	0x01,/*1*/
// 	0x02,/*2*/
// 	0x03,/*3*/
// 	0x04,/*4*/
// 	0x05,/*5*/
// 	0x06,/*6*/
// 	0x07,/*7*/
// 	0x08,/*8*/
// 	0x09,/*9*/
// 	0x0A,/*FUNCTION*/
// 	0x0B,/*MENU / BROWSER*/
// 	0x0C,/*UP*/
// 	0x0D,/*DOWN*/
// 	0x0E,/*RIGHT*/
// 	0x0F,/*LEFT*/
// 	0x10,/*RETURN/EXIT*/
// 	0x11,/*PROGRAM / MEMORY*/
// 	0x12,/*STOP*/
// 	0x13,/*PLAY PAUSE*/
// 	0x14,/*ENTER*/
// 	0x15,/*MUTE*/
// 	0x16,/*SLEEP*/
// 	0x17,/*POWER*/
// 	0x18,/*FWD*/
// 	0x19,/*REV*/
// 	0x1A,/*NEXT*/
// 	0x1B,/*PREV*/
// 	0x1C,/*SLOW*/
// 	0x1D,/*GOTO*/
// 	0x1E,/*REPEAT*/
// 	0x1F,/*A-B*/
// 	0x20,/*FOLDER +*/
// 	0x21,/*FOLDER -*/
// 	0x22,/*ROCK*/
// 	0x23,/*POP*/
// 	0x24,/*JAZZ*/
// 	0x25,/*CLASSIC*/
// 	0x26,/*DANGDUT*/
// 	0x27,/*MOVIE*/
// 	0x28,/*DRAMA*/
// 	0x29,/*FLAT*/
// 	0x2A,/**/
// 	0x2B,/**/
// 	0x2C,/**/
// 	0x2D,/**/
// 	0x2E,/**/
// 	0x2F,/**/
// 	0x30,/*BAZZOKE*/
// 	0x31,/*EQ*/
// 	0x32,/*PLAY*/
// 	0x33,/*PAUSE*/
// 	0x34,/*ECHO-*/
// 	0x35, /*SURROUND*/
// 	0x36,/*MIC+*/
// 	0x37,/*MIC-*/
// 	0x38,/*TREBLE+*/
// 	0x39,/*TREBLE-*/
// 	0x3A,/*BASS+*/
// 	0x3B,/*BASS-*/
// 	0x3C,/*LIGHT*/
// 	0x3D,/*MIDDLE+*/
// 	0x3E,/*MIDDLE-*/
// 	0x3F,/**/
// 	0x40,/*SCAN*/
// 	0x41,/*OPEN CLOSE*/
// 	0x42,/*FLASHRIP*/
// 	0x43,/*TITLE*/
// 	0x44,/*PAUSE remote PAS59*/
// 	0x45,/*SUBTITLE*/
// 	0x46,/*STEP*/
// 	0x47,/*AUDIO*/
// 	0x48,/*ANGLE*/
// 	0x49,/*CARD*/
// 	0x4A,/*OSD*/
// 	0x4B,/*ZOOM*/
// 	0x4C,/*SETUP*/
// 	0x4D,/*CLOCK/TIMER*/
// 	0x4E,/*PAL/NTSC*/
// 	0x4F,/*BROWSER*/
// 	0x50,/*VOL+*/
// 	0x51,/*VOL-*/
// 	0x52,/*KARAOKE*/
// 	0x53,/*SOUND SET*/
// 	0x54,/*ECHO+*/
// 	0x55,/*MULTIMEDIA*/
// 	0x56,/*VIDEO*/
// 	0x57,/*CLEAR*/
// 	0x58,/*BT*/
// 	0x59,/*SPK*/
// 	0x5A,/*Direct LineIN*/
// 	0x5B,/*Direct AUX/GIN*/
// 	0x5C,/*Direct FM*/
// 	0x5D,/*SBass*/
// 	0x5E,/*TREBLE BOOST*/
// 	0x5F,/*RECORD*/
// 	0x60,/*VOL+ SMART*/
// 	0x61,/*VOL- SMART*/
// 	0x62,/*AVC L*/
// 	0x63,/*AVC R*/
// 	0x64,/*MPX L*/
// 	0x65,/*MPX R*/
// 	0x66,/*OPTIC*/
// 	0x67,/*HOME*/
// 	0x68,/*SCAN*/
// 	0x69,/**/
// 	0x6A,/*SMART*/
// 	0x6B, //wireless MIC
// 	0x6C, /*TWS*/
// 	0x6D,/*SUBW LVL+*/
// 	0x6E,/*SUBW LVL-*/
// 	0x6F,/**/
// };

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
void remote_init(void)
{
		bRemote_flag.byte_access = 0x00;

		HAL_TIM_Base_Start(&htim16);
		__HAL_TIM_SET_COUNTER(&htim16, 0);
}

uint8_t remote_getReceived_code(void)
{
	return  bRemote_received_code;
}

void remote_check(void)
{
	if((fRemote_pressed == 1) && (fRemote_processed == 0))
	{
		if(soundCt.bSoundMode != SOUND_MODE_DIGITAL)
		{
			if(bCmdLow == 0x50/*0x6D*/)
			{
				soundCt.bSoundMenu = 0xA0;
			
				bDisplay_flag.byte_access &= 16;
				fDisplay_MenuUpdate = 1;
				fDisplay_SmartRGB = 1;
				fDisplay_Level = 1;
				bRemote_received_code = 0xB0;
			}
			else if(bCmdLow == 0x51/*0x6E*/)
			{
				soundCt.bSoundMenu = 0xA0;
			
				bDisplay_flag.byte_access &= 16;
				fDisplay_MenuUpdate = 1;
				fDisplay_SmartRGB = 1;
				fDisplay_Level = 1;
				bRemote_received_code = 0xB1;
			}
			bRemote_received_code = bCmdLow;
			fRemote_pressed = 0;
			fRemote_processed = 1;
		}
	}
}

uint8_t remote_task(void)
{
	// if(fRemote_pressed == 1)
	// {
	// 	fRemote_processed = 0;
	// 	return 1;
	// }
	if(fRemote_pressed == 1)
	{
		if(soundCt.bSoundMode != SOUND_MODE_DIGITAL)
		{
			if(bCmdLow == 0x50/*0x6D*/)
			{
				soundCt.bSoundMenu = 0xA0;
			
				bDisplay_flag.byte_access &= 16;
				fDisplay_MenuUpdate = 1;
				fDisplay_SmartRGB = 1;
				fDisplay_Level = 1;
				bRemote_received_code = 0xB1;
				bSoundMenu_tasktick = MCUTICK_MS(9000);
			}
			else if(bCmdLow == 0x51/*0x6E*/)
			{
				soundCt.bSoundMenu = 0xA0;
			
				bDisplay_flag.byte_access &= 16;
				fDisplay_MenuUpdate = 1;
				fDisplay_SmartRGB = 1;
				fDisplay_Level = 1;
				bRemote_received_code = 0xB0;
				bSoundMenu_tasktick = MCUTICK_MS(9000);
			}
			// bRemote_received_code = bCmdLow;
			bCmdLow = 0;
			fRemote_pressed = 0;
			return 1;
		}
	}
	return 0;
}

