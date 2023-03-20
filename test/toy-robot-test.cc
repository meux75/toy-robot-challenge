#include <functional>
#include "gtest/gtest.h"

#include "lib/common.h"
#include "lib/command-parser.h"
#include "lib/robot.h"

using namespace ToyRobot;

TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(CommandParserTest, ValidPlaceCommandMin)
{
    CommandParser parser;
    Command cmd = parser("PLACE 0,0,NORTH");
    ASSERT_EQ(cmd.type, CommandType::PLACE);
    ASSERT_EQ(cmd.pos.x, MIN_X);
    ASSERT_EQ(cmd.pos.y, MIN_Y);
    ASSERT_EQ(cmd.dir, Direction::NORTH);
}

TEST(CommandParserTest, ValidPlaceCommand)
{
    CommandParser parser;
    Command cmd = parser("PLACE 1,2,NORTH");
    EXPECT_EQ(cmd.type, CommandType::PLACE);
    EXPECT_EQ(cmd.pos.x, 1);
    EXPECT_EQ(cmd.pos.y, 2);
    EXPECT_EQ(cmd.dir, Direction::NORTH);
}

TEST(CommandParserTest, ValidMoveCommand)
{
    CommandParser parser;
    Command cmd = parser("MOVE");
    EXPECT_EQ(cmd.type, CommandType::MOVE);
}

TEST(CommandParserTest, ValidLeftCommand)
{
    CommandParser parser;
    Command cmd = parser("LEFT");
    EXPECT_EQ(cmd.type, CommandType::LEFT);
}

TEST(CommandParserTest, ValidRightCommand)
{
    CommandParser parser;
    Command cmd = parser("RIGHT");
    EXPECT_EQ(cmd.type, CommandType::RIGHT);
}

TEST(CommandParserTest, ValidReportCommand)
{
    CommandParser parser;
    Command cmd = parser("REPORT");
    EXPECT_EQ(cmd.type, CommandType::REPORT);
}

TEST(CommandParserTest, InvalidPlaceCommand)
{
    CommandParser parser;
    try
    {
        Command cmd = parser("PLACE a,b,INVALID_DIRECTION");
        FAIL() << "Expected std::invalid_argument exception not thrown";
    }
    catch (std::invalid_argument &e)
    {
        EXPECT_EQ(e.what(), std::string("stoi"));
    }
    catch (...)
    {
        FAIL() << "Expected std::invalid_argument exception not thrown";
    }
}

TEST(CommandParserTest, InvalidCommand)
{
    CommandParser parser;
    try {
        Command cmd = parser("INVALID_COMMAND");
        FAIL() << "Expected std::invalid_argument exception not thrown";
    } catch (std::invalid_argument& e) {
        EXPECT_EQ(e.what(), std::string("Invalid command"));
    } catch (...) {
        FAIL() << "Expected std::invalid_argument exception not thrown";
    }
}
TEST(RobotTest, PlaceAndReport)
{
    Robot robot;
    robot.place(0, 0, Direction::NORTH);
    testing::internal::CaptureStdout();
    robot.report();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Output: 0,0,NORTH\n");
}

TEST(RobotTest, InvalidPlacement)
{
    Robot robot;
    EXPECT_ANY_THROW(robot.place(5, 5, Direction::NORTH));
}

TEST(RobotTest, Move)
{
    Robot robot;
    robot.place(0, 0, Direction::NORTH);
    robot.move();
    testing::internal::CaptureStdout();
    robot.report();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Output: 0,1,NORTH\n");
}

TEST(RobotTest, TurnLeft)
{
    Robot robot;
    robot.place(0, 0, Direction::NORTH);
    robot.left();
    testing::internal::CaptureStdout();
    robot.report();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Output: 0,0,WEST\n");
}

TEST(RobotTest, TurnRight)
{
    Robot robot;
    robot.place(0, 0, Direction::NORTH);
    robot.right();
    testing::internal::CaptureStdout();
    robot.report();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Output: 0,0,EAST\n");
}

TEST(RobotTest, MultipleCommands)
{
    Robot robot;
    robot.place(1, 2, Direction::EAST);
    robot.move();
    robot.move();
    robot.left();
    robot.move();
    testing::internal::CaptureStdout();
    robot.report();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "Output: 3,3,NORTH\n");
}
