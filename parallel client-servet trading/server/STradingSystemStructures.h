//
// Created by Elon on 20/06/2020.
//

#ifndef TRADING_SYSTEM_TRANNING_STRADINGSYSTEMSTRUCTURES_H
#define TRADING_SYSTEM_TRANNING_STRADINGSYSTEMSTRUCTURES_H

#include <ctime>
#include <string>
#include <thread>

#pragma pack(push,1)

struct SStockDetails{
    std::string stock_name="";
    uint32_t current_value=0;
    uint32_t quantity=0;
};

struct SSaleInfo{
    std::string date_time_of_the_saleing="";
    std::string stock_name="";
    uint32_t sales_quantity=0;
    uint32_t sales_price=0;
};

struct SCleintRequest{
    uint32_t stock_id=0;
    uint32_t quantity=0;
};

struct SServerReply{
    bool the_purchase_is_approved=0;
    uint32_t current_stock_quantity=0;
    uint8_t quantity=0;
    uint32_t total_price=0;
};

#pragma pack(pop)

#endif //TRADING_SYSTEM_TRANNING_STRADINGSYSTEMSTRUCTURES_H
