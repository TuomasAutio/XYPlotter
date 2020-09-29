/*
 * ServoController.cpp
 *
 *  Created on: 28 Sep 2020
 *      Author: Lauri
 */

#include "StepperController.h"


volatile uint32_t RIT_count;
SemaphoreHandle_t sbRIT;

DigitalIoPin *limSW1, *limSW2,*limSW3,*limSW4,*xMotor,*xMotorDir,*yMotor,*yMotorDir;

extern "C" {
void MRT_IRQHandler(void)
{
	uint32_t int_pend;

	portBASE_TYPE xHigherPriorityWoken = pdFALSE;

	/* Get and clear interrupt pending status for all timers */
	int_pend = Chip_MRT_GetIntPending();
	Chip_MRT_ClearIntPending(int_pend);

	if(RIT_count > 0) {
		--RIT_count;

		/* Channel 0 */
		if (int_pend & MRTn_INTFLAG(0)) {
			xMotor->flip();
		}

		/* Channel 1 */
		if (int_pend & MRTn_INTFLAG(1)) {
			yMotor->flip();
		}


	} else {
		Chip_RIT_Disable(LPC_RITIMER); // disable timer

		// Give semaphore and set context switch flag if a higher priority task was woken up
		xSemaphoreGiveFromISR(sbRIT, &xHigherPriorityWoken);
	}
	portEND_SWITCHING_ISR(xHigherPriorityWoken);
}
/*void RIT_IRQHandler(void) {
	// This used to check if a context switch is required
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	// Tell timer that we have processed the interrupt.
	// Timer then removes the IRQ until next match occurs
	Chip_RIT_ClearIntStatus(LPC_RITIMER); // clear IRQ flag
	if(RIT_count > 0) {

		--RIT_count;


	} else {
		Chip_RIT_Disable(LPC_RITIMER); // disable timer

		// Give semaphore and set context switch flag if a higher priority task was woken up
		xSemaphoreGiveFromISR(sbRIT, &xHigherPriorityTaskWoken);
	}
	// End the ISR and (possibly) do a context switch
	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}*/
}
/* Setup a timer for a periodic (repeat mode) rate */
static void setupMRT(uint8_t ch, MRT_MODE_T mode, uint32_t rate)
{
	LPC_MRT_CH_T *pMRT;

	/* Get pointer to timer selected by ch */
	pMRT = Chip_MRT_GetRegPtr(ch);

	/* Setup timer with rate based on MRT clock */
	Chip_MRT_SetInterval(pMRT, (Chip_Clock_GetSystemClockRate() / rate) |
			MRT_INTVAL_LOAD);

	/* Timer mode */
	Chip_MRT_SetMode(pMRT, mode);

	/* Clear pending interrupt and enable timer */
	Chip_MRT_IntClear(pMRT);
	Chip_MRT_SetEnabled(pMRT);
}

void MRT_start(int xCount, int yCount, int us) {
	uint64_t cmp_value;
	// Determine approximate compare value based on clock rate and passed interval
	cmp_value = (uint64_t) Chip_Clock_GetSystemClockRate() * (uint64_t) us / 1000000;

	// disable timer during configuration
	Chip_RIT_Disable(LPC_RITIMER);

	RIT_count = ((xCount > yCount) ? xCount :yCount);
	// enable automatic clear on when compare value==timer value
	// this makes interrupts trigger periodically
	Chip_RIT_EnableCompClear(LPC_RITIMER);
	// reset the counter
	Chip_RIT_SetCounter(LPC_RITIMER, 0);
	Chip_RIT_SetCompareValue(LPC_RITIMER, cmp_value);
	// start counting
	Chip_RIT_Enable(LPC_RITIMER);
	// Enable the interrupt signal in NVIC (the interrupt controller)
	NVIC_EnableIRQ(MRT_IRQn);
	int ratio =  yCount/xCount;
	if(ratio < 0){
		ratio *= -1;
	}

	setupMRT(0, MRT_MODE_REPEAT, 1000);/* 2Hz rate */
	setupMRT(1, MRT_MODE_REPEAT, 1000*ratio);/* 5Hz rate */

	// wait for ISR to tell that we're done
	if(xSemaphoreTake(sbRIT, portMAX_DELAY) == pdTRUE) {
		// Disable the interrupt signal in NVIC (the interrupt controller)
		NVIC_DisableIRQ(MRT_IRQn);

	} else {
		// unexpected error
	}
}

#define simulator

StepperController::StepperController() {

	Chip_RIT_Init(LPC_RITIMER);


	Chip_MRT_Init();

	for (int mrtch = 0; mrtch < MRT_CHANNELS_NUM; mrtch++) {
		Chip_MRT_SetDisabled(Chip_MRT_GetRegPtr(mrtch));
	}
	NVIC_SetPriority( MRT_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1 );



	sbRIT = xSemaphoreCreateBinary();

#ifndef simulator
	// plotter

	limSW1 = new DigitalIoPin(1,3,DigitalIoPin::pullup);
	limSW2 = new DigitalIoPin(0,0,DigitalIoPin::pullup);
	limSW3 = new DigitalIoPin(0,9,DigitalIoPin::pullup);
	limSW4 = new DigitalIoPin(0,29,DigitalIoPin::pullup);

#else
	// simulator

	limSW1 = new DigitalIoPin(0,9,DigitalIoPin::pullup);
	limSW2 = new DigitalIoPin(0,29,DigitalIoPin::pullup);
	limSW3 = new DigitalIoPin(0,0,DigitalIoPin::pullup);
	limSW4 = new DigitalIoPin(1,3,DigitalIoPin::pullup);


#endif

	xMotor = new DigitalIoPin(0,24,DigitalIoPin::output);
	xMotorDir = new DigitalIoPin(1,0,DigitalIoPin::output);

	yMotor = new DigitalIoPin(0,27,DigitalIoPin::output);
	yMotorDir = new DigitalIoPin(0,28,DigitalIoPin::output);
}

StepperController::~StepperController() {

	delete limSW1;
	delete limSW1;
	delete limSW1;
	delete limSW1;

	delete xMotor;
	delete xMotorDir;
	delete yMotor;
	delete yMotorDir;
	vSemaphoreDelete(sbRIT);
}

/*
 * Moves in relative value,
 */
int StepperController::move(signed int xSteps,signed int ySteps){
	// TODO: implement entering 0 as value
	if(xSteps > 0){
		xMotorDir->write(1);
	}else{
		xSteps *= -1; // reverse number
		xMotorDir->write(0);
	}
	if(ySteps > 0){

		yMotorDir->write(1);
	}else {
		ySteps *= -1; // reverse number
		yMotorDir->write(0);
	}


	MRT_start(xSteps, ySteps, 1000000 / (800));

	return 1; // ph
}


