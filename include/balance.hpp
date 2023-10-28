#pragma once

#include <unordered_map>
#include <string>

class balance
{
public:
    balance(uint32_t profile_id, double init_balance);

public:

    /// @brief Getter for the profile ID.
    const inline uint32_t profile_id() const noexcept
    {
        return m_profile_id;
    }

    /// @brief Getter for the current balance.
    double get_balance() const noexcept
    {
        return m_balance;
    }

    /// @brief Adds stocks to the balance for a given symbol and quantity.
    inline void add_stock(const std::string& symbol, int quantity) 
    {
        m_stocks[symbol] = quantity;
    }

private:
    uint32_t m_profile_id;
    double m_balance;
    std::unordered_map<std::string, int> m_stocks;
};