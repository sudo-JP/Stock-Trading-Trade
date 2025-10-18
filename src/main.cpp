#include "account_service.h"
#include "config.h"
#include "tcp_client.h"
#include <iostream>

int main() {
  ENV env = get_env();
  TCPClient client(env);
  TCPMessage a;
  client.send_data(a);
  client.disconnect();
  return 0;
}
