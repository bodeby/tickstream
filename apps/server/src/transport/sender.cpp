// sender.cpp

#include "sender.hpp"

#include <arpa/inet.h>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <unistd.h>

namespace transport {

Sender::Sender(std::string_view host, std::uint16_t port) {
  sock_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_ < 0) throw std::runtime_error("socket() failed");

  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);

  if (inet_pton(AF_INET, host.data(), &addr_.sin_addr) != 1)
    throw std::runtime_error("inet_pton() failed");
}

Sender::~Sender() {
  if (sock_ >= 0) close(sock_);
}

bool Sender::send(const void *data, std::size_t size) {
  return sendto(
           sock_,
           data,
           size,
           0,
           reinterpret_cast<sockaddr *>(&addr_),
           sizeof(addr_)
         ) == static_cast<ssize_t>(size);
}

bool Sender::send(std::string_view msg) {
  return send(msg.data(), msg.size());
}

bool Sender::send(std::span<const std::byte> msg) {
  return send(msg.data(), msg.size());
}

} // namespace transport
