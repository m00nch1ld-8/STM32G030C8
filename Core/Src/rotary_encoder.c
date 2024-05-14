#include "stm32g0xx_hal.h"
#include "type.h"
#include "rotary_encoder.h"
#include "main.h"


extern uint8_t counterQ;

sBIT_BYTE_ACCESS	bRotEnc_flag;
uint8_t bRotEnc_code;
uint8_t bRotaryEnc_tasktick = 0;
#ifdef TIMER_ENCODER_CODE
extern TIM_HandleTypeDef htim3;
uint8_t bRotEnc_State;
uint8_t bRotEnc_newCount;
uint8_t bRotEnc_oldCount;
#else	//TIMER_ENCODER_CODE
#ifdef NEW_ENCODER_DIFF_CODE
uint8_t bRotEnc_diff;
uint8_t bRotEnc_newCount;
#endif
#ifdef USE_OLD_ENCODER_CODE
uint8_t bRotEnc_state;
#else
uint8_t bRotEnc_newState;
uint8_t bRotEnc_oldState;
uint8_t bRotEnc_oldCount;
uint8_t bRotEnc_count;
uint8_t bRotEnc_counter;
#endif
#endif	//TIMER_ENCODER_CODE

void rotaryEncoder_init(void)
{
	fRotEnc_changed = 0;
	bRotEnc_code = cINPUT_NONE;
#ifdef TIMER_ENCODER_CODE
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	bRotEnc_State = cROTENC_STATE_IDLE;
#else	//TIMER_ENCODER_CODE
#ifdef USE_OLD_ENCODER_CODE
	bRotEnc_state = cROTENC_STATE_IDLE;
#else
	bRotEnc_newState = cROTENC_STATE_IDLE;
	bRotEnc_oldState = cROTENC_STATE_IDLE;
#endif
#endif	//TIMER_ENCODER_CODE
}

bool rotEnc1(void)
{
	return HAL_GPIO_ReadPin(ROT_ENC1_GPIO_Port, ROT_ENC1_Pin);
}
bool rotEnc2(void)
{
	return HAL_GPIO_ReadPin(ROT_ENC2_GPIO_Port, ROT_ENC2_Pin);
}

#ifndef USE_OLD_ENCODER_CODE
uint8_t rotaryEncoder_getState(void)
{
	#ifdef NEW_ENCODER_DIFF_CODE
	if((rotEnc1() == 0) && (rotEnc2() == 0))
	{
		return 0;
	}
	else if((rotEnc1() == 0) && (rotEnc2() == 1))
	{
		return 1;
	}
	else if((rotEnc1() == 1) && (rotEnc2() == 1))
	{
		return 2;
	}
	else	// if((rotEnc1() == 1) && (rotEnc2() == 0))
	{
		return 3;
	}
	#else
	return (uint8_t)((rotEnc1() << 1) | rotEnc2());
	#endif
}
#endif

uint8_t rotaryEncoder_getReceived_code(void)
{
	return bRotEnc_code;
}

void rotaryEncoder_check(void)
{
#ifdef TIMER_ENCODER_CODE
	bRotEnc_newCount = ((TIM3->CNT)>>2);
	bRotEnc_State = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);
#else	//TIMER_ENCODER_CODE
#ifdef USE_OLD_ENCODER_CODE
	switch(bRotEnc_state)
	{
		case cROTENC_STATE_IDLE:
			if((rotEnc1() == 0) && (rotEnc2() == 1))
			{
				bRotEnc_state = cROTENC_STATE_PRELEFT;
			}
			else if((rotEnc1() == 1) && rotEnc2() == 0)
			{
				bRotEnc_state = cROTENC_STATE_PRERIGHT;
			}
			break;

		case cROTENC_STATE_PRELEFT:
			if((rotEnc1() == 0) && (rotEnc2() == 0))
			{
				bRotEnc_state = cROTENC_STATE_LEFT;
			}
			else if((rotEnc1() == 1) && (rotEnc2() == 0))
			{
				bRotEnc_state = cROTENC_STATE_IDLE;
			}
			break;

		case cROTENC_STATE_LEFT:
			if((rotEnc1() == 1) && (rotEnc2() == 1))
			{
				fRotEnc_changed = 1;
				bRotEnc_code = cROTENC_CODE_DOWN;
				bRotEnc_state = cROTENC_STATE_IDLE;
			}
			break;

		case cROTENC_STATE_PRERIGHT:
			if((rotEnc1() == 0) && (rotEnc2() == 0))
			{
				bRotEnc_state = cROTENC_STATE_RIGHT;
			}
			else if((rotEnc1() == 0) && (rotEnc2() == 1))
			{
				bRotEnc_state = cROTENC_STATE_IDLE;
			}
			break;

		case cROTENC_STATE_RIGHT:
			if((rotEnc1() == 1) && (rotEnc2() == 1))
			{
				fRotEnc_changed = 1;
				bRotEnc_code = cROTENC_CODE_UP;
				bRotEnc_state = cROTENC_STATE_IDLE;
			}
			break;
	}
