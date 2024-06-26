#include "type.h"
#include "main.h"

#define TAS5548_ADDR	0x34	//0x36 when ASEL pin = '1', 0x34 when ASEL pin = '0'
#define TAS5548_WRITE	0x00
#define TAS5548_READ	0x01

/* Register definitions */
#define TAS5548_CLK_CTRL					0x00
#define TAS5548_GENERAL_STAT				0x01
#define TAS5548_ERR_STAT					0x02
#define TAS5548_SYS_CTRL1					0x03
#define TAS5548_SYS_CTRL2					0x04
#define TAS5548_CH_CFG_CTRL1				0x05
#define TAS5548_CH_CFG_CTRL2				0x06
#define TAS5548_CH_CFG_CTRL3				0x07
#define TAS5548_CH_CFG_CTRL4				0x08
#define TAS5548_CH_CFG_CTRL5				0x09
#define TAS5548_CH_CFG_CTRL6				0x0A
#define TAS5548_CH_CFG_CTRL7				0x0B
#define TAS5548_CH_CFG_CTRL8				0x0C
#define TAS5548_HEADPHONE_CFG				0x0D
#define TAS5548_SERIAL_DATA					0x0E
#define TAS5548_SOFT_MUTE					0x0F
#define TAS5548_EMO_STAT					0x10
#define TAS5548_OSC_TRIM					0x12
#define TAS5548_AUTOMUTE_CTRL				0x14
#define TAS5548_AUTOMUTE_PWM				0x15
#define TAS5548_MODULATION_LIMIT1			0x16
#define TAS5548_MODULATION_LIMIT2			0x17
#define TAS5548_MODULATION_LIMIT3			0x18
#define TAS5548_MODULATION_LIMIT4			0x19
#define TAS5548_IC_DELAY_CH0				0x1B
#define TAS5548_IC_DELAY_CH1				0x1C
#define TAS5548_IC_DELAY_CH2				0x1D
#define TAS5548_IC_DELAY_CH3				0x1E
#define TAS5548_IC_DELAY_CH4				0x1F
#define TAS5548_IC_DELAY_CH5				0x20
#define TAS5548_IC_DELAY_CH6				0x21
#define TAS5548_IC_DELAY_CH7				0x22
#define TAS5548_IC_OFFSET_DELAY				0x23
#define TAS5548_PWM_SEQ_TIM					0x24
#define TAS5548_PWM_EMO_CTRL				0x25
#define TAS5548_IND_CH_SHUTDOWN				0x27
#define TAS5548_IN_MUX_CH_1_2				0x30
#define TAS5548_IN_MUX_CH_3_4				0x31
#define TAS5548_IN_MUX_CH_5_6				0x32
#define TAS5548_IN_MUX_CH_7_8				0x33
#define TAS5548_PWM_MUX_CH_1_2				0x34
#define TAS5548_PWM_MUX_CH_3_4				0x35
#define TAS5548_PWM_MUX_CH_5_6				0x36
#define TAS5548_PWM_MUX_CH_7_8				0x37
#define TAS5548_IC_DELAY_BD_CH0				0x38
#define TAS5548_IC_DELAY_BD_CH1				0x39
#define TAS5548_IC_DELAY_BD_CH2				0x3A
#define TAS5548_IC_DELAY_BD_CH3				0x3B
#define TAS5548_IC_DELAY_BD_CH4				0x3C
#define TAS5548_IC_DELAY_BD_CH5				0x3D
#define TAS5548_IC_DELAY_BD_CH6				0x3E
#define TAS5548_IC_DELAY_BD_CH7				0x3F
#define TAS5548_IN_MIXER_CH1				0x41
#define TAS5548_IN_MIXER_CH2				0x42
#define TAS5548_IN_MIXER_CH3				0x43
#define TAS5548_IN_MIXER_CH4				0x44
#define TAS5548_IN_MIXER_CH5				0x45
#define TAS5548_IN_MIXER_CH6				0x46
#define TAS5548_IN_MIXER_CH7				0x47
#define TAS5548_IN_MIXER_CH8				0x48
#define TAS5548_BASS_MIXER_CH1  			0x49
#define TAS5548_BASS_MIXER_CH2				0x4A
#define TAS5548_BASS_MIXER_CH3				0x4B
#define TAS5548_BASS_MIXER_CH4				0x4C
#define TAS5548_BASS_MIXER_CH5				0x4D
#define TAS5548_BASS_MIXER_CH6				0x4E
#define TAS5548_BASS_MIXER_CH7				0x4F
#define TAS5548_BASS_MIXER_CH8				0x50
#define TAS5548_CH1_BIQUAD1_FILTER			0x51
#define TAS5548_CH1_BIQUAD2_FILTER			0x52
#define TAS5548_CH1_BIQUAD3_FILTER			0x53
#define TAS5548_CH1_BIQUAD4_FILTER			0x54
#define TAS5548_CH1_BIQUAD5_FILTER			0x55
#define TAS5548_CH1_BIQUAD6_FILTER			0x56
#define TAS5548_CH1_BIQUAD7_FILTER			0x57
#define TAS5548_CH2_BIQUAD1_FILTER			0x58
#define TAS5548_CH2_BIQUAD2_FILTER			0x59
#define TAS5548_CH2_BIQUAD3_FILTER			0x5A
#define TAS5548_CH2_BIQUAD4_FILTER			0x5B
#define TAS5548_CH2_BIQUAD5_FILTER			0x5C
#define TAS5548_CH2_BIQUAD6_FILTER			0x5D
#define TAS5548_CH2_BIQUAD7_FILTER			0x5E
#define TAS5548_CH3_BIQUAD1_FILTER			0x5F
#define TAS5548_CH3_BIQUAD2_FILTER			0x60
#define TAS5548_CH3_BIQUAD3_FILTER			0x61
#define TAS5548_CH3_BIQUAD4_FILTER			0x62
#define TAS5548_CH3_BIQUAD5_FILTER			0x63
#define TAS5548_CH3_BIQUAD6_FILTER			0x64
#define TAS5548_CH3_BIQUAD7_FILTER			0x65
#define TAS5548_CH4_BIQUAD1_FILTER			0x66
#define TAS5548_CH4_BIQUAD2_FILTER			0x67
#define TAS5548_CH4_BIQUAD3_FILTER			0x68
#define TAS5548_CH4_BIQUAD4_FILTER			0x69
#define TAS5548_CH4_BIQUAD5_FILTER			0x6A
#define TAS5548_CH4_BIQUAD6_FILTER			0x6B
#define TAS5548_CH4_BIQUAD7_FILTER			0x6C
#define TAS5548_CH5_BIQUAD1_FILTER			0x6D
#define TAS5548_CH5_BIQUAD2_FILTER			0x6E
#define TAS5548_CH5_BIQUAD3_FILTER			0x6F
#define TAS5548_CH5_BIQUAD4_FILTER			0x70
#define TAS5548_CH5_BIQUAD5_FILTER			0x71
#define TAS5548_CH5_BIQUAD6_FILTER			0x72
#define TAS5548_CH5_BIQUAD7_FILTER			0x73
#define TAS5548_CH6_BIQUAD1_FILTER			0x74
#define TAS5548_CH6_BIQUAD2_FILTER			0x75
#define TAS5548_CH6_BIQUAD3_FILTER			0x76
#define TAS5548_CH6_BIQUAD4_FILTER			0x77
#define TAS5548_CH6_BIQUAD5_FILTER			0x78
#define TAS5548_CH6_BIQUAD6_FILTER			0x79
#define TAS5548_CH6_BIQUAD7_FILTER			0x7A
#define TAS5548_CH7_BIQUAD1_FILTER			0x7B
#define TAS5548_CH7_BIQUAD2_FILTER			0x7C
#define TAS5548_CH7_BIQUAD3_FILTER			0x7D
#define TAS5548_CH7_BIQUAD4_FILTER			0x7E
#define TAS5548_CH7_BIQUAD5_FILTER			0x7F
#define TAS5548_CH7_BIQUAD6_FILTER			0x80
#define TAS5548_CH7_BIQUAD7_FILTER			0x81
#define TAS5548_CH8_BIQUAD1_FILTER			0x82
#define TAS5548_CH8_BIQUAD2_FILTER			0x83
#define TAS5548_CH8_BIQUAD3_FILTER			0x84
#define TAS5548_CH8_BIQUAD4_FILTER			0x85
#define TAS5548_CH8_BIQUAD5_FILTER			0x86
#define TAS5548_CH8_BIQUAD6_FILTER			0x87
#define TAS5548_CH8_BIQUAD7_FILTER			0x88
#define TAS5548_BASS_TREB_CH1				0x89
#define TAS5548_BASS_TREB_CH2				0x8A
#define TAS5548_BASS_TREB_CH3				0x8B
#define TAS5548_BASS_TREB_CH4				0x8C
#define TAS5548_BASS_TREB_CH5				0x8D
#define TAS5548_BASS_TREB_CH6				0x8E
#define TAS5548_BASS_TREB_CH7				0x8F
#define TAS5548_BASS_TREB_CH8				0x90
#define TAS5548_LOUD_LOG2_GAIN				0x91
#define TAS5548_LOUD_LOG2_OFFSET			0x92
#define TAS5548_LOUD_GAIN	    			0x93
#define TAS5548_LOUD_OFFSET					0x94
#define TAS5548_LOUD_BIQUAD					0x95
#define TAS5548_DRC1_CTRL					0x96
#define TAS5548_DRC2_CTRL					0x97
#define TAS5548_DRC1_ENERGY					0x98
#define TAS5548_DRC1_THRES					0x99
#define TAS5548_DRC1_SLOPE					0x9A
#define TAS5548_DRC1_OFFSET					0x9B
#define TAS5548_DRC1_ATK_DCY				0x9C
#define TAS5548_DRC2_ENERGY					0x9D
#define TAS5548_DRC2_THRES					0x9E
#define TAS5548_DRC2_SLOPE					0x9F
#define TAS5548_DRC2_OFFSET					0xA0
#define TAS5548_DRC2_ATK_DCY				0xA1
#define TAS5548_DRC1_CH1					0xA2
#define TAS5548_DRC1_CH2					0xA3
#define TAS5548_DRC1_CH3					0xA4
#define TAS5548_DRC1_CH4					0xA5
#define TAS5548_DRC1_CH5					0xA6
#define TAS5548_DRC1_CH6					0xA7
#define TAS5548_DRC1_CH7					0xA8
#define TAS5548_DRC2_CH8					0xA9
#define TAS5548_OUT_SEL_MIX_PWM1			0xAA
#define TAS5548_OUT_SEL_MIX_PWM2			0xAB
#define TAS5548_OUT_SEL_MIX_PWM3			0xAC
#define TAS5548_OUT_SEL_MIX_PWM4			0xAD
#define TAS5548_OUT_SEL_MIX_PWM5			0xAE
#define TAS5548_OUT_SEL_MIX_PWM6			0xAF
#define TAS5548_OUT_SEL_MIX_PWM7			0xB0
#define TAS5548_OUT_SEL_MIX_PWM8			0xB1
#define TAS5548_EMO_COEF					0xB2
#define TAS5548_EMO_WEIGHT_CH1				0xB3
#define TAS5548_EMO_WEIGHT_CH2				0xB4
#define TAS5548_EMO_WEIGHT_CH3				0xB5
#define TAS5548_EMO_WEIGHT_CH4				0xB6
#define TAS5548_EMO_WEIGHT_CH5				0xB7
#define TAS5548_EMO_WEIGHT_CH6				0xB8
#define TAS5548_EMO_WEIGHT_CH7				0xB9
#define TAS5548_EMO_WEIGHT_CH8				0xBA
#define TAS5548_EMO_HIGH_THRES_SAT			0xBB
#define TAS5548_EMO_LOW_THRES_SAT			0xBC
#define TAS5548_EMO_HIGH_THRES_SUB			0xBD
#define TAS5548_EMO_LOW_THRES_SUB			0xBE
#define TAS5548_ASRC_STAT					0xC3
#define TAS5548_ASRC_CTRL					0xC4
#define TAS5548_ASRC_MODE					0xC5
#define TAS5548_AUTOMUTE_BHV				0xCC
#define TAS5548_PSVC_VOL_BIQUAD				0xCF
#define TAS5548_VOL_TREB_BASS_SLEW			0xD0
#define TAS5548_VOL_CH1						0xD1
#define TAS5548_VOL_CH2						0xD2
#define TAS5548_VOL_CH3						0xD3
#define TAS5548_VOL_CH4						0xD4
#define TAS5548_VOL_CH5						0xD5
#define TAS5548_VOL_CH6						0xD6
#define TAS5548_VOL_CH7						0xD7
#define TAS5548_VOL_CH8						0xD8
#define TAS5548_MASTER_VOL					0xD9
#define TAS5548_BASS_FIL_SET				0xDA
#define TAS5548_BASS_FIL_INDEX				0xDB
#define TAS5548_TREB_FIL_SET				0xDC
#define TAS5548_TREB_FIL_INDEX				0xDD
#define TAS5548_AM_MODE						0xDE
#define TAS5548_PSVC_RANGE					0xDF
#define TAS5548_GENERAL_CTRL				0xE0
#define TAS5548_DOLBY_COEFLR				0xE3
#define TAS5548_DOLBY_COEFC					0xE4
#define TAS5548_DOLBY_COEFLSP				0xE5
#define TAS5548_DOLBY_COEFRSP				0xE6
#define TAS5548_DOLBY_COEFLSM				0xE7
#define TAS5548_DOLBY_COEFRSM				0xE8
#define TAS5548_THD_MGR_PRE					0xE9
#define TAS5548_THD_MGR_POST				0xEA
#define TAS5548_SDIN5_IN_MIXER_CH1			0xEC
#define TAS5548_SDIN5_IN_MIXER_CH2			0xED
#define TAS5548_SDIN5_IN_MIXER_CH3			0xEE
#define TAS5548_SDIN5_IN_MIXER_CH4			0xEF
#define TAS5548_SDIN5_IN_MIXER_CH5			0xF0
#define TAS5548_SDIN5_IN_MIXER_CH6			0xF1
#define TAS5548_SDIN5_IN_MIXER_CH7			0xF2
#define TAS5548_SDIN5_IN_MIXER_CH8			0xF3
#define TAS5548_OUT_MIXER_CH1				0xF4
#define TAS5548_OUT_MIXER_CH2				0xF5
#define TAS5548_OUT_MIXER_CH3				0xF6
#define TAS5548_OUT_MIXER_CH4				0xF7
#define TAS5548_DOLBY_DOWNMIX_L				0xFB
#define TAS5548_DOLBY_DOWNMIX_r				0xFC
#define TAS5548_MULTI_BYTE_WRITE			0xFE





