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

#define WIDTH 380
#define HEIGHT 310

enum {
	toOrigin,
	xAxis,
	yAxis,
};

class StepperController : public Singleton<StepperController>{
public:
	StepperController();
	virtual ~StepperController();

	void move(signed int xSteps,signed int ySteps);
	void calibrate();

	void update_cor(int x, int y);
	int getX();
	int getY();
	int getSPM();


private:

	int totalStepY;
	int totalStepX;

	int ySteps;
	int xSteps;

	int CordinateX;
	int CordinateY;
	int stepsPerMM;

};


#endif /* STEPPERCONTROLLER_H_ */
