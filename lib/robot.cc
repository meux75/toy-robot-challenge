#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

#include "robot.h"
#include "command-parser.h"

namespace ToyRobot
{
    void Robot::place(int x, int y, Direction dir)
    {
        if (x < MIN_X || x > MAX_X || y < MIN_Y || y > MAX_Y)
        {
            throw std::invalid_argument("Invalid position");
        }
        placed_ = true;
        pos_.x = x;
        pos_.y = y;
        dir_ = dir;
    }

    void Robot::move()
    {
        if (!placed_)
        {
            return;
        }
        Position new_pos = pos_;
        switch (dir_)
        {
        case Direction::NORTH:
            new_pos.y++;
            break;
        case Direction::EAST:
            new_pos.x++;
            break;
        case Direction::SOUTH:
            new_pos.y--;
            break;
        case Direction::WEST:
            new_pos.x--;
            break;
        }
        if (new_pos.x < MIN_X || new_pos.x > MAX_X || new_pos.y < MIN_Y || new_pos.y > MAX_Y)
        {
            return;
        }
        pos_ = new_pos;
    }

    void Robot::left()
    {
        if (!placed_)
        {
            return;
        }
        switch (dir_)
        {
        case Direction::NORTH:
            dir_ = Direction::WEST;
            break;
        case Direction::EAST:
            dir_ = Direction::NORTH;
            break;
        case Direction::SOUTH:
            dir_ = Direction::EAST;
            break;
        case Direction::WEST:
            dir_ = Direction::SOUTH;
            break;
        }
    }

    void Robot::right()
    {
        if (!placed_)
        {
            return;
        }
        switch (dir_)
        {
        case Direction::NORTH:
            dir_ = Direction::EAST;
            break;
        case Direction::EAST:
            dir_ = Direction::SOUTH;
            break;
        case Direction::SOUTH:
            dir_ = Direction::WEST;
            break;
        case Direction::WEST:
            dir_ = Direction::NORTH;
            break;
        }
    }

    void Robot::report() const
    {
        if (!placed_)
        {
            return;
        }
        std::cout << "Output: " << pos_.x << "," << pos_.y << ",";
        switch (dir_)
        {
        case Direction::NORTH:
            std::cout << "NORTH";
            break;
        case Direction::EAST:
            std::cout << "EAST";
            break;
        case Direction::SOUTH:
            std::cout << "SOUTH";
            break;
        case Direction::WEST:
            std::cout << "WEST";
            break;
        }
        std::cout << std::endl;
    }

    void Robot::execute(Command cmd)
    {
        if (cmd.type == CommandType::PLACE)
        {
            place(cmd.pos.x, cmd.pos.y, cmd.dir);
        }
        else if (cmd.type == CommandType::MOVE)
        {
            move();
        }
        else if (cmd.type == CommandType::LEFT)
        {
            left();
        }
        else if (cmd.type == CommandType::RIGHT)
        {
            right();
        }
        else if (cmd.type == CommandType::REPORT)
        {
            report();
        }
    }

}
