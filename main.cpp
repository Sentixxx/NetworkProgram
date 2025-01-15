#include <iostream>
#include <pcap.h>
#include <format>

int main() {
    pcap_if_t *all_devices;
    
    int i = 0;
    char err_buf[PCAP_ERRBUF_SIZE];
    if(pcap_findalldevs_ex(PCAP_SRC_IF_STRING, nullptr, &all_devices, err_buf) == -1) {
        std::cerr << "Error in pcap_findalldevs_ex: " << err_buf << std::endl;
        return -1;
    }

    for(const pcap_if_t *d = all_devices; d != nullptr; d = d->next) {
        std::cout << i << ". " << "Device: " << d->name << std::endl;
        i++;
        if(d->description) {
            std::cout << std::format("({})\n", d->description);
        } else {
            std::cout << "(No description available)\n";
        }
    }

    if(i == 0) {
        std::cout << "No interfaces found! Make sure Npcap is installed.\n";
        return 1;
    }

    pcap_freealldevs(all_devices);
    return 0;
}
