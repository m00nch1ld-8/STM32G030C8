/**
	******************************************************************************
	* @file			: input_process.h
	* @brief			: Header for input_process.c file.
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
#ifndef __INPUT_PROCESS_H
#define __INPUT_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "type.h"


/* Exported types ------------------------------------------------------------*/
extern sBIT_BYTE_ACCESS  bInput_flag;

extern uint8_t bInput_newkey;
extern uint8_t bInput_oldkey;
extern uint8_t bInput_prckey;
extern uint8_t bInput_key_state;
extern uint8_t bInput_press_state;
extern uint8_t bInput_keypress_counter;
extern uint8_t bInput_prcindex;

extern const uint8_t input_keytofunction[];


/* Exported constants --------------------------------------------------------*/
#define cINPUT_NONE				0xFF

#define fInput_key										bInput_flag.bit_access.bit_0
#define fInput_prckey									bInput_flag.bit_access.bit_1
#define fInput_from_RotEnc								bInput_flag.bit_access.bit_2
#define fInput_from_AdcKey								bInput_flag.bit_access.bit_3
#define fInput_center_Level								bInput_flag.bit_access.bit_4
#define fInput_center_cutoff							bInput_flag.bit_access.bit_5
#define fInput_center_phase								bInput_flag.bit_access.bit_6

// definisi state keypress
#define cINPUT_KEY_NEEDTORELEASE						0
#define cINPUT_KEY_PRESS								1
#define cINPUT_KEY_STILLPRESS							2
#define cINPUT_KEY_PRESS1SEC							3
#define cINPUT_KEY_PRESS1_2SEC							4
#define cINPUT_KEY_PRESS2SEC							5
#define cINPUT_KEY_PRESSMORETHAN2SEC					6
#define cINPUT_KEY_PRESS2_5SEC							7
#define cINPUT_KEY_PRESS5SEC							8
#define cINPUT_KEY_PRESS5_10SEC							9
#define cINPUT_KEY_PRESS10SEC							10
#define cINPUT_KEY_PRESSMORETHAN10SEC					11

// definisi state keyrelease
#define cINPUT_KEY_RELEASEBEFORE						12
#define cINPUT_KEY_RELEASEBEFORE1SEC					13
#define cINPUT_KEY_RELEASE1SEC							14
#define cINPUT_KEY_RELEASE1_2SEC						15
#define cINPUT_KEY_RELEASE2SEC							16
#define cINPUT_KEY_RELEASEAFTER2SEC						17
#define cINPUT_KEY_RELEASE2_5SEC						18
#define cINPUT_KEY_RELEASE5SEC							19
#define cINPUT_KEY_RELEASE5_10SEC						20
#define cINPUT_KEY_RELEASE10SEC							21
#define cINPUT_KEY_RELEASEAFTER10SEC					22
#define cINPUT_KEY_ENCODERTURN							23

// definisi keytype
#define cINPUT_KEY_ONCE									1
#define cINPUT_KEY_REPEAT								2
#define cINPUT_KEY_RELEASELONG							3
#define cINPUT_KEY_ENCODER								4

// Number Key
#define cINPUT_IRKEY_NUM0								0x00	// 0xFF
#define cINPUT_IRKEY_NUM1								0x01	// 0xFE
#define cINPUT_IRKEY_NUM2								0x02	// 0xFD
#define cINPUT_IRKEY_NUM3								0x03	// 0xFC
#define cINPUT_IRKEY_NUM4								0x04	// 0xFB
#define cINPUT_IRKEY_NUM5								0x05	// 0xFA
#define cINPUT_IRKEY_NUM6								0x06	// 0xF9
#define cINPUT_IRKEY_NUM7								0x07	// 0xF8
#define cINPUT_IRKEY_NUM8								0x08	// 0xF7
#define cINPUT_IRKEY_NUM9								0x09	// 0xF6
#define cINPUT_IRKEY_FUNCTION							0x0A	// 0xF5
#define cINPUT_IRKEY_MENU								0x0B	// 0xF4
#define cINPUT_IRKEY_UP									0x0C	// 0xF3
#define cINPUT_IRKEY_DOWN								0x0D	// 0xF2
#define cINPUT_IRKEY_RIGHT								0x0E	// 0xF1
#define cINPUT_IRKEY_LEFT								0x0F	// 0xF0
#define cINPUT_IRKEY_RETURN								0x10	// 0xEF
#define cINPUT_IRKEY_MEMORY								0x11	// 0xEE
#define cINPUT_IRKEY_STOP								0x12	// 0xED
#define cINPUT_IRDSA_PLAYPAUSE							0x13	// 0xEC
#define cINPUT_IRKEY_ENTER								0x14	// 0xEB
#define cINPUT_IRKEY_MUTE								0x15	// 0xEA
#define cINPUT_IRKEY_SLEEP								0x16	// 0xE9
#define cINPUT_IRKEY_POWER								0x17	// 0xE8
#define cINPUT_IRKEY_FASTFWD							0x18	// 0xE7
#define cINPUT_IRKEY_FASTRVS							0x19	// 0xE6
#define cINPUT_IRKEY_NEXT								0x1A	// 0xE5
#define cINPUT_IRKEY_PREV								0x1B	// 0xE4
#define cINPUT_IRKEY_SLOW								0x1C	// 0xE3
#define cINPUT_IRKEY_GOTO								0x1D	// 0xE2
#define cINPUT_IRKEY_REPEAT								0x1E	// 0xE1
#define cINPUT_IRKEY_REPEAT_AB							0x1F	// 0xE0

