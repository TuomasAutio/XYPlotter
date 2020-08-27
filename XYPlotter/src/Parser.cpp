#include "Parser.h"
#include "board.h"

Parser::Parser() {
}

Parser::~Parser() {
}

/* M10
 G28
 G1
 M1
 M4
 */

/**
 * @param *line the command string
 * @return command type
 */
CommandType_t Parser::getMovetype(const char *line) {
	CommandType_t cmd = INVALID_COMMAND; // if matching command not found, stays as invalid command

  //TODO: parse uart g-code



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
	}

	return cmd;
}
