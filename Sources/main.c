#include "derivative.h"
#include "led_module_lib.h"

int main(void)
{
	initPorts();
	int i, count = 0;
	setNumber(1);
	for(i=0; i<999999 ;i++) 
	{	   
		count++;
	}
	setNumber(3);
	
	return 0;
}
