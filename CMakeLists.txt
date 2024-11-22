cmake_minimum_required(VERSION 3.10)
project(PacketSniffer VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(SOURCES
    src/main.cpp
    src/packet_handler.cpp
    src/helper.cpp
    src/parsers/ethernet_parser.cpp
    src/parsers/ipv4_parser.cpp
    src/parsers/icmp_parser.cpp
    src/parsers/tcp_parser.cpp
    src/parsers/udp_parser.cpp
    src/parsers/dhcp_parser.cpp
    src/parsers/ipv6_parser.cpp
    src/parsers/icmpv6_parser.cpp
    src/parsers/arp_parser.cpp
)

add_executable(pcap ${SOURCES})

find_path(PCAP_INCLUDE_DIR pcap.h
    PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
)

find_library(PCAP_LIBRARY NAMES pcap
    PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
)

if (PCAP_LIBRARY AND PCAP_INCLUDE_DIR)
    message(STATUS "Found libpcap library: ${PCAP_LIBRARY}")
    message(STATUS "Found libpcap include directory: ${PCAP_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Could not find the libpcap library and/or headers. Please install libpcap development files.")
endif()

target_include_directories(pcap PRIVATE ${PCAP_INCLUDE_DIR})
target_link_libraries(pcap PRIVATE ${PCAP_LIBRARY})

set_target_properties(pcap PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
)
