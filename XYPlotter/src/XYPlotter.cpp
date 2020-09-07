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

/**
 * @brief
 * @return	Nothing, function should not exit
 */

#include <stdio.h>
#include <ctype.h>
#include "task.h"
#include "tools/UartController.h"
#include "tools/Parser.h"
#include "tools/Assingments/PlottingSimulator.h"

int main(void) {
	//vTaskStartScheduler();
	prvSetupHardware();

	UartController URT('\n');
	Parser p;
	PlottingSimulator ps;
	char buff[128];
	char response[128];
	while(1){

		URT.getUartMessage(buff);
		ps.responseForMdraw(response, p.parse(buff));
		URT.SendUartMessage(response);

		Board_UARTPutSTR(buff);
	}
	return 0 ;
}
