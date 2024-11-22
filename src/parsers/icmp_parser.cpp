#include <iostream>
#include "icmp_parser.h"
#include "../helper.h"

void parse_icmp(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 4 > size) {
        return;
    }

    std::cout << "  ICMP Packet:\n";
    uint8_t type = frame[offset];
    uint8_t code = frame[offset + 1];

    std::cout << "    Type: " << static_cast<int>(type) << "\n";
    std::cout << "    Code: " << static_cast<int>(code) << "\n";

    offset += 4;
}
