/*
 * led_module_lib.h
 *
 *  Created on: Apr 15, 2024
 *      Author: Alumno
 */
#include <stdlib.h>

#ifndef LED_MODULE_LIB_H_
#define LED_MODULE_LIB_H_

#define NUM_DIGITS 2

#define D1 (1<<10)
#define D2 (1<<11)
#define LED_A (1<<7)
#define LED_B (1<<0)
#define LED_C (1<<3)
#define LED_D (1<<4)
#define LED_E (1<<5)
#define LED_F (1<<6)
#define LED_G (1<<12)

#define OFF = -1

 
struct digit {
	int8_t curr ;
	int8_t next;
	uint16_t dir;
};

struct display {
	struct digit digits[NUM_DIGITS];
	int8_t active;
};
struct display* createDisplay(uint16_t* dir, int length);
void initPorts();
void loadNumber(struct display *disp, uint8_t digit);
void turnOff();
void refresh(struct display *digits);


#endif /* LED_MODULE_LIB_H_ */
