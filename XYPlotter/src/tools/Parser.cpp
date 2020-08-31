#include "Parser.h"
#include "board.h"

Parser::Parser() {
}

Parser::~Parser() {
}

const char* Parser::readFromfile(){

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
	cmd.type = INVALID_COMMAND; // if matching command not found, stays as invalid command
	if (strstr(line, "G1 "))
		cmd.type = COMMAND_MOVE;
	if (strstr(line, "G28  "))
		cmd.type = COMMAND_ORIGIN;
	if (strstr(line, "M10 "))
		cmd.type = COMMAND_START;
	if (strstr(line, "M1  "))
		cmd.type = COMMAND_PEN;
	if (strstr(line, "M4 "))
		cmd.type = COMMAND_LASER;
}

/**
 * @param *line the command string
 *
 */
void Parser::getParams(const char* line, Command& cmd) {
	//find according params and cast to correct types
	if (cmd.type == COMMAND_MOVE) {
		cmd.x = std::stof(findValue('X', line));
		cmd.y = std::stof(findValue('Y', line));
		cmd.absolute = std::stoi(findValue('A', line)) == 1 ? true : false;
	} else if (cmd.type == COMMAND_ORIGIN) {
		//goto origin
	} else if (cmd.type == COMMAND_START) {
		//start
	} else if (cmd.type == COMMAND_LASER) {
		//pen values
	}
}

/**
 * @param *line the command string, key to look for
 * @return parameter as string
 */
const char* Parser::findValue(const char key, const char* cmdline) {
	int pos = -1;

	for (size_t i = 0; i < strlen(cmdline); i++)
		if (cmdline[i] == key)
			pos = i;

	if (pos == -1)
		return 0;

	auto ret = cmdline + pos + 1;
	return ret;
}
