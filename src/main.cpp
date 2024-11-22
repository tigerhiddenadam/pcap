#include <iostream>
#include <csignal>
#include <pcap.h>
#include "packet_handler.h"

volatile sig_atomic_t stop_capture = 0;

void handle_sigint(int /*signum*/) {
    stop_capture = 1;
}

int main(int argc, char* argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t* alldevs = nullptr;
    pcap_if_t* device = nullptr;
    std::string target_device = "eth0";

    if (argc > 1) {
        target_device = argv[1];
    }

    signal(SIGINT, handle_sigint);

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << "\n";
        return 1;
    }

    for (pcap_if_t* d = alldevs; d != nullptr; d = d->next) {
        if (std::string(d->name).find(target_device) != std::string::npos) {
            device = d;
            break;
        }
    }

    if (device == nullptr) {
        std::cerr << "Device " << target_device << " not found.\n";
        std::cout << "Available Devices:\n";
        int count = 1;
        for (pcap_if_t* d = alldevs; d != nullptr; d = d->next) {
            std::cout << count++ << ". " << d->name << " ("
                      << (d->description ? d->description : "No description") << ")\n";
        }
        pcap_freealldevs(alldevs);
        return 1;
    }

    pcap_t* handle = pcap_open_live(device->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Could not open device " << device->name << ": " << errbuf << "\n";
        pcap_freealldevs(alldevs);
        return 1;
    }

    if (pcap_datalink(handle) != DLT_EN10MB) {
        std::cerr << "Device " << device->name << " does not provide Ethernet headers - not supported.\n";
        pcap_close(handle);
        pcap_freealldevs(alldevs);
        return 1;
    }

    std::cout << "Listening on " << device->name << "...\n";
    std::cout << "Press Ctrl+C to stop capturing.\n\n";

    while (!stop_capture) {
        if (pcap_dispatch(handle, 10, packet_handler, nullptr) < 0) {
            std::cerr << "Error occurred during packet capture: " << pcap_geterr(handle) << "\n";
            break;
        }
    }

    std::cout << "\nCapture stopped by user.\n";

    pcap_close(handle);
    pcap_freealldevs(alldevs);

    return 0;
}
