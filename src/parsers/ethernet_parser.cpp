#include <iostream>
#include "ethernet_parser.h"
#include "../helper.h"
#include "ipv4_parser.h"
#include "ipv6_parser.h"
#include "arp_parser.h"

constexpr uint16_t ETHERTYPE_IPv4 = 0x0800;
constexpr uint16_t ETHERTYPE_ARP  = 0x0806;
constexpr uint16_t ETHERTYPE_VLAN = 0x8100;
constexpr uint16_t ETHERTYPE_IPv6 = 0x86DD;

void parse_ethernet_header(const uint8_t* frame, size_t size, size_t& offset,
                           std::string& dest_mac, std::string& src_mac, uint16_t& ether_type) {
    if (offset + 14 > size) {
        return;
    }

    dest_mac = get_mac_address(frame, size, offset);
    offset += 6;
    src_mac = get_mac_address(frame, size, offset);
    offset += 6;
    ether_type = get_uint16(frame, size, offset);
    offset += 2;

    std::cout << "Ethernet Header:\n";
    std::cout << "  Destination MAC: " << dest_mac << "\n";
    std::cout << "  Source MAC: " << src_mac << "\n";
    std::cout << "  EtherType: 0x" << std::hex << ether_type << std::dec << "\n";
}

bool parse_vlan(const uint8_t* frame, size_t size, size_t& offset, uint16_t& ether_type) {
    if (offset + 4 > size) {
        return false;
    }

    uint16_t vlan_tpid = get_uint16(frame, size, offset);
    if (vlan_tpid == ETHERTYPE_VLAN) {
        uint16_t vlan_tci = get_uint16(frame, size, offset + 2);
        offset += 4;
        ether_type = get_uint16(frame, size, offset);
        offset += 2;

        std::cout << "  VLAN Tag:\n";
        std::cout << "    TPID: 0x" << std::hex << vlan_tpid << std::dec << "\n";
        std::cout << "    TCI: " << vlan_tci << "\n";
        std::cout << "    New EtherType: 0x" << std::hex << ether_type << std::dec << "\n";
        return true;
    }
    return false;
}

void parse_ethernet_frame(const uint8_t* frame, size_t size) {
    size_t offset = 0;
    std::string dest_mac, src_mac;
    uint16_t ether_type;

    parse_ethernet_header(frame, size, offset, dest_mac, src_mac, ether_type);

    if (ether_type == ETHERTYPE_VLAN) {
        parse_vlan(frame, size, offset, ether_type);
    }

    switch (ether_type) {
        case ETHERTYPE_IPv4:
            parse_ip(frame, size, offset);
            break;
        case ETHERTYPE_ARP:
            parse_arp(frame, size, offset);
            break;
        case ETHERTYPE_IPv6:
            parse_ipv6(frame, size, offset);
            break;
        default:
            std::cout << "Unknown EtherType: 0x" << std::hex << ether_type << std::dec << "\n";
            break;
    }
}
