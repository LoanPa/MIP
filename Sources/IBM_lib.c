/*
 * IBM_lib.c
 *
 *  Created on: May 13, 2024
 *      Author: Loan
 */
#include "IBM_lib.h"
#include "derivative.h"
#define IN 0
#define OUT 1

#define PERIODE 13
#define DATA_LINE 0
#define CLOCK_LINE 1
char clock = 0;

void KB_pin_init()
{
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORT_PCR_REG(PORTB_BASE_PTR, DATA_LINE)  = PORT_PCR_MUX(1);
    PORT_PCR_REG(PORTB_BASE_PTR, CLOCK_LINE) = PORT_PCR_MUX(1);
    
    GPIOB_PDDR |= 1<< CLOCK_LINE;
}

void KB_data_dir(char dir)
{
    if (dir == OUT)
    	GPIOB_PDDR |= 1 << CLOCK_LINE;   
    if (dir == IN)
    	GPIOB_PDDR &= !(1 << CLOCK_LINE);   
}

void KB_clock_init ()
{
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

void KB_clock_manage(){
	
}

void KB_clock_tick(){
	clock = 1 & (GPIOB_PDOR >> CLOCK_LINE);

	
}

void LPTimer_IRQHandler() __attribute__((interrupt("IRQ")));
void LPTimer_IRQHandler (void)
{
	// Tornar a activar el clock
	LPTMR0_BASE_PTR->CSR |= (1<<7);
}
