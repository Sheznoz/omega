#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/streambuf.hpp>
#include <memory>
#include <map>

namespace Net
{

struct Server;
struct TCPConnection;

using ConnectionPtr = std::shared_ptr<TCPConnection>;

struct TCPConnection
{
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::streambuf       streambuf;
    unsigned                     m_id;

    TCPConnection(boost::asio::ip::tcp::socket socket, unsigned id);
};

void async_read_message(ConnectionPtr connection);
void handle_read_message(ConnectionPtr                    connection,
                         const boost::system::error_code& error,
                         size_t                           bytes_transferred);
void async_write_message(ConnectionPtr connection, const char* message_data, size_t message_len);
void handle_write_message(ConnectionPtr                    connection,
                          const boost::system::error_code& error,
                          size_t                           bytes_transferred);

struct Server
{
    boost::asio::io_context           m_io_service;
    boost::asio::ip::tcp::acceptor    m_acceptor;
    std::map<unsigned, TCPConnection> m_active_connections;
    unsigned                          m_next_connection_id;

    Server(int port);
};

void run_server(Server& server);
void start_accept_loop(Server& server);

void handle_accept(Server&                          server,
                   const boost::system::error_code& error,
                   boost::asio::ip::tcp::socket     socket);

}  // namespace Net
#endif  // !SERVER_HPP
