#include <iostream>
#include "CTradingSystem.h"




int main() {
    CTradingSystem tradingSystem;

    tradingSystem.handleRequests();

    tradingSystem.printTradingHistory();
}