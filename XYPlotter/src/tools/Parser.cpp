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


Command Parser::parse(std::string cmdLine) {
	Command cmd;
	getMovetype(cmdline, &cmd);
	getParams(cmdline, &cmd);
	return cmd;
}

/**
 * @param *line the command string, &command
 *
 */
void Parser::getMovetype(std::string line, Command cmd) {
	CommandType_t cmd = INVALID_COMMAND; // if matching command not found, stays as invalid command
	if (line.find("G1 ") != string::npos)
		cmd.type = COMMAND_MOVE;
	if (line.find("G28 ") != string::npos)
		cmd.type = COMMAND_ORIGIN;
	if (line.find("M10 ") != string::npos)
		cmd.type = COMMAND_START;
	if (line.find("M1 ") != string::npos)
		cmd.type = COMMAND_PEN;
	if (line.find("M4 ") != string::npos)
		cmd.type = COMMAND_LASER;
	return cmd;
}

/**
 * @param *line the command string
 *
 */
void Parser::getParams(std::string line, Command cmd) {
	//find according params and cast to correct types
	if (cmd.type == COMMAND_MOVE) {
		cmd.x = stol(findValue("X", line));
		cmd.y = stol(findValue("Y", line));
		cmd.absolute = findValue("A") == "1" ? true : false;
	} else if (cmd.type == COMMAND_ORIGIN) {
		//goto origin
	} else if (cmd.type == COMMAND_START) {
		//start
	} else if (cmd.type == COMMAND_PEN) {
		cmd.penvalue = stoi(findValue("M4 ", line));
	}
}

/**
 * @param *line the command string, key to look for
 * @return parameter as string
 */
std::string Parser::findValue(std::string key, std::string arg) {
	//find key from argument and save key pos for copying
	auto pos = arg.find(key) + 1;
	string ret;
	for (int i = pos; i < strlen(line); i++) {
		//copy value and return it
		ret.push_back(line[i]);
		if (arg[i] == ' ' || arg[i] == '\r' || arg[i] == '\n') {
			break;
		}
	}
	return ret;
}
