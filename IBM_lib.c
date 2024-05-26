/*
 * IBM_lib.c
 *
 *  Created on: May 13, 2024
 *      Author: Loan
 */
#include "IBM_lib.h"
#include "derivative.h"

int clock = 0;
int data_bit;
int bitNumber = 0;
int data;
int data_ready;

void KB_pin_init(){
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORT_PCR_REG(PORTB_BASE_PTR, DATA_LINE)  = PORT_PCR_MUX(1);
    PORT_PCR_REG(PORTB_BASE_PTR, CLOCK_LINE) = PORT_PCR_MUX(1);
    
    // Clock line out
    GPIOB_PDDR |= 1<< CLOCK_LINE;
    // Data line in
    GPIOB_PDDR &= !(1 << DATA_LINE);
}

void KB_clock_init (){
	// Emprem el clock ERCLK32K  d'uns 32kHz i activem el bypass del filtre
	LPTMR0_BASE_PTR->PSR |= (2<<0) | (1 << 2);
	
	// Volem la interrupcio a cada cicle del clock
	LPTMR0_BASE_PTR->CMR = 0;
	
	// Donem energia al timer
	SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
	
	// Activar IRQ
	LPTMR0_BASE_PTR->CSR |= (1<<6);
	NVIC_BASE_PTR->ICPR |= 1 << (INT_LPTimer - 16);
	NVIC_BASE_PTR->ISER |= 1 << (INT_LPTimer - 16);
	
	// Iniciem el clock
	LPTMR0_BASE_PTR->CSR |= (1<<7);
}


void KB_clock_set(int status){
	if (status)
		GPIOB_PSOR |= (1 << CLOCK_LINE);
	else
		GPIOB_PCOR |= (1 << CLOCK_LINE);
}

void KB_clock_event(){
   //Tornem a enviar l'interrupcio
	LPTMR0_BASE_PTR->CSR |= (1<<7);
	KB_data_listen();
	/* 
	clock = !clock;
	
	if (clock == 0)
	{
		KB_data_listen();
		KB_clock_set(OFF);
	}
	else
	{
		KB_clock_set(ON);

	}
	*/
	// Tornar a activar el clock
}

void KB_data_listen(){
	/*
	// Llegir DATA
	data_bit = 1 & (GPIOB_PDOR >> DATA_LINE);
	data |= (data_bit << bitNumber);
	// Si es l'utim bit del stream guardem el valor a data_ready
	if(bitNumber == STREAM_LEN -1)
	{
		data_ready = data;
		bitNumber = 0;
	}
	bitNumber ++;
		*/
	data = 0x1c;
}

char KB_data_process(){
	if(!data_ready)
		return 0;
	char result = 0;
	char aux = (char) (data_ready >> 1) && 0xFF;
	/* Faltaria comprovar la paritat, pero assumim que no hi ha errors */
	
	/* Data processing*/
	
	switch (aux) {
		case 0x1c:
			result = 'a';
			break;
		case 0x29:
			result = ' ';
			break;		
		case 0x16:
			result = '1';
			break;
		default:
			break;
	}
	return result;
}

void LPTimer_IRQHandler() __attribute__((interrupt("IRQ")));
void LPTimer_IRQHandler (void)
{
	KB_clock_event();
}
