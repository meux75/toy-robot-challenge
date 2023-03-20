#ifndef ROBOT_H
#define ROBOT_H

#include "common.h"
namespace ToyRobot
{
    class Robot
    {
    public:
        Robot() : placed_(false) {}

        void place(int x, int y, Direction dir);
        void move();
        void left();
        void right();
        void report() const;
        void execute(Command cmd);

    private:
        Position pos_;
        Direction dir_;
        bool placed_;
    };

}

#endif
