#include "derivative.h"
#include "led_module_lib.h"

int main(void)
{
	const uint16_t dirs[NUM_DIGITS] = {D1, D2};
	int i, count = 0;
	
	struct display* disp = createDisplay(&dirs, NUM_DIGITS);
	initPorts();
	
	disp->digits[0].next = 2;
	loadNumber(disp, 0);
	refresh(disp);
	
	for(i=0; i<999999 ;i++) 
	{	   
		count++;
	}
	
	disp->digits[0].next = 3;
	loadNumber(disp, 0);
	refresh(disp);
	
	free(disp);
	return 0;
}
