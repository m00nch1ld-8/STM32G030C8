/**
	******************************************************************************
	* @file				: mcu_circular_buf.h
	* @brief			: Header for mcu_circular_buf.c file.
	*					  This file contains the common defines of the application.
	******************************************************************************
	* @attention
	*
	* @author			: BeeHa
	* @version			: v1.0.0
	* @date created		: 2024-05-28
	*
	* @author modified	:
	* @date modified	:
	*
	* @copyright		: (C) 2024, PT. Hartono Istana Teknologi. All rights reserved.
	*
	******************************************************************************
	*/
#ifndef		__MCU_CIRCULAR_BUF_H__
#define		__MCU_CIRCULAR_BUF_H__

#include "type.h"

typedef struct __MCU_CIRCULAR_CONTEXT__
{
	uint32_t    R;              //Loop buf reading pointer, byte number
	uint32_t    W;              //Loop buf writing pointer, byte number
	uint32_t    BufDepth;       //Loop length, number of bytes
	int8_t*     CircularBuf;    //Loop buf pointer
} MCU_CIRCULAR_CONTEXT;

extern MCU_CIRCULAR_CONTEXT OTGCircularBuf;

/*
 * Software loop fifo configuration
 */
void MCUCircular_Config(MCU_CIRCULAR_CONTEXT* CircularBuf, void* Buf, uint32_t Len);

/*
 * Get the remaining space length of the loop fifo, in Byte
 * Note: The overlap of read and write pointers only occurs when the MCU loop fifo is initialized or empty.
 * The system needs to control the water level when writing data to the fifo to prevent it from being full.
 */
int32_t MCUCircular_GetSpaceLen(MCU_CIRCULAR_CONTEXT* CircularBuf);

/*
 * Store data in the loop fifo
 * Note: The overlap of read and write pointers only occurs when the MCU loop fifo is initialized or empty.
 * The system needs to control the water level when writing data to the fifo to prevent it from being full.
 */
void MCUCircular_PutData(MCU_CIRCULAR_CONTEXT* CircularBuf, void* InBuf, uint16_t Len);

/*
 * Read data into loop fifo
 */
int32_t MCUCircular_GetData(MCU_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

/*
 * Get the effective data length of the loop fifo, unit is Byte
 */
uint16_t MCUCircular_GetDataLen(MCU_CIRCULAR_CONTEXT* CircularBuf);

/*
 * Discard data in loop fifo
 */
int32_t MCUCircular_AbortData(MCU_CIRCULAR_CONTEXT* CircularBuf, uint16_t MaxLen);


/*
 * Read new data from fifo without changing the read pointer or data length.
 */
int32_t MCUCircular_ReadData(MCU_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);


typedef struct __MCU_DOUBLE_CIRCULAR_CONTEXT__
{
	uint32_t    R1;				//Loop buf read pointer, byte number
	uint32_t    R2;				//Loop buf second read pointer, byte number, R2 is located at the data position between R1 and W.
	uint32_t    W;				//Loop buf write pointer, byte number
	uint32_t    BufDepth;		//Loop length, number of bytes
	int8_t*     CircularBuf;	//Loop buf pointer
} MCU_DOUBLE_CIRCULAR_CONTEXT;


/*
 * Software loop fifo configuration
 */
void MCUDCircular_Config(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* Buf, uint32_t Len);

/*
 * Get the remaining space length of the loop fifo, in Byte
 * Note: The overlap of read and write pointers only occurs when the MCU loop fifo is initialized or empty.
 * The system needs to control the water level when writing data to the fifo to prevent it from being full.
 */
int32_t MCUDCircular_GetSpaceLen(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf);

/*
 * Store data in the loop fifo
 * Note: The overlap of read and write pointers only occurs when the MCU loop fifo is initialized or empty.
 * The system needs to control the water level when writing data to the fifo to prevent it from being full.
 */
void MCUDCircular_PutData(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* InBuf, uint16_t Len);

/*
 * Read data into loop fifo
 */
int32_t MCUDCircular_GetData1(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

/*
 * Get the effective data length of the loop fifo, unit is Byte
 */
uint16_t MCUDCircular_GetData1Len(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf);

/*
 * Read data into the loop fifo without changing the read and write pointers
 */
int32_t MCUDCircular_ReadData1(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

/*
 * Read data into loop fifo
 */
int32_t MCUDCircular_GetData2(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf, void* OutBuf, uint16_t MaxLen);

/*
 * Get the effective data length of the loop fifo, unit is Byte
 */
uint16_t MCUDCircular_GetData2Len(MCU_DOUBLE_CIRCULAR_CONTEXT* CircularBuf);





#endif
