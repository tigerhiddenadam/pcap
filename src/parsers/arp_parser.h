#pragma once

#include <cstddef>
#include <cstdint>

void parse_arp(const uint8_t* frame, size_t size, size_t& offset);
