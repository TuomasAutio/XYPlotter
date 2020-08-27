#include <stdio.h>
#include "singleton.h"

enum CommandType_t
{
	COMMAND_START, //M10
	COMMAND_ORIGIN, //G28 aka go to origin
	COMMAND_MOVE, //G1 go to position
	COMMAND_PEN, //M1 set pen pos
	COMMAND_STOP, //M4 stop
	COMMAND_QUERY,
	INVALID_COMMAND,
};


class Parser : public Singleton<Parser>
{
public:
	Parser();
    ~Parser();
    CommandType_t getMovetype(const char*);

};

