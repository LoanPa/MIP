#include "derivative.h"
#include "led_module_lib.h"

struct display* createDisplay(uint16_t* dir, int length)
 {
	int i;
	
	struct display* tmp = malloc(length * sizeof(struct display));
	for(i = 0; i < length; i++) {
		tmp->digits[i].curr = 0;
		tmp->digits[i].dir = dir[i];
		tmp->digits[i].next = 0;
	}
	tmp->active = -1;
	
	return tmp;
}

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

void turnOff() {
	GPIOC_PCOR |= LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G;
}

void loadNumber(struct display *disp, uint8_t digit) {
	
	if (digit < 0 || digit >= NUM_DIGITS)
		return;
	
	if(disp->digits[digit].curr != disp->digits[digit].next){
		//currentNumber = led;
		disp->digits[digit].curr = disp->digits[digit].next;
		disp->active = digit;
		
	
		//Apagem tots els LEDs
		turnOff();
		switch(disp->digits[digit].next) {
			case 1 : 
				GPIOC_PSOR |= LED_B | LED_C ; 
				break;
			case 2 : 
				GPIOC_PSOR |= LED_A | LED_B | LED_G | LED_E| LED_D; 
				break;
			case 3 : 
				GPIOC_PSOR |= LED_A | LED_B | LED_G | LED_C| LED_D; 
				break;
			// FALTA ACABAR TODO
			default:  
				break;
		}
	}
}


void refresh(struct display *disp) {
	int i;
	
	if (disp->active > -1) {
		GPIOC_PSOR |= disp->digits[disp->active].dir;
		for (i = 0; i < NUM_DIGITS; i++) {
			if (i  != disp->active)
				GPIOC_PCOR |= disp->digits[i].dir; 
		}
	}	
}


