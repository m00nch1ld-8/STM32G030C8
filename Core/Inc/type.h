/**
  ******************************************************************************
  * @file			: input_process.h
  * @brief			: Header for input_process.c file.
  *					  This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * @author         : BeeHa
  * @version		: v1.0.0
  * @date created	: 2023-07-26
  *
  * @author modified: 
  * @date modified	: 2023-07-26
  * 
  * @copyright		: (C) 2023, PT. Hartono Istana Teknologi. All rights reserved.
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TYPE_H
#define __TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

/* Exported types ------------------------------------------------------------*/
typedef struct  {
	unsigned int	bit_0 : 1;
	unsigned int	bit_1 : 1;
	unsigned int	bit_2 : 1;
	unsigned int	bit_3 : 1;
	unsigned int	bit_4 : 1;
	unsigned int	bit_5 : 1;
	unsigned int	bit_6 : 1;
	unsigned int	bit_7 : 1;
} sBIT_BYTE;

typedef struct  {
	unsigned int	bit_0 : 1;
	unsigned int	bit_1 : 1;
	unsigned int	bit_2 : 1;
	unsigned int	bit_3 : 1;
	unsigned int	bit_4 : 1;
	unsigned int	bit_5 : 1;
	unsigned int	bit_6 : 1;
	unsigned int	bit_7 : 1;
	unsigned int	bit_8 : 1;
	unsigned int	bit_9 : 1;
	unsigned int	bit_10 : 1;
	unsigned int	bit_11 : 1;
	unsigned int	bit_12 : 1;
	unsigned int	bit_13 : 1;
	unsigned int	bit_14 : 1;
	unsigned int	bit_15 : 1;
} sBIT_WORD;

typedef struct  {
	unsigned int	byte_0 : 8;  	// LSB
	unsigned int	byte_1 : 8;    // MSB
} sBYTE_WORD;

typedef struct  {
	unsigned int	bit_0 : 1;
	unsigned int	bit_1 : 1;
	unsigned int	bit_2 : 1;
	unsigned int	bit_3 : 1;
	unsigned int	bit_4 : 1;
	unsigned int	bit_5 : 1;
	unsigned int	bit_6 : 1;
	unsigned int	bit_7 : 1;
	unsigned int	bit_8 : 1;
	unsigned int	bit_9 : 1;
	unsigned int	bit_10 : 1;
	unsigned int	bit_11 : 1;
	unsigned int	bit_12 : 1;
	unsigned int	bit_13 : 1;
	unsigned int	bit_14 : 1;
	unsigned int	bit_15 : 1;
	unsigned int	bit_16 : 1;
	unsigned int	bit_17 : 1;
	unsigned int	bit_18 : 1;
	unsigned int	bit_19 : 1;
	unsigned int	bit_20 : 1;
	unsigned int	bit_21 : 1;
	unsigned int	bit_22 : 1;
	unsigned int	bit_23 : 1;
	unsigned int	bit_24 : 1;
	unsigned int	bit_25 : 1;
	unsigned int	bit_26 : 1;
	unsigned int	bit_27 : 1;
	unsigned int	bit_28 : 1;
	unsigned int	bit_29 : 1;
	unsigned int	bit_30 : 1;
	unsigned int	bit_31 : 1;
} sBIT_DWORD;

typedef struct  {
	unsigned int	byte_0 : 8;		// LSB
	unsigned int	byte_1 : 8;
	unsigned int	byte_3 : 8;
	unsigned int	byte_4 : 8;		// MSB
} sBYTE_DWORD;

// +++++++++++++++++++++++++++
// +	union structure
// +++++++++++++++++++++++++++

typedef union  {
	sBIT_BYTE			bit_access;
	uint8_t				byte_access;
} sBIT_BYTE_ACCESS;

typedef union  {
	sBIT_WORD			bit_access;
	// unsigned int		word_access;
	uint16_t			word_access;
} sBIT_WORD_ACCESS;

typedef union  {
	sBYTE_WORD			byte_access;
	// unsigned int		word_access;
	uint16_t			word_access;
} sBYTE_WORD_ACCESS;

typedef union  {
	sBIT_WORD			bit_access;
	sBYTE_WORD			byte_access;
	// unsigned int		word_access;
	uint16_t			word_access;
} sBIT_BYTE_WORD_ACCESS;

typedef union  {
	sBIT_DWORD			bit_access;
	// unsigned int		word_access;
	uint32_t			dword_access;
} sBIT_DWORD_ACCESS;

typedef union  {
	sBYTE_DWORD			byte_access;
	// unsigned int		word_access;
	uint32_t			dword_access;
} sBYTE_DWORD_ACCESS;

typedef union  {
	sBIT_DWORD			bit_access;
	sBYTE_DWORD			byte_access;
	// unsigned int		word_access;
	uint32_t			dword_access;
} sBIT_BYTE_DWORD_ACCESS;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define BYTE0(val)			(((uint8_t*)(&val))[0])
#define BYTE1(val)			(((uint8_t*)(&val))[1])
#define BYTE2(val)			(((uint8_t*)(&val))[2])
#define BYTE3(val)			(((uint8_t*)(&val))[3])
/* Exported functions prototypes ---------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __TYPE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
