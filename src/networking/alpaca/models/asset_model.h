#include <string>
#include "core/status.h"
#ifndef _ASSET_MODEL_H_
#define _ASSET_MODEL_H_ 

#pragma pack(1)
struct AssetBinaryPayload {
    char id[64];
    char asset_class[16];
    char exchange[16];
    char symbol[16];
    char name[32];
    uint32_t status;
    char tradeable;
    char marginable; 
    char shortable;
    char easy_to_borrow;
    char fractionable;
};
#pragma pack()

#endif
