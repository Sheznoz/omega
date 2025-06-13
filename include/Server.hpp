#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/streambuf.hpp>
#include <memory>

namespace Mud
{
namespace Net
{

struct TCPConnection
{
    boost::asio::ip::tcp::socket m_socket;
    unsigned                     m_id;
    boost::asio::streambuf       m_read_buffer;
    // constructor
};

class Server
{
public:
    Server(int port)
    : m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
    }
    void run()
    {
        accept();
        m_io_service.run();
    }

private:
    void accept()
    {
        // Handler
        accept();
    }
    boost::asio::io_context        m_io_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::shared_ptr<TCPConnection> m_pointer;
};
}  // namespace Net
}  // namespace Mud

#endif
