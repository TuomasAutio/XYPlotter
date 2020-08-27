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

class GetUartString : public Singleton<GetUartString>{
public:
	GetUartString(char EndOFLineChar);
	virtual ~GetUartString();
	char* getUartMessage();
private:
	char endOfLineChar;
	char ch;
	char str[MaxMessageSize];

};

#endif /* GETUARTSTRING_H_ */
