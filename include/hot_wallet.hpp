#pragma once

#include "stock.hpp"

#include <unordered_map>

class hot_wallet
{
public:
    /// @brief Returns a reference to the singleton instance of the hot_wallet.
    static hot_wallet& wallet();

    /// @brief Registers a stock with the given symbol in the hot wallet.
    void register_stock(const std::string& symbol, stock&& st);

    ///@brief constructors ans assignment operators
    ///@{
private:
    hot_wallet() = default;

    hot_wallet(const hot_wallet& other) = delete;
    hot_wallet& operator=(const hot_wallet& other) = delete;

    hot_wallet(hot_wallet&& other) = delete;
    hot_wallet& operator=(hot_wallet&& other) = delete;
    ///@}
    
private:
    std::unordered_map<std::string, stock> m_registered_stocks; // Map to store registered stocks in the hot wallet.
};