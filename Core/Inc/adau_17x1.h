/**
	******************************************************************************
	* @file			: adau_17x1.h
	* @brief			: Header for adau_17x1.c file.
	*					  This file contains the common defines of the application.
	******************************************************************************
	* @attention
	*
	* @author         : BeeHa
	* @version		: v1.0.0
	* @date created	: 2024-04-16
	*
	* @author modified:
	* @date modified	:
	*
	* @copyright		: (C) 2024, PT. Hartono Istana Teknologi. All rights reserved.
	*
	******************************************************************************
	*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef INC_ADAU_17X1_H_
#define INC_ADAU_17X1_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/
#include "stdint.h"
#include "stm32g0xx_hal.h"

extern I2C_HandleTypeDef hi2c2;
#define DEVICE_ADDR_IC_1                          0x38
#define ADAU_ADDR_WRITE							  0x70
#define ADAU_ADDR_READ							  0x71

#define ADAU_ADDR_DSP_SAMPLING_RATE_0			0x40EB
#define ADAU_ADDR_DSP_RUN_0						0x40F6
#define ADAU_ADDR_CLOCK_CONTROL					0x4000
#define ADAU_ADDR_PLL_CONTROL					0x4002
#define ADAU_ADDR_SERIAL_PORT					0x4015
#define ADAU_ADDR_ALC							0x4011
#define ADAU_ADDR_DIG_MIG						0x4008
#define ADAU_ADDR_REC_POWER_MGMT				0x4009
#define ADAU_ADDR_ADC_CONTROL					0x4019
#define ADAU_ADDR_PLAY_MIXER					0x401C
#define ADAU_ADDR_CONVERTER						0x4017
#define ADAU_ADDR_DAC_CONTROL					0x402A
#define ADAU_ADDR_SERIAL_PORT_PAD				0x402D
#define ADAU_ADDR_CONTROL_PORT_PAD				0x402F
#define ADAU_ADDR_JACK_DETECT					0x4031
#define ADAU_ADDR_CLEAR_RAM_00					0x0800
#define ADAU_ADDR_CLEAR_RAM_01					0x080C
#define ADAU_ADDR_CLEAR_RAM_02					0x0818
#define ADAU_ADDR_CLEAR_RAM_03					0x0824
#define ADAU_ADDR_CLEAR_RAM_04					0x0830
#define ADAU_ADDR_CLEAR_RAM_05					0x083C
#define ADAU_ADDR_CLEAR_RAM_06					0x0848
#define ADAU_ADDR_CLEAR_RAM_07					0x0854
#define ADAU_ADDR_CLEAR_RAM_08					0x0860
#define ADAU_ADDR_CLEAR_RAM_09					0x086C
#define ADAU_ADDR_CLEAR_RAM_10					0x0878
#define ADAU_ADDR_CLEAR_RAM_11					0x0884
#define ADAU_ADDR_CLEAR_RAM_12					0x0890
#define ADAU_ADDR_CLEAR_RAM_13					0x089C
#define ADAU_ADDR_CLEAR_RAM_14					0x08A8
#define ADAU_ADDR_CLEAR_RAM_15					0x08B4
#define ADAU_ADDR_CLEAR_RAM_16					0x08C0
#define ADAU_ADDR_CLEAR_RAM_17					0x08CC
#define ADAU_ADDR_CLEAR_RAM_18					0x08D8
#define ADAU_ADDR_CLEAR_RAM_19					0x08E4
#define ADAU_ADDR_CLEAR_RAM_20					0x08F0
#define ADAU_ADDR_CLEAR_RAM_21					0x08FC
#define ADAU_ADDR_CLEAR_RAM_22					0x0908
#define ADAU_ADDR_CLEAR_RAM_23					0x0914
#define ADAU_ADDR_CLEAR_RAM_24					0x0920
#define ADAU_ADDR_CLEAR_RAM_25					0x092C
#define ADAU_ADDR_CLEAR_RAM_26					0x0938
#define ADAU_ADDR_CLEAR_RAM_27					0x0944
#define ADAU_ADDR_CLEAR_RAM_28					0x0950
#define ADAU_ADDR_CLEAR_RAM_29					0x095C
#define ADAU_ADDR_CLEAR_RAM_30					0x0968
#define ADAU_ADDR_CLEAR_RAM_31					0x0974
#define ADAU_ADDR_CLEAR_RAM_32					0x0980
#define ADAU_ADDR_CLEAR_RAM_33					0x098C
#define ADAU_ADDR_CLEAR_RAM_34					0x0998
#define ADAU_ADDR_CLEAR_RAM_35					0x09A4
#define ADAU_ADDR_CLEAR_RAM_36					0x09B0
#define ADAU_ADDR_CLEAR_RAM_37					0x09BC
#define ADAU_ADDR_CLEAR_RAM_38					0x09C8
#define ADAU_ADDR_CLEAR_RAM_39					0x09D4
#define ADAU_ADDR_CLEAR_RAM_40					0x09E0
#define ADAU_ADDR_CLEAR_RAM_41					0x09EC
#define ADAU_ADDR_CLEAR_RAM_42					0x09F8
#define ADAU_ADDR_CLEAR_RAM_43					0x0A04
#define ADAU_ADDR_CLEAR_RAM_44					0x0A10
#define ADAU_ADDR_CLEAR_RAM_45					0x0A1C
#define ADAU_ADDR_CLEAR_RAM_46					0x0A28
#define ADAU_ADDR_CLEAR_RAM_47					0x0A34
#define ADAU_ADDR_CLEAR_RAM_48					0x0A40
#define ADAU_ADDR_CLEAR_RAM_49					0x0A4C
#define ADAU_ADDR_CLEAR_RAM_50					0x0A58
#define ADAU_ADDR_CLEAR_RAM_51					0x0A64
#define ADAU_ADDR_CLEAR_RAM_52					0x0A70
#define ADAU_ADDR_CLEAR_RAM_53					0x0A7C
#define ADAU_ADDR_CLEAR_RAM_54					0x0A88
#define ADAU_ADDR_CLEAR_RAM_55					0x0A94
#define ADAU_ADDR_CLEAR_RAM_56					0x0AA0
#define ADAU_ADDR_CLEAR_RAM_57					0x0AAC
#define ADAU_ADDR_CLEAR_RAM_58					0x0AB8
#define ADAU_ADDR_CLEAR_RAM_59					0x0AC4
#define ADAU_ADDR_CLEAR_RAM_60					0x0AD0
#define ADAU_ADDR_CLEAR_RAM_61					0x0ADC
#define ADAU_ADDR_CLEAR_RAM_62					0x0AE8
#define ADAU_ADDR_CLEAR_RAM_63					0x0AF4
#define ADAU_ADDR_CLEAR_RAM_64					0x0B00
#define ADAU_ADDR_CLEAR_RAM_65					0x0B0C
#define ADAU_ADDR_CLEAR_RAM_66					0x0B18
#define ADAU_ADDR_CLEAR_RAM_67					0x0B24
#define ADAU_ADDR_CLEAR_RAM_68					0x0BFC
#define ADAU_ADDR_DSP_ENABLE					0x40F5
#define ADAU_ADDR_CRC							0x40C0
#define ADAU_ADDR_GPIO_PIN_CONTROL				0x40C6
#define ADAU_ADDR_NON_MODULO_RAM				0x40E9
#define ADAU_ADDR_WATCHDOG_EN					0x40D0
#define ADAU_ADDR_DSP_SAMPLING_RATE_1			0x40EB
#define ADAU_ADDR_SERIAL_IN_CONTROL				0x40F2
#define ADAU_ADDR_SERIAL_OUT_CONTROL			0x40F3
#define ADAU_ADDR_SERIAL_DATA_CONFIG			0x40F4
#define ADAU_ADDR_DSP_SLEW_MODE					0x40F7
#define ADAU_ADDR_SERIAL_PORT_SAMPLING_RATE		0x40F8
#define ADAU_ADDR_CLOCK_ENABLE					0x40F9
#define ADAU_ADDR_PROGRAM_RAM_00				0x0800
#define ADAU_ADDR_PROGRAM_RAM_01				0x080C
#define ADAU_ADDR_PROGRAM_RAM_02				0x0818
#define ADAU_ADDR_PROGRAM_RAM_03				0x0824
#define ADAU_ADDR_PROGRAM_RAM_04				0x0830
#define ADAU_ADDR_PROGRAM_RAM_05				0x083C
#define ADAU_ADDR_PROGRAM_RAM_06				0x0848
#define ADAU_ADDR_PROGRAM_RAM_07				0x0854
#define ADAU_ADDR_PROGRAM_RAM_08				0x0860
#define ADAU_ADDR_PROGRAM_RAM_09				0x086C
#define ADAU_ADDR_PROGRAM_RAM_10				0x0878
#define ADAU_ADDR_PROGRAM_RAM_11				0x0884
#define ADAU_ADDR_PROGRAM_RAM_12				0x0890
#define ADAU_ADDR_PROGRAM_RAM_13				0x089C
#define ADAU_ADDR_PROGRAM_RAM_14				0x08A8
#define ADAU_ADDR_PROGRAM_RAM_15				0x08B4
#define ADAU_ADDR_PROGRAM_RAM_16				0x08C0
#define ADAU_ADDR_PROGRAM_RAM_17				0x08CC
#define ADAU_ADDR_PROGRAM_RAM_18				0x08D8
#define ADAU_ADDR_PROGRAM_RAM_19				0x08E4
#define ADAU_ADDR_PROGRAM_RAM_20				0x08F0
#define ADAU_ADDR_PROGRAM_RAM_21				0x08FC
#define ADAU_ADDR_PARAMETER_RAM_0				0x0000
#define ADAU_ADDR_PARAMETER_RAM_1				0x000F
#define ADAU_ADDR_PARAMETER_RAM_2				0x001E
#define ADAU_ADDR_PARAMETER_RAM_3				0x002D
#define ADAU_ADDR_PARAMETER_RAM_4				0x003C
#define ADAU_ADDR_PARAMETER_RAM_5				0x004B
#define ADAU_ADDR_PARAMETER_RAM_6				0x005A
#define ADAU_ADDR_PARAMETER_RAM_7				0x0069
#define ADAU_ADDR_PARAMETER_RAM_8				0x0078
#define ADAU_ADDR_DSP_SAMPLING_RATE_2			0x40EB
#define ADAU_ADDR_DSP_RUN_1						0x40F6
#define ADAU_ADDR_DEJITTER_CONTROL_0			0x4036
#define ADAU_ADDR_DEJITTER_CONTROL_1			0x4036


/*    From USER_SETTINGS.h    */

