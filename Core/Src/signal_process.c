/**
	*  Signal_Process.c
	*  Created & Modif by Yeremias Yosef Bria on 19 Desemberember 2019.
	*  yeramias.bria@gmail.com
	*  Source Code Signal Processing (FFT).
	*/

#include "signal_process.h"
// #include "type.h"

#ifdef USE_FFT_SIGNAL_PROCESS


ComplexValue dataFFT[sampleData+1];

extern uint32_t millis(void);
/* Private typedef Config --------------------------------------------------------*/
#define pi2					(6.2831853072)

#define ANIM_RGB_AUTO		(0)
#define	ANIM_RGB_MANUAL	(1)

static uint16_t _nData=0;
static uint8_t _power=0;

// Variable Support Spectrume Bargraph
volatile uint8_t mode_barGraph = 1, timeHold = 10;

// Config. Mapping Magnitude Signal to Log. Level-Bar..
const int16_t map_100Hz[8] = {0,30,90,135,210,380,780,1350};
const int16_t map_315Hz[8] = {0,30,60,125,180,280,600,1150};
const int16_t map_1kHz[8] = {0,60,70,100,180,270,580,1100};
const int16_t map_3k1Hz[8] = {0,58,65,90,160,210,420,700};
const int16_t map_10kHz[8] = {0,56,62,85,120,190,300,450};

uint8_t frame = 0, i = 0;
int magnitudeBand[5] = {0,0,0,0,0};
uint8_t timeHold_peak[5];
uint16_t timeMode = 0;
uint8_t rawLevel[5] = {0,0,0,0,0};
uint8_t last_rawLevel[5] = {0,0,0,0,0};
uint8_t valueBar[5] = {0,0,0,0,0};
uint8_t peakHold[5] = {0,0,0,0,0};

;// Variable Suport ADC. (FFT Spectrume & Trigger LED RGB)
volatile uint8_t adcComplate=0;
int16_t data_ADC[sampleData+2];

uint32_t tlast, timeLast1, timeLast2, timeLast3, lastUpdate;

// Variable Support Filter Audio
uint16_t sampling[bufSampling], countSampling = 0, minLVL = 0, maxLVL = 0;
uint16_t maxAVG, minAVG;
volatile uint16_t avgLVL = 0, avgLVL_filter = 0;
uint8_t noSignal = 0;
int8_t height = 0, last_height = 0, height2 = 1, last_height2 = 0;

// Variable Support RGB Led Color
uint8_t dir = 0, speed_up = 0, putar = 0, jColor = 0, RGB_Mode = ANIM_RGB_AUTO, cntColor_Mode = 0;
uint16_t wColor = 0;
uint32_t warna = 0, modeColor[max_modeColor];

const float Kc1[] = {0.0000000000, 0.7071067812, 0.9238795325, 0.9807852804,
										0.9951847267, 0.9987954562, 0.9996988187, 0.9999247018,
										0.9999811753, 0.9999952938, 0.9999988235, 0.9999997059,
										0.9999999265, 0.9999999816, 0.9999999954, 0.9999999989,
										0.9999999997};
const float Kc2[] = {1.0000000000, 0.7071067812, 0.3826834324, 0.1950903220,
										0.0980171403, 0.0490676743, 0.0245412285, 0.0122715383,
										0.0061358846, 0.0030679568, 0.0015339802, 0.0007669903,
										0.0003834952, 0.0001917476, 0.0000958738, 0.0000479369,
										0.0000239684};

uint8_t Exponent(uint16_t value)
{
	// Calculates the base 2 logarithm of a value
	uint8_t result = 0;
	while (((value >> result) & 1) != 1) result++;
	return(result);
}

void swap(int16_t *a, int16_t *b)
{
	int temp = *b;
	*b=*a;
	*a=temp;
}

void DC_Blocker(int16_t *data, ComplexValue *ComplexData)
{
	int mean=0;
	for(uint16_t i=0; i<_nData; i++) mean += data[i];
	mean/=_nData;
	
	// mengubah data ke bilangan komplex dan block INPUT DC
	for(uint16_t i=0; i<_nData; i++)
	{
		ComplexData[i].Bil_real=(float)(data[i]-mean);
		ComplexData[i].Bil_imag=0.0;
	}
}

