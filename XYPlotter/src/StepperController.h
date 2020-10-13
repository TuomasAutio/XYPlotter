/*
 * ServoController.h
 *
 *  Created on: 28 Sep 2020
 *      Author: Lauri
 */

#ifndef STEPPERCONTROLLER_H_
#define STEPPERCONTROLLER_H_

#include "board.h"
#include "FreeRTOS.h"
#include "semphr.h"


#include "tools/Singleton.h"
#include "tools/DigitalIoPin.h"

enum {
	toOrigin,
	xAxis,
	yAxis,
};

class StepperController : public Singleton<StepperController>{
public:
	StepperController();
	virtual ~StepperController();

	int move(signed int xSteps,signed int ySteps);
	void calibrate();

	void update_cor(int x, int y);
	int getX();
	int getY();


private:

	int totalStepY;
	int totalStepX;

	int ySteps;
	int xSteps;

	int mm_corX = 950;
	int mm_corY = 775;


};


#endif /* STEPPERCONTROLLER_H_ */