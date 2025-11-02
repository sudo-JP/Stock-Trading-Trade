#include "protocol.h"
#include <cstring>

std::vector<uint8_t> serialize(const BinaryMessage &msg, const void *payload, size_t payload_size) {
    std::vector<uint8_t> buf; 
    buf.reserve(sizeof(msg) + payload_size);
    const uint8_t *bin_msg = reinterpret_cast<const uint8_t*>(&msg);
    const uint8_t *bin_payload = reinterpret_cast<const uint8_t*>(payload);

    buf.insert(buf.end(), bin_msg, bin_msg + sizeof(msg));
    buf.insert(buf.end(), bin_payload, bin_payload + payload_size);

    return buf;
}

std::vector<uint8_t> serialize(const BinaryMessage &msg, const std::vector<void *> &payload, size_t payload_size) {
    std::vector<uint8_t> buf; 
    // Reserver binary 
    buf.reserve(sizeof(msg) + payload_size * payload.size());
    const uint8_t *bin_msg = reinterpret_cast<const uint8_t*>(&msg);
    buf.insert(buf.end(), bin_msg, bin_msg + sizeof(msg));

    for (auto const &element : payload) {
        const uint8_t *bin_payload = reinterpret_cast<const uint8_t*>(element);
        buf.insert(buf.end(), bin_payload, bin_payload + payload_size);
    }

    return buf;
}