#define DSP_TYPE_SIGMA100     1    // Sigma100: ADAU1701/ADAU1702/ADAU1401
#define DSP_TYPE_SIGMA200     2    // Sigma200: ADAU176x/ADAU178x/ADAU144x
#define DSP_TYPE_SIGMA300_350 3    // Sigma300/Sigma350: ADAU145x, ADAU146x

// Which type of DSP is connected?
#define DSP_TYPE DSP_TYPE_SIGMA100

/** If true, the DSP is programmed over SPI. If false, the DSP is programmed over I2C.
 * NOTE: On the example schematic I2C and SPI pins from the microcontroller are connected to
 * the same pins (because Sigma300/Sigma350 multiplex the I2C and SPI pins). The setup
 * function in main.cpp tristates the unused interface to avoid contention between I2C
 * and SPI pins.
 * NOTE: Sigma100 and Sigma200 place I2C on different USBi pins than Sigma300/Sigma350, again due
 * to pin multiplexing. This is why SDA and SCL will each appear twice on the USBi header in
 * the example schematic.
 */
// #define ADAU_USE_SPI

#ifdef ADAU_USE_SPI
#include <SPI.h>

/** Set the SPI bus to run at a clock speed of 1MHz.
 * Very high SPI speeds (>15 MHz) may require shorter programmer cabling for sufficient signal
 * integrity. Keep the SPI speed low (~1MHz) the first time programming the DSP, once the code is
 * working try increasing the bus speed. SPI signal integrity should be verified on an oscilloscope. Some
 * SigmaDSPs have higher maximum SPI speeds than others. Check the datasheet of your DSP for the maximum
 * allowed SPI speed.
 */
