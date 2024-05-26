/*
 * led_module_lib.h
 *
 *  Created on: Apr 15, 2024
 *      Author: ikerb
 */

#include <stdlib.h>

#ifndef LED_MODULE_LIB_H_
#define LED_MODULE_LIB_H_

#define D1 (1<<10)
#define D2 (1<<11)


void createDisplay(const uint16_t* dir, const int length);
void initPorts();
void loadValue(const char value);
void turnOff();
void refresh();


#endif /* LED_MODULE_LIB_H_ */