/* TAS5548 General Status */
#define TAS5548_ID_CODE						0x04

/* TAS5548 Error Status */
#define TAS5548_ERR_FRAME_SLIP				0x08
#define TAS5548_ERR_CLIP_IND				0x04
#define TAS5548_ERR_FAULTZ					0x02
#define TAS5548_ERR_NO_ERROR				0x00

/* Energy Manager Status Register */
#define TAS5548_ABOVE_LOW_THRES_SAT			0x00
#define TAS5548_BELOW_LOW_THRES_SAT			0x01
#define TAS5548_ABOVE_HIGH_THRES_SAT		0x00
#define TAS5548_BELOW_HIGH_THRES_SAT		0x02
#define TAS5548_ABOVE_LOW_THRES_SUB			0x00
#define TAS5548_BELOW_LOW_THRES_SUB			0x04
#define TAS5548_ABOVE_HIGH_THRES_SUB		0x00
#define TAS5548_BELOW_HIGH_THRES_SUB		0x08

/* Input Mixer Registers, Channels 1�C8 (0x41�C0x48) */
// #define TAS5548_IN_MIXER_CH1_A				
// #define TAS5548_IN_MIXER_CH1_B				
// #define TAS5548_IN_MIXER_CH1_C				
// #define TAS5548_IN_MIXER_CH1_D				
// #define TAS5548_IN_MIXER_CH1_E				
// #define TAS5548_IN_MIXER_CH1_F				
// #define TAS5548_IN_MIXER_CH1_G				
// #define TAS5548_IN_MIXER_CH1_H				


void tas5548_init(void);
void tas5548_mode(uint8_t iMode);
void tas5548_freqCutOff(uint8_t fCutOff);
void tas5548_masterVolume(uint8_t mVol);
void tas5548_polarity(uint8_t bPol);

