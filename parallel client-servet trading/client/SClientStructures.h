//
// Created by Elon on 21/06/2020.
//

#ifndef CLIENT_TRADINGSYSTEM_SCLIENTSTRUCTURES_H
#define CLIENT_TRADINGSYSTEM_SCLIENTSTRUCTURES_H

#include <ctime>
#include <string>
#include <thread>

enum stocks{
    SC_ASHDOD_STK_SMART =   0,
    BITAR_JL_STK_SMART =    1,
    MACCABI_HIFA_STK_SMART =2,
    GOOGLE_STK_SMART =      3,
    AMAZON_STK_SMART =      4,
    YES_STK_SMART =         5,
    PLUS500_STK_SMART =     6,
    RAFAEL_STK_SMART =      7,
    ELBIT_STK_SMART =       8,
    FACEBOOK_STK_SMART =    9,
    HAPOEL_TLV_STK_SMART =  10,
    APPLE_STK_SMART =       11,
    MELLANOX_STK_SMART =    12,
    NVIDIA_STK_SMART =      13,
    MONDAY_STK_SMART =      14,
    CHECK_POINT_STK_SMART = 15,
    MICROSOFT_STK_SMART =   16,
    BLOOMBERG_STK_SMART =   17,
    JP_MORGAN_STK_SMART =   18,
    MACCABI_TLV_STK_SMART = 19
};

#pragma pack(push,1)

//struct SStockDetails{
//    std::string stock_name="";
//    uint32_t current_value=0;
//    uint32_t quantity=0;
//};

struct SBuyInfo{
    std::string date_time_of_the_saleing="";
    uint32_t stock_id=0;
    uint32_t sales_quantity=0;
    uint32_t total_price=0;
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

#endif //CLIENT_TRADINGSYSTEM_SCLIENTSTRUCTURES_H