#define SPI_SPEED 1000000

const SPISettings settingsA(SPI_SPEED, MSBFIRST, SPI_MODE3);// Store SPI transaction information to settingsA
#else // ADAU_USE_SPI
/**
 * Set the I2C bus to run at a clock speed of 400kHz (fast mode). I2C signal integrity
 * should be verified on an oscilloscope. Don't forget I2C pullup resistors!
 */
#define I2C_SPEED 400000
#endif // ADAU_USE_SPI

// Store mapping to USBi header here
#define DSP_RESET_PIN PB7    // Any GPIO will work
#define DSP_SS_PIN    10

/** By default, SPI instantiates to the main SPI port.
 * MOSI -> pin 11
 * MISO -> pin 12
 * SLCK -> pin 13
 * NOTE: Pin 13 is the built in LED pin on Teensy 4. Lift the LED off the board to avoid unwanted
 * loading of the SCLK pin. You may also change the SPI initializer to use alternate pins. Not
 * every pin can be used as an alternate; refer to Teensy documentation.
 *
 * By default, I2C is mapped to hardware I2C instance 0.
 * SCL -> pin 19
 * SDA -> pin 18
 */

/** If SigmaStudio is set to use the DSP in SPI mode (default for Sigma300/Sigma350), the
 * SigmaStudio exported device address is 0x00. This causes issues if the microcontroller needs to
 * program the DSP over I2C. If OVERRIDE_SIGMASTUDIO_DEVICE_ADDRESS is true, SigmaStudioFW.cpp will
 * use the following device address instead of the one passed to it by argument. The Wire library
 * uses 7-bit I2C addressing, so the R/W bit is omitted from the device address.
 * NOTE: Manually overwriting DEVICE_ADDR_IC_1 in the SigmaStudio exported file is not a good idea
 * because the file will be re-created scratch every time a new SigmaStudio export is performed. It
 * is better to store this configuration data here. NOTE: Additional software logic will be needed
 * if more than one SigmaDSP IC is connected simultaneously.
 */
