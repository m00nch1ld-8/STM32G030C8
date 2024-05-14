#include "stm32g0xx_hal.h"
#include "type.h"
#include "process.h"
// #include "system.h"
#include "input_process.h"
#include "sound.h"
#include "display.h"

uint8_t dPrc_index;
uint8_t dPrc_pressstate;


void prc_manager(sSystem_input *sManager)
{
	dPrc_index			= sManager->index;
	dPrc_pressstate		= sManager->press_state;

	if(dPrc_index == cINPUT_NONE) return;

#ifdef USE_SOUND_SHIFT_EN
	if((dPrc_index == cINPUT_LKKEY_LEVEL || dPrc_index == cINPUT_LKKEY_CUT_OFF || dPrc_index == cINPUT_LKKEY_PHASE) && soundCt.bSoundMode != SOUND_MODE_DIGITAL)
#else
	if((dPrc_index == cINPUT_LKKEY_LEVEL || dPrc_index == cINPUT_LKKEY_CUT_OFF || dPrc_index == cINPUT_LKKEY_POLAR) && soundCt.bSoundMode != SOUND_MODE_DIGITAL)
#endif
	{
		soundCt.bSoundMenu = dPrc_index;// - 0xA0;
	
		bDisplay_flag.byte_access &= 16;
		fDisplay_MenuUpdate = 1;
		fDisplay_SmartRGB = 1;
		if(dPrc_index == cINPUT_LKKEY_LEVEL) fDisplay_Level = 1;
		else if (dPrc_index == cINPUT_LKKEY_CUT_OFF) fDisplay_CutOff = 1;
	#ifdef USE_SOUND_SHIFT_EN
		else if (dPrc_index == cINPUT_LKKEY_PHASE) fDisplay_Phase = 1;
	#else
		else if (dPrc_index == cINPUT_LKKEY_POLAR) fDisplay_Polar = 1;
	#endif
		// else if (dPrc_index == cINPUT_LKKEY_MODE) fDisplay_Mode = 1;
		// else if (dPrc_index == cINPUT_LKKEY_CENTER) fDisplay_Center = 1;

		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}

	if(dPrc_index == cINPUT_LKKEY_MODE && dPrc_pressstate == cINPUT_KEY_STILLPRESS)
	{
		soundCt.bSoundMenu = dPrc_index;
		bDisplay_flag.byte_access &= 16;
		fDisplay_MenuUpdate = 1;
		fDisplay_SmartRGB = 1;
		if(soundCt.bSoundMode)
		{
			fDisplay_Mode = 0;
			soundCt.bSoundMode = SOUND_MODE_ANALOG;
		}
		else
		{
			fDisplay_Mode = 1;
			soundCt.bSoundMode = SOUND_MODE_DIGITAL;
		}
		bSoundMenu_tasktick = MCUTICK_MS(5000);
	}

	if((dPrc_index == cINPUT_LKKEY_DIAL_UP || dPrc_index == cINPUT_LKKEY_DIAL_DOWN) && bSoundMenu_tasktick != 0)
	{
		switch (soundCt.bSoundMenu)
		{
			case cINPUT_LKKEY_LEVEL:
				if(soundCt.bSoundMode != SOUND_MODE_DIGITAL)
				{
					if(dPrc_index == cINPUT_LKKEY_DIAL_UP)
					{
						soundCt.bSoundLevel++;
						if(soundCt.bSoundLevel > MAX_LEVEL_VOL) soundCt.bSoundLevel = MAX_LEVEL_VOL;
						if(fInput_center_Level) fInput_center_Level = 0;
					}
					else if(dPrc_index == cINPUT_LKKEY_DIAL_DOWN)
					{
						if(soundCt.bSoundLevel > 0 && soundCt.bSoundLevel < MAX_LEVEL_VOL+1) soundCt.bSoundLevel--;
						else soundCt.bSoundLevel = 0;
					}
				}
				break;

			case cINPUT_LKKEY_CUT_OFF:
				if(soundCt.bSoundMode != SOUND_MODE_DIGITAL)
				{
					if(dPrc_index == cINPUT_LKKEY_DIAL_UP)
					{
						soundCt.bSoundCutOff++;
						if(soundCt.bSoundCutOff > MAX_FREQ_CUTOFF) soundCt.bSoundCutOff = MAX_FREQ_CUTOFF;
						if(fInput_center_cutoff) fInput_center_cutoff = 0;
					}
					else if(dPrc_index == cINPUT_LKKEY_DIAL_DOWN)
					{
						if(soundCt.bSoundCutOff > 0 && soundCt.bSoundCutOff < MAX_FREQ_CUTOFF+1) soundCt.bSoundCutOff--;
						else soundCt.bSoundCutOff = 0;
					}
				}
				break;

	#ifdef USE_SOUND_SHIFT_EN
			case cINPUT_LKKEY_PHASE:
				if(soundCt.bSoundMode != SOUND_MODE_DIGITAL)
				{
					if(dPrc_index == cINPUT_LKKEY_DIAL_UP)
					{
						soundCt.bSoundPhase++;
						if(soundCt.bSoundPhase > MAX_PHASE_LEVEL) soundCt.bSoundPhase = MAX_PHASE_LEVEL;
						if(fInput_center_phase) fInput_center_phase = 0;
					}
					else if(dPrc_index == cINPUT_LKKEY_DIAL_DOWN)
					{
						if(soundCt.bSoundPhase > 0 && soundCt.bSoundPhase < MAX_PHASE_LEVEL+1) soundCt.bSoundPhase--;
						else soundCt.bSoundPhase = 0;
					}
				}
				break;
	#else
			case cINPUT_LKKEY_POLAR:
				if(soundCt.bSoundMode != SOUND_MODE_DIGITAL)
				{
					if(dPrc_index == cINPUT_LKKEY_DIAL_UP)
					{
						soundCt.bSoundPolar = 1;
					}
					else if(dPrc_index == cINPUT_LKKEY_DIAL_DOWN)
					{
						soundCt.bSoundPolar = 0;
					}
				}
				break;
	#endif

			// case cINPUT_LKKEY_MODE:
			// 	if(dPrc_index == cINPUT_LKKEY_DIAL_UP)
			// 	{
			// 		soundCt.bSoundMode = SOUND_MODE_DIGITAL;
			// 	}
			// 	else if(dPrc_index == cINPUT_LKKEY_DIAL_DOWN)
			// 	{
			// 		soundCt.bSoundMode = SOUND_MODE_ANALOG;
			// 	}
			// 	break;

			default:
				break;
		}
		fDisplay_SmartRGB = 1;
		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}

	if(dPrc_index == cINPUT_LKKEY_CENTER && bSoundMenu_tasktick != 0 && dPrc_pressstate == cINPUT_KEY_PRESS)
	{
		switch (soundCt.bSoundMenu)
		{
			case cINPUT_LKKEY_LEVEL:
				if(!fInput_center_Level)
				{
					soundCt.bSoundLevel_center = soundCt.bSoundLevel;
					soundCt.bSoundLevel = 0;
					fInput_center_Level = 1;
				}
				else
				{
					soundCt.bSoundLevel = soundCt.bSoundLevel_center;
					soundCt.bSoundLevel_center = 0;
					fInput_center_Level = 0;
				}
				break;

			case cINPUT_LKKEY_CUT_OFF:
				if(!fInput_center_cutoff)
				{
					soundCt.bSoundCutOff_center = soundCt.bSoundCutOff;
					soundCt.bSoundCutOff = 0;
					fInput_center_cutoff = 1;
				}
				else
				{
					soundCt.bSoundCutOff = soundCt.bSoundCutOff_center;
					soundCt.bSoundCutOff_center = 0;
					fInput_center_cutoff = 0;
				}
				break;

	#ifdef USE_SOUND_SHIFT_EN
			case cINPUT_LKKEY_PHASE:
				soundCt.bSoundPhase = 0;
				if(!fInput_center_phase)
				{
					soundCt.bSoundPhase_center = soundCt.bSoundPhase;
					soundCt.bSoundPhase = 0;
					fInput_center_phase = 1;
				}
				else
				{
					soundCt.bSoundCutOff = soundCt.bSoundPhase_center;
					soundCt.bSoundPhase_center = 0;
					fInput_center_phase = 0;
				}
				break;
	#else
			case cINPUT_LKKEY_POLAR:
				soundCt.bSoundPolar = 0;
				break;
	#endif

			default:
				// soundCt.bSoundMode = 0;
				break;
		}
		fDisplay_SmartRGB = 1;
		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}

	if(dPrc_index == cINPUT_SPP_LEVEL)
	{
		soundCt.bSoundMenu = cINPUT_LKKEY_LEVEL;
		if(fInput_center_Level) fInput_center_Level = 0;
		bDisplay_flag.byte_access &= 16;
		fDisplay_MenuUpdate = 1;
		fDisplay_SmartRGB = 1;
		fDisplay_Level = 1;
		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}

	if(dPrc_index == cINPUT_SPP_FREQ)
	{
		soundCt.bSoundMenu = cINPUT_LKKEY_CUT_OFF;
		if(fInput_center_cutoff) fInput_center_cutoff = 0;
		bDisplay_flag.byte_access &= 16;
		fDisplay_MenuUpdate = 1;
		fDisplay_SmartRGB = 1;
		fDisplay_CutOff = 1;
		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}

#ifdef USE_SOUND_SHIFT_EN
	if(dPrc_index == cINPUT_SPP_PHASE)
	{
		soundCt.bSoundMenu = cINPUT_LKKEY_PHASE;
		if(fInput_center_phase) fInput_center_phase = 0;
		bDisplay_flag.byte_access &= 16;
		fDisplay_MenuUpdate = 1;
		fDisplay_SmartRGB = 1;
		fDisplay_Phase = 1;
		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}
#else
	if(dPrc_index == cINPUT_SPP_POLAR)
	{
		soundCt.bSoundMenu = cINPUT_LKKEY_POLAR;
		bDisplay_flag.byte_access &= 16;
		fDisplay_MenuUpdate = 1;
		fDisplay_SmartRGB = 1;
		fDisplay_Polar = 1;
		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}
#endif

	if(dPrc_index == cINPUT_SPP_LFE)
	{
		soundCt.bSoundMenu = cINPUT_LKKEY_MODE;
		bDisplay_flag.byte_access &= 16;
		fDisplay_MenuUpdate = 1;
		fDisplay_SmartRGB = 1;
		if(soundCt.bSoundMode)
		{
			fDisplay_Mode = 0;
		}
		else
		{
			fDisplay_Mode = 1;
		}
		bSoundMenu_tasktick = MCUTICK_MS(9000);
	}
	dPrc_index = 0;
}

