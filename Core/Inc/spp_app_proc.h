/**
 *******************************************************************************
 * @file    spp_app_proc.h
 * @author  Halley
 * @version V1.0.0
 * @date    26-June-2012
 * @brief   Bluetooth LE releated APIs
 * @maintainer Halley
 *******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, MVSILICON SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */
 
/**
* @addtogroup Bluetooth
* @{
* @defgroup spp_app_proc spp_app_proc
* @{
*/
 
#ifndef __SPP_APP_PROC_H__
#define __SPP_APP_PROC_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

/**
 * Command define
 */

//------------MODE------------------------
#define SLAVE_NEXT_MODE				0X0101
#define SLAVE_SELECT_MODE			0X0102
#define SLAVE_GET_MODE              0X0103
#define SLAVE_GET_DEVICE_LINK       0X0104
#define SLAVE_SELECT_MODE_PENDING	0X0105

#define SLAVE_CLEAR_DEVICE			0X0121

//------------FS--------------------------
#define SLAVE_GET_VALID_FOLDER_SUM  0X0201
#define SLAVE_GET_FILE_SUM          0X0202
#define SLAVE_GET_FOLDER_INFO       0X0203
#define SLAVE_GET_FILE_INFO         0X0204
#define SLAVE_GET_FOLDER_LONG_NAME  0X0205

//------------PLAYER----------------------
#define SLAVE_PLAY                  0X0301
#define SLAVE_PAUSE                 0X0302
#define SLAVE_STOP                  0X0303
#define SLAVE_NEXT                  0X0304
#define SLAVE_PRE                   0X0305
#define SLAVE_PLAY_PAUSE            0X0306
#define SLAVE_FF                    0X0307
#define SLAVE_FB                    0X0308
#define SLAVE_STOP_FF_FB            0X0309
#define SLAVE_SEEK_PLAY_TIME        0X030A
#define SLAVE_NEXT_FOLDER        	0X030B
#define SLAVE_PRE_FOLDER        	0X030C
#define SLAVE_SELECT_SONG        	0X030D


#define SLAVE_GET_PLAY_STATUS       0X0320
#define SLAVE_GET_SONG_INFO         0X0321
#define SLAVE_SET_REPEAT_MODE       0X0322
#define SLAVE_GET_REPEAT_MODE       0X0323
#define SLAVE_ENABLE_FOLDER         0X0324
#define SLAVE_DISABLE_FOLDER        0X0325
#define SLAVE_SEND_REPEAT_MODE     	0X0326


#define SLAVE_GET_TITLE             0X0330
#define SLAVE_GET_ARTIST            0X0331
#define SLAVE_GET_ALBUM             0X0332
#define SLAVE_GET_COMMENT           0X0333
#define SLAVE_GET_YEAR              0X0334


#define SLAVE_VOLADD                0X0401
#define SLAVE_VOLSUB                0X0402
#define SLAVE_SET_VOL               0X0403
#define SLAVE_GET_VOL               0X0404
#define SLAVE_SET_EQ                0X0405
#define SLAVE_GET_EQ                0X0406
#define SLAVE_MUTE                  0X0407
#define SLAVE_UNMUTE                0X0408
//#define SLAVE_SET_LINEIN_CHANNEL    0X0409
#define SLAVE_SET_LINEIN_GAIN       0X0409
#define SLAVE_ENABLE_MIC            0X040A
#define SLAVE_DISABLE_MIC           0X040B

#define SLAVE_BASS_ADD              0X040C
#define SLAVE_BASS_SUB              0X040D
#define SLAVE_SET_BASS              0X040E
#define SLAVE_GET_BASS              0X040F

#define SLAVE_MIDD_ADD              0X0410
#define SLAVE_MIDD_SUB              0X0411
#define SLAVE_SET_MIDD              0X0412
#define SLAVE_GET_MIDD              0X0413

#define SLAVE_TREB_ADD              0X0414
#define SLAVE_TREB_SUB              0X0415
#define SLAVE_SET_TREB              0X0416
#define SLAVE_GET_TREB              0X0417