float absMagnitude(float bilReal, float bilImag)
{
	// Fungsi ini sama dengan |magnitude|=square(real^2 + imaginer^2);
	// namun di sederhanakn untuk perhitungan waktu yang cepat.
	float temp = abs(bilReal) + abs(bilImag);
	return temp/1.414;		// sama dengan akar2
}

ComplexValue perkalianComplex(ComplexValue a, ComplexValue b)
{
	ComplexValue temp;
	temp.Bil_real=(float)(a.Bil_real*b.Bil_real)-(a.Bil_imag*b.Bil_imag);
	temp.Bil_imag=(float)(a.Bil_real*b.Bil_imag)+(a.Bil_imag*b.Bil_real);
	return temp;
}

__weak void ComplexTo_5_FreqBand(ComplexValue *data, int *magnitudeBand_out)
{
	int temp1=0, temp2=0, temp3=0, temp4=0, temp5=0;
	// konversi output bilangan komplex ke data absoluted magnitude
	// data hasil FFT 1/2 dari data sample. 1/2 lagi merupakan mirror.
	for(uint16_t i=1; i<120; i++)
	{
		// Fungsi ini sama dengan |magnitude|=square(real^2 + imaginer^2); (Prosses lebih cepat)
		int temp = absMagnitude(data[i].Bil_real, data[i].Bil_imag);	
				     //sqrtf(pow(data[i].Bil_real,2) + pow(data[i].Bil_imag,2));
		if(temp > NOISE) 
		{
			if(i<3)temp1 += temp;
			else if(i<6)temp2 += temp;
			else if(i<20)temp3 += temp;
			else if(i<70)temp4 += temp;
			else if(i<120)temp5 += temp;
		}
	}
	magnitudeBand_out[0]=temp1/11;
	magnitudeBand_out[1]=temp2/14;
	magnitudeBand_out[2]=temp3/26;
	magnitudeBand_out[3]=temp4/49;
	magnitudeBand_out[4]=temp5/43;
}

__weak void ComplexTo_Magnitude(ComplexValue *data, int *magnitudeBand_out)
{
	// konversi output bilangan komplex ke data absoluted magnitude
	// data hasil FFT 1/2 dari data sample. 1/2 lagi merupakan mirror.
	for(uint16_t i=1; i<_nData/2; i++)
	{
		int temp=absMagnitude(data[i].Bil_real, data[i].Bil_imag);	
		if(temp > NOISE) temp -= NOISE;
		// Out Magnitude
		magnitudeBand_out[i] = temp;
	}
}

void FFT_init(void)
{
	for(uint8_t i=1; i<16; i++)
	{
		if(pow(2,i)==sampleData) 		// mencari quadrat sesuai biner 2^n
		{
			_nData=sampleData;
			break;
		}
	}
	_power=Exponent(_nData);
}

void FFT_analysis(int16_t *data, ComplexValue *dataOut_FFT)
{
	uint32_t j = 0;
	uint32_t index = 0;
	
	// tukar bit data / reverese bits (Data)
	for (uint16_t i = 0; i < (_nData - 1); i++)
	{
		if (i < j) swap(&data[i], &data[j]);
		uint32_t k = (_nData >> 1);
		while (k <= j)
		{
			j -= k;
			k >>= 1;
		}
		j += k;
	}
	
	DC_Blocker(data, dataOut_FFT);
	
	// hitung FFT dengan butterfly -> 2 Radix:
	float c1 = -1.0;
	float c2 = 0.0;
	uint32_t l2 = 1;
	for(uint8_t l = 0; (l < _power); l++) 
	{
		uint32_t l1 = l2;
		l2 <<= 1;
		float u1 = 1.0;
		float u2 = 0.0;
		for(j = 0; j < l1; j++) 
		{
			for(uint16_t i = j; i < _nData; i += l2)
			{
					uint32_t i1 = i + l1;
					float t1 = u1 * dataOut_FFT[i1].Bil_real - u2 * dataOut_FFT[i1].Bil_imag;
					float t2 = u1 * dataOut_FFT[i1].Bil_imag + u2 * dataOut_FFT[i1].Bil_real;
					dataOut_FFT[i1].Bil_real = dataOut_FFT[i].Bil_real - t1;
					dataOut_FFT[i1].Bil_imag = dataOut_FFT[i].Bil_imag - t2;
					dataOut_FFT[i].Bil_real += t1;
					dataOut_FFT[i].Bil_imag += t2;
			 }
			 float z = ((u1 * c1) - (u2 * c2));
			 u2 = ((u1 * c2) + (u2 * c1));
			 u1 = z;
		}
		
		c2 = (Kc2[index]);
		c1 = (Kc1[index]);
		index++;

		c2 = -c2;
	}
}

