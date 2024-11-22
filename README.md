# pcap++
Packet Capturing and Parsing.

## Getting Started

### Set the Adapter

Type `ip a` into the terminal to get a list of network adapters. Then edit line 16 of `main.cpp` and set the string to be adapter of your choice.

```
std::string target_device = "eth0";
```

Let's say we wanted to capture packets on a wireless adapter, we might edit line 16 to the following:

```
std::string target_device = "wlan0";
```

### Building

Type the following into the terminal:
```
sudo apt-get install libpcap-dev

mkdir build && cd build
cmake ..
cmake --build .
```

### Running

```
sudo bin/pcap
```

Please be aware pressing `Ctrl+C` will terminate when the next packet is received and fixing this is a good first pull request. You can also kill the program with `CTRL+Z` and typing `sudo pkill pcap` into the terminal.

## Code Overview

The program is a simple packet sniffer that captures network traffic from a specified interface using `libpcap`. The `main.cpp` sets up the interface, handles stopping with `Ctrl+C`, and enters a loop to collect packets. Each captured packet is passed to a `packet_handler` function, which extracts raw network frames as byte arrays and forwards them to specific parsers for further analysis.

The parsers pull values like IP addresses, MAC addresses, and protocol details directly from the byte arrays. This includes Ethernet, IPv4, IPv6, ARP, TCP, UDP, ICMP, ICMPv6, and DHCP protocols. Each parser handles just one protocol, keeping the code clean and modular. The utility functions simplify reading data from the byte arrays, ensuring values are correctly extracted and formatted.

## Project Structure

1. **Entry Point (`main.cpp`)**
   - Handles command-line arguments to specify the network interface.
   - Sets up signal handling to gracefully stop the packet capture when interrupted (e.g., via `Ctrl+C`).
   - Uses `libpcap` to find available devices and opens the specified device for capturing.
   - Enters a loop to continuously capture packets until interrupted.
   - Utilizes a callback function `packet_handler` to process each captured packet.

2. **Packet Handler (`packet_handler.cpp` and `packet_handler.h`)**
   - Defines the `packet_handler` function, which is called by `libpcap` for each captured packet.
   - Prints packet metadata such as timestamp and length.
   - Calls the `parse_ethernet_frame` function to begin parsing the packet data.

3. **Helper Functions (`helper.cpp` and `helper.h`)**
   - Provides utility functions to read data from the raw packet bytes:
     - `get_uint16` and `get_uint32` to read 16-bit and 32-bit unsigned integers, handling endianness.
     - `get_mac_address` to extract and format MAC addresses.
     - `get_ipv4_address` and `get_ipv6_address` to extract and format IP addresses.

4. **Protocol Parsers (`parsers/` directory)**
   - **Ethernet Parser (`ethernet_parser.cpp` and `ethernet_parser.h`)**
     - Parses the Ethernet frame header to extract source and destination MAC addresses and the EtherType.
     - Handles VLAN tagging if present.
     - Determines the next protocol (IPv4, IPv6, or ARP) based on the EtherType and calls the appropriate parser.
   - **IPv4 Parser (`ipv4_parser.cpp` and `ipv4_parser.h`)**
     - Parses the IPv4 header to extract version, header length, total length, protocol, source IP, and destination IP.
     - Determines the next protocol (TCP, UDP, or ICMP) based on the protocol field and calls the appropriate parser.
   - **IPv6 Parser (`ipv6_parser.cpp` and `ipv6_parser.h`)**
     - Parses the IPv6 header to extract version, traffic class, flow label, payload length, next header, hop limit, source IP, and destination IP.
     - Handles extension headers if present.
     - Determines the next protocol (TCP, UDP, or ICMPv6) based on the next header field and calls the appropriate parser.
   - **ARP Parser (`arp_parser.cpp` and `arp_parser.h`)**
     - Parses ARP packets to extract hardware type, protocol type, operation code, sender and target MAC and IP addresses.
   - **ICMP Parser (`icmp_parser.cpp` and `icmp_parser.h`)**
     - Parses ICMP packets to extract type and code.
   - **ICMPv6 Parser (`icmpv6_parser.cpp` and `icmpv6_parser.h`)**
     - Parses ICMPv6 packets to extract type and code.
   - **TCP Parser (`tcp_parser.cpp` and `tcp_parser.h`)**
     - Parses TCP segments to extract source and destination ports, sequence number, acknowledgment number, and header length.
   - **UDP Parser (`udp_parser.cpp` and `udp_parser.h`)**
     - Parses UDP datagrams to extract source and destination ports.
     - If the ports correspond to DHCP, calls the DHCP parser.
   - **DHCP Parser (`dhcp_parser.cpp` and `dhcp_parser.h`)**
     - Parses DHCP packets to extract operation, hardware type, transaction ID, client IP, your IP, server IP, gateway IP, and client MAC address.