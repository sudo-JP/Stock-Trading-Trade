#include <cstdint>
#ifndef _POSITION_MODEL_H_
#define _POSITION_MODEL_H_

#pragma pack(1)
struct PositionBinaryPayload {
    char asset_id[64];
    char symbol[16];
    char exchange[8];
    char asset_class[16];
    char side[8];

    float qty;
    double qty_available;
    float avg_entry_price;
    float market_value;
    float cost_basis;

    float unrealized_pl;
    float unrealized_plpc;
    float unrealized_intraday_pl;
    float unrealized_intraday_plpc;

    float current_price;
    float lastday_price;
    float change_today;

    bool asset_marginable;
    int64_t last_update;  // nanoseconds
};
#pragma pack()

#endif 
