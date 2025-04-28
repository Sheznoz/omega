#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>

namespace Mud {
namespace Server {
class Server {
public:
  Server(int port)
      : m_acceptor(m_io_service, boost::asio::ip::tcp::endpoint(
                                     boost::asio::ip::tcp::v6(), port)) {}
  void Run() {
    Accept();
    m_io_service.run();
  }

private:
  void Accept() {
    m_accept.async_accept(
        // Handler
        Accept());
  }
  boost::asio::io_service m_io_service;
  boost::asio::ip::tcp::acceptor m_acceptor;
};
} // namespace Server
} // namespace Mud

#endif
