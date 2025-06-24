#include "server.cpp"
// #include <iostream>

using namespace Net;

namespace
{
const int SERVER_PORT = 8080;
}

int main()
{
    Server server(SERVER_PORT);
    return 0;
}
