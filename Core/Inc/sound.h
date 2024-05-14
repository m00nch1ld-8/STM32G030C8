/**
  ******************************************************************************
  * @file			: sound.h
  * @brief			: Header for sound.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version		: v1.0.0
  * @date created	: 2023-07-31
  *
  * @author modified: 
  * @date modified	: 2023-07-31
  * 
  * @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SOUND_H
#define __SOUND_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"


/* Exported types ------------------------------------------------------------*/
typedef struct _SoundContext
{
	uint8_t		bSoundMenu;
	uint8_t		bSoundMode;
	uint8_t		bSoundMode_bak;
	uint8_t		bSoundLevel;
	uint8_t		bSoundLevel_bak;
	uint8_t		bSoundLevel_center;
	uint8_t		bSoundCutOff;
	uint8_t		bSoundCutOff_bak;
	uint8_t		bSoundCutOff_center;
#ifdef USE_SOUND_SHIFT_EN
	uint8_t		bSoundPhase;
	uint8_t		bSoundPhase_bak;
	uint8_t		bSoundPhase_center;
	uint8_t		bDspSoundFlag;
#else
	uint8_t		bSoundPolar;
	uint8_t		bSoundPolar_bak;
#endif
	uint8_t		bInputSoundFlag;
	uint8_t		bOutputSoundFlag;
#ifdef USE_BREAKPOINT_EN
	uint8_t   bEepromFlag;
#endif
}SoundContext;

extern SoundContext soundCt;
extern uint16_t bSoundMenu_tasktick;

/* Exported constants --------------------------------------------------------*/
#define	SOUND_MODE_ANALOG		0
#define SOUND_MODE_DIGITAL		1

#define MAX_LEVEL_VOL     		32
#define MAX_FREQ_CUTOFF			30
#define NORMAL_POLARITY			0xE0
#define INVERT_POLARITY			0xF0
#define MAX_PHASE_LEVEL     10


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void sound_init(void);
void input_sound_init(void);
void output_sound_init(void);
void sound_task(void);


#ifdef __cplusplus
}
#endif

#endif /* __SOUND_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
