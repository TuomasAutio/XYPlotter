#include <stdio.h>
#include "singleton.h"

enum CommandType_t
	{
		INVALID_COMMAND,//NULL
		COMMAND_ORIGIN, //G28 aka go to origin
		COMMAND_MOVE, //G1 go to position
		COMMAND_PEN, //M1 set pen pos
		COMMAND_LASER, //M4 stop
		COMMAND_START, //M10
		COMMAND_READY, //M 11

	};


struct Command
{
	CommandType_t type;
	int x;
	int y;
	bool absolute;
	int penvalue;
};



class Parser : public Singleton<Parser>
{
public:
	Parser();
    ~Parser();
    Command parse(const char* cmdLine);
    const char* readFromfile();
    CommandType_t getMovetype(const char*);
    const char* getParams(const char* line, Command cmd);
    const char* findValue(const char key, const char* line);

};

