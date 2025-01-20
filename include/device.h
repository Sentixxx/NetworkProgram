#ifndef DEVICE_H
#define DEVICE_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <pcap.h>
#include <format>
#include "logging.h"

#pragma comment(lib, "ws2_32.lib")

int get_device_list(pcap_if_t **all_devices);

pcap_if_t* find_device(pcap_if_t **all_devices, const std::string &device_name);

void device_handler(u_char *user, const struct pcap_pkthdr *header, const u_char *packet);

#endif
