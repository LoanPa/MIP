#include "derivative.h"
#include "pit_lib.h"

#define CLK_FREQ 50000000  // Defineix la freq��ncia del rellotge.

static void (*recurrentFunction)(void);  // Punter a funci� que es cridar� recurrentment.

// Aquesta funci� assigna una funci� al punter per ser cridada pel gestor d'interrupci�.
void setRecurrentFunction(void (*func)(void)) {
    recurrentFunction = func;
}

// Inicialitza el PIT per generar interrupcions a una freq��ncia espec�fica.
void pit_Init(uint8_t frequency) {
    // Habilitar el rellotge per al PIT
    SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
    
    // Desactiva el PIT i permet que corri en mode depuraci�
    PIT_MCR = 0; // Abans: PIT_MCR |= PIT_MCR_FRZ_MASK;
    
    // Configura el valor de c�rrega del temporitzador per al temporitzador 0
    PIT_LDVAL0 = CLK_FREQ / frequency - 1;  // Calcula el valor de c�rrega adequat
    
    // Configura el temporitzador per habilitar interrupcions i activar el temporitzador
    PIT_TCTRL0 = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
    
    // Neteja banderes pendents i habilita la interrupci� al controlador NVIC
    NVIC_BASE_PTR->ICPR |= 1 << (INT_PIT - 16);  // Neteja banderes pendents
    NVIC_BASE_PTR->ISER |= 1 << (INT_PIT - 16);  // Habilita la interrupci�
}

// Gestor d'interrupci� per al PIT.
void PIT_IRQHandler(void) __attribute__((interrupt("IRQ")));
void PIT_IRQHandler(void) {
    if (recurrentFunction) {  // Assegura que el punter no sigui NULL
        recurrentFunction();  // Truca a la funci� recurrent
    }
    
    // Netejar el flag d'interrupci� per evitar interrupcions repetides
    PIT_TFLG0 = PIT_TFLG_TIF_MASK;  // Escriu 1 per netejar el flag d'interrupci�
}