extern uint8_t DSP_I2C_ADDR;

/*    From SigmaStudioFW.h    */
/*
 * Parameter data format
 */
#define SIGMASTUDIOTYPE_FIXPOINT 0
#define SIGMASTUDIOTYPE_INTEGER  1

/*
 * Convert a floating-point value to SigmaDSP (5.23 or 8.24) fixed point format
 */
// #if DSP_TYPE == DSP_TYPE_SIGMA300_350
// uint32_t SIGMASTUDIOTYPE_FIXPOINT_CONVERT(uint16_t value) { return (uint32_t)(value * (0x01 << 24)); }
// #else
// uint32_t SIGMASTUDIOTYPE_FIXPOINT_CONVERT(uint16_t value) { return (uint32_t)(value * (0x01 << 23)) & 0xFFFFFFF; }
// #endif

// For compatibility with certain export files, redirect SIGMASTUDIOTYPE_8_24_CONVERT to
// SIGMASTUDIOTYPE_FIXPOINT_CONVERT
// #define SIGMASTUDIOTYPE_8_24_CONVERT(x) SIGMASTUDIOTYPE_FIXPOINT_CONVERT(x)

// Separate a 32-bit floating point value into four bytes
// void SIGMASTUDIOTYPE_REGISTER_CONVERT(uint32_t fixpt_val, uint8_t dest[4]) {
//     dest[0] = (fixpt_val >> 24) & 0xFF;
//     dest[1] = (fixpt_val >> 16) & 0xFF;
//     dest[2] = (fixpt_val >> 8) & 0xFF;
//     dest[3] = (fixpt_val)&0xFF;
// }

// The I2C buffer declared by Arduino is 32 bytes long by default. Adjust for your processor.
// Longer buffers use more microcontroller RAM, but allow faster programming
// because I2C overhead is lower.
// The two address bytes shorten the data burst size by 2 bytes.
// const uint8_t MAX_I2C_DATA_LENGTH = 30;

/** Return the depth (in bytes) of a certain DSP memory location.
 * Currently this function is only implemented for data memory and program memory.
 * Control registers are not included.
 * Function is only required for I2C; it exists because of buffer size limitations in the Teensy I2C library.
 */
#ifndef ADAU_USE_SPI
// uint8_t getMemoryDepth(uint32_t address) {
// #if DSP_TYPE == DSP_TYPE_SIGMA100
//     if (address < 0x0400)
//         return 4;    // Parameter RAM is 4 bytes deep
//     else {
//         return 5;    // Program RAM is 5 bytes deep
//     }
// #elif DSP_TYPE == DSP_TYPE_SIGMA200
//     // Based on ADAU1761
//     if (address < 0x0800) {
//         return 4;    // Parameter RAM is 4 bytes deep
//     } else {
//         return 5;
//     }
// #elif (DSP_TYPE == DSP_TYPE_SIGMA300_350)
//     if (address < 0xF000) {
//         return 4;    // Program Memory, DM0, and DM1 all store 4 bytes (ADAU1463 datasheet
//                      // page 90)
//     } else {
//         return 2;    // Control registers all store 2 bytes (ADAU1463 datasheet page 93)
//     }
// #else
//     return 0;    // We should never reach this return
// #endif
// }
#endif

