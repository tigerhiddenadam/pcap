#include <iostream>
#include "arp_parser.h"
#include "../helper.h"

void parse_arp(const uint8_t* frame, size_t size, size_t& offset) {
    if (offset + 28 > size) {
        return;
    }

    std::cout << "ARP Packet:\n";
    uint16_t hardware_type = get_uint16(frame, size, offset);
    uint16_t protocol_type = get_uint16(frame, size, offset + 2);
    uint8_t hardware_size = frame[offset + 4];
    uint8_t protocol_size = frame[offset + 5];
    uint16_t opcode = get_uint16(frame, size, offset + 6);
    std::string sender_mac = get_mac_address(frame, size, offset + 8);
    std::string sender_ip = get_ipv4_address(frame, size, offset + 14);
    std::string target_mac = get_mac_address(frame, size, offset + 18);
    std::string target_ip = get_ipv4_address(frame, size, offset + 24);

    std::cout << "  Hardware Type: " << hardware_type << "\n";
    std::cout << "  Protocol Type: 0x" << std::hex << protocol_type << std::dec << "\n";
    std::cout << "  Hardware Size: " << static_cast<int>(hardware_size) << "\n";
    std::cout << "  Protocol Size: " << static_cast<int>(protocol_size) << "\n";
    std::cout << "  Opcode: " << opcode << "\n";
    std::cout << "  Sender MAC: " << sender_mac << "\n";
    std::cout << "  Sender IP: " << sender_ip << "\n";
    std::cout << "  Target MAC: " << target_mac << "\n";
    std::cout << "  Target IP: " << target_ip << "\n";

    offset += 28;
}
