#pragma once

#include <cstddef>
#include <cstdint>

void parse_icmpv6(const uint8_t* frame, size_t size, size_t& offset);
