#include "board.h"
#include "FreeRTOS.h"

void PIN_INT0_IRQHandler(void){

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	Board_LED_Set(1, true);
	vTaskSuspendAll(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
void PIN_INT1_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	Board_LED_Set(1, true);
	vTaskSuspendAll(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
void PIN_INT2_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	Board_LED_Set(1, true);
	vTaskSuspendAll(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
void PIN_INT3_IRQHandler(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	Board_LED_Set(1, true);
	vTaskSuspendAll(); // limit switch hit, drawing is ruined, stop program
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
