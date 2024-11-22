#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

uint16_t get_uint16(const uint8_t* frame, size_t size, size_t offset);
uint32_t get_uint32(const uint8_t* frame, size_t size, size_t offset);
std::string get_mac_address(const uint8_t* frame, size_t size, size_t offset);
std::string get_ipv4_address(const uint8_t* frame, size_t size, size_t offset);
std::string get_ipv6_address(const uint8_t* frame, size_t size, size_t offset);