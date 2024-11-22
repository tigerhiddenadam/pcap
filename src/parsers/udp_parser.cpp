#include <iostream>
#include "udp_parser.h"
#include "../helper.h"
#include "dhcp_parser.h"

void parse_udp(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 8 > size) {
        return;
    }

    std::cout << "  UDP Datagram:\n";
    uint16_t src_port = get_uint16(frame, size, offset);
    uint16_t dest_port = get_uint16(frame, size, offset + 2);

    std::cout << "    Source Port: " << src_port << "\n";
    std::cout << "    Destination Port: " << dest_port << "\n";

    offset += 8;

    if (src_port == 67 || dest_port == 67 || src_port == 68 || dest_port == 68) {
        parse_dhcp(frame, size, offset);
    }
}
