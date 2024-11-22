#pragma once

#include <cstddef>
#include <cstdint>

void parse_dhcp(const uint8_t* frame, size_t size, size_t& offset);
