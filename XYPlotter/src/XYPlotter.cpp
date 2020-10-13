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
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "tools/ITM_write.h"
#include "tools/Servo.h"
#include "tools/LpcUart.h"
#include "tools/Parser.h"
#include "StepperController.h"

QueueHandle_t q_cmd;

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	//disable laser
	//DigitalIoPin laser(0, 12, DigitalIoPin::output, false);
	//laser.write(false);

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

Parser parse;

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* the following is required if runtime statistics are to be collected */
extern "C" {

void vConfigureTimerForRunTimeStats(void) {
	Chip_SCT_Init(LPC_SCTSMALL1);
	LPC_SCTSMALL1->CONFIG = SCT_CONFIG_32BIT_COUNTER;
	LPC_SCTSMALL1->CTRL_U = SCT_CTRL_PRE_L(255) | SCT_CTRL_CLRCTR_L; // set prescaler to 256 (255 + 1), and start timer
}

}
/* end runtime statictics collection */

static void stepperTask(void *pvParameters) {
	StepperController stepper;
	Servo pen(0, 10);
	int motordelay = 10;
	int moveSize = 50;

	Command cmd;
	vTaskDelay(500);
	pen.Draw();
	vTaskDelay(500);


	while (1) {
		xQueueReceive(q_cmd, &cmd, portMAX_DELAY);
		if (cmd.type == COMMAND_MOVE) {
			//motor move
			stepper.move((int) (5*cmd.x - stepper.getX()), (int) (5*cmd.y - stepper.getY()));
		} else if (cmd.type == COMMAND_PEN) {
			if (cmd.penvalue != 100) {
				//Move pen

			} else {
				//move Pen

			}
		} else if (cmd.type == COMMAND_LASER) {
			//laser power
		} else if (cmd.type == COMMAND_ORIGIN) {
			//Motor move 0,0

		}
		vTaskDelay(10);
	}
}
/**
 * @brief
 * @return	Nothing, function should not exit
 */


void bresenham(float x0, float y0, float x1, float y1) {
	auto dx = x1-x0;
	auto dy = y1-y0;

	auto max = std::max(std::abs(dx),std::abs(dy));

	auto deltaX = std::abs(dx) / max;
	auto deltaY = std::abs(dy) / max;
}

static void vUartTask(void *pvParameters) {
	LpcPinMap none = { .port = -1, .pin = -1};
	LpcPinMap txpin1 = { .port = 0, .pin = 18 };
	LpcPinMap rxpin1 = { .port = 0, .pin = 13 };
	LpcUartConfig cfg1 = {
			.pUART = LPC_USART0,
			.speed = 115200,
			.data = UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1,
			.rs485 = false,
			.tx = txpin1,
			.rx = rxpin1,
			.rts = none,
			.cts = none
	};
	LpcUart UARTobj(cfg1);
	Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2);

	int count;
	char str[40];

	while (1) {
		count = UARTobj.read(str, 40, portTICK_PERIOD_MS * 10);

		if (count > 0) {

			vTaskDelay(10);
			str[count] = '\0';

			//ITM_write(str);

			auto cmd = parse.parse(str);

			if (cmd.type == COMMAND_START) {
				//start and calibrate
				UARTobj.write("M10 XY 380 310 0.00 0.00 A0 B0 H0 S80 U160 D90\r\n");
				vTaskDelay(25);
			} else if (cmd.type == COMMAND_MOVE) xQueueSendToBack(q_cmd, &cmd, portMAX_DELAY);
			UARTobj.write("OK\r\n");
			vTaskDelay(10);


		}
	}
}


int main(void) {
	prvSetupHardware();
	q_cmd = xQueueCreate(1, sizeof(Command));
	//ITM_init();
	assert(q_cmd != NULL);

	xTaskCreate(stepperTask, "stepperTask",
			configMINIMAL_STACK_SIZE * 4, NULL, (tskIDLE_PRIORITY + 2UL),
			(TaskHandle_t *) NULL);

	xTaskCreate(vUartTask, "Uart Task",
			configMINIMAL_STACK_SIZE * 4, NULL, (tskIDLE_PRIORITY + 1UL),
			(TaskHandle_t *) NULL);


	vTaskStartScheduler();
	/* Should never arrive here */

	while(1);

	return 0 ;

}
