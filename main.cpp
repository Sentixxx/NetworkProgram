#include "device.h"
#include "logging.h"


int main(int argc, char *argv[]) {
    // get_device_list();

    if(argc < 2) {
        LOG_ERROR("Usage: " + std::string(argv[0]) + " <device_name>");
        return 1;
    }

    char error_buffer[PCAP_ERRBUF_SIZE];

    pcap_if_t *all_devices = nullptr;
    get_device_list(&all_devices);
    
    pcap_if_t *device = find_device(&all_devices, argv[1]);

    if(device == nullptr) {
        LOG_ERROR("Device not found");
        pcap_freealldevs(all_devices);
        return 1;
    }

    LOG_INFO("Starting capture on device: " + std::string(device->name));
    pcap_t *handle = pcap_open_live(device->name, 65535, 1 , 1000, error_buffer);
    if(handle == nullptr) {
        LOG_ERROR("Failed to open device: " + std::string(error_buffer));
        pcap_freealldevs(all_devices);
        return 1;
    }

    pcap_loop(handle, 0, device_handler, nullptr);

    pcap_close(handle);
    pcap_freealldevs(all_devices);

    return 0;
}