// void SIGMA_WRITE_REGISTER_BLOCK(uint8_t devAddress, uint16_t address, uint16_t length, uint8_t pData[]) {
// #ifdef ADAU_USE_SPI    // Start of function for SPI write
//     // Assert SPI slave select line
//     digitalWrite(DSP_SS_PIN, LOW);        // Assert SPI slave select line (active low)
//     SPI.beginTransaction(settingsA);      // Initialize SPI
//     SPI.transfer(0x0);                    // SPI read address + read/!write bit
//     SPI.transfer(address >> 8);           // High uint8_t of address
//     SPI.transfer(address & 0xff);         // Low uint8_t of address
//     for (uint8_t i = 0; i < length; i++) {    // For each data uint8_t in the packet...
//         SPI.transfer(pData[i]);           // Write the data uint8_t to the DSP
//     }
//     SPI.endTransaction();              // Release the SPI bus
//     digitalWrite(DSP_SS_PIN, HIGH);    // Pull up the slave select line
// // End of function for SPI write
// #else     // Start of function for I2C write

//     /* The Teensy does not have a large I2C buffer. If a very large I2C message is requested, it
//      * needs to be split up into multiple smaller messages.
//      * Depending on the DSP in use, different memory locations may have a different bit depth.
//      * For example, on the ADAU1701, address 0x0807 holds 4 bytes and address 0x0808 holds 2
//      * bytes. To account for this SigmaStudio writes control registers one at a time. Data
//      * memory and program memory transfers are called as very long writes (potentially >4k
//      * words). For these writes, the getMemoryDepth function is used to keep track of
//      * addressing.
//      *
//      * The following code assumes that any write will not pass a memory boundary, e.g. DM0 and
//      * DM1 must be split into separate function calls. Files exported from SigmaStudio should be
//      * fine.
//      */
//     // uint8_t sendData[length+2];
//     // uint8_t i = 0;

//     // sendData[0] = address >> 8;
//     // sendData[1] = address & 0xFF;
//     // for(i = 0; i < length; i++)
//     // {
//     //     sendData[i+2] = pData[i];
//     // }
//     // HAL_I2C_Master_Transmit(&hi2c2, DSP_I2C_ADDR, &sendData, I2C_MEMADD_SIZE_8BIT, length, 100);/

//     // If data can fit into one I2C buffer, send it in one burst.
//     // if (length < MAX_I2C_DATA_LENGTH) {
//         // HAL_I2C_Mem_Write(&hi2c2,DSP_I2C_ADDR,address,I2C_MEMADD_SIZE_8BIT,&pData,length,100);
//         // Wire.beginTransmission(DSP_I2C_ADDR);    // Initialize a new I2C transmission at
//         //                                          // DSP_I2C_ADDR (adjust in USER_DEFINES.h)
//         // Wire.write(address >> 8);                // Add high uint8_t of address to the I2C buffer
//         // Wire.write(address & 0xff);              // Add low uint8_t of address to the I2C buffer
//         // Wire.write(pData, length);               //  Add the whole data packet to the I2C buffer
//         // Wire.endTransmission();                  // Send the entire I2C transmission to the DSP
//     // } else {
//         // Go through the transmission one uint8_t at a time.
//         // uint8_t currentByte = 0;

//         // while (currentByte < length) {
//         //     // Begin a new I2C transaction.
//         //     // Wire.beginTransmission(DSP_I2C_ADDR);
//         //     // Wire.write(address >> 8);
//         //     // Wire.write(address & 0xff);

//         //     uint8_t bytesTransmitted = 0;
//         //     // For each uint8_t, find out if it will fit into the current transaction, and
//         //     // make sure there is still data left to send.
//         //     while ((bytesTransmitted + getMemoryDepth(uint32_t(address)) <= MAX_I2C_DATA_LENGTH) &&
//         //            (currentByte < length)) {
//         //         // If another register will fit inside the current I2C burst write,
//         //         // add each uint8_t to the I2C buffer one at a time.
//         //         for (uint8_t i = 0; i < getMemoryDepth(uint32_t(address)); i++) {
//         //             // Wire.write(pData[currentByte++]);
//         //             bytesTransmitted++;
//         //         }
//         //         // Increment address once per written register.
//         //         address++;
//         //     }
//         //     // Wire.endTransmission();    // Now that the buffer is full, send the I2C burst.
//         //     if (currentByte == length) {
//         //         break;
//         //     }
//         // }
//     // }
// #endif    // End of function for I2C write
// }

// Alternative function call without the address (single dsp system)
// void SIGMA_WRITE_REGISTER_BLOCK(uint8_t address, uint16_t length, uint8_t pData[]) {
//     SIGMA_WRITE_REGISTER_BLOCK(DSP_I2C_ADDR, address, length, pData);
// }

