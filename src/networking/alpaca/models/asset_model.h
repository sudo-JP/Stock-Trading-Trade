#include <string>
#include "core/status.h"
#ifndef _ASSET_MODEL_H_
#define _ASSET_MODEL_H_ 

#pragma pack(1)
struct AssetBinaryPayload {
    char id[64];
    char symbol[16];
    char name[64];
    char asset_class[16];        // us_equity, crypto, crypto_perp, etc.
    char exchange[16];
    char status[8];        // "active" / "inactive"

    bool tradable;
    bool marginable;
    bool shortable;
    bool fractionable;
    bool easy_to_borrow;

    float maintenance_margin_requirement;
    float margin_requirement_long;
    float margin_requirement_short;

    float min_order_size;
    float min_trade_increment;
    float price_increment;

    uint32_t attribute_flags; // convert attribute strings to bits
};
#pragma pack()

#endif