void MagnitudeTo_levelBar(void)
{
	// konversi output bilangan komplex hitungan FFT ke data absoluted magnitude Level BAR 5 Band
	ComplexTo_5_FreqBand(dataFFT, magnitudeBand);
	// konversi nilai magnitude 5 band ke log. level bargraph
	for(uint8_t i=0; i<8; i++)
	{
		if(magnitudeBand[0]>=map_100Hz[i])rawLevel[0]=i;
		if(magnitudeBand[1]>=map_315Hz[i])rawLevel[1]=i;
		if(magnitudeBand[2]>=map_1kHz[i]) rawLevel[2]=i;
		if(magnitudeBand[3]>=map_3k1Hz[i])rawLevel[3]=i;
		if(magnitudeBand[4]>=map_10kHz[i])rawLevel[4]=i;
	}
	
	// Untuk Slow down Bar-Level.
	for(uint8_t i=0; i<5; i++)
	{
		if(rawLevel[i] >= last_rawLevel[i]) valueBar[i] = rawLevel[i];
		else valueBar[i] = last_rawLevel[i] - 1;
		
		last_rawLevel[i] = valueBar[i];
	}
}

void Mode_Blank(void)
{
	// set pixel led bar to Clear
	// for(uint8_t i=0; i<5; i++) PT6964_setBuffer(i, 0x00);
}

void Mode_LevelBar(void)
{
	// set pixel led bar.
	// for(uint8_t i=0; i<5; i++) PT6964_setLevel_Bar(i,valueBar[i]);
}

void Mode_pixelBar(void)
{
	// set pixel led bar.
	// for(uint8_t i=0; i<5; i++) PT6964_setPixel_Bar(i,valueBar[i]);
}

void Mode_LevelBar_half(void)
{
	// set pixel led bar.
	// for(uint8_t i=0; i<5; i++) 
	// {
	// 	valueBar[i] = valueBar[i]/1.5;
	// 	PT6964_setPixel_BarHalf(i,valueBar[i]);
	// }
}

void Mode_peakHold(void)
{
	static uint8_t waitDown=0;
	if(millis() - timeLast1 > 22)
	{
		timeLast1 = millis();
		waitDown = 0;
	}
	// set pixel led bar.
	for(uint8_t i=0; i<5; i++) 
	{
		if(valueBar[i] > peakHold[i])
		{
			peakHold[i]=valueBar[i]+1;
			timeHold_peak[i]=0;
		}
		else
		{
			if(!waitDown)
			{
				timeHold_peak[i]++;
				if(timeHold_peak[i] >= timeHold)
				{
					if(peakHold[i])peakHold[i]--;
					timeHold_peak[i]=0;
				}
			}
		}
		
		// PT6964_setLevelPeak_Bar(i,valueBar[i],peakHold[i]);
	}
	if(!waitDown)waitDown=1;
}

void Animation_1(void)
{
	if(millis() - timeLast1 > 30)
	{
		timeLast1 = millis();
		if(++frame > 18)frame=0;
		// set pixel led bar.
		// for(uint8_t i=0; i<5; i++) PT6964_setBuffer(i, animRaw_1[frame][i]);
	}
}

void Animation_2(void)
{
	if(millis() - timeLast1 > 30)
	{
		timeLast1 = millis();
		if(++frame > 43)frame=0;
		// set pixel led bar.
		// for(uint8_t i=0; i<5; i++) PT6964_setBuffer(i, animRaw_2[frame][i]);
	}
}

