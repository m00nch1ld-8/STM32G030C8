#include "system.h"
#include "input_process.h"
#include "process.h"
//#include "..\inc\process.h"
#include "sound.h"
#ifdef USE_ROTARY_ENCODER
#include "rotary_encoder.h"
#endif
#ifdef USE_ADC_KEY
#include "adc_key.h"
#endif
#ifdef USE_IR_KEY
#include "remote.h"
#endif
#include "display.h"
#include "main.h"
#ifdef USE_BLE_SPP_EN
#include "bt4502.h"
#endif

sSystem_input	sSystem_process;
sBIT_BYTE_ACCESS bSystem_flag = 0;
uint8_t	bSystem_tasktick;
extern bool ledOnOff;
extern void changeLedStat(bool onOff);

#ifdef USE_ADC_KEY
uint8_t	bAdcKey_tasktick;
uint8_t bAdcKey_softwareversion = 0;
#endif

#ifdef USE_SYSTEM_STANDBY
void systemState_standby(void)
{}
#endif	//USE_SYSTEM_STANDBY

void systemState_on(void)
{
	//sound_mute_off();

	while(1)
	{
#if 0 //def USE_ROTARY_ENCODER
    	rotaryEncoder_check();
#endif
// #ifdef USE_ADC_KEY
//     	adcKey_check();
// #endif

#ifdef USE_BLE_SPP_EN
		bt4502_task();
#endif

		if(fInput_prckey)
		{
			if(bInput_prckey < 5)
			{
				sSystem_process.index		= input_keytofunction[bInput_prckey];
				sSystem_process.press_state	= bInput_press_state;

				prc_manager(&sSystem_process);
			}
			else if(bInput_prckey >= 0xB0)
			{
				sSystem_process.index		= bInput_prckey;
				sSystem_process.press_state	= bInput_press_state;

				prc_manager(&sSystem_process);
			}

			bInput_prckey = 0xFF;
			fInput_prckey = 0;
			sSystem_process.index = cINPUT_NONE;
		}

		sound_task();

		display_task();
	}
}

void system_main(void)
{
	bAdcKey_softwareversion = adcKey_softwareVersion();
	if(bAdcKey_softwareversion == 1)
	{
		display_softwareVersion();
	}
	else
	{
		display_init();
	}

	inputProcess_init();

	sound_init();

    input_sound_init();

	output_sound_init();

#ifdef USE_BLE_SPP_EN	
	bt4502_init();
#endif

#ifdef USE_SOUND_SHIFT_EN
	adau_init();
#endif

	finished_init();
	//disp_stby
	//sound_stby
	
	while(1)
	{
#ifdef USE_SYSTEM_STANDBY
		if(dSystem_State == cSYSTEMSTATE_STANDBY)
		{
			//systemState_standby();
		}
		else
#endif	//USE_SYSTEM_STANDBY
		{
			systemState_on();
		}
	}
}










// void changeLedStat(bool onOff)
// {
// 	HAL_GPIO_WritePin(LED_LEVEL_GPIO_Port, LED_LEVEL_Pin, onOff);
// }


void system_timer20ms_handler(void)
{

    inputProcess_get();
    
	if (bInput_keypress_counter != 0)									--bInput_keypress_counter;
	if (bSoundMenu_tasktick != 0)										--bSoundMenu_tasktick;
	if (bSystem_tasktick != 0)											--bSystem_tasktick;
#ifdef USE_ROTARY_ENCODER
	bRotaryEnc_tasktick++;
	if (bRotaryEnc_tasktick > 2)								    	rotaryEncoder_check();
	// rotaryEncoder_check();
#endif
// #ifdef USE_ADC_KEY
// 	bAdcKey_tasktick++;
// 	if (bAdcKey_tasktick > 3)											
// 	{
		adcKey_check();
	// 	bAdcKey_tasktick = 0;
	// }
// #endif
	// ledOnOff = !ledOnOff;
	// changeLedStat(ledOnOff);
}












