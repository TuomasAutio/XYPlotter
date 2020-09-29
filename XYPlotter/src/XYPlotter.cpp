/*
===============================================================================
 Name        : main.c
 Author      : Lauri.M Tuomas.A Taneli.T
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#include "FreeRTOS.h"

#include <stdio.h>
#include <ctype.h>
#include "task.h"
#include "tools/UartController.h"
#include "tools/Parser.h"
#include "StepperController.h"

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}



/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* the following is required if runtime statistics are to be collected */
extern "C" {

void vConfigureTimerForRunTimeStats( void ) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}
/* end runtime statictics collection */



static void stepperTask(void *pvParameters) {
	StepperController stepper;


	while (1) {
		stepper.move(50, 50);
		vTaskDelay(100);

		stepper.move(80, -50);
		vTaskDelay(100);

		stepper.move(-50, -100);
		vTaskDelay(100);

		stepper.move(-90, 100);
		vTaskDelay(100);
	}
}
/**
 * @brief
 * @return	Nothing, function should not exit
 */


int main(void) {

	prvSetupHardware();

	xTaskCreate(stepperTask, "stepperTask",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);


	vTaskStartScheduler();
	/* Should never arrive here */


	return 0 ;
}
