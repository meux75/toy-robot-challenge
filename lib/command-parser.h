#ifndef ROBOT_COMMAND_PARSER_H
#define ROBOT_COMMAND_PARSER_H

#include "common.h"
#include <string>

namespace ToyRobot {
class CommandParser {
public:
  Command operator()(const std::string &in_str);
};

} // namespace ToyRobot

#endif
