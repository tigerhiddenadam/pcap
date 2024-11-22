#include <sstream>
#include <iomanip>
#include "helper.h"

uint16_t get_uint16(const uint8_t* frame, size_t size, size_t offset) {
    if (offset + 2 > size) {
        return 0;
    }
    return static_cast<uint16_t>(frame[offset]) << 8 | frame[offset + 1];
}

uint32_t get_uint32(const uint8_t* frame, size_t size, size_t offset) {
    if (offset + 4 > size) {
        return 0;
    }
    return static_cast<uint32_t>(frame[offset]) << 24 |
           static_cast<uint32_t>(frame[offset + 1]) << 16 |
           static_cast<uint32_t>(frame[offset + 2]) << 8 |
           frame[offset + 3];
}

std::string get_mac_address(const uint8_t* frame, size_t size, size_t offset) {
    if (offset + 6 > size) {
        return "";
    }
    std::ostringstream macStream;
    macStream << std::hex << std::setfill('0');
    for (size_t i = offset; i < offset + 6; ++i) {
        macStream << std::setw(2) << static_cast<int>(frame[i]);
        if (i != offset + 5) {
            macStream << ":";
        }
    }
    return macStream.str();
}

std::string get_ipv4_address(const uint8_t* frame, size_t size, size_t offset) {
    if (offset + 4 > size) {
        return "";
    }
    std::ostringstream ipStream;
    for (size_t i = offset; i < offset + 4; ++i) {
        ipStream << static_cast<int>(frame[i]);
        if (i != offset + 3) {
            ipStream << ".";
        }
    }
    return ipStream.str();
}

std::string get_ipv6_address(const uint8_t* frame, size_t size, size_t offset) {
    if (offset + 16 > size) {
        return "";
    }
    std::ostringstream ipStream;
    ipStream << std::hex << std::setfill('0');
    for (size_t i = offset; i < offset + 16; i += 2) {
        uint16_t segment = static_cast<uint16_t>(frame[i]) << 8 | frame[i + 1];
        ipStream << std::setw(4) << segment;
        if (i != offset + 14) {
            ipStream << ":";
        }
    }
    return ipStream.str();
}
