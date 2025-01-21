#ifndef HEADER_H
#define HEADER_H

#include <cstdint>
#include <cstring>

#define ETH_II_MAC_LENGTH 6

class EthernetIIHeader {

    public:
    EthernetIIHeader();
    EthernetIIHeader(uint8_t *target_mac, uint8_t *source_mac, uint16_t ether_type);

    void parse(const uint8_t *packet);

    uint8_t* get_target_mac();

    uint8_t* get_source_mac();

    uint16_t get_ether_type();

    void print();

    private:
    uint8_t target_mac[ETH_II_MAC_LENGTH];
    uint8_t source_mac[ETH_II_MAC_LENGTH];
    uint16_t ether_type;
};

#endif // HEADER_H