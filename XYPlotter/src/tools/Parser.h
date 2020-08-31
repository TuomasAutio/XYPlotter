#include <stdio.h>
#include <string>
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
	const char* readFromfile();
	Command parse(const char*);
	void getMovetype(const char*, Command&);
	void getParams(const char*, Command&);
	const char* findValue(const char, const char*);
};

