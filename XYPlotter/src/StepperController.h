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



class StepperController : public Singleton<StepperController>{
public:
	StepperController();
	virtual ~StepperController();

	int move(signed int xSteps,signed int ySteps);


};


#endif /* STEPPERCONTROLLER_H_ */
