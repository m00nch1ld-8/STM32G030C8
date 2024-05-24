#include "stm32g0xx_hal.h"
#include "config.h"
#include "display.h"
#include "sound.h"
#include "main.h"
#include "system.h"

#ifdef USE_SMARTLED_EN
#include "rgb_smartled.h"
// #include "signal_process.h"
#endif

#ifdef SOUND_INPUT_PCM9211
extern void pcm9211_mainOutput(void);
#endif
extern void tas5548_mode(uint8_t iMode);

uint8_t binaryNum[8];

sBIT_BYTE_ACCESS bDisplay_flag;
void decToBin(uint8_t conv)
{
	uint8_t i = 0;

	while(conv > 0)
	{
		binaryNum[i] = conv % 2;
		conv = conv / 2;
		i++;
	}

}

void display_softwareVersion(void)
{
#ifdef USE_SMARTLED_EN
	ws2812_init();

	decToBin(SOFTWARE_VERSION);

	if(binaryNum[7] == 1)
	{
		ws2812_setLED(3, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(3, 0, 0, 0);
	}

	if(binaryNum[6] == 1)
	{
		ws2812_setLED(4, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(4, 0, 0, 0);
	}

	if(binaryNum[5] == 1)
	{
		ws2812_setLED(5, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(5, 0, 0, 0);
	}

	if(binaryNum[4] == 1)
	{
		ws2812_setLED(6, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(6, 0, 0, 0);
	}

	if(binaryNum[3] == 1)
	{
		ws2812_setLED(7, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(7, 0, 0, 0);
	}

	if(binaryNum[2] == 1)
	{
		ws2812_setLED(8, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(8, 0, 0, 0);
	}

	if(binaryNum[1] == 1)
	{
		ws2812_setLED(9, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(9, 0, 0, 0);
	}

	if(binaryNum[0] == 1)
	{
		ws2812_setLED(10, 255, 255, 255);
	}
	else
	{
		ws2812_setLED(10, 0, 0, 0);
	}
#endif
}

void display_init(void)
{
#ifdef USE_SMARTLED_EN
	ws2812_init();

	#ifdef USE_FFT_SIGNAL_PROCESS
	spectrume_init();
	#endif

	ws2812_setLED(bPos_Led_Level, 0, 255, 0);
	ws2812_setLED(bPos_Led_CutOff, 255, 0, 255);
#ifdef USE_SOUND_SHIFT_EN
	ws2812_setLED(bPos_Led_Phase, 0, 255, 255);
#else
	ws2812_setLED(bPos_Led_Polar, 0, 255, 255);
#endif
	ws2812_setLED(bPos_Led_Mode, 255, 80, 0);
#endif
}

void finished_init(void)
{
	if(!fSystem_flag)
	{
#ifdef SOUND_INPUT_PCM9211
		pcm9211_mainOutput();
#endif
#ifdef SOUND_OUTPUT_TAS5548
		tas5548_mode(soundCt.bSoundMode);
#endif
		ws2812_setLED(bPos_Led_Level, 0, 0, 0);
		ws2812_setLED(bPos_Led_CutOff, 0, 0, 0);
#ifdef USE_SOUND_SHIFT_EN
		ws2812_setLED(bPos_Led_Phase, 0, 0, 0);
#else
		ws2812_setLED(bPos_Led_Polar, 0, 0, 0);
#endif
		ws2812_setLED(bPos_Led_Mode, 0, 0, 0);
	}
	else
	{
		//tunggu Sigit
		HAL_Delay(100);
	}
}

void display_task(void)
{
	if(fDisplay_MenuUpdate)
	{
		ws2812_setLED(bPos_Led_Level, 0, 0, 0);
		ws2812_setLED(bPos_Led_CutOff, 0, 0, 0);
	#ifdef USE_SOUND_SHIFT_EN
		ws2812_setLED(bPos_Led_Phase, 0, 0, 0);
	#else
		ws2812_setLED(bPos_Led_Polar, 0, 0, 0);
	#endif
		// ws2812_setLED(bPos_Led_Mode, 0, 0, 0);
		if(fDisplay_Level)
		{
			ws2812_setLED(bPos_Led_Level, 0, 255, 0);
		}
		else if(fDisplay_CutOff)
		{
			ws2812_setLED(bPos_Led_CutOff, 255, 0, 255);
		}
	#ifdef USE_SOUND_SHIFT_EN
		else if(fDisplay_Phase)
		{
			ws2812_setLED(bPos_Led_Phase, 0, 255, 255);
		}
	#else
		else if(fDisplay_Polar)
		{
			ws2812_setLED(bPos_Led_Polar, 0, 255, 255);
		}
	#endif
		else if(fDisplay_Mode)
		{
			if(soundCt.bSoundMode)
			{
				ws2812_setLED(bPos_Led_Mode, 255, 80, 0);
			}
			else
			{
				ws2812_setLED(bPos_Led_Mode, 0, 0, 0);
			}
			// fDisplay_Mode = 0;
		}
		fDisplay_MenuUpdate = 0;
	}

	if(fDisplay_SmartRGB)
	{
		if(fDisplay_Level)
		{
			ws2812_displayLevel(soundCt.bSoundLevel);
		}
		else if(fDisplay_CutOff)
		{
			ws2812_displayCutOff(soundCt.bSoundCutOff);
		}
	#ifdef USE_SOUND_SHIFT_EN
		else if(fDisplay_Phase)
		{
			ws2812_displayPhase(soundCt.bSoundPhase);
		}
	#else
		else if(fDisplay_Polar)
		{
			ws2812_displayPolar(soundCt.bSoundPolar);
		}
	#endif
		else if(fDisplay_Mode)
		{
			ws2812_displayMode(soundCt.bSoundMode);
		}
		else
		{
			ws2812_init();
			ws2812_setLED(5, 127, 0, 0);
			ws2812_Send();
		}

		fDisplay_SmartRGB = 0;
	}

	#ifdef USE_FFT_SIGNAL_PROCESS
	spectrume_task();
	#endif
}
































