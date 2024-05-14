#include "stm32g0xx_hal.h"
#include "type.h"
#include "adc_key.h"


extern ADC_HandleTypeDef hadc1;

sBIT_BYTE_ACCESS bAdcKey_flag;

uint8_t bAdcKey_key;
uint8_t bAdcKeyadc_key;
uint8_t bAdcKey_received_code;
uint8_t bAdcKey_oldreceived_code;

uint8_t adcVal;
uint32_t tempVal;

void adcKey_init(void)
{
	fAdcKey_pressed = 0;

	bAdcKey_key = cADCKEY_NOKEY;
	bAdcKey_received_code = cADCKEY_NOKEY;
	bAdcKey_oldreceived_code = cADCKEY_NOKEY;

	bAdcKey_flag.byte_access = 0x00;
}

uint8_t adcKey_getReceived_code(void)
{
	return bAdcKey_received_code;
}

uint8_t adcKey_getValue(void)
{
	HAL_ADC_Start(&hadc1);

	HAL_ADC_PollForConversion(&hadc1, 100);

	tempVal = HAL_ADC_GetValue(&hadc1);

	HAL_ADC_Stop(&hadc1);

	// adcVal = (uint8_t)(tempVal >> 9);
	if((tempVal >= cADC_KEY_0_MIN) && (tempVal <= cADC_KEY_0_MAX))
	{
		adcVal = 0;
	}
	else if((tempVal >= cADC_KEY_1_MIN) && (tempVal <= cADC_KEY_1_MAX))
	{
		adcVal = 1;
	}
	else if((tempVal >= cADC_KEY_2_MIN) && (tempVal <= cADC_KEY_2_MAX))
	{
		adcVal = 2;
	}
	else if((tempVal >= cADC_KEY_3_MIN) && (tempVal <= cADC_KEY_3_MAX))
	{
		adcVal = 3;
	}
	else if((tempVal >= cADC_KEY_4_MIN) && (tempVal <= cADC_KEY_4_MAX))
	{
		adcVal = 4;
	}
	else
	{
		adcVal = 0xFF;
	}

	return adcVal;
}

void adcKey_check(void)
{
	bAdcKey_key = adcKey_getValue();

	if(bAdcKey_key != cADCKEY_NOKEY)
	{
		fAdcKey_pressed = 1;
		// bAdcKey_key += 0xA0;
	}
	else
	{
		bAdcKey_key = cADCKEY_NOKEY;
	}
}

uint8_t adcKey_softwareVersion(void)
{
	uint8_t adcKey_softVersion = 0;
	adcKey_softVersion = adcKey_getValue();
	return adcKey_softVersion;
}

uint8_t adcKey_task(void)
{
	if(fAdcKey_pressed == 1)
	{
		fAdcKey_pressed = 0;
		bAdcKey_received_code = bAdcKey_key;

		if(bAdcKey_received_code == bAdcKey_oldreceived_code)
		{
			return 1;
		}
		else
		{
			bAdcKey_oldreceived_code = bAdcKey_received_code;
			return 0;
		}
	}

	bAdcKey_received_code    = cADCKEY_NOKEY;
	bAdcKey_oldreceived_code = cADCKEY_NOKEY;

	return(0);
}











