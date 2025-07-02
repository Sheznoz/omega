#include "server.cpp"
// #include <iostream>

using namespace Net;

namespace
{
const int SERVER_PORT = 5111;
}

int main()
{
    Server server(SERVER_PORT);
    server.m_io_service.run();
    return 0;
}
