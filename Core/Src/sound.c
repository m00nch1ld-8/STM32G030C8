#include "stm32g0xx_hal.h"
#include "type.h"
#include "sound.h"
#include "display.h"
#include "input_process.h"
#include "system.h"

#ifdef USE_BREAKPOINT_EN
#include "eeprom.h"
#endif
#ifdef SOUND_INPUT_PCM9211
#include "pcm9211.h"
#endif
#ifdef SOUND_OUTPUT_TAS5548
#include "tas5548.h"
#endif


uint16_t bSoundMenu_tasktick;
SoundContext soundCt;

void input_sound_init(void)
{
#ifdef SOUND_INPUT_PCM9211
    pcm9211_init();
#endif
}

void output_sound_init(void)
{
#ifdef SOUND_OUTPUT_TAS5548
	tas5548_init();
#endif
}

void sound_init(void)
{
#ifdef USE_BREAKPOINT_EN
	soundCt.bEepromFlag = I2C_STAT_BUSY;

	eeprom_init();

	if(soundCt.bEepromFlag == I2C_STAT_OK)
	{
		eeprom_read_byte(EPPROM_ADR_LEVEL, 4);

		soundCt.bSoundLevel = bEep_buf[0];
		if(soundCt.bSoundLevel > MAX_LEVEL_VOL)
		{
			soundCt.bSoundLevel = 10;
			fEeprom_Level = 1;
			bSoundMenu_tasktick = MCUTICK_MS(5000);
		}

		soundCt.bSoundCutOff = bEep_buf[1];
		if(soundCt.bSoundCutOff > MAX_FREQ_CUTOFF)
		{
			soundCt.bSoundCutOff = 0;
			fEeprom_CutOff = 1;
			bSoundMenu_tasktick = MCUTICK_MS(5000);
		}

	#ifdef USE_SOUND_SHIFT_EN
		soundCt.bSoundPhase = bEep_buf[2];
		if(soundCt.bSoundPhase > MAX_PHASE_LEVEL)
		{
			soundCt.bSoundPhase = 0;
			fEeprom_Phase = 1;
			bSoundMenu_tasktick = MCUTICK_MS(5000);
		}
	#else
		soundCt.bSoundPolar = bEep_buf[2];
		if(soundCt.bSoundPolar > 1)
		{
			soundCt.bSoundPolar = 0;
			fEeprom_Polar = 1;
			bSoundMenu_tasktick = MCUTICK_MS(5000);
		}
	#endif

		soundCt.bSoundMode = bEep_buf[3];
		if(soundCt.bSoundMode > 1)
		{
			soundCt.bSoundMode = 0;
			fEeprom_Mode = 1;
			bSoundMenu_tasktick = MCUTICK_MS(5000);
		}
		if(soundCt.bSoundMode == 1)
		{
			fDisplay_MenuUpdate = 1;
			fDisplay_SmartRGB = 1;
			fDisplay_Mode = 1;
		}
		soundCt.bSoundLevel_bak = soundCt.bSoundLevel;
		soundCt.bSoundCutOff_bak = soundCt.bSoundCutOff;
	#ifdef USE_SOUND_SHIFT_EN
		soundCt.bSoundPhase_bak = soundCt.bSoundPhase;
	#else
		soundCt.bSoundPolar_bak = soundCt.bSoundPolar;
	#endif
		soundCt.bSoundMode_bak = soundCt.bSoundMode;
	}
	else
#endif
	{
		soundCt.bSoundMenu = 0xFF;
		soundCt.bSoundLevel = 10;
		soundCt.bSoundLevel_bak = soundCt.bSoundLevel;
		soundCt.bSoundCutOff = 0;
		soundCt.bSoundCutOff_bak = soundCt.bSoundCutOff;
	#ifdef USE_SOUND_SHIFT_EN
		soundCt.bSoundPhase = 0;
		soundCt.bSoundPhase_bak = soundCt.bSoundPhase;
	#else
		soundCt.bSoundPolar = 0;
		soundCt.bSoundPolar_bak = soundCt.bSoundPolar;
	#endif
		soundCt.bSoundMode = 0;
		soundCt.bSoundMode_bak = soundCt.bSoundMode;
	}
}

void sound_volume(uint8_t volLevel)
{
	if(soundCt.bSoundLevel != soundCt.bSoundLevel_bak)
	{
		soundCt.bSoundLevel_bak = soundCt.bSoundLevel;
		tas5548_masterVolume(volLevel);
		fEeprom_Level = 1;
	}
}

