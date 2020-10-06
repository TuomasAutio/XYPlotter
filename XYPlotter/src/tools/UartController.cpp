/*
 * GetUartString.cpp
 *
 *  Created on: 27 Aug 2020
 *      Author: Lauri
 */

#include "UartController.h"

UartController::UartController(char EndOFLineChar): endOfLineChar(EndOFLineChar) {
	// TODO Auto-generated constructor stub

}

UartController::~UartController() {
	// TODO Auto-generated destructor stub
}

void UartController::getUartMessageFromFile(const char* filename){ // TODO placeholder func
	Parser p;

	auto infile = fopen(filename, "r");
		if (infile)
		{
			char cmdLine[255];
			while (fgets(cmdLine, 255, infile))
			{
				strtok(cmdLine, "\n");

				auto cmd = p.parse(cmdLine);
				printf("\nx:%f\ny:%f\nType:%d\nabsolute:%d\nPenvalue:%d\n", cmd.x, cmd.y, cmd.type, cmd.absolute, cmd.penvalue); //send command somewhere
			}
		}
		else
			printf("File could not be opened");


}
void UartController::getUartMessage(char * str){

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
void UartController::SendUartMessage(char * message){
	DEBUGOUT(message);
}