#define cINPUT_IRKEY_BAZZOKE							0x30	// 0xCF
#define cINPUT_IRKEY_EQUALIZER							0x31	// 0xCE
#define cINPUT_IRKEY_PLAY								0x32	// 0xCD
#define cINPUT_IRKEY_PAUSE								0x33	// 0xCC
#define cINPUT_IRKEY_ECHOMINUS							0x34	// 0xCB
#define cINPUT_IRKEY_SURROUND							0x35	// 0xCA
#define cINPUT_IRKEY_MIC_VOLUMEUP						0x36	// 0xC9
#define cINPUT_IRKEY_MIC_VOLUMEDOWN						0x37	// 0xC8
#define cINPUT_IRKEY_TREBLE								0x38	// 0xC7
#define cINPUT_IRKEY_BASS								0x3A	// 0xC5
#define cINPUT_IRKEY_LIGHT								0x3C	// 0xC3
#define cINPUT_IRKEY_MIDDLE								0x3D	// 0xC2
#define cINPUT_IRKEY_SCAN								0x40	// 0xBF
#define cINPUT_IRKEY_OPENCLOSE							0x41	// 0xBE
#define cINPUT_IRKEY_FLASHRIP							0x42	// 0xBD
#define cINPUT_IRKEY_TITLE								0x43	// 0xBC
#define cINPUT_IRKEY_PAUSE_PAS59						0x44	// 0xBB
#define cINPUT_IRKEY_SUBTITLE							0x45	// 0xBA
#define cINPUT_IRKEY_STEP								0x46	// 0xB9
#define cINPUT_IRKEY_AUDIO								0x47	// 0xB8
#define cINPUT_IRKEY_OSDLANGUAGE						0x4A	// 0xB5
#define cINPUT_IRKEY_ZOOM								0x4B	// 0xB4
#define cINPUT_IRKEY_SETUP								0x4C	// 0xB3
#define cINPUT_IRKEY_CLOCK_TIMER						0x4D	// 0xB2
#define cINPUT_IRKEY_BROWSER							0x4F	// 0xB0
#define cINPUT_IRKEY_VOLUMEUP							0x50	// 0xAF
#define cINPUT_IRKEY_VOLUMEDOWN							0x51	// 0xAE
#define cINPUT_IRKEY_KARAOKE							0x52	// 0xAD
#define cINPUT_IRKEY_ECHOPLUS							0x54	// 0xAB
#define cINPUT_IRKEY_USB_CARD							0x55	// 0xAA
#define cINPUT_IRKEY_VIDEO								0x56	// 0xA9
#define cINPUT_IRKEY_CLEAR								0x57	// 0xA8
#define cINPUT_IRKEY_BLUETOOTH							0x58	// 0xA7
#define cINPUT_IRKEY_SPK_MODE							0x59	// 0xA6
#define cINPUT_IRKEY_LINEIN								0x5A	// 0xA5
#define cINPUT_IRKEY_MP3IN								0x5B	// 0xA4
#define cINPUT_IRKEY_TUNER								0x5C	// 0xA3
#define cINPUT_IRKEY_SBASS								0x5D	// 0xA2

#define cINPUT_IRKEY_SMART_VOLUMEUP						0x60	// 0x9F
#define cINPUT_IRKEY_SMART_VOLUMEDOWN					0x61	// 0x9E
#define cINPUT_IRKEY_OPTIC								0x66	// 0x99
#define cINPUT_IRKEY_HOME								0x67	// 0x98
#define cINPUT_IRKEY_SCAN2								0x68	// 0x97
#define cINPUT_IRKEY_SMART								0x6A	// 0x95
#define cINPUT_IRKEY_WMIC								0x6B	// 0x94
#define cINPUT_IRKEY_TWS								0x6C	// 0x93

#define cINPUT_LKKEY_LEVEL								0xA0
#define cINPUT_LKKEY_CUT_OFF							0xA1
#ifdef USE_SOUND_SHIFT_EN
#define cINPUT_LKKEY_PHASE								0xA2
#else
#define cINPUT_LKKEY_POLAR								0xA2
#endif
#define cINPUT_LKKEY_MODE								0xA3
#define cINPUT_LKKEY_CENTER								0xA4
#define cINPUT_LKKEY_DIAL_DOWN							0xB0
#define cINPUT_LKKEY_DIAL_UP							0xB1
#define cINPUT_SPP_LEVEL								0xE0
#define cINPUT_SPP_FREQ									0xE1
#ifdef USE_SOUND_SHIFT_EN
#define cINPUT_SPP_PHASE								0xE2
#else
#define cINPUT_SPP_POLAR								0xE2
#endif
#define cINPUT_SPP_LFE									0xE3


/* Exported macro ------------------------------------------------------------*/
#define MCUTICK_MS(MS)				(MS/20)


/* Exported functions prototypes ---------------------------------------------*/
void inputProcess_resetVariable(void);
void inputProcess_init(void);
void inputProcess_scan(void);
void inputProcess_get(void);


#ifdef __cplusplus
}
#endif

#endif /* __INPUT_PROCESS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
