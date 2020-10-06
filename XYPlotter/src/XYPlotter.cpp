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
	int motordelay = 10;
	int moveSize = 50;

	srand(2);

	while (1) {
#if 0
		// random
		stepper.move((rand() % 100)- 50, (rand() % 100)- 50);
		vTaskDelay(motordelay);

#elif 0

		// circular shape , set canvas size to max and quarter step
		for(int i = -10; i < 10; i++){
			stepper.move(i, 10);
			vTaskDelay(motordelay);
		}

		for (int j = 10; j > -10; j--){
			stepper.move(10, j);
			vTaskDelay(motordelay);
		}

		for(int i = 10; i > -10; i--){
			stepper.move(i, -10);
			vTaskDelay(motordelay);
		}

		for (int j = -10; j < 10; j++){
			stepper.move(-10, j);
			vTaskDelay(motordelay);
		}


#else
		//  octagon
		stepper.move(moveSize, 0); // East
		vTaskDelay(motordelay);

		stepper.move(moveSize, -moveSize); // SouthEast
		vTaskDelay(motordelay);

		stepper.move(0, -moveSize); // South
		vTaskDelay(motordelay);

		stepper.move(-moveSize, -moveSize); // SouthWest
		vTaskDelay(motordelay);

		stepper.move(-moveSize, 0); // West
		vTaskDelay(motordelay);

		stepper.move(-moveSize, moveSize); // NorthWest
		vTaskDelay(motordelay);

		stepper.move(0, moveSize); // North
		vTaskDelay(motordelay);

		stepper.move(moveSize, moveSize); // NorthEeast
		vTaskDelay(motordelay);
		moveSize-=5;

		if (moveSize == -55){
			while(1);
		}

#endif

	}
}
/**
 * @brief
 * @return	Nothing, function should not exit
 */


int main(void) {

ö	prvSetupHardware();

	xTaskCreate(stepperTask, "stepperTask",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);


	vTaskStartScheduler();
	/* Should never arrive here */

	while(1);

	return 0 ;
}
