/*
 * Servo.h
 *
 *  Created on: 6.10.2020
 *      Author: Tuge
 */

#ifndef TOOLS_LASER_H_
#define TOOLS_LASER_H_
#include "chip.h"


class Laser {
public:
	Laser(int port, int pin);
	void setVal(signed int);
private:
	int port;
	int pin;

	int laserVals;
};


#endif /* TOOLS_SERVO_H_ */
