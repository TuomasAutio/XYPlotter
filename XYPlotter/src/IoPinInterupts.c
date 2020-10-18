#include "board.h"
#include "FreeRTOS.h"


void startLimSwitchCheck(){
	NVIC_ClearPendingIRQ(PIN_INT0_IRQn);
	NVIC_EnableIRQ(PIN_INT0_IRQn);

	NVIC_ClearPendingIRQ(PIN_INT1_IRQn);
	NVIC_EnableIRQ(PIN_INT1_IRQn);

	NVIC_ClearPendingIRQ(PIN_INT2_IRQn);
	NVIC_EnableIRQ(PIN_INT2_IRQn);

	NVIC_ClearPendingIRQ(PIN_INT3_IRQn);
	NVIC_EnableIRQ(PIN_INT3_IRQn);
}
// if lim swithc needs to be stopped
void stopLimSwitchCheck(){

	NVIC_DisableIRQ(PIN_INT0_IRQn);

	NVIC_DisableIRQ(PIN_INT1_IRQn);

	NVIC_DisableIRQ(PIN_INT2_IRQn);

	NVIC_DisableIRQ(PIN_INT3_IRQn);
}
/*
 * Stops pin & mrt interupts, then stop program
 */
void stopProgram(){
	NVIC_DisableIRQ(MRT_IRQn);
	Board_LED_Set(1, true);

	NVIC_DisableIRQ(PIN_INT0_IRQn);
	NVIC_DisableIRQ(PIN_INT1_IRQn);
	NVIC_DisableIRQ(PIN_INT2_IRQn);
	NVIC_DisableIRQ(PIN_INT3_IRQn);



	while(1){

	}
}



void PIN_INT0_IRQHandler(void){
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(0));
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	stopProgram(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
void PIN_INT1_IRQHandler(void){
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(1));
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	stopProgram(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
void PIN_INT2_IRQHandler(void){
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(2));
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	stopProgram(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
void PIN_INT3_IRQHandler(void){
	Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(3));
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	stopProgram(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