// Write a 32-bit integer to the DSP. NOTE: 5.23 not supported quite yet.
// void SIGMA_WRITE_REGISTER_INTEGER(uint8_t address, uint32_t pData) {
//     uint8_t byte_data[4];
//     SIGMASTUDIOTYPE_REGISTER_CONVERT(pData, byte_data);
//     SIGMA_WRITE_REGISTER_BLOCK(DSP_I2C_ADDR, address, 4, byte_data);
// }

// void SIGMA_WRITE_REGISTER_FLOAT(uint8_t address, uint16_t pData) {
//     SIGMA_WRITE_REGISTER_INTEGER(address, SIGMASTUDIOTYPE_FIXPOINT_CONVERT(pData));
// }

// void SIGMA_WRITE_DELAY(uint8_t devAddress, uint16_t length, uint8_t pData[]) {
//     uint8_t delay_length = 0;    // Initialize delay length variable
//     for (uint8_t i = length; i > 0; i--) {
//         // Unpack pData to calculate the delay length as an integer
//         delay_length = (delay_length << 8) + pData[i];
//     }
//     HAL_Delay(delay_length);    // Delay this processor (not the DSP) by the appropriate time
// }

// Function to read back data from the DSP, not called by SigmaStudio export files
// void SIGMA_READ_REGISTER_BYTES(uint8_t address, uint16_t length, uint8_t *pData) {
// #ifdef ADAU_USE_SPI
//     digitalWrite(DSP_SS_PIN, LOW);
//     SPI.beginTransaction(settingsA);
//     // SPI read address + read/!write bit
//     SPI.transfer(0x1);
//     SPI.transfer(address >> 8);
//     SPI.transfer(address & 0xff);
//     for (uint8_t i = 0; i < length; i++) {
//         pData[i] = SPI.transfer(0);
//     }
//     SPI.endTransaction();
//     digitalWrite(DSP_SS_PIN, HIGH);
// #else
//     // Wire.beginTransmission(DSP_I2C_ADDR);
//     // Wire.write(address >> 8);
//     // Wire.write(address & 0xff);
//     // Wire.endTransmission(false);
//     // Wire.requestFrom(DSP_I2C_ADDR, length);
//     // for (uint8_t i = 0; i < length; i++) {
//     //     if (Wire.available()) pData[i] = Wire.read();
//     // }
// #endif
// }

// uint32_t SIGMA_READ_REGISTER_INTEGER(uint8_t address, uint16_t length) {
//     uint32_t result = 0;
//     uint8_t register_value[length];
//     SIGMA_READ_REGISTER_BYTES(address, length, register_value);
//     for (uint8_t i = 0; i < length; i++) {
//         result = (result << 8) + register_value[i];
//     }
//     return result;
// }

// uint32_t SIGMA_READ_REGISTER_FLOAT(uint8_t address) {
//     uint32_t integerValue = SIGMA_READ_REGISTER_INTEGER(address, 4);
// #if DSP_TYPE == DSP_TYPE_SIGMA300_350
//     return (uint32_t)(integerValue / (1 << 24));
// #else
//     return (uint32_t)(integerValue / (1 << 23));
// #endif
// }

// Function for reading and printing DSP registers to the serial port, not called by
// SigmaStudio export files
// Since memory must be allocated for register_value bytes, keep dataLength to a low value
// void SIGMA_PRINT_REGISTER(uint8_t address, uint8_t dataLength) {
//     Serial.print("VALUE AT 0x");
//     Serial.print(address, HEX);
//     Serial.print(": 0x");
//     uint8_t register_value[dataLength] = {};
//     SIGMA_READ_REGISTER_BYTES(address, dataLength, register_value);
//     for (uint8_t i = 0; i < dataLength; i++) {
//         if (register_value[i] < 16) {
//             Serial.print('0');
//         }
//         Serial.print(register_value[i], HEX);
//         Serial.print(' ');
//     }
//     Serial.println();
// }

/* SIGMASTUDIOTYPE_INTEGER_CONVERT is included in export files but not generally required.
 * Here it is simply a passthrough macro.
 */
#define SIGMASTUDIOTYPE_INTEGER_CONVERT(_value) (_value)


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
void adau_init(void);
void adau_shiftPhase(uint8_t phs);


#ifdef __cplusplus
}
#endif

#endif /* INC_ADAU_17X1_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
