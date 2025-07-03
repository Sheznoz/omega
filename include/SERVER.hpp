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

struct TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::streambuf       m_buffer;
    unsigned                     m_id;

    TCPConnection(boost::asio::ip::tcp::socket socket, unsigned id);
};

void async_read_message(ConnectionPtr connection);
void handle_read_message(ConnectionPtr                    connection,
                         const boost::system::error_code& error,
                         size_t                           bytes_transferred);

void async_write_message(ConnectionPtr      connection,
                         const std::string& message_data,
                         size_t             message_len);
void handle_write_message(ConnectionPtr                    connection,
                          const boost::system::error_code& error,
                          size_t                           bytes_transferred);

struct Server
{
    boost::asio::io_context           m_io_service;
    boost::asio::ip::tcp::acceptor    m_acceptor;
    std::map<unsigned, ConnectionPtr> m_active_connections;
    unsigned                          m_next_connection_id;

    Server(int port);
};

void start_accept(Server& server);

void handle_accept(Server&                                       server,
                   std::shared_ptr<boost::asio::ip::tcp::socket> socket,
                   const boost::system::error_code&              error);

}  // namespace Net
#endif  // !SERVER_HPP