void prc_handler_command_apk(uint8_t bSPP_cmd, uint8_t bSPP_dat)
{
	switch(bSPP_cmd)
	{
		case 0x00:	//SLAVE_SET_VOL
			soundCt.bSoundLevel = bSPP_dat;
			fInput_prckey = 1;
			bInput_prckey = cINPUT_SPP_LEVEL;
			break;

		case 0x01:	//SLAVE_GET_VOL
			break;

		case 0x06:	//SLAVE_SET_SWF_FREQ
			soundCt.bSoundCutOff = bSPP_dat;
			fInput_prckey = 1;
			bInput_prckey = cINPUT_SPP_FREQ;
			break;

		case 0x07:	//SLAVE_GET_SWF_FREQ
			break;

		case 0x08:	//SLAVE_SET_SWF_PHASE
	#ifdef USE_SOUND_SHIFT_EN
			soundCt.bSoundPhase = bSPP_dat;
			bInput_prckey = cINPUT_SPP_PHASE;
	#else
			soundCt.bSoundPolar = bSPP_dat;
			bInput_prckey = cINPUT_SPP_POLAR;
	#endif
			fInput_prckey = 1;
			break;

		case 0x09:	//SLAVE_GET_SWF_PHASE
			break;

		case 0x0A:	//SLAVE_SET_SWF_LFE
			soundCt.bSoundMode = bSPP_dat;
			fInput_prckey = 1;
			bInput_prckey = cINPUT_SPP_LFE;
			break;

		case 0x0B:	//SLAVE_GET_SWF_LFE
			break;
			
		default:
			break;
	}
}







































