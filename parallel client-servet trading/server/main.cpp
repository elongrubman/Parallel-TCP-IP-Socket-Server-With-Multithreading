#include <iostream>
#include "CTradingSystem.h"




int main() {
    CTradingSystem tradingSystem;

    tradingSystem.handleRequests();

    std::cout<< "--------------------- Stocks Status ----------------------" << std::endl << std::endl;

    tradingSystem.printStocksStatus();

    std::cout << std::endl << std::endl << "--------------------- Thrading History ----------------------" << std::endl << std::endl;

    tradingSystem.printTradingHistory();
}