#include <iostream>
#include "ipv4_parser.h"
#include "../helper.h"
#include "icmp_parser.h"
#include "tcp_parser.h"
#include "udp_parser.h"

void parse_ip(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 20 > size) {
        return;
    }

    std::cout << "IP Packet:\n";
    uint8_t version_ihl = frame[offset];
    uint8_t version = version_ihl >> 4;
    uint8_t ihl = version_ihl & 0x0F;
    uint16_t total_length = get_uint16(frame, size, offset + 2);
    uint8_t protocol = frame[offset + 9];
    std::string src_ip = get_ipv4_address(frame, size, offset + 12);
    std::string dest_ip = get_ipv4_address(frame, size, offset + 16);

    std::cout << "  Version: " << static_cast<int>(version) << "\n";
    std::cout << "  Header Length: " << static_cast<int>(ihl * 4) << " bytes\n";
    std::cout << "  Total Length: " << total_length << "\n";
    std::cout << "  Protocol: " << static_cast<int>(protocol) << "\n";
    std::cout << "  Source IP: " << src_ip << "\n";
    std::cout << "  Destination IP: " << dest_ip << "\n";

    offset += ihl * 4;

    switch (protocol) {
        case 1:
            parse_icmp(frame, size, offset);
            break;
        case 6:
            parse_tcp(frame, size, offset);
            break;
        case 17:
            parse_udp(frame, size, offset);
            break;
        default:
            std::cout << "  Unknown Protocol: " << static_cast<int>(protocol) << "\n";
            break;
    }
}
