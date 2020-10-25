/*
 * Servo.h
 *
 *  Created on: 6.10.2020
 *      Author: Tuge
 */

#ifndef TOOLS_SERVO_H_
#define TOOLS_SERVO_H_
#include "chip.h"
#include "FreeRTOS.h"
#include "task.h"

class Servo {
public:
	Servo(int port, int pin);
	void Draw();
	void Stop();

	int getPenDownValue();
	int getPenUpValue();
	void setPenDownValue(int value);
	void setPenUpValue(int value);
private:
	int port;
	int pin;

	int servoPos;

	int penUP = 160;
	int penDOWN = 90;
};


#endif /* TOOLS_SERVO_H_ */
