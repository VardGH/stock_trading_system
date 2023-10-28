#pragma once

#include <string>

class stock_factory
{
public:
    /// @brief Returns a reference to the singleton instance of the stock_factory.
    static stock_factory& get();

    /// @brief Reads stock data from a specified file path.
    bool read_stock_db(const std::string& path) const noexcept;

    ///@brief constructors ans assignment operators
    ///@{
private:
    stock_factory() = default;
    ~stock_factory() = default;

    stock_factory(const stock_factory& other) = delete;
    stock_factory& operator=(const stock_factory& other) = delete;

    stock_factory(stock_factory&& other) = delete;
    stock_factory& operator=(stock_factory&& other) = delete;
    ///@}
};