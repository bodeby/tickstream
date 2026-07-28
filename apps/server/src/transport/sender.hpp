// apps/server/src/transport/sender.hpp

#pragma once

#include <cstddef>
#include <cstdint>
#include <netinet/in.h>
#include <span>
#include <string_view>

namespace transport {

class Sender {
public:
  Sender(std::string_view host, uint16_t port);
  ~Sender();

  Sender(const Sender &) = delete;
  Sender &operator=(const Sender &) = delete;

  Sender(Sender &&) noexcept;
  Sender &operator=(Sender &&) noexcept;

  bool send(const void *data, std::size_t size);
  bool send(std::string_view message);
  bool send(std::span<const std::byte>);

private:
  int sock_{-1};
  sockaddr_in addr_{};
};

} // namespace transport
