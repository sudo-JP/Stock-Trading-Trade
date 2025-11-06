#include "core/config/config.hpp"
#include "networking/tcp/common/protocol.hpp"
#include <boost/asio.hpp>
#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_


using boost::asio::ip::tcp;

class TCPServer {
public:
  TCPServer(const ENV env)
      : host(env.TCP_HOST), port(env.TCP_PORT), io_context(),
        resolver(io_context), socket(io_context) {
    boost::asio::connect(socket, resolver.resolve(host, port));
  };

  std::vector<uint8_t> receive();

  bool disconnect();

private:
  const std::string host;
  const std::string port;
  boost::asio::io_context io_context;
  tcp::resolver resolver;
  tcp::socket socket;
};


#endif