#define SLAVE_MICLV_ADD				0X0418
#define SLAVE_MICLV_SUB   			0X0419
#define SLAVE_SET_MICLV   			0X041A
#define SLAVE_GET_MICLV   			0X041B

#define SLAVE_ECHOLV_ADD   			0X041C
#define SLAVE_ECHOLV_SUB   			0X041D
#define SLAVE_SET_ECHOLV   			0X041E
#define SLAVE_GET_ECHOLV   			0X041F

#define SLAVE_SBASS_ADD   			0X0420
#define SLAVE_SBASS_SUB   			0X0421
#define SLAVE_SET_SBASS   			0X0422
#define SLAVE_GET_SBASS   			0X0423

#define SLAVE_SET_KARAOKE           0X0424
#define SLAVE_GET_KARAOKE           0X0425

#define SLAVE_SET_BAZOKE1           SLAVE_SET_BAZOKE
#define SLAVE_GET_BAZOKE            0X0427

#define SLAVE_SET_SURROUND          0X0428
#define SLAVE_GET_SURROUND          0X0429

#define SLAVE_SET_MIC_PRIORITY      0X042A
#define SLAVE_GET_MIC_PRIORITY      0X042B


#define SLAVE_SET_RECORD            0x042C
#define SLAVE_GET_RECORD            0x042D

#define SLAVE_REC_FILE_DEL          0x042E
#define SLAVE_REC_MUSIC_CTRL        0x042F

#define SLAVE_SET_MIC_EFFECT        0X0430
#define SLAVE_GET_MIC_EFFECT        0X0431

#define SLAVE_REVBLV_ADD            0X0432
#define SLAVE_REVBLV_SUB            0X0433
#define SLAVE_SET_REVBLV            0X0434
#define SLAVE_GET_REVBLV            0X0435

#define SLAVE_MIC_SET_EQ            0x0436
#define SLAVE_MIC_GET_EQ            0x0437

#define SLAVE_SET_BTPIN             0x0438

#define SLAVE_SET_SWF_FREQ	        0x0439
#define SLAVE_GET_SWF_FREQ	        0x043A
#define SLAVE_SET_SWF_PHASE	        0x043B
#define SLAVE_GET_SWF_PHASE	        0x043C
#define SLAVE_SET_SWF_LFE	        0x043D
#define SLAVE_GET_SWF_LFE	        0x043E

//------------RTC-------------------------
#define SLAVE_SET_TIME              0X0501
#define SLAVE_GET_TIME              0X0502
#define SLAVE_SET_ALARM_TIME        0X0503
#define SLAVE_GET_ALARM_TIME        0X0504
#define SLAVE_ENABLE_ALARM			0x0505
#define SLAVE_DISABLE_ALARM			0x0506
#define SLAVE_GET_ALARM_STATUS      0X0507
#define SLAVE_GET_ALARM_FLAG		0x0508
#define SLAVE_GET_MONTH_DAYS        0X0510
#define SLAVE_SOLAR_TO_LUNAR        0X0511
#define SLAVE_GET_HEAVENLY_STEM     0X0512
#define SLAVE_GET_EARTHLY_BRANCH    0X0513
#define SLAVE_SET_TIMER_ON        	0X0514
#define SLAVE_GET_TIMER_ON        	0X0515
#define SLAVE_SET_TIMER_OFF        	0X0516
#define SLAVE_GET_TIMER_OFF        	0X0517
#define SLAVE_SET_SLEEP_TIME        0X0518
#define SLAVE_GET_SLEEP_TIME        0X0519

// #ifdef GENERAL_ALARM
#define SLAVE_SET_GEN_ALARM_TIME    0X051a      // add SY
#define SLAVE_GET_GEN_ALARM_TIME    0X051b      // add SY
// #endif

