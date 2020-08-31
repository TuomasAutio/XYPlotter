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
std::string GetUartString::getUartMessage(){
	std::string str;
	char ch;
	int i = 0;
	while ((((ch = Board_UARTGetChar()) !='n' ) && str.back() != '\r') && i++ < MaxMessageSize ){
		if(isalnum(ch) || iscntrl(ch)){
			str.push_back(ch);
		}
	}
	str.pop_back();// removes carriage return
	return str;
}
