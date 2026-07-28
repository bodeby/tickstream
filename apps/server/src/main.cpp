// apps/server/src/main.cpp

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  // create UDP socket
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("socket error");
    return 1;
  };

  // create socket address
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(5000);

  // configure internet number
  constexpr auto HOST = "127.0.0.1";
  inet_pton(AF_INET, HOST, &addr.sin_addr);
  const char *msg = "hello udp\n";

  // send message
  ssize_t sent = sendto(
    sock,
    msg,
    std::strlen(msg),
    0,
    reinterpret_cast<sockaddr *>(&addr),
    sizeof(addr)
  );

  if (sent < 0) {
    perror("sendto");
  } else {
    printf("Sent %zd bytes\n", sent);
  }

  close(sock);

  return EXIT_SUCCESS;
}