void RGB_show(uint32_t color)
{	
	// phtim->Instance->CCR1 = ((color >> 16) & 0x00ff);			// set PWM LED RED
	// phtim->Instance->CCR2 = ((color >> 8) & 0x00ff);			// set PWM LED GREEN
	// phtim->Instance->CCR3 = (color & 0x00ff);							// set PWM LED BLUE
}

// ===================================================================================
void Auto_changeColor(const uint16_t time)
{
	// if(millis()-timeLast3 >= time)
	// {
	// 	timeLast3 = millis();
	// 	jColor++;
	// 	warna = RGBwheel_color(jColor);
	// }
}

// ===================	Stayle Mode RGB-LED Light Anim.		=====================
void modeRGB_visual1(void)
{
	if(height > last_height2) 
	{
		last_height2 = height+2;
		if(speed_up == 0) 
		{
			if(++dir >= (max_modeColor - 2)) dir = 0;
			wColor = dir*42;
			if(wColor > 255) wColor=0;
			jColor = wColor;
			speed_up = 1;
			putar = 1;
		}
	}
	else if(height < last_height2) last_height2 = height;
	
	if(speed_up)
	{
		if(millis()-timeLast2 > 5)
		{
			timeLast2 = millis();
			if(putar != 0)
			{
				height2++;
				if(height2 > 6)putar = 0;
			}
			else 
			{
				putar = 0;
				speed_up = 0;
			}
		}
	}
	else
	{
		if(millis()-timeLast2 > 10)
		{
			height2 = 0;
		}
	}
	
	if(noSignal) Auto_changeColor(timeCh_color);		// LED Mode Standby
	else warna = modeColor[dir];		// LED Kedip ganti2 warna.
}

void draw_modeAnimation(void)
{
	// BarGraph Visual Handler
	switch(mode_barGraph)
	{
		case 0: Mode_Blank(); break;
		case 1: Mode_LevelBar(); break;
		case 2: Mode_pixelBar(); break;
		case 3: Mode_LevelBar_half(); break;
		case 4: Mode_peakHold(); break;
		case 5: Animation_1(); break;
		case 6: Animation_2(); break;
	}
	
	// RGB Visual Auto Handler
	if(RGB_Mode == ANIM_RGB_AUTO) modeRGB_visual1();
	// RGB Visual Manual Handler
	else warna = modeColor[cntColor_Mode];
	
	// setiap 20ms Update Display Animation & Update LED-RGB Light
	if(millis()-lastUpdate >= timeUpdate)
	{
		lastUpdate = millis();
		
		// PT6964_show();
		RGB_show(warna);
	}
}

// ============================ **************** ==============================
void AudioADC_Init(TIM_HandleTypeDef *htimTrigger, ADC_HandleTypeDef *hadc)
{	
	// Kalibrasi ADC. . . . .
	HAL_ADCEx_Calibration_Start(hadc);
	HAL_Delay(10);
	// Start timer untuk trigger ADC sampling.....
	HAL_TIM_Base_Start(htimTrigger);
	// Start DMA ADC
	HAL_ADC_Start_DMA(hadc, (uint32_t *)data_ADC, sampleData);
	
	// modeColor[0] = RGB_setColor(0x00, 0xFF, 0x00);		// Hijau
	// modeColor[1] = RGB_setColor(0xFF, 0xFF, 0x00);		// Kuning 
	// modeColor[2] = RGB_setColor(0xFF, 0x00, 0x00);		// Merah
	// modeColor[3] = RGB_setColor(0xFF, 0x00, 0xFF);		// Ungu
	// modeColor[4] = RGB_setColor(0x00, 0x00, 0xFF);		// Biru
	// modeColor[5] = RGB_setColor(0x00, 0xFF, 0xFF);		// Hijau-Biru
	// modeColor[6] = RGB_setColor(0xFF, 0xFF, 0xFF);		// Putih
	
	// modeColor[7] = RGB_setColor(0x00, 0x00, 0x00);		// LED OFF
	// modeColor[8] = RGB_setColor(0x00, 0x00, 0x00);		// Identifikasi (index) Mode Auto Random Follow Musik
}

