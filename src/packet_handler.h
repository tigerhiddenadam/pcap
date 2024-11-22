#pragma once

#include <pcap.h>

void packet_handler(u_char* user, const struct pcap_pkthdr* header, const u_char* packet);