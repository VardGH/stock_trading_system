#pragma once

#include "stock.hpp"
#include "trader.hpp"

#include <unordered_map>

class trader_service
{
public:
    /// @brief Returns a reference to the singleton instance of the trader_service.
    static trader_service& get();

    /// @brief Registers a trader with the given ID.
    void register_trader(uint32_t id, trader&& tr);

    ///@brief constructors ans assignment operators
    ///@{
private:
    trader_service() = default;

    trader_service(const trader_service& other) = delete;
    trader_service& operator=(const trader_service& other) = delete;

    trader_service(trader_service&& other) = delete;
    trader_service& operator=(trader_service&& other) = delete;
    ///@}

private:
    std::unordered_map<uint32_t, trader> m_traders; // Map to store registered traders.
};