#include "core/config/config.hpp"
#include "networking/tcp/common/protocol.hpp"
#include <boost/asio.hpp>
#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H

using boost::asio::ip::tcp;

class TCPClient {
  public:
    TCPClient(const ENV &env)
        : host(env.TCP_HOST), port(env.TCP_PORT), io_context(),
          resolver(io_context), socket(io_context) {
      boost::asio::connect(socket, resolver.resolve(host, port));
    };

    bool send_data(const BinaryMessage msg, void *payload, size_t payload_size);

    bool disconnect();

  private:
    const std::string host;
    const std::string port;
    boost::asio::io_context io_context;
    tcp::resolver resolver;
    tcp::socket socket;
};

#endif
