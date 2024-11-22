#include <iostream>
#include "tcp_parser.h"
#include "../helper.h"

void parse_tcp(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 20 > size) {
        return;
    }

    std::cout << "  TCP Segment:\n";
    uint16_t src_port = get_uint16(frame, size, offset);
    uint16_t dest_port = get_uint16(frame, size, offset + 2);

    std::cout << "    Source Port: " << src_port << "\n";
    std::cout << "    Destination Port: " << dest_port << "\n";

    offset += 20;
}
