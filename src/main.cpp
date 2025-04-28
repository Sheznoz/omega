#include "Server.hpp"
#include <iostream>

using namespace Mud::Server

    namespace {
  const int SERVER_PORT = 5000;
}

int main() {
  Server server(SERVER_PORT);
  server.Run();

  std::cout << "Yep that worked" << std::endl;

  return 0;
}
