/*
 * Servo.h
 *
 *  Created on: 6.10.2020
 *      Author: Tuge
 */

#ifndef TOOLS_SERVO_H_
#define TOOLS_SERVO_H_


class Servo {
public:
	Servo(int port, int pin);
	void move(double value);
private:
	int port;
	int pin;
};


#endif /* TOOLS_SERVO_H_ */
