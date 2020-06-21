//
// Created by Elon on 21/06/2020.
//

#ifndef CLIENT_TRADINGSYSTEM_CCLIENTTRADER_H
#define CLIENT_TRADINGSYSTEM_CCLIENTTRADER_H

#include "SClientStructures.h"
#include <list>
#include <mutex>

class CClientTrader {
public:

    explicit CClientTrader();

    void printTradingHistory();


private:

    void initTrading();
    void clientThread();
    void updateTradingHistory(SServerReply& serverReply, int stock_to_buy);


    std::mutex m_send_request_gaurd;

    int m_stocks_id[20] = {100,105,120,117,207,202,169,70,44,201,333,175,15,802,243,232,111,139,261,244};
    char m_server_message[sizeof(SServerReply)]{};
    std::list<SBuyInfo> m_tradingHistory;
};


#endif //CLIENT_TRADINGSYSTEM_CCLIENTTRADER_H
