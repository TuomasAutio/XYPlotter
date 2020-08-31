#include <stdio.h>
#include <iostream>
#include <string>
#include "singleton.h"

enum CommandType_t {
	INVALID_COMMAND, //NULL
	COMMAND_ORIGIN, //G28 aka go to origin
	COMMAND_MOVE, //G1 go to position
	COMMAND_PEN, //M1 set pen pos
	COMMAND_LASER, //M4 stop
	COMMAND_START, //M10
	COMMAND_READY, //M 11

};

struct Command {
	CommandType_t type;
	int x;
	int y;
	bool absolute;
	int penvalue;
};

class Parser: public Singleton<Parser> {
public:
	Parser();
	~Parser();
	void getMovetype(std::string);
	void getParams(std::string line, Command cmd);
	std::string findValue(std::string key, std::string line);
};

