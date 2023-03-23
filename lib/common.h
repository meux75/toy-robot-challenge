#ifndef ROBOT_COMMON_H
#define ROBOT_COMMON_H

namespace ToyRobot {
const int MAX_X = 4;
const int MIN_X = 0;
const int MAX_Y = 4;
const int MIN_Y = 0;

enum class Direction { NORTH, EAST, SOUTH, WEST };

struct Position {
  int x;
  int y;
};

enum class CommandType { PLACE, MOVE, LEFT, RIGHT, REPORT };

struct Command {
  CommandType type;
  Position pos;
  Direction dir;
};

} // namespace ToyRobot

#endif