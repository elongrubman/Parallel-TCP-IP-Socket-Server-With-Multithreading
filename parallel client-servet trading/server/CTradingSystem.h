//
// Created by Elon on 20/06/2020.
//

#ifndef TRADING_SYSTEM_TRANNING_CTRADINGSYSTEM_H
#define TRADING_SYSTEM_TRANNING_CTRADINGSYSTEM_H


#include "STradingSystemStructures.h"
#include <unordered_map>
#include <list>
#include<pthread.h>
#include <mutex>
#include<sys/socket.h>
#include<netinet/in.h>

#define PATH_TO_DATA_TRADING "./stacks.txt"

class CTradingSystem {
public:

    explicit CTradingSystem();

    void handleRequests();

    void printTradingHistory();

private:
    void socketThread();
    void readTreadingData(const std::string& path_to_data);
    void initTradeSystem();
    void updateTradingHistory(SCleintRequest& clientRequest);


    std::mutex m_map_gaurd;
    std::unordered_map<uint32_t, SStockDetails> m_stocks;
    std::list<SSaleInfo> m_trade_history;


    char m_client_message[sizeof(SCleintRequest)]{};
    char m_server_message[sizeof(SServerReply)]{};
    int m_serverSocket=0, m_newSocket=0;

};


#endif //TRADING_SYSTEM_TRANNING_CTRADINGSYSTEM_H
