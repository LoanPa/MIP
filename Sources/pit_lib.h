/*
 * pit_lib.h
 *
 *  Created on: May 25, 2024
 *      Author: ikerb
 */

#ifndef PIT_LIB_H_
#define PIT_LIB_H_

void pit_Init(uint8_t frequency);
void setRecurrentFunction(void (*func)(void));
void PIT_IRQHandler(void);

#endif /* PIT_LIB_H_ */
