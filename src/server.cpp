#include "SERVER.hpp"

#include <boost/asio.hpp>
#include <boost/asio/streambuf.hpp>
#include <memory>
#include <map>
#include <iostream>

namespace Net
{

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
Server::Server(int port)
: m_io_service()
, m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
, m_next_connection_id(1)
{
}


void run_server(Server& server)
{
    // server.m_acceptor.async_accept();
    std::cout << "Server starting. Waiting for connection..." << std::endl;
};

void handle_accept(Server&                          server,
                   const boost::system::error_code& error,
                   boost::asio::ip::tcp::socket     socket);

}  // namespace Net
