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
#include "task.h"
#include "tools/GetUartString.h"
#include "FreeRTOS.h"
#include "tools/Parser.h"


static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();

	/* Initial LED0 state is off */
	Board_LED_Set(0, false);
}

Parser parse;
GetUartString uartReader('\n');

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

void bresenham(float x0, float y0, float x1, float y1) {
	auto dx = x1-x0;
	auto dy = y1-y0;

	auto max = std::max(std::abs(dx),std::abs(dy));

	auto deltaX = std::abs(dx) / max;
	auto deltaY = std::abs(dy) / max;
}

void calibrate() {

}

void worker() {
	char str[64];
	float lastX;
	float lastY;

	while (1) {
		uartReader.getUartMessage(str);
		auto cmd = parse.parse(str);

		if (cmd.type == COMMAND_MOVE) {
			//motor move
			bresenham(lastX,lastY,cmd.x,cmd.y);

		} else if (cmd.type == COMMAND_PEN) {
			if (cmd.penvalue != 100) {
				//Move pen
			} else {
				//move Pen
			}
		} else if (cmd.type == COMMAND_LASER) {
			//laser power
		} else if (cmd.type == COMMAND_START) {
			//start and calibrate
			calibrate();
			lastX = 0;
			lastY = 0;
		} else if (cmd.type == COMMAND_ORIGIN) {
			//Motor move 0,0
		} else if (cmd.type == COMMAND_READY) {
			//ready
		}
	}
}

int main(void) {
	//vTaskStartScheduler();
	prvSetupHardware();

	GetUartString URT('\n');
	char buff[64];
	while (1) {
		URT.getUartMessageFromFile(buff);

		Board_UARTPutSTR(buff);
	}
	return 0;
}
