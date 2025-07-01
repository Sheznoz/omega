#include "SERVER.hpp"

#include <boost/asio.hpp>
#include <boost/asio/streambuf.hpp>
#include <memory>
#include <iostream>
// #include <memory>

namespace Net
{

// constructor
TCPConnection::TCPConnection(boost::asio::ip::tcp::socket socket, unsigned id)
: m_socket(std::move(socket))
, m_id(id)
{
    std::cout << "Connection (ID: " << m_id << ") created for: " << m_socket.remote_endpoint()
              << std::endl;
}

void async_read_message(ConnectionPtr connection);
void handle_read_message(ConnectionPtr                    connection,
                         const boost::system::error_code& error,
                         size_t                           bytes_transferred);
void async_write_message(ConnectionPtr connection, const char* message_data, size_t message_len);
void handle_write_message(ConnectionPtr                    connection,
                          const boost::system::error_code& error,
                          size_t                           bytes_transferred);
// constructor
Server::Server(int port)
: m_io_service()
, m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
, m_next_connection_id(0)
{
    start_accept(*this);
    std::cout << "Server starting. Waiting for connection..." << std::endl;
}


void start_accept(Server& server)
{
    auto temp_socket = std::make_shared<boost::asio::ip::tcp::socket>(server.m_io_service);
    server.m_acceptor.async_accept(
        *temp_socket,
        std::bind(handle_accept, server, temp_socket, boost::asio::placeholders::error));
};

void handle_accept(Server&                          server,
                   const boost::system::error_code& error,
                   boost::asio::ip::tcp::socket     socket)
{
    if (!error)
    {
        unsigned      current_id = server.m_next_connection_id++;
        ConnectionPtr new_connection
            = std::make_shared<TCPConnection>(std::move(socket), current_id);

        server.m_active_connections[current_id] = new_connection;

        async_read_message(new_connection);
    }
    else
    {
        std::cerr << "Accept error: " << error.message() << std::endl;
    }
    start_accept(server);
}

}  // namespace Net
