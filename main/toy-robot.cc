#include <iostream>
#include <stdexcept>
#include <string>

#include "lib/command-parser.h"
#include "lib/common.h"
#include "lib/robot.h"

using namespace ToyRobot;

int main() {
  CommandParser parser;
  Robot robot;
  std::string line;

  while (std::getline(std::cin, line)) {
    try {
      Command cmd = parser(line);
      robot.execute(cmd);
    } catch (const std::exception &e) {
      // Handle invalid commands gracefully
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  return 0;
}