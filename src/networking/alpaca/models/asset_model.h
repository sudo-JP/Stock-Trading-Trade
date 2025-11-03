#include <string>
#include "core/status.h"
#ifndef _ASSET_MODEL_H_
#define _ASSET_MODEL_H_ 

#pragma pack(1)
struct AssetBinaryPayload {
    char id[64];
    char symbol[16];
    char name[64];
    char asset_class[16];        
    char exchange[16];
    char status[8];        

    char tradable;
    char marginable;
    char shortable;
    char fractionable;
    char easy_to_borrow;

    double maintenance_margin_requirement;
    double margin_requirement_long;
    double margin_requirement_short;
};
#pragma pack()

#endif
