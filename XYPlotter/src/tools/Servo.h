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
private:
	int port;
	int pin;

	int servoPos;
};


#endif /* TOOLS_SERVO_H_ */
