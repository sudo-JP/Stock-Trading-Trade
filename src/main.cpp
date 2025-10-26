#include "networking/alpaca/services/account/account_service.h"
#include "core/config/config.h"
#include "networking/tcp/client/tcp_client.h"
#include <iostream>

int main() {
  ENV env = get_env();
  TCPClient client(env);
  BinaryMessage msg; 
  msg.sql_command = 1;
  msg.table = 1; 
  msg.timestamp = 10;
  
  client.send_data(msg);
  client.disconnect();
  return 0;
}
