#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
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
	CommandType_t type = INVALID_COMMAND;
	float x = 0;
	float y = 0;
	bool absolute = NULL;
	int penvalue = 0;
};

class Parser : public Singleton<Parser> {
public:
	Parser();
	~Parser();
	void readFromfile(const char*);
	Command parse(const char*);
	void getMovetype(const char*, Command&);
	void getParams(const char*, Command&);
	const char* findValue(const char, const char*);
};

