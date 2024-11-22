#include <iostream>
#include "dhcp_parser.h"
#include "../helper.h"

void parse_dhcp(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 236 > size) {
        return;
    }

    std::cout << "    DHCP Packet:\n";
    uint8_t op = frame[offset];
    uint8_t htype = frame[offset + 1];
    uint8_t hlen = frame[offset + 2];
    uint8_t hops = frame[offset + 3];
    uint32_t xid = get_uint32(frame, size, offset + 4);
    uint16_t secs = get_uint16(frame, size, offset + 8);
    uint16_t flags = get_uint16(frame, size, offset + 10);
    std::string ciaddr = get_ipv4_address(frame, size, offset + 12);
    std::string yiaddr = get_ipv4_address(frame, size, offset + 16);
    std::string siaddr = get_ipv4_address(frame, size, offset + 20);
    std::string giaddr = get_ipv4_address(frame, size, offset + 24);
    std::string chaddr = get_mac_address(frame, size, offset + 28);

    std::cout << "      Operation: " << static_cast<int>(op) << "\n";
    std::cout << "      Hardware Type: " << static_cast<int>(htype) << "\n";
    std::cout << "      Hardware Address Length: " << static_cast<int>(hlen) << "\n";
    std::cout << "      Hops: " << static_cast<int>(hops) << "\n";
    std::cout << "      Transaction ID: " << xid << "\n";
    std::cout << "      Seconds: " << secs << "\n";
    std::cout << "      Flags: " << flags << "\n";
    std::cout << "      Client IP: " << ciaddr << "\n";
    std::cout << "      Your IP: " << yiaddr << "\n";
    std::cout << "      Server IP: " << siaddr << "\n";
    std::cout << "      Gateway IP: " << giaddr << "\n";
    std::cout << "      Client MAC: " << chaddr << "\n";

    offset += 236;
}
