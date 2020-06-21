#include <iostream>
#include "CClientTrader.h"

int main() {

    srand ( time(NULL) );

    CClientTrader client;

    client.printTradingHistory();
}