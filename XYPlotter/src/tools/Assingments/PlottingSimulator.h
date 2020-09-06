/*
 * PlottingSimulator.h
 *
 *  Created on: 6 Sep 2020
 *      Author: Lauri
 */

#ifndef TOOLS_ASSINGMENTS_PLOTTINGSIMULATOR_H_
#define TOOLS_ASSINGMENTS_PLOTTINGSIMULATOR_H_

#include "../singleton.h"
#include "../Parser.h"
#include "../UartController.h"

class PlottingSimulator : public Singleton<PlottingSimulator>{
public:
	PlottingSimulator();
	virtual ~PlottingSimulator();
	void responseForMdraw(char *, Command cmd);
private:


	uint8_t x_pos = 0; // pen/lasers pos
	uint8_t y_pos = 0; // pen/lasers pos


	// placeholder values
	int stepperXDir = 0;
	int stepperYDir = 0;
	int plotAreaHeight = 310, plotAreawidth = 350;
	int plottingSpeed = 80;
	int penUp = 160;
	int penDown = 90;
	int laserPWR = 0;

	const char* aknowlege = "OK\r\n";


	int clamp(int , int ,int );
};

#endif /* TOOLS_ASSINGMENTS_PLOTTINGSIMULATOR_H_ */
