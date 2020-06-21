//
// Created by Elon on 21/06/2020.
//

#include "CClientTrader.h"
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <iostream>
#include <cstdlib>

const int MAX_REQUESTS=10;

CClientTrader::CClientTrader() {
    initTrading();
}

void CClientTrader::initTrading() {

    std::vector<std::thread> requests;
    int i = 0;
    while(i< MAX_REQUESTS)
    {
        requests.emplace_back(std::thread([this]() { return clientThread(); }));
        i++;
    }
//    sleep(5);
    i = 0;
    while(i< MAX_REQUESTS)
    {
        requests[i++].join();
    }
}

void CClientTrader::clientThread() {

    std::lock_guard<std::mutex> guard(m_send_request_gaurd);

    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    // Create the socket.
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    //Configure settings of the server address
    // Address family is Internet
    serverAddr.sin_family = AF_INET;
    //Set port number, using htons function
    serverAddr.sin_port = htons(7799);
    //Set IP address to localhost
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

    SCleintRequest cleintRequest;
    int random_index = static_cast<int>(rand() % 20);
    int random_quantity = static_cast<int>((rand() % 9) + 1);
    int stock_to_buy = m_stocks_id[random_index];

    cleintRequest.stock_id = stock_to_buy;
    cleintRequest.quantity = random_quantity;

    if (send(clientSocket, &cleintRequest, sizeof(cleintRequest), 0) < 0) {
        printf("Send failed\n");
    }

    //Read the message from the server into the buffer
    while (recv(clientSocket, m_server_message, sizeof(m_server_message), 0) < 0) {
        printf("Receive failed\n");
    }

    auto serverReply = new SServerReply;
    memcpy(serverReply, m_server_message, sizeof(m_server_message));
    if (serverReply->the_purchase_is_approved) {
        updateTradingHistory(*serverReply, stock_to_buy);
    }
    free(serverReply);
    close(clientSocket);
}

void CClientTrader::updateTradingHistory(SServerReply& serverReply, int stock_to_buy) {
    SBuyInfo buyInfo;

    time_t now = time(nullptr);
    char* current_time = ctime(&now);

    buyInfo.sales_quantity = serverReply.quantity;
    buyInfo.total_price = serverReply.total_price;
    buyInfo.stock_id = stock_to_buy;
    buyInfo.date_time_of_the_saleing = current_time;

    m_tradingHistory.push_back(buyInfo);
}

void CClientTrader::printTradingHistory() {

    for (auto it = m_tradingHistory.begin(); it != m_tradingHistory.end(); ++it){
        std::cout << it->date_time_of_the_saleing << " | "<< it->stock_id <<" | "<<it->sales_quantity <<" | "<<
                  it->total_price << std::endl;
    }
}
