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

void GetUartString::getUartMessageFromFile(char * buff){
	static int pos = 0;
	int count = 0;

	FILE *fp = fopen( "gcode01.txt", "r");
	if (!fp){
		fp = nullptr; // TODO: REMOVE DEBUG BREAKPOINT
	}

	while (fgets(buff, sizeof buff, fp) != NULL) /* read a line */
	{
		if (count == pos)
		{
			fclose(fp);

			return;

		}
		else
		{
			count++;
		}
	};

	fclose(fp);
	return;
}
void GetUartString::getUartMessage(char * str){

	char ch;
	int i = 0;
	while ((((ch = Board_UARTGetChar()) !='n' ) && str[i] != '\r') && i < MaxMessageSize ){
		if(isalnum(ch) || iscntrl(ch)){
			str[i++] = ch;
		}
	}
	str[i-1] = '\0'; // removes carriage return & adds nullterminator
	return;
}
