#include "SERVER.hpp"

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/system/detail/error_code.hpp>
#include <memory>
#include <iostream>
#include <functional>

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

void async_read_message(ConnectionPtr connection)
{
    std::cout << "Connection (ID: " << connection->m_id << ") starting read operation."
              << std::endl;

    boost::asio::async_read_until(
        connection->m_socket,
        connection->m_buffer,
        '\n',
        std::bind(handle_read_message, connection, std::placeholders::_1, std::placeholders::_2));
}

void handle_read_message(ConnectionPtr                    connection,
                         const boost::system::error_code& error,
                         size_t                           bytes_transferred)
{
    // boost::asio::const_buffer buffer_sequence = connection->m_buffer.data();
    // write this make it work idiot
}
void async_write_message(ConnectionPtr connection, const char* message_data, size_t message_len);
void handle_write_message(ConnectionPtr                    connection,
                          const boost::system::error_code& error,
                          size_t                           bytes_transferred);

Server::Server(int port)  // constructor
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
        std::bind(handle_accept, std::ref(server), temp_socket, std::placeholders::_1));
    std::cout << "start_accept" << std::endl;
};

void handle_accept(Server&                                       server,
                   std::shared_ptr<boost::asio::ip::tcp::socket> socket,
                   const boost::system::error_code&              error)
{
    std::cout << "handle_accept" << std::endl;
    if (!error)
    {
        unsigned      current_id = server.m_next_connection_id++;
        ConnectionPtr new_connection
            = std::make_shared<TCPConnection>(std::move(*socket), current_id);

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
