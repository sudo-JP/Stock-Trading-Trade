#include <cstdint>
#ifndef _STATUS_H
#define _STATUS_H

#pragma pack(1)
enum class BinaryStatus : uint32_t {
    UNKNOWN = 0,
    ACTIVE = 1,
    INACTIVE = 2, 
    PENDING = 3,
    SUSPENDED = 4,
    CLOSED = 5,
    DELISTED = 6,
    MAINTENANCE = 7,
};
#pragma pack()

inline constexpr uint32_t status_to_uint32(BinaryStatus status) {
    return static_cast<uint32_t>(status);
}

#endif 
