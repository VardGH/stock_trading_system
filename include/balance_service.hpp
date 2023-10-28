#pragma once

#include "stock.hpp"
#include "balance.hpp"

#include <unordered_map>

class balance_service
{
public:
    /// @brief Returns a reference to the singleton instance of the balance_service.
    static balance_service& get();

    /// @brief Registers a balance profile with the given profile ID.
    void register_balance(uint32_t profile_id, balance&& bal);

    ///@brief constructors ans assignment operators
    ///@{
private:
    balance_service() = default;

    balance_service(const balance_service& other) = delete;
    balance_service& operator=(const balance_service& other) = delete;

    balance_service(balance_service&& other) = delete;
    balance_service& operator=(balance_service&& other) = delete;
    ///@}
    
private:
    std::unordered_map<uint32_t, balance> m_balances; // Map to store balance profiles.
};