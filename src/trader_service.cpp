#include "trader_service.hpp"
#include <iostream>

trader_service& trader_service::get() 
{
    static trader_service instance;
    return instance;
}

void trader_service::register_trader(uint32_t trader_id, trader&& tr) 
{
    if (auto trader_iter = m_traders.find(trader_id); trader_iter == m_traders.end()) {
        m_traders.emplace(trader_id, std::move(tr));
        //std::cout << "Trader " << name << " with ID " << trader_id << " registered." << std::endl;
    } else {
        std::cout << "[Error] Trader with ID " << trader_id << " is already registered." << std::endl;
    }
}
