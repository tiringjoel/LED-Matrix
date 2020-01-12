/*
 * max7219ptr.h
 *
 * Created: 12.01.2020 22:53:09
 *  Author: Joel
 */ 


#ifndef MAX7219PTR_H_
#define MAX7219PTR_H_

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

void max7219ptrtest(void);


#endif /* MAX7219PTR_H_ */