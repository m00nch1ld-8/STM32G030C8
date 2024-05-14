#include "stm32g0xx_hal.h"
#include "input_process.h"
#ifdef USE_ROTARY_ENCODER
#include "rotary_encoder.h"
#endif
#ifdef USE_ADC_KEY
#include "adc_key.h"
#endif



const uint8_t input_keytofunction[] =
{
	cINPUT_LKKEY_LEVEL		,
	cINPUT_LKKEY_CUT_OFF	,
#ifdef USE_SOUND_SHIFT_EN
	cINPUT_LKKEY_PHASE		,
#else
	cINPUT_LKKEY_POLAR		,
#endif
	cINPUT_LKKEY_MODE		,
	cINPUT_LKKEY_CENTER		,
	cINPUT_LKKEY_DIAL_DOWN	,
	cINPUT_LKKEY_DIAL_UP	,
};


sBIT_BYTE_ACCESS bInput_flag;

uint8_t	bInput_newkey;
uint8_t	bInput_oldkey;
uint8_t	bInput_prckey;
uint8_t	bInput_key_state;
uint8_t	bInput_press_state;
uint8_t	bInput_keypress_counter;			// place into interrupt timer 20ms
uint8_t	bInput_prcindex;

void inputProcess_resetVariable(void)
{
	fInput_key				= 0;
	fInput_prckey			= 0;
	fInput_from_RotEnc		= 0;
	fInput_from_AdcKey		= 0;
	fInput_center_Level		= 0;
	fInput_center_cutoff	= 0;

	bInput_key_state	= 0x00;
	bInput_press_state	= 0x00;

	bInput_newkey		= 0xff;
	bInput_oldkey		= 0xff;
	bInput_prckey		= 0xff;
}

void inputProcess_init(void)
{
#ifdef USE_ROTARY_ENCODER
	rotaryEncoder_init();
#endif

#ifdef USE_ADC_KEY
	adcKey_init();
#endif

	inputProcess_resetVariable();
}

void inputProcess_scan(void)
{
	fInput_from_RotEnc	= 0;
	fInput_from_AdcKey	= 0;
	fInput_key = 0;
	bInput_newkey   = 0x00;
	
#ifdef USE_ROTARY_ENCODER
	if(rotaryEncoder_task() == 1)
	{
		bInput_newkey = rotaryEncoder_getReceived_code();
		fInput_key = 1;
	}
#endif

#ifdef USE_ADC_KEY
	if(adcKey_task() == 1)
	{
		bInput_newkey = adcKey_getReceived_code();
		fInput_key = 1;
	}
#endif
}

void inputProcess_get(void)
{
	/* tunggu key direlease */
	if(bInput_key_state == 0)
	{
		bInput_keypress_counter = 0;
		bInput_oldkey = 0xFF;

		inputProcess_scan();

		if(!fInput_key) bInput_key_state++;

		return;
	}

	/* tunggu key ditekan */
	if(bInput_key_state == 1)
	{
		inputProcess_scan();

		if(fInput_key && (bInput_keypress_counter == 0))
		{
			if(bInput_oldkey == bInput_newkey)
			{
				bInput_prckey = bInput_newkey;
				bInput_press_state = cINPUT_KEY_PRESS;
				fInput_prckey = 1;
				bInput_keypress_counter = MCUTICK_MS(200);
				bInput_key_state++;
			}
			else
			{
				bInput_oldkey = bInput_newkey;
			}
		}
		return;
	}

	/* cek key masih ditekan sebelum 600ms */
	if(bInput_key_state <= 3)
	{
		inputProcess_scan();

		if(fInput_key && (bInput_newkey == bInput_oldkey) && (bInput_keypress_counter == 0))
		{
			bInput_prckey = bInput_newkey;
			bInput_keypress_counter = MCUTICK_MS(200);
			bInput_key_state++;
		}

		if(!fInput_key)
		{
			bInput_key_state = 0;
			bInput_press_state = cINPUT_KEY_RELEASEBEFORE;
			fInput_prckey = 1;
		}

		return;
	}

	/* cek key masih ditekan sesudah 600ms */
	if(bInput_key_state == 4)
	{
		inputProcess_scan();

		if(fInput_key && (bInput_newkey == bInput_oldkey) && (bInput_keypress_counter == 0))
		{
			bInput_prckey = bInput_newkey;
			bInput_keypress_counter = MCUTICK_MS(200);
			bInput_press_state = cINPUT_KEY_STILLPRESS;
			fInput_prckey = 1;
			bInput_key_state++;
		}

		if(!fInput_key)
		{
			bInput_key_state = 0;
			bInput_press_state = cINPUT_KEY_RELEASEBEFORE;
			fInput_prckey = 1;
		}

		return;
	}

	/* cek key masih ditekan sesudah 1sec */
	if(bInput_key_state == 6)
	{
		inputProcess_scan();

		if(fInput_key && (bInput_newkey == bInput_oldkey) && (bInput_keypress_counter == 0))
		{
			bInput_prckey = bInput_newkey;
			bInput_keypress_counter = MCUTICK_MS(200);
			bInput_press_state = cINPUT_KEY_PRESS1SEC;
			fInput_prckey = 1;
			bInput_key_state++;
		}

		if(!fInput_key)
		{
			bInput_key_state = 0;
			bInput_press_state = cINPUT_KEY_RELEASE1SEC;
			fInput_prckey = 1;
		}

		return;
	}

	/* repeat key setiap 200ms */
	if(bInput_key_state <= 9)
	{
		inputProcess_scan();

		if(fInput_key && (bInput_newkey == bInput_oldkey) && (bInput_keypress_counter == 0))
		{
			bInput_prckey = bInput_newkey;
			bInput_keypress_counter = MCUTICK_MS(200);
			bInput_press_state = cINPUT_KEY_PRESS1_2SEC;
			fInput_prckey = 1;
			bInput_key_state++;
		}

		if(!fInput_key)
		{
			bInput_key_state = 0;
			bInput_press_state = cINPUT_KEY_RELEASE1_2SEC;
			fInput_prckey = 1;
		}

		return;
	}

	/* cek apakah key masih ditekan saat 2sec */
	if(bInput_key_state == 10)
	{
		inputProcess_scan();

		if (fInput_key && (bInput_newkey == bInput_oldkey) && (bInput_keypress_counter == 0))
		{
			bInput_prckey = bInput_newkey;
			bInput_keypress_counter = MCUTICK_MS(200);
			bInput_press_state = cINPUT_KEY_PRESS2SEC;
			fInput_prckey = 1;
			bInput_key_state++;
		}

		if (!fInput_key)
		{
			bInput_key_state = 0;
			bInput_press_state = cINPUT_KEY_RELEASE2SEC;
			fInput_prckey = 1;
		}

		return;
	}


	/* cek apakah key masih ditekan setelah lebih dari 2sec */
	if(bInput_key_state == 11)
	{
		inputProcess_scan();

		if(fInput_key && (bInput_newkey == bInput_oldkey) && (bInput_keypress_counter == 0))
		{
			bInput_prckey = bInput_newkey;
			bInput_keypress_counter = MCUTICK_MS(200);
			bInput_press_state = cINPUT_KEY_PRESSMORETHAN2SEC;
			fInput_prckey = 1;
		}

		if(!fInput_key)
		{
			bInput_key_state = 0;
			bInput_press_state = cINPUT_KEY_RELEASEAFTER2SEC;
			fInput_prckey = 1;
		}

		return;
	}
}









