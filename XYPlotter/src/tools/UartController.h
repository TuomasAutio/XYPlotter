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
#include "Parser.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>


class UartController : public Singleton<UartController>{
public:
	UartController(char EndOFLineChar);
	virtual ~UartController();
	void getUartMessage(char *); //read from uart buffer, modifies the string it recives as parameter
	void SendUartMessage(char *); // read from file , modifies the string it recives as parameter
	void getUartMessageFromFile(const char* filename); // read from file, modifies the string it recives as parameter
private:
	char endOfLineChar;

};

#endif /* GETUARTSTRING_H_ */
