/*
 * GetUartString.h
 *
 *  Created on: 27 Aug 2020
 *      Author: Lauri
 */

#ifndef GETUARTSTRING_H_
#define GETUARTSTRING_H_

#define MaxMessageSize 64

#include "board.h"
#include "singleton.h"

#include <stdio.h>
#include <ctype.h>
#include <string>

class GetUartString : public Singleton<GetUartString>{
public:
	GetUartString(char EndOFLineChar);
	virtual ~GetUartString();
	std::string getUartMessage();
private:
	char endOfLineChar;

};

#endif /* GETUARTSTRING_H_ */
