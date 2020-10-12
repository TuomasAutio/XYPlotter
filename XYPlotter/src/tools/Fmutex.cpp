/*
 * Fmutex.cpp
 *
 *  Created on: 15.8.2017
 *      Author: krl
 */

#include "Fmutex.h"

Fmutex::Fmutex() {
	// TODO Auto-generated constructor stub
	mutex = xSemaphoreCreateMutex();
}

Fmutex::~Fmutex() {
	// TODO Auto-generated destructor stub
	vSemaphoreDelete(mutex);
}

void Fmutex::lock()
{
	xSemaphoreTake(mutex, portMAX_DELAY);
}

void Fmutex::unlock()
{
	xSemaphoreGive(mutex);
}
