#include <string>
#include <stdexcept>

#include "command-parser.h"

namespace ToyRobot
{
    Command CommandParser::operator()(const std::string &in_str)
    {
        CommandType type;
        Position pos;
        Direction direction = Direction::NORTH;

        std::string cmd = in_str.substr(0, in_str.find(' '));
        if (cmd == "PLACE")
        {
            type = CommandType::PLACE;
            // Parse the PLACE command arguments
            pos.x = std::stoi(in_str.substr(in_str.find(' ') + 1, in_str.rfind(',') - in_str.find(',') - 1));
            pos.y = std::stoi(in_str.substr(in_str.find(',') + 1, in_str.rfind(',') - in_str.find(',') - 1));
            std::string dir_str = in_str.substr(in_str.rfind(',') + 1);
            if (dir_str == "NORTH")
            {
                direction = Direction::NORTH;
            }
            else if (dir_str == "EAST")
            {
                direction = Direction::EAST;
            }
            else if (dir_str == "SOUTH")
            {
                direction = Direction::SOUTH;
            }
            else if (dir_str == "WEST")
            {
                direction = Direction::WEST;
            }
            else
            {
                throw std::invalid_argument("Invalid direction");
            }
        }
        else if (cmd == "MOVE")
        {
            type = CommandType::MOVE;
        }
        else if (cmd == "LEFT")
        {
            type = CommandType::LEFT;
        }
        else if (cmd == "RIGHT")
        {
            type = CommandType::RIGHT;
        }
        else if (cmd == "REPORT")
        {
            type = CommandType::REPORT;
        }
        else
        {
            throw std::invalid_argument("Invalid command");
        }

        return {type, pos, direction};
    }
}