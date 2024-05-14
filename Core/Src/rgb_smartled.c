#include "stm32g0xx_hal.h"
#include "type.h"
#include "rgb_smartled.h"
#include "math.h"
#include "string.h"


uint8_t xpos, xbrght, xi = 0;
uint8_t bVolBright[5] = {51, 102, 153, 204, 255};
uint8_t bFreqBright[3] = {85, 170, 255};


#ifdef USE_WS2812_PWM
uint8_t LED_Data[MAX_LED][4];
uint8_t LED_Mod[MAX_LED][4];  // for brightness
uint8_t datasentflag = 0;

uint16_t pwmData[(24*MAX_LED)+50];

extern TIM_HandleTypeDef htim1;

#define PI 3.14159265

void ws2812_setBrightness(int brightness)  // 0-45
{
#if USE_BRIGHTNESS

	if (brightness > 45) brightness = 45;
	for (int i=0; i<MAX_LED; i++)
	{
		LED_Mod[i][0] = LED_Data[i][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[i][j] = (LED_Data[i][j])/(tan(angle));
		}
	}

#endif

}

void ws2812_send_pwm(void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{
#if USE_BRIGHTNESS
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
#else
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
#endif

		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 60;  // 2/3 of 90
			}

			else pwmData[indx] = 30;  // 1/3 of 90

			indx++;
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);

	while (!datasentflag){};
	datasentflag = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	datasentflag=1;
}

#endif //USE_WS2812_PWM

#ifdef USE_WS2812_SPI
uint8_t ws2812_buffer[WS2812_BUFFER_SIZE];

void ws2812_send_spi(void) {
	// HAL_SPI_Transmit(&hspi2, ws2812_buffer, WS2812_BUFFER_SIZE, HAL_MAX_DELAY);
	HAL_SPI_Transmit_DMA(&hspi2, ws2812_buffer, WS2812_BUFFER_SIZE);
}

#define WS2812_FILL_BUFFER(COLOR) \
    for( uint8_t mask = 0x80; mask; mask >>= 1 ) { \
        if( COLOR & mask ) { \
            *ptr++ = 0xfc; \
        } else { \
            *ptr++ = 0x80; \
        } \
    }

void ws2812_pixel_all(uint8_t r, uint8_t g, uint8_t b) {
    uint8_t * ptr = ws2812_buffer;
    for( uint16_t i = 0; i < WS2812_NUM_LEDS; ++i) {
        WS2812_FILL_BUFFER(g);
        WS2812_FILL_BUFFER(r);
        WS2812_FILL_BUFFER(b);
    }
}
#endif //USE_WS2812_SPI

void ws2812_setLED(int LEDnum, int Red, int Green, int Blue)
{
#ifdef USE_WS2812_PWM
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
#endif

#ifdef USE_WS2812_SPI
	uint8_t * ptr = &ws2812_buffer[24 * LEDnum];
	WS2812_FILL_BUFFER(Green);
	WS2812_FILL_BUFFER(Red);
	WS2812_FILL_BUFFER(Blue);
#endif
}

void ws2812_clear_all(void)
{
#ifdef USE_WS2812_PWM
	for(int i=0; i < MAX_LED; i++)
	{
		ws2812_setLED(i, 0, 0, 0);
	}
	// memset(LED_Data, 0, sizeof(LED_Data));
#endif

#ifdef USE_WS2812_SPI
	ws2812_pixel_all(0, 0, 0);
	// memset(ws2812_buffer, 0, WS2812_BUFFER_SIZE);
#endif
}

void ws2812_clear_bar(void)
{
	uint8_t i = 0;
#ifdef USE_WS2812_PWM
	for(int i=0; i < 11; i++)
	{
		ws2812_setLED(i, 0, 0, 0);
	}
	// memset(LED_Data, 0, sizeof(LED_Data));
#endif

#ifdef USE_WS2812_SPI
	for(i = 0; i < 11; i++)
	{
		ws2812_setLED(i, 0, 0, 0);
	}
#endif
}

void ws2812_Send(void)
{
#ifdef USE_WS2812_PWM
	ws2812_send_pwm();
#endif

#ifdef USE_WS2812_SPI
	ws2812_send_spi();
#endif
}

void ws2812_clear_one(uint8_t pos)
{
	ws2812_setLED(pos, 0, 0, 0);
}

void ws2812_init(void)
{
	ws2812_clear_all();

	// ws2812_setLED(0, 255, 0, 0);
	// ws2812_setLED(1, 0, 255, 0);
	// ws2812_setLED(2, 0, 0, 255);
	// ws2812_setLED(3, 46, 89, 128);
	// ws2812_setLED(4, 156, 233, 100);
	// ws2812_setLED(5, 102, 0, 235);
	// ws2812_setLED(6, 47, 38, 77);
	// ws2812_setLED(7, 255, 200, 0);

	ws2812_Send();
}

void ws2812_displayLevel(uint8_t lvl)
{
	uint8_t i = 0;

	ws2812_clear_bar();

	xpos = lvl/3;
	xbrght = lvl%3;

	if(xpos > 10) xpos = 10;

	for(i = 0; i <= xpos; i++)
	{
		if(xpos == 0 && xbrght == 0)
		{

		}
		else if(i != xpos)
		{
			ws2812_setLED(i, 0, 255, 0);
		}
		else
		{
			ws2812_setLED(i, 0, bFreqBright[xbrght], 0);
		}
	}
	
	ws2812_Send();
}

void ws2812_displayCutOff(uint8_t lvl)
{
	uint8_t i, j;

	ws2812_clear_bar();

	ws2812_setLED(0, 255, 0, 255);

	j = lvl + 2;
	xpos = (j)/3;
	j = lvl - 1;
	xbrght = (j)%3;

	for(i = 1; i <= xpos; i++)
	{
		if(i != xpos)
		{
			ws2812_setLED(i, 255, 0, 255);
		}
		else
		{
			ws2812_setLED(i, bFreqBright[xbrght], 0, bFreqBright[xbrght]);
		}
	}
	
	ws2812_Send();
}

void ws2812_displayPhase(uint8_t lvl)
{
	ws2812_clear_bar();
	ws2812_setLED(lvl, 0, 255, 255);
	ws2812_Send();
}

void ws2812_displayPolar(uint8_t lvl)
{
	// uint8_t i;

	ws2812_clear_bar();

	if(lvl)
	{
		// for(i = 0; i <= 5; i++)
		// {
		// 	ws2812_setLED(i, 0, 255, 255);
		// }
		ws2812_setLED(10, 0, 255, 255);
	}
	else
	{
		// for(i = 5; i < 11; i++)
		// {
		// 	ws2812_setLED(i, 0, 255, 255);
		// }
		ws2812_setLED(0, 0, 255, 255);
	}
	ws2812_Send();
}

void ws2812_displayMode(uint8_t lvl)
{
	// uint8_t i;

	ws2812_clear_bar();

	// if(lvl)
	// {
	// 	for(i = 0; i <= 5; i++)
	// 	{
	// 		ws2812_setLED(i, 255, 255, 255);
	// 	}
	// }
	// else
	// {
	// 	for(i = 5; i < 11; i++)
	// 	{
	// 		ws2812_setLED(i, 255, 255, 255);
	// 	}
	// }
	ws2812_Send();
}

void ws2812_displayCenter(void)
{
	// uint8_t i;

	ws2812_clear_bar();
}





























