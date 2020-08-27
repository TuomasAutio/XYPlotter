#include "Parser.h"
#include "board.h"
#include <cstring>
#include <string>

Parser::Parser() {
}

Parser::~Parser() {
}

/**
 * @param *line the command string
 * @return command
 */
Parser::parse(const char* cmdLine)
{
	Command cmd;
	cmd.type = getMovetype(cmdline);
	cmd.parameters = getParams(cmdline);
	return cmd;
}


/**
 * @param *line the command string
 * @return command type
 */
CommandType_t Parser::getMovetype(const char *line) {
	CommandType_t cmd = INVALID_COMMAND; // if matching command not found, stays as invalid command

	if (line[0] == 'G') { // looks for matching command
		if (line[1] == '1')
			cmd = COMMAND_MOVE;
		else if (line[2] == '2' && line[3] == '8')
			cmd = COMMAND_ORIGIN;
	} else if (line[0] == 'M') {
		if (line[1] == '1' && line[2] == '0')
			cmd = COMMAND_START;
		else if (line[1] == '1')
			cmd = COMMAND_PEN;
		else if (line[1] == '4')
			cmd = COMMAND_LASER;
	}

	return cmd;
}

/**
 * @param *line the command string
 * @return command type
 */
const char* Parser::getParams(const char* line, Command cmd)
{
	if (cmd.type == COMMAND_MOVE)
	{
		cmd.x = stoi(findValue("X", line));
		cmd.y = stoi(findValue("Y", line));
		cmd.absolute = findValue("A") == '1' ? true : false;
	}
	else if (cmd.type == COMMAND_ORIGIN)
	{
		//goto origin
	}
	else if (cmd.type == COMMAND_START)
	{
		//start
	}
	else if (cmd.type == COMMAND_PEN)
	{
		//get value
	}
}

/**
 * @param *line the command string
 * @return parameter as string
 */
const char* Parser::findValue(const char key, const char* line)
{
	char* ret = NULL;
	for(int i = 0; i < strlen(line); i++)
	{
		if(line[i] == key)
		{
			strcat(ret, line[i]);
			if(line[i] == ' ' || line[i] == '\r'|| line[i] == '\n')
				break;
		}
	}
}
