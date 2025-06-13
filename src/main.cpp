#include "Server.hpp"
// #include <iostream>

using namespace Mud::Net;

namespace
{
const int SERVER_PORT = 5000;
}

int main()
{
    Server server(SERVER_PORT);
    server.run();


    return 0;
}
