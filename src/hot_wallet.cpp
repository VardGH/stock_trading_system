#include "hot_wallet.hpp"

#include <iostream>

hot_wallet& hot_wallet::wallet()
{
    static hot_wallet val;
    return val;
}

void hot_wallet::register_stock(const std::string& symbol, stock&& st)
{
    if (auto stock_iter = m_registered_stocks.find(symbol);  stock_iter == m_registered_stocks.end()) {
        m_registered_stocks.emplace(symbol, std::move(st));
    } else {
        std::cout << "[Error] symbol " << symbol << " is already registered in the wallet" << std::endl;
    }
}