//------------GPIO-----------------------
#define SLAVE_SET_GPIO_REG          0X0601
#define SLAVE_GET_GPIO_REG          0X0602
#define SLAVE_SET_GPIO_REG_BIT      0X0603
#define SLAVE_CLR_GPIO_REG_BIT      0X0604


#define SLAVE_ENABLE_ADC_CHANNEL    0X0701
#define SLAVE_DISABLE_ADC_CHANNEL   0X0702
#define SLAVE_GET_ADC_CHANNEL_VALUE 0X0703
#define SLAVE_GET_VIN_VOLTAGE       0X0704


#define SLAVE_PWM_CONFIG_CHANNEL    0X0801
#define SLAVE_ENABLE_PWM_CHANNEL    0X0802
#define SLAVE_DISABLE_PWM_CHANNEL   0X0803


#define SLAVE_SET_WAKEUP_MODE       0X0901
#define SLAVE_GOTO_DEEP_SLEEP       0X0902

//------------RADIO-----------------------
#define SLAVE_SET_RADIO_PARAM       0X0A01
#define SLAVE_SET_RADIO_FREQ        0X0A02
#define SLAVE_NEXT_STEP        		0X0A03
#define SLAVE_PREV_STEP        		0X0A04
#define SLAVE_NEXT_STATION        	0X0A05
#define SLAVE_PREV_STATION        	0X0A06
#define SLAVE_AUTO_SCAN        		0X0A07
#define SLAVE_NEXT_SEEK        		0X0A08
#define SLAVE_PREV_SEEK        		0X0A09
#define SLAVE_SAVE_STATION        	0X0A0A
#define SLAVE_SET_MONO_MODE        	0X0A0B
#define SLAVE_GET_CUR_STATUS       	0X0A0C
#define SLAVE_GET_STORED_STATION    0X0A0D
#define SLAVE_SAVE_MEM_USED		    0X0A0E
#define SLAVE_GOTO_STATION		    0X0A0F
#define SLAVE_CLEAR_STATION		    0X0A10
#define SLAVE_AUTOSCAN_STATUS		0x0A11


//------------compabilitas PMA------------
#define SLAVE_GET_SET_TYPE		    0X0B01
#define SLAVE_REQUEST_PTM       	0X0B02
#define SLAVE_PLAY_STATUS_CUSTOM	0X0B03

#define SLAVE_GET_VOLUME_CHECK		0X0B04
#define SLAVE_VOLUME_CHECK			0X0B05

#define SLAVE_FM_FREQ_CHECK			0X0B06
#define SLAVE_FM_FREQ_SAVE			0X0B07
#define SLAVE_FM_STATION_LOAD		0X0B08

#define SLAVE_AMBIENT_LIGHT			0X0B09
#define SLAVE_SET_BAZOKE			0X0B0A  // 20180716 kompabilitas PMA, tambah cmd baru
#define SLAVE_BAZZOKE_LIGHT_STATUS	0x0B0B	
#define SLAVE_3D_EFFECT				0x0B0C


#define SLAVE_CHECK_SW_VERSION		0x0B21

//=====================


//------------PACKET DATA-----------------
#define SLAVE_LIGHT_CHECK           0X0B12//81 // 0b12
#define SLAVE_TONECONTROL_CHECK		0X0B13
#define SLAVE_KARAOKE_CHECK			0X0B14


//------------DVD----------------------
#define SLAVE_DVD	                0x0C01
#define SLAVE_DVD_PLAYER_STATE	    0x0C02
#define SLAVE_DVD_PLAY_MODE	        0x0C03
#define SLAVE_DVD_FILE_INDEX	    0x0C04
#define SLAVE_DVD_PLAYING_TIME	    0x0C05
#define SLAVE_DVD_CONTENT           0x0C06




//------------REMOTE----------------------
#define SLAVE_REMOTE_DATA	        0X0D01

//------------WIRELESS MIC----------------
#define SLAVE_WIRELESS_MIC_STATUS	0X0E01
#define SLAVE_WIRELESS_MIC_SETTING	0X0E02
#define SLAVE_WIRELESS_MIC_SCAN	    0X0E03

