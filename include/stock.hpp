#pragma once

#include <string>

class stock 
{
public:
    stock(const std::string& symbol, double initial_price, int quantity = 0);

    /// @brief Getter for the stock symbol.
    const inline std::string symbol() const noexcept
    {
        return m_symbol;
    }

    /// @brief Getter for the current stock price.
    const inline double price() const noexcept
    {
        return m_current_price;
    }

    /// @brief Getter for the quantity of the stock.
    const inline double quantity() const noexcept
    {
        return m_quantity;
    }

    /// @brief Randomly updates the stock's current price.
    void randomize_price();

private:
    std::string m_symbol;
    double m_current_price;
    int m_quantity;
};
