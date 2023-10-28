#pragma once

#include <string>

class trader 
{
public:
    trader(uint32_t trader_id, const std::string& name);

    /// @brief Getter for the trader ID.
    const inline uint32_t trader_id() const noexcept
    {
        return m_trader_id;
    }

    /// @brief Getter for the trader name.
    const inline std::string name() const noexcept
    {
        return m_name;
    }

private:
    uint32_t m_trader_id;
    std::string m_name;
};