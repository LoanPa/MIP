#include "derivative.h"
#include "led_module_lib.h"

#define LED_A (1<<7)
#define LED_B (1<<0)
#define LED_C (1<<3)
#define LED_D (1<<4)
#define LED_E (1<<5)
#define LED_F (1<<6)
#define LED_G (1<<12)

struct digit {
	uint8_t value;
	uint16_t dir;
};

struct display {
	struct digit* digits;
	uint8_t num_digits;
	int8_t active;
};

static struct display disp;


void createDisplay(const uint16_t* dir, const int length) {
	int i;
	
	disp.digits = malloc(length * sizeof(struct digit));
	if (!disp.digits) {
		exit(-1);
	}
	
	disp.num_digits = length;
	
	for(i = 0; i < length; i++) {
		disp.digits[i].value = '0';
		disp.digits[i].dir = dir[i];
	}
	
	disp.active = -1;
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
	GPIOC_PCOR |= LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G | D1 | D2;
}

void loadValue(const char value) {
	
	int ascii = (int) value;
	if ((ascii > 127) || (ascii < 0)) return;
	
	if (disp.digits) {
		disp.digits[0].value = ascii / 16;
		disp.digits[1].value = ascii % 16;

	}
	
}

static uint16_t encode(const uint8_t value) {
    uint16_t ret;

    switch(value) {
        case 0:
            ret = LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G; 
            break;
        case 1:
            ret = LED_B | LED_C; 
            break;
        case 2:
            ret = LED_A | LED_B | LED_G | LED_E | LED_D;
            break;
        case 3:
            ret = LED_A | LED_B | LED_G | LED_C | LED_D;
            break;
        case 4:
            ret = LED_B | LED_C | LED_F | LED_G;
            break;
        case 5:
            ret = LED_A | LED_F | LED_G | LED_C | LED_D;
            break;
        case 6:
            ret = LED_A | LED_F | LED_G | LED_C | LED_D | LED_E;
            break;
        case 7:
            ret = LED_A | LED_B | LED_G | LED_C;
            break;
        case 8:
            ret = LED_A | LED_B | LED_C | LED_D | LED_E | LED_F | LED_G;
            break;
        case 9:
            ret = LED_A | LED_B | LED_C | LED_F | LED_G;
            break;
        case 10: // A
            ret = LED_A | LED_B | LED_C | LED_E | LED_F | LED_G; 
            break;
        case 11: // B
            ret =  LED_E | LED_F | LED_G | LED_C | LED_D;
            break;
        case 12: // C
            ret = LED_A | LED_F | LED_E | LED_D;
            break;
        case 13: // D
            ret = LED_B | LED_C | LED_D | LED_E | LED_G;
            break;
        case 14: // E
            ret = LED_A | LED_F | LED_G | LED_E | LED_D;
            break;
        case 15: // F 
            ret = LED_A | LED_F | LED_G | LED_E;
            break;
        default:
            ret = LED_G;
        }

    return ret;
}

static void nextDigit() {
	if (++disp.active >= disp.num_digits)
		disp.active = 0;
}

void refresh() {
		
	if (disp.active > -1 && disp.digits) {
		turnOff();
		uint16_t value = encode(disp.digits[disp.active].value);
		GPIOC_PSOR |= disp.digits[disp.active].dir | value;
	}
	
	nextDigit();
}


