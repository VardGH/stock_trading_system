#pragma once

#include "balance.hpp"

#include <string>

class balance_factory
{
public:
    /// @brief Returns a reference to the singleton instance of the balance_factory.
    static balance_factory& get();

    /// @brief Reads balance data from a specified file path.
    bool read_balance_db(const std::string& path) const noexcept;

    /// @brief Processes stock data and updates the given balance instance.
    void process_stock_data(balance& bal, std::string& stock_data) const;

    ///@brief constructors ans assignment operators
    ///@{
private:
    balance_factory() = default;
    ~balance_factory() = default;

    balance_factory(const balance_factory& other) = delete;
    balance_factory& operator=(const balance_factory& other) = delete;

    balance_factory(balance_factory&& other) = delete;
    balance_factory& operator=(balance_factory&& other) = delete;
    ///@}
};