/*
 * GetUartString.cpp
 *
 *  Created on: 27 Aug 2020
 *      Author: Lauri
 */

#include "GetUartString.h"

GetUartString::GetUartString(char EndOFLineChar): endOfLineChar(EndOFLineChar) {
	// TODO Auto-generated constructor stub

}

GetUartString::~GetUartString() {
	// TODO Auto-generated destructor stub
}
char* GetUartString::getUartMessage(){
	int i = 0;
	while (((ch = Board_UARTGetChar()) != endOfLineChar) && i < MaxMessageSize){
			str[i++] = ch;
	}
	if(i == 0) {
		i = 0;// TODO: remove breakpoint debug
	}
	return str;
}
