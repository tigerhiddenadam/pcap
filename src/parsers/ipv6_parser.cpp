#include <iostream>
#include "ipv6_parser.h"
#include "../helper.h"
#include "icmpv6_parser.h"
#include "tcp_parser.h"
#include "udp_parser.h"

void parse_ipv6(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 40 > size) {
        return;
    }

    std::cout << "IPv6 Packet:\n";
    uint8_t next_header = frame[offset + 6];
    std::string src_ip = get_ipv6_address(frame, size, offset + 8);
    std::string dest_ip = get_ipv6_address(frame, size, offset + 24);

    std::cout << "  Next Header: " << static_cast<int>(next_header) << "\n";
    std::cout << "  Source IP: " << src_ip << "\n";
    std::cout << "  Destination IP: " << dest_ip << "\n";

    offset += 40;

    switch (next_header) {
        case 58:
            parse_icmpv6(frame, size, offset);
            break;
        case 6:
            parse_tcp(frame, size, offset);
            break;
        case 17:
            parse_udp(frame, size, offset);
            break;
        default:
            std::cout << "  Unknown Next Header: " << static_cast<int>(next_header) << "\n";
            break;
    }
}
