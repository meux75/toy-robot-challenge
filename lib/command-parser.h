#ifndef ROBOT_COMMAND_PARSER_H
#define ROBOT_COMMAND_PARSER_H

#include <string>
#include "common.h"

namespace ToyRobot
{
    class CommandParser
    {
    public:
        Command operator()(const std::string &in_str);
    };

}

#endif
