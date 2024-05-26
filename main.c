#include "derivative.h"
#include "led_module_lib.h"
#include "pit_lib.h"

#define FREQ 120 // Hz
#define NUM_DIGITS 2


void setup();
void loop();

void setup() {
	const uint16_t dirs[NUM_DIGITS] = {D1, D2};
	
	createDisplay(dirs, NUM_DIGITS);
	initPorts();
	
	pit_Init(FREQ);
	setRecurrentFunction(refresh);
	loadValue('o');
}

void loop() {
	// Do something

}


int main(void)
{
	setup();
	
	while(1) {
		loop();
	}
	
	return 0;
}
