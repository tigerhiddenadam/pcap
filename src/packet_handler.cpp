#include <iostream>
#include "packet_handler.h"
#include "parsers/ethernet_parser.h"

void packet_handler(u_char* /*user*/, const struct pcap_pkthdr* header, const u_char* packet) {
    std::cout << "----------------------------------------\n";
    std::cout << "Packet captured!\n";
    std::cout << "Timestamp: " << header->ts.tv_sec << "." << header->ts.tv_usec << "\n";
    std::cout << "Captured Length: " << header->caplen << " bytes\n";
    std::cout << "Original Length: " << header->len << " bytes\n\n";

    parse_ethernet_frame(packet, header->caplen);
    std::cout << "\n";
}
