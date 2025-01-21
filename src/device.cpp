#include <iostream>
#include <cstdint>

#include "device.h"
#include "header.h"

int get_device_list(pcap_if_t **all_devices) {
    char error_buffer[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(all_devices, error_buffer) == -1) {
        LOG_ERROR("(pcap_findalldevs): " + std::string(error_buffer));
        return -1;
    }

    LOG_INFO("Network devices found: ");

    for(pcap_if_t *device = *all_devices; device; device = device->next) {
        LOG_INFO("Device Name: " + std::string(device->name));

        if(device->description) {
            LOG_INFO("Description: " + std::string(device->description));
        } else {
            LOG_INFO("No description available.");
        }

        for(pcap_addr *address = device->addresses; address; address = address->next) {
            if(address->addr && address->addr->sa_family == AF_INET) {
                const auto *ip_addr = reinterpret_cast<const sockaddr_in*>(address->addr);
                const auto *netmask = reinterpret_cast<const sockaddr_in*>(address->netmask);

                LOG_INFO("IP Address: " + std::string(inet_ntoa(ip_addr->sin_addr)));
                if(netmask) {
                    LOG_INFO("Netmask: " + std::string(inet_ntoa(netmask->sin_addr)));
                }
            }
        }

        LOG_INFO("--------------------------------");
    }

    return 0;
}

pcap_if_t* find_device(pcap_if_t **all_devices, const std::string &device_name) {
    if (device_name.empty()) {
        LOG_ERROR("Device name cannot be empty");
        return nullptr;
    }

    LOG_DEBUG("Finding device: " + device_name);

    for(pcap_if_t *device = *all_devices; device; device = device->next) {
        const std::string curr_name(device->name);
        LOG_DEBUG("Checking device: " + curr_name);
        if(curr_name == device_name) {
            LOG_INFO("Device found: " + device_name);
            return device;
        }
    }

    LOG_WARNING("Device not found: " + device_name);
    return nullptr;
}

void device_handler(u_char *user, const struct pcap_pkthdr *header, const uint8_t *packet) {
    static EthernetIIHeader eth_header;
    
    LOG_INFO("Packet captured: ");
    LOG_INFO("Packet timestamp: " + std::to_string(header->ts.tv_sec) + "." + 
             std::to_string(header->ts.tv_usec));
    LOG_INFO("Packet length: " + std::to_string(header->len));

    eth_header.parse(packet);
    eth_header.print();

    std::cout << std::endl;
}