void sound_freqCutOff(uint8_t freqCut)
{
	if(soundCt.bSoundCutOff != soundCt.bSoundCutOff_bak)
	{
		soundCt.bSoundCutOff_bak = soundCt.bSoundCutOff;
		tas5548_freqCutOff(freqCut);
		fEeprom_CutOff = 1;
	}
}

#ifdef USE_SOUND_SHIFT_EN
void sound_phase(uint8_t phase)
{
	if(soundCt.bSoundPhase != soundCt.bSoundPhase_bak)
	{
		soundCt.bSoundPhase_bak = soundCt.bSoundPhase;
		adau_shiftPhase(phase);
		fEeprom_Phase = 1;
	}
}
#else
void sound_polar(uint8_t polar)
{
#ifdef SMOOTH_POLARITY_EN
	uint8_t volChange = 0;
#endif
	if(soundCt.bSoundPolar != soundCt.bSoundPolar_bak)
	{
		soundCt.bSoundPolar_bak = soundCt.bSoundPolar;
#ifdef SMOOTH_POLARITY_EN
		volChange = soundCt.bSoundLevel;
		while(volChange != 0)
		{
			volChange -= 2;
			if (volChange == 0xFF) volChange = 0;
			tas5548_masterVolume(volChange);
			HAL_Delay(15);
		}
#endif
		tas5548_polarity(polar);
		fEeprom_Polar = 1;
#ifdef SMOOTH_POLARITY_EN
		while(volChange < soundCt.bSoundLevel)
		{
			volChange += 2;
			if (volChange > soundCt.bSoundLevel) volChange = soundCt.bSoundLevel;
			tas5548_masterVolume(volChange);
			HAL_Delay(15);
		}
#endif
	}
}
#endif

void sound_mode(uint8_t mode)
{
	if(soundCt.bSoundMode != soundCt.bSoundMode_bak)
	{
		soundCt.bSoundMode_bak = soundCt.bSoundMode;
		tas5548_mode(mode);
		fEeprom_Mode = 1;
	}
}

void sound_task(void)
{
    if(bSoundMenu_tasktick == 0) 
    {
		if(soundCt.bSoundMenu != 0xFF)
		{
			soundCt.bSoundMenu      = 0xFF;
			fDisplay_Level  = 0;
			fDisplay_CutOff = 0;
	#ifdef USE_SOUND_SHIFT_EN
			fDisplay_Phase  = 0;
	#else
			fDisplay_Polar  = 0;
	#endif
			// fDisplay_Mode  = 0;
			fDisplay_MenuUpdate = 1;
			fDisplay_SmartRGB = 1;
		}

#ifdef USE_BREAKPOINT_EN
		if(fEeprom_Level)
		{
			eeprom_write_byte(EPPROM_ADR_LEVEL, soundCt.bSoundLevel);
			HAL_Delay(10);
			fEeprom_Level = 0;
		}
		if(fEeprom_CutOff)
		{
			eeprom_write_byte(EPPROM_ADR_FREQ, soundCt.bSoundCutOff);
			HAL_Delay(10);
			fEeprom_CutOff = 0;
		}
	#ifdef USE_SOUND_SHIFT_EN
		if(fEeprom_Phase)
		{
			eeprom_write_byte(EPPROM_ADR_PHASE, soundCt.bSoundPhase);
			HAL_Delay(10);
			fEeprom_Phase = 0;
		}
	#else
		if(fEeprom_Polar)
		{
			eeprom_write_byte(EPPROM_ADR_POLAR, soundCt.bSoundPolar);
			HAL_Delay(10);
			fEeprom_Polar = 0;
		}
	#endif
		if(fEeprom_Mode)
		{
			eeprom_write_byte(EPPROM_ADR_MODE, soundCt.bSoundMode);
			HAL_Delay(10);
			fEeprom_Mode = 0;
		}
#endif
    }
	else
	{
		switch (soundCt.bSoundMenu)
		{
		
			case cINPUT_LKKEY_LEVEL:
				sound_volume(soundCt.bSoundLevel);
				break;

			case cINPUT_LKKEY_CUT_OFF:
				sound_freqCutOff(soundCt.bSoundCutOff);
				break;

	#ifdef USE_SOUND_SHIFT_EN
			case cINPUT_LKKEY_PHASE:
				sound_phase(soundCt.bSoundPhase);
				break;
	#else
			case cINPUT_LKKEY_POLAR:
				sound_polar(soundCt.bSoundPolar);
				break;
	#endif

			case cINPUT_LKKEY_MODE:
				sound_mode(soundCt.bSoundMode);
				break;

			default:
				break;
		}
	}
}
