#else
	bRotEnc_newState = rotaryEncoder_getState();
	#ifdef NEW_ENCODER_DIFF_CODE
	bRotEnc_diff = bRotEnc_oldState - bRotEnc_newState;

	if((bRotEnc_diff == 0xFF) || (bRotEnc_diff == 0x03) || (bRotEnc_diff == 0x02))
	{
		bRotEnc_oldState = bRotEnc_newState;
		/*if(bRotEnc_count < 20)*/ bRotEnc_count++;
	}
	else if((bRotEnc_diff == 0x01) || (bRotEnc_diff == 0xFD) || (bRotEnc_diff == 0xFE))
	{
		bRotEnc_oldState = bRotEnc_newState;
		/*if(bRotEnc_count > 0)*/ bRotEnc_count--;
	}
	// else if((bRotEnc_diff == 0xFE) || (bRotEnc_diff == 0x02))
	// {

	// }
	#else
	if(bRotEnc_oldState == 3 && bRotEnc_newState == 2)			{bRotEnc_count++;}	//3 -> 2
	else if(bRotEnc_oldState == 2 && bRotEnc_newState == 0)		{bRotEnc_count++;}	//2 -> 0
	else if(bRotEnc_oldState == 0 && bRotEnc_newState == 1)		{bRotEnc_count++;}	//0 -> 1
	else if(bRotEnc_oldState == 1 && bRotEnc_newState == 3)		{bRotEnc_count++;}	//1 -> 3
	else if(bRotEnc_oldState == 3 && bRotEnc_newState == 1)		{bRotEnc_count--;}	//3 -> 1
	else if(bRotEnc_oldState == 1 && bRotEnc_newState == 0)		{bRotEnc_count--;}	//1 -> 0
	else if(bRotEnc_oldState == 0 && bRotEnc_newState == 2)		{bRotEnc_count--;}	//0 -> 2
	else if(bRotEnc_oldState == 2 && bRotEnc_newState == 3)		{bRotEnc_count--;}	//2 -> 3

	bRotEnc_oldState = bRotEnc_newState;
	// if(bRotEnc_state != rotEnc2())
	// {
	// 	if(rotEnc1() == 0)
	// 	{
	// 		fRotEnc_changed = 1;
	// 		bRotEnc_code = cROTENC_CODE_DOWN;
	// 	}
	// 	else
	// 	{
	// 		fRotEnc_changed = 1;
	// 		bRotEnc_code = cROTENC_CODE_UP;
	// 	}
	// 	bRotEnc_state = rotEnc1();
	// }
	#endif

#endif
#endif	//TIMER_ENCODER_CODE
	bRotaryEnc_tasktick = 0;
}

uint8_t rotaryEncoder_task(void)
{
	// rotaryEncoder_check();
#ifdef TIMER_ENCODER_CODE
	if(bRotEnc_oldCount != bRotEnc_newCount)
	{
		if(bRotEnc_State)
		{
			bRotEnc_code = cROTENC_CODE_UP;
		}
		else
		{
			bRotEnc_code = cROTENC_CODE_DOWN;
		}
		bRotEnc_oldCount = bRotEnc_newCount;
		fRotEnc_changed = 1;
	}
#else	//TIMER_ENCODER_CODE
#ifndef USE_OLD_ENCODER_CODE
	#ifdef NEW_ENCODER_DIFF_CODE
	bRotEnc_newCount = bRotEnc_count>>2;		// jika ingin lebih cepat bisa shift 1 atau tanpa shift
	if(bRotEnc_oldCount != bRotEnc_newCount)
	{
		if(bRotEnc_oldCount < bRotEnc_newCount)
		{
			bRotEnc_code = cROTENC_CODE_UP;
		}
		else
		{
			bRotEnc_code = cROTENC_CODE_DOWN;
		}
		bRotEnc_oldCount = bRotEnc_newCount;
		fRotEnc_changed = 1;
	}
	#else
	// if(fRotEnc_count == 1)
	// {
	// 	bRotEnc_counter++;
	// 	fRotEnc_count = 0;
	// 	if(bRotEnc_counter == 5)
	// 	{
	// 		bRotEnc_counter = 0;
	// 		fRotEnc_changed = 1;
	// 	}
	// }
	if(bRotEnc_oldCount != bRotEnc_count)
	{
		bRotEnc_counter++;
		if(bRotEnc_counter > 10)
		{
			fRotEnc_changed = 1;
			bRotEnc_counter = 0;
			if(bRotEnc_oldCount >= bRotEnc_count)
			{
				bRotEnc_code = cROTENC_CODE_DOWN;
			}
			else
			{
				bRotEnc_code = cROTENC_CODE_UP;
			}
		}
		bRotEnc_oldCount = bRotEnc_count;
	}
	#endif
#endif
#endif	//TIMER_ENCODER_CODE

	if(fRotEnc_changed == 1)
	{
		fRotEnc_changed = 0;
		
		bInput_prckey = bRotEnc_code;// + cROTENC_OFFSET_CODE;
		fInput_prckey = 1;
		bInput_press_state = cINPUT_KEY_PRESS;
		return 1;
	}
	else
	{
		return 0;
	}
}



