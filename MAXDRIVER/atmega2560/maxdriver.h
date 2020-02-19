/*
 * max7219.h
 *
 * Created: 08.01.2020 22:36:27
 *  Author: Joel
 */ 


#ifndef MAXDRIVER_H_
#define MAXDRIVER_H_

#define NRMAX			(4)
#define reg_noop        0x0
#define reg_digit0      0x1
#define reg_digit1      0x2
#define reg_digit2      0x3
#define reg_digit3      0x4
#define reg_digit4      0x5
#define reg_digit5      0x6
#define reg_digit6      0x7
#define reg_digit7      0x8
#define reg_decodemode  0x9
#define reg_intensity   0xA
#define reg_scanlimit   0xB
#define reg_shutdown    0xC
#define reg_displaytest 0xF

// macros for Intensity
#define LOW				0x2
#define MEDIUM			0x7
#define HIGH			0xE

// macros for shift commands
#define BYTE		(8)
#define FALSE		(0)
#define TRUE		(!FALSE)
#define LSBFIRST	(1)
#define MSBFIRST	(!LSBFIRST)

typedef struct MAX{
	volatile uint8_t * port;
	uint8_t clkpin;
	uint8_t cspin;
	uint8_t datapin;
	uint8_t nrmax;
	}S_MAX;
	
void shiftByte(S_MAX * max, uint8_t byte, uint8_t lsbfirst);
void shiftBit(S_MAX * max, volatile uint8_t bit);
void shiftData(S_MAX * max, uint8_t address, uint8_t value);
void clearDatabus(S_MAX * max);
void latchData(S_MAX * max);
void writeMax(S_MAX * max, uint8_t maxItem, uint8_t address, uint8_t value);
void clearDisplay(S_MAX * max);
void initMax(S_MAX * max, volatile uint8_t * port, uint8_t clkpin, uint8_t cspin, uint8_t datapin, uint8_t nrmax);
void shiftBufferOut(S_MAX * max, volatile uint8_t * rdptr);

#endif /* MAXDRIVER_H_ */
