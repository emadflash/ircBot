#include "utils.h"

int main() {

  //////////////////////////
  // TOR CONNECT         //
  /////////////////////////
  client_sock_t *tor_client = (client_sock_t *)calloc(1, sizeof(client_sock_t));
  strcpy(tor_client->ip, "localhost");
  tor_client->port = 9050;
  tor_connect(tor_client);
  tor_authenticate(tor_client);

  client_sock_t_destroy(tor_client);
  return 0;
}
