#pragma once

#include <string>

class trader_factory
{
public:
    /// @brief Returns a reference to the singleton instance of the trader_factory.
    static trader_factory& get();

    /// @brief Reads trader data from a specified file path.
    bool read_trader_db(const std::string& path) const noexcept;

    ///@brief constructors ans assignment operators
    ///@{
private:
    trader_factory() = default;
    ~trader_factory() = default;

    trader_factory(const trader_factory& other) = delete;
    trader_factory& operator=(const trader_factory& other) = delete;

    trader_factory(trader_factory&& other) = delete;
    trader_factory& operator=(trader_factory&& other) = delete;
    ///@}
};