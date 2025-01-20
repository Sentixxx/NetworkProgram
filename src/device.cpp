#include <iostream>
#include "device.h"

int get_device_list(pcap_if_t **all_devices) {
    char error_buffer[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(all_devices, error_buffer) == -1) {
        LOG_ERROR("(pcap_findalldevs): " + std::string(error_buffer));
        return -1;
    }

    LOG_INFO("Network devices found: ");

    for(pcap_if_t *device = *all_devices; device; device = device->next) {
        LOG_INFO(std::format("Device Name: {}", device->name));

        if(device->description) {
            LOG_INFO(std::format("Description: {}", device->description));
        } else {
            LOG_INFO("No description available.");
        }

        for(pcap_addr *address = device->addresses; address; address = address->next) {
            if(address->addr && address->addr->sa_family == AF_INET) {
                sockaddr_in *ip_addr = (sockaddr_in*)address->addr;
                sockaddr_in *netmask = (sockaddr_in*)address->netmask;

                LOG_INFO(std::format("IP Address: {}", inet_ntoa(ip_addr->sin_addr)));
                if(netmask) {
                    LOG_INFO(std::format("Netmask: {}", inet_ntoa(netmask->sin_addr)));
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
        LOG_DEBUG("Checking device: " + std::string(device->name));
        if(std::string(device->name) == device_name) {
            LOG_INFO("Device found: " + device_name);
            return device;
        }
    }

    LOG_WARNING("Device not found: " + device_name);
    return nullptr;
}

void device_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet) {
    LOG_INFO("Packet captured: ");
    LOG_INFO(std::format("Packet timestamp: {}.{}", header->ts.tv_sec, header->ts.tv_usec));
    LOG_INFO(std::format("Packet length: {}", header->len));
}
