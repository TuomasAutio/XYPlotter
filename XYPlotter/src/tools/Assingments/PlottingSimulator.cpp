/*
 * PlottingSimulator.cpp
 *
 *  Created on: 6 Sep 2020
 *      Author: Lauri
 */

#include "PlottingSimulator.h"



PlottingSimulator::PlottingSimulator() {
	// TODO Auto-generated constructor stub

}

PlottingSimulator::~PlottingSimulator() {
	// TODO Auto-generated destructor stub
}
int clamp(int val, int min,int max){
	if (val > max){
		val = max;
	}else if(val < min){
		val = min;
	}
	return val;
}

void PlottingSimulator::responseForMdraw(char * str, Command cmd){

	// char str[128]; can't use this, as compiler will complain about returning local variable

	switch(cmd.type){
	case COMMAND_ORIGIN: // no response needed
	case COMMAND_LASER: // no response
		break;
	case COMMAND_MOVE:
	case COMMAND_PEN:
		sprintf(str,"OK\r\n");
		break;
	case COMMAND_START:
		sprintf(str, "M10 XY %d %d 0.00 0.00 A%d B%d H0 S%d U1%d D%d\r\nOK\r\n",
				plotAreaHeight,plotAreawidth,stepperXDir,stepperYDir,plottingSpeed,penUp,penDown);
		break;
	case INVALID_COMMAND:
	default:
		while(1); // breakpoint error
		break;
	}
}
