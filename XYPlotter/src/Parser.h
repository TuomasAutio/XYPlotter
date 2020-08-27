#ifndef	PARSER_H_
#define PARSER_H_

#include <stdio>

enum CommandType_T
{
	COMMAND_START, //M10
	COMMAND_ORIGIN, //G28 aka go to origin
	COMMAND_MOVE, //G1 go to position
	COMMAND_PEN, //M1 set pen pos
	COMMAND_STOP, //M4 stop
	COMMAND_QUERY,
};


class Parser
{
public:
	Parser();
    ~Parser();
    MoveType_t getMovetype(char*);

};

