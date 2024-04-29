#include "derivative.h"
#include "led_module_lib.h"

void initPorts() {
	const int ports[] = {0, 3, 4, 5, 6, 7, 10, 11, 12};
	int i;
	
	// Clock active
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
    //Mode GPIO
	for (i = 0; i < 9; i++) {
		PORT_PCR_REG(PORTC_BASE_PTR,ports[i]) = PORT_PCR_MUX(1);
	}

	//Default value to 0
	GPIOC_PCOR |= LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G;
	
	// Output direction
	GPIOC_PDDR |= D1 | D2 | LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G;
}

void turnOff()
{
	GPIOC_PCOR |= LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G;
}

void setNumber(int led)
{
	if(currentNumber != led){
		currentNumber = led;
	
		//Apagem tots els LEDs
		turnOff();
		switch(led)
		{
			case 1 : GPIOC_PSOR |= LED_B | LED_C ; break;
			case 2 : GPIOC_PSOR |= LED_A | LED_B | LED_G | LED_E| LED_D; break;
			case 3 : GPIOC_PSOR |= LED_A | LED_B | LED_G | LED_C| LED_D; break;
			default:  break;
		}
	}
}


void refresh(int number1, int number2)
{
	
	if(/*timer*/)
	{
		//  Encenem el display 1
		GPIOC_PsOR |= D1;
		//  Apaguem el display 2
		GPIOC_PCOR |= D2;
		
		setNumber(number1);
	}
	else
	{	
		//  Encenem el display 2
		GPIOC_PSOR |= D2;
		//  Apaguem el display 1
		GPIOC_PCOR |= D1;

		setNumber(number2);
	}

	
}


