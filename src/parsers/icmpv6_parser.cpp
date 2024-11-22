#include <iostream>
#include "icmpv6_parser.h"
#include "../helper.h"

void parse_icmpv6(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 4 > size) {
        return;
    }

    std::cout << "  ICMPv6 Packet:\n";
    uint8_t type = frame[offset];
    uint8_t code = frame[offset + 1];

    std::cout << "    Type: " << static_cast<int>(type) << "\n";
    std::cout << "    Code: " << static_cast<int>(code) << "\n";

    offset += 4;
}
