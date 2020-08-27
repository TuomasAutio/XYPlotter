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

auto testline = "G1 X-0.50 Y101.50 A0";

MoveType_t Parser::getMovetype(char *line) {
	MoveType_t cmd;




	if (line[0] == 'G') {
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
