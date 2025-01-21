#include "header.h"

#include <array>
#include <cstdint>
#include <cstring>
#include <format>
#include <winsock2.h>

#include "logging.h"

#define ETH_II_MAC_LENGTH 6

EthernetIIHeader::EthernetIIHeader(uint8_t *target_mac, uint8_t *source_mac, uint16_t ether_type) {

    std::memcpy(this->target_mac, target_mac, ETH_II_MAC_LENGTH);
    std::memcpy(this->source_mac, source_mac, ETH_II_MAC_LENGTH);
    this->ether_type = ether_type;
}

EthernetIIHeader::EthernetIIHeader() = default;

void EthernetIIHeader::parse(const uint8_t *packet) {
    // 复制目标MAC地址(前6字节)
    std::memcpy(target_mac, packet, ETH_II_MAC_LENGTH);
    // 复制源MAC地址(接下来6字节)
    std::memcpy(source_mac, packet + ETH_II_MAC_LENGTH, ETH_II_MAC_LENGTH);
    
    // 以网络字节序(大端序)读取类型字段
    ether_type = ntohs(*reinterpret_cast<const uint16_t*>(packet + 12));
}

uint8_t* EthernetIIHeader::get_target_mac() {
    return target_mac;
}

uint8_t* EthernetIIHeader::get_source_mac() {
    return source_mac;
}

uint16_t EthernetIIHeader::get_ether_type() {
    return ether_type;
}

void EthernetIIHeader::print() {
    const auto& t_mac = target_mac;
    const auto& s_mac = source_mac;
    

    static constexpr auto format_str1 = "Target MAC: {:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}";

    static constexpr auto format_str2 = "Source MAC: {:02x}:{:02x}:{:02x}:{:02x}:{:02x}:{:02x}";

    LOG_INFO(std::format(format_str1, t_mac[0], t_mac[1], t_mac[2], t_mac[3], t_mac[4], t_mac[5]));
    LOG_INFO(std::format(format_str2, s_mac[0], s_mac[1], s_mac[2], s_mac[3], s_mac[4], s_mac[5]));

    switch (ether_type)
    {
    case 0x800:
        LOG_INFO("Ether Type: IPv4");
        break;
    case 0x86dd:
        LOG_INFO("Ether Type: IPv6");
        break;
    case 0x0806:
        LOG_INFO("Ether Type: ARP");
        break;
    case 0x08006:
        LOG_INFO("Ether Type: Transparent Ethernet Bridging");
        break;
    default:
        LOG_INFO("Ether Type: Unknown > " + std::to_string(ether_type));
        break;
    }
}
