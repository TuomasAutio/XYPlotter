#include "parser.h"

Parser::Parser() {
}

Parser::~Parser() {
}


/**
 * @param *line the command string
 * @return command
 */
Command Parser::parse(const char* cmdLine) {
	Command cmd;
	getMovetype(cmdLine, cmd);
	getParams(cmdLine, cmd);
	return cmd;
}

/**
 * @param *line the command string, &command
 *
 */
void Parser::getMovetype(const char* line, Command& cmd) {
	cmd.type = INVALID_COMMAND; 						// if matching command not found, stays as invalid command
	if (strstr(line, "G1 ") != nullptr)
		cmd.type = COMMAND_MOVE;
	else if (strstr(line, "G28 ")!= nullptr)
		cmd.type = COMMAND_ORIGIN;
	else if (strstr(line, "M10\n")!= nullptr)
		cmd.type = COMMAND_START;
	else if (strstr(line, "M1 ")!= nullptr)
		cmd.type = COMMAND_PEN;
	else if (strstr(line, "M2 ")!= nullptr)
		cmd.type = COMMAND_SAVEPEN;
	else if (strstr(line, "M4 ")!= nullptr)
		cmd.type = COMMAND_LASER;
	else if (strstr(line, "M5 ")!= nullptr)
		cmd.type = COMMAND_SET_DIR_AND_AREA_SPEED;
	else if (strstr(line, "M11\n")!= nullptr)
		cmd.type = COMMAND_LSQUERY;
}

/**
 * @param *line the command string, &Command struct
 *
 */
void Parser::getParams(const char* line, Command& cmd) {
	//find according params and cast to correct types
	if (cmd.type == COMMAND_MOVE) {
		cmd.x = std::stof(findValue('X', line));								//set x value
		cmd.y = std::stof(findValue('Y', line));								//set y value
		cmd.absolute = std::stoi(findValue('A', line)) == 1 ? true : false;		//set abs value
	}
	else if (cmd.type == COMMAND_ORIGIN) {
		//goto origin
	}
	else if (cmd.type == COMMAND_START) {
		//start
	}
	else if (cmd.type == COMMAND_LASER) {
		strtok((char*)line, " ");
		cmd.laservalue = std::stoi(strtok(NULL, " "));							//set laser value
	}
	else if (cmd.type == COMMAND_PEN) {
		strtok((char*)line, " ");
		cmd.penvalue = std::stoi(strtok(NULL, " "));							//set pen value
	}
	else if (cmd.type == COMMAND_SET_DIR_AND_AREA_SPEED) {
		cmd.width = std::stoi(findValue('W', line));
		cmd.height = std::stoi(findValue('H', line));
	}
	else if (cmd.type == COMMAND_SAVEPEN) {
		cmd.penUP = std::stoi(findValue('U', line));
		cmd.penDOWN = std::stoi(findValue('D', line));
	}
}

/**
 * @param *line the command string, key to look for
 * @return parameter as string
 */
const char* Parser::findValue(const char key, const char* cmdline) {
	int pos = -1;
	for (size_t i = 0; i < strlen(cmdline); i++)
		if (cmdline[i] == key) 						//if we find the key
			pos = i; 								//set pos

	if (pos == -1)									//if pos not found return 0
		return 0;

	auto ret = cmdline + pos + 1; 					//get pos we want
	return ret;
}