//------------WHITEGOODS------------------
#define SLAVE_WHITEGOODS_TIME	    0X1001
#define SLAVE_WHITEGOODS_TEMP	    0X1002
#define SLAVE_WHITEGOODS_SPEED	    0X1003
#define SLAVE_WHITEGOODS_PARAM	    0X1004
#define SLAVE_WHITEGOODS_STATUS	    0X1005
#define SLAVE_WHITEGOODS_KEY	    0X1006






//------------SPECIAL FUNCTION------------
#define SLAVE_ENABLE_VIRTUAL_BASS   0X7001
#define SLAVE_DISABLE_VIRTUAL_BASS  0X7002

#define SLAVE_SET_BATTERY           0X7101
#define SLAVE_GET_BATTERY           0X7102

#define SLAVE_SET_LOCKING           0X7201
#define SLAVE_GET_LOCKING           0X7202




/**
 * Defines
 */

//#define BYTE0(val)			(((uint8_t*)(&val))[0])
//#define BYTE1(val)			(((uint8_t*)(&val))[1])
//#define BYTE2(val)			(((uint8_t*)(&val))[2])
//#define BYTE3(val)			(((uint8_t*)(&val))[3])
//
//#define WORD0(val)			(((uint16_t*)(&val))[0])
//#define WORD1(val)			(((uint16_t*)(&val))[1])



/**
 * @brief
 *  	Clear data in buffer, -1 means clear all data
 *
 * @param Size The size of data to be cleared
 *
 * @return
 *		NONE
 *
 * @note
 *		
 */
void  SppFlushRecBuf(int16_t Size);

/**
 * @brief
 *  	Send data. The maximum size of the buffer can be sent
 *		is SppGetSendBufFreeSize()
 *
 * @param Buf Data to be sent
 * @param Size The size of data to be sent
 *
 * @return
 *		The actual size of data have been sent
 *
 * @note
 *		
 */
//uint16_t  SppSendData(uint8_t* Buf, uint16_t Size);

/**
 * @brief
 *  	Get the free size of buffer that could be sent
 *
 * @param NONE
 *
 * @return
 *		The size of the buffer
 *
 * @note
 *		
 */
int16_t SppGetSendBufFreeSize(void);

/**
 * @brief
 *  	Get the data in the read buffer
 *
 * @param Buf Buffer to receive the data
 * @param Len The length of data to be read
 *
 * @return
 *		The actual length of data to be read
 *
 * @note
 *		
 */
uint16_t  SppReadData(uint8_t* Buf, uint16_t Len);

/**
 * @brief
 *  	Get the size of the receive buffer
 *
 * @param NONE
 *
 * @return
 *		The the size of the receive buffer
 *
 * @note
 *		
 */
uint16_t  SppGetRecBufDataSize(void);        //��ȡ��ǰ���ջ�������������С

/**
 * @brief
 *  	Get the size of free buffer
 *
 * @param NONE
 *
 * @return
 *		the size of the free buffer
 *
 * @note
 *		
 */
int32_t SppGetWRingFreeSpace(void);

#define SppGetSendBufFreeSize() SppGetWRingFreeSpace()


/**
* The following functions is used in stack
*/
uint8_t *SppGetWorkParameterByte1(void);
uint8_t *SppGetWorkParameterByte2(void);
#define SppGetWorkParAppFuncID   SppGetWorkParameterByte1
#define SppGetWorkParProcStatus  SppGetWorkParameterByte2

uint16_t *SppGetWorkParameterWord1(void);
uint16_t *SppGetWorkParameterWord2(void);
#define SppGetWorkParWorkBufFillSize SppGetWorkParameterWord1
#define SppGetWorkParAppWantDataSize SppGetWorkParameterWord2

uint8_t *SppGetWorkBuf(void);
uint16_t SppGetWorkBufLen(void);

#ifdef __cplusplus
}
#endif//__cplusplus

#endif

/**
 * @}
 * @}
 */
