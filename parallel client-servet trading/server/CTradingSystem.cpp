//
// Created by Elon on 20/06/2020.
//

#include <fstream>
#include <iostream>
#include <arpa/inet.h>
#include <zconf.h>
#include <vector>
#include "CTradingSystem.h"

const int MAXLINE = 1000;
const uint32_t MAX_REQUESTS = 10;

CTradingSystem::CTradingSystem() {

    readTreadingData(PATH_TO_DATA_TRADING);
    initTradeSystem();
}

void CTradingSystem::readTreadingData(const std::string& path_to_data) {

    std::ifstream inFile ("stocks.txt");
    if (!inFile)
    {
        std::cerr << "unable to open input file: "
             << " --bailing out! \n";
        return ;
    }

    char oneline[MAXLINE];
    while (inFile)
    {
        inFile.getline(oneline, sizeof(oneline));
        std::string line(oneline);
        std::string delimiter = " | ";
        uint32_t id=0;
        SStockDetails sStockDetails{};
        size_t pos=0;
        std::string stockDetails[4];
        int i=0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            stockDetails[i++] = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
        }
        stockDetails[i]=line;

        for (i = 0; i < 4; ++i) {
            switch(i) {
                case 0:
                    id = static_cast<uint32_t>(stoi(stockDetails[i]));
                    continue;
                case 1:
                    sStockDetails.stock_name = stockDetails[i];
                    continue;
                case 2:
                    sStockDetails.current_value = static_cast<uint32_t>(stoi(stockDetails[i]));
                    continue;
                case 3:
                    sStockDetails.quantity = static_cast<uint32_t>(stoi(stockDetails[i]));
                    continue;
            }
        }
        std::pair<uint32_t ,SStockDetails> stock(id,sStockDetails);
        m_stocks.insert(stock);
    }

    inFile.close();

}

void CTradingSystem::initTradeSystem() {
    struct sockaddr_in serverAddr{};
    //Create the socket.
    m_serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    // Configure settings of the server address struct
    // Address family = Internet
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function to use proper byte order
    serverAddr.sin_port = htons(7799);
    //Set IP address to localhost
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //Set all bits of the padding field to 0
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Bind the address struct to the socket
    bind(m_serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
}

void CTradingSystem::handleRequests() {
    std::vector<std::thread> requests;
    socklen_t addr_size=0;
    struct sockaddr_storage serverStorage{};
    if(listen(m_serverSocket,50)==0)
        printf("Listening\n");
    else
        printf("Error\n");

    int i = 0;
    while(true)
    {
        //Accept call creates a new socket for the incoming connection
        addr_size = sizeof serverStorage;
        m_newSocket = accept(m_serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
        //for each client request creates a thread and assign the client request to it to process
        //so the main thread can entertain next request

        requests.emplace_back(std::thread([this]() { return socketThread(); }));
        i++;

        if( i >= MAX_REQUESTS)
        {
            i = 0;
            while(i < MAX_REQUESTS)
            {
                requests[i++].join();
            }
            break;
        }
    }
}


void CTradingSystem::socketThread() {

    std::lock_guard<std::mutex> guard(m_map_gaurd);
    SServerReply serverReply;
    recv(m_newSocket , m_client_message , sizeof(m_client_message) , 0);
    // Send message to the client socket

    auto clientRequest = new SCleintRequest;
    memcpy(clientRequest, m_client_message, sizeof(m_client_message));


    auto map_iterator = m_stocks.find(clientRequest->stock_id);
    if (map_iterator == m_stocks.end()) {
        serverReply.the_purchase_is_approved = false;
    } else if (map_iterator->second.quantity < clientRequest->quantity) {
        serverReply.the_purchase_is_approved = false;
        serverReply.current_stock_quantity = map_iterator->second.quantity;
    } else {
        serverReply.the_purchase_is_approved = true;
        serverReply.current_stock_quantity = map_iterator->second.quantity - clientRequest->quantity;
        map_iterator->second.quantity -= clientRequest->quantity;
        serverReply.quantity = clientRequest->quantity;
        serverReply.total_price = clientRequest->quantity * map_iterator->second.current_value;
    }

    updateTradingHistory(*clientRequest);
    send(m_newSocket, &serverReply, sizeof(serverReply), 0);
    free(clientRequest);
    close(m_newSocket);

}

void CTradingSystem::updateTradingHistory(SCleintRequest& clientRequest) {

    time_t now = time(0);
    char* current_time = ctime(&now);

    auto iterator = m_stocks.find(clientRequest.stock_id);
    if(iterator == m_stocks.end()){
        return;
    }
    SSaleInfo saleInfo;
    saleInfo.sales_quantity = clientRequest.quantity;
    saleInfo.sales_price = clientRequest.quantity * iterator->second.current_value;
    saleInfo.stock_name = iterator->second.stock_name;
    saleInfo.date_time_of_the_saleing = current_time;

    m_trade_history.push_back(saleInfo);
}

void CTradingSystem::printTradingHistory() {

    for (auto it = m_trade_history.begin(); it != m_trade_history.end(); ++it){
        std::cout << it->date_time_of_the_saleing << "| "<< it->stock_name <<" | "<<it->sales_quantity <<" | "<<
        it->sales_price <<" | " << std::endl << std::endl;
    }

}

void CTradingSystem::printStocksStatus() {

    for (auto& it : m_stocks){
        std::cout << it.second.stock_name << "-" << it.first << " | " << it.second.quantity << std::endl;
    }

}




