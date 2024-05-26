/*
 * IBM_lib.c
 *
 *  Created on: May 13, 2024
 *      Author: Loan
 */

#define OFF 0
#define ON 1


#define DATA_LINE 0
#define CLOCK_LINE 1
#define STREAM_LEN 11



void KB_pin_init();
void KB_clock_init ();
void KB_clock_event();
void KB_data_listen();
char KB_data_process();
