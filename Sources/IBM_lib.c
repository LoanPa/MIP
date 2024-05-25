/*
 * IBM_lib.c
 *
 *  Created on: May 13, 2024
 *      Author: Loan
 */
#include "IBM_lib.h"
#include "derivative.h"


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
	// Emprem el clock d'1kHz i activem el bypass del filtre
	LPTMR0_BASE_PTR->PSR |= (1<<0) | (1 << 2);
	
	// Dividim la frequencia pel que ens interessi (13kHz)
	LPTMR0_BASE_PTR->CMR |= PERIODE;
	
	// Donem energia al timer
	SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;
	
	// Activar IRQ
	LPTMR0_BASE_PTR->CSR |= (1<<6);
	NVIC_BASE_PTR->ICPR |= 1 << (44 - 16);
	NVIC_BASE_PTR->ISER |= 1 << (44 - 16);
	
	// Iniciem el clock
	LPTMR0_BASE_PTR->CSR |= (1<<7);
}

void KB_clock_event_manager(int status){
	if(status)
	{
		
	}
	else
	{
		
	}
}

void KB_clock_set(int status){
	if (status)
		GPIOB_PSOR |= (1 << CLOCK_LINE);
	else
		GPIOB_PCOR |= (1 << CLOCK_LINE);
}

void KB_clock_event(){
	//Mirem el valor 
	//clock = 1 & (GPIOB_PDOR >> CLOCK_LINE);
	
	clock = !clock;
	
	if (clock == 0)
	{
		KB_clock_set(OFF);

	}
	else
	{
		KB_clock_set(ON);
		KB_clock_event_manager();
		KB_data_listen();
	}
	
	// Tornar a activar el clock
	LPTMR0_BASE_PTR->CSR |= (1<<7);
}

void KB_data_listen(){
	data_bit = 1 & (GPIOB_PDOR >> DATA_LINE);
	data |= (data_bit << bitNumber);
	// Si es l'utim bit del stream guardem el valor a data_ready
	if(bitNumber == STREAM_LEN -1)
	{
		data_ready = data;
		bitNumber = 0;
	}
	bitnumber ++;

}

char KB_data_process(){
	if(!data_ready)
		return 0;
	char result;
	/* Data processing*/
	return result;
}

void LPTimer_IRQHandler() __attribute__((interrupt("IRQ")));
void LPTimer_IRQHandler (void)
{
	KB_clock_event();
}
