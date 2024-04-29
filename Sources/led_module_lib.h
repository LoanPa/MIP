/*
 * led_module_lib.h
 *
 *  Created on: Apr 15, 2024
 *      Author: Alumno
 */

#ifndef LED_MODULE_LIB_H_
#define LED_MODULE_LIB_H_

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

int currentNumber = 0;

/*
struct Display

{
	int number;
	
} Display;
*/

void initPorts();
void setNumber(int led);
void turnOff();
void refresh(int number, int display);


#endif /* LED_MODULE_LIB_H_ */
