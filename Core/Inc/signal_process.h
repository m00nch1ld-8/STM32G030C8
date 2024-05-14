
/**
  ******************************************************************************
  * @file			: signal_process.h
  * @brief			: Header for signal_process.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : Yeremias Yosef Bria
  * @version		: v1.0.0
  * @date created	: 2019-12-19
  *
  * @author modified: BeeHa
  * @date modified	: 2023-08-04
  * 
  * @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIGNAL_PROCESS_H
#define __SIGNAL_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "config.h"
#include <math.h>

#ifdef USE_FFT_SIGNAL_PROCESS


/* Exported types ------------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;


/* Exported constants --------------------------------------------------------*/

// Jika ingin Debug time FFT dan Proses Animasi.
#define debugTime					(0)

/* Private Definend Macro ----------------------------- */
#define BASS_ONLY					(0)
#define BASS_TREBLE					(1)

// ****************************		User Defined Params-1 CONTROL-LED & Signal **************************** //
// Set RGB Led Trigger
#define RGB_TRIGGER					(BASS_TREBLE)	// BassOnly / BassTreble trigger RGB-LED

#define bufSampling 				(15)			// Buffer FIlter Trigger RGB-LED
#define timeCh_color				(80)			// (........ms)
#define max_modeColor				(9)				// Jumlah Warna RGB (7 Warna RGB) + OFF + Auto_Random.

#define max_ModeBargraph			(7)				// Jumlah Animasi pada bargraph + Blank Display.

#define timeUpdate					(20)			// Update rate display (........ms) *(Saran >= 20ms)

/* User Defined */
#define freqSample					24000			// Fs (Hz)
#define sampleData					256				// Nilai N data harus = 2^n

#define NOISE						25


/* Exported macro ------------------------------------------------------------*/
#define max(a,b)					((a>b)?(a):(b))
#define abs(a)						((a>=0)?(a):(a*-1))

// membuat tipe data untuk bilangan Complex (Real & Imaginer)
typedef struct
{
	float Bil_real;
	float Bil_imag;
}ComplexValue;


/* Exported functions prototypes ---------------------------------------------*/
extern ComplexValue dataFFT[sampleData+1];

void spectrume_init(void);
void spectrume_task(void);
float absMagnitude(float bilReal, float bilImag);
ComplexValue perkalianComplex(ComplexValue a, ComplexValue b);
void ComplexTo_5_FreqBand(ComplexValue *data, int *magnitudeBand_out);
void ComplexTo_Magnitude(ComplexValue *data, int *magnitudeBand_out);

void FFT_init(void);
void FFT_analysis(int16_t *data, ComplexValue *dataOut_FFT);

void spectrume_init(void);

#endif  //USE_FFT_SIGNAL_PROCESS


#ifdef __cplusplus
}
#endif

#endif /* __SIGNAL_PROCESS_H */