void read_audio(void)
{
	static uint16_t timeNo_signal=0; 
	volatile static int16_t tt1=0;
	
	// Get Data ADC Audio-IN, Jika ADC Complate.
	if(adcComplate)
	{
	#if debugTime
		tADC = millis() - tCapADC;
		tCapture = millis();
	#endif
		// gain disini (BeeHa)
		for(int a = 0; a < (sampleData+2); a++)
		{
			data_ADC[a] = data_ADC[a] * 4;
		}
		FFT_analysis(data_ADC, dataFFT);
		// Reset ADC untuk Baca ADC lagi.
		HAL_TIM_Base_Start(&htim1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t *)data_ADC, sampleData);
		adcComplate=0;
		
	#if debugTime
		tFFT=millis()-tCapture;
		tCapADC = millis();
		tCapture = tCapADC;
	#endif
		
		// Konversi nilai magnitude Freq. -> Display Level-bar 
		MagnitudeTo_levelBar();
		
		// Get trigger Audio Filter RGB-LED
	#if RGB_TRIGGER == BASS_ONLY
		// GET Filter Bass (untuk trigger RGB-Light).
		if(magnitudeBand[0] > 30) tt1 = magnitudeBand[0]-30;
		else tt1 = 0;

	#elif RGB_TRIGGER == BASS_TREBLE
		// GET Filter Bass dan Treble (untuk trigger RGB-Light).
		// Jika tidak ada Bass, maka treble sebagai acuan utk trigger.
		if(magnitudeBand[0] >= magnitudeBand[3])
		{
			if(magnitudeBand[0] > 30) tt1 = magnitudeBand[0]-30;
			else tt1 = 0;
		}
		else
		{
			if(magnitudeBand[3] > 50) tt1 = magnitudeBand[3]-50;
			else tt1 = 0;
		}
	#endif
		
		sampling[countSampling] = tt1;
		if(++countSampling >= bufSampling) countSampling = 0;
		minLVL = maxLVL = sampling[0];
		for(uint8_t i = 0; i < bufSampling; i++)
		{
			if (sampling[i] < minLVL) minLVL = sampling[i];
			else if (sampling[i] > maxLVL) maxLVL = sampling[i];
		}
//		maxAVG = (float) (maxAVG * 0.9391) + (0.0609 * maxLVL);
//		minAVG = (float) (minAVG * 0.9391) + (0.0609 * minLVL);
//		avgLVL = ((minAVG + maxAVG)/2);
//		avgLVL_filter = (maxAVG + avgLVL)/2;		
		
		avgLVL = ((minLVL + maxLVL)/2);
		avgLVL = (maxLVL + avgLVL)/2;
		avgLVL_filter = (float) (avgLVL_filter * 0.9391) + (0.0609 * avgLVL);
		
	#if debugTime
		tConv = millis() - tCapture;
	#endif
	}
	
	// Setiap ~= 2ms, read data audio input.
	if((millis()-tlast) > 1)
	{
		tlast = millis();
		if(tt1 > avgLVL_filter+5)
		{
			height=10;
		}
		else if(tt1 <= avgLVL_filter) height=0;
		
		// deteksi jika tidak ada signal.
		if(height <= 1)
		{
			if(++timeNo_signal > 250)		// wait > 0,5s tdk ada signal : LED mode standby
			{
				noSignal = 1;
				timeNo_signal = 0;
			}
		}
		else 
		{
			timeNo_signal = 0;
			noSignal = 0;
		}
	}
}

void spectrume_init(void)
{
    // FFT Init. . . . . . . . .
	FFT_init();
	// Init ADC-Audio Sampling Driver. . . . . . . .
	AudioADC_Init(&htim1, &hadc1);
	// Init User Interface UART. . . . . .
	// User_Interface_Init();
}

void spectrume_task(void)
{
    // Read Audio Input.
	read_audio();
	// Draw Animated Bar-Display & Animated RGB Light.
	draw_modeAnimation();
}

// Get Sampling data dari ADC Interupt. (Callback ADC DMA Complate)
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	HAL_TIM_Base_Stop(&htim1);
	adcComplate=1;
}

#endif	//USE_FFT_SIGNAL_PROCESS


/* =========================      end FFT Code    ============================ */
