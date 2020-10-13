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
	void update_cor(float x, float y);
	float getX();
	float getY();


private:

	int totalStepY;
	int totalStepX;

	int ySteps;
	int xSteps;

	float mm_corX = 190;
	float mm_corY = 155;

};


#endif /* STEPPERCONTROLLER_H_ */
