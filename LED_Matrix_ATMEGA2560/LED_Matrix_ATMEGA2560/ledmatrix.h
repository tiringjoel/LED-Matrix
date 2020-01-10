/*
 * ledmatrix.h
 *
 * Created: 09.01.2020 00:32:22
 *  Author: Joel
 */ 


#ifndef LEDMATRIX_H_
#define LEDMATRIX_H_

#define ROWLENGTH	(32)
#define COLLENGTH	(8)

void writeBuffer(volatile bool _buf[ROWLENGTH][COLLENGTH]);
void clearBuffer(volatile bool _buf[ROWLENGTH][COLLENGTH]);
void testfncmatrix(void);
#endif /* LEDMATRIX_H_ */
