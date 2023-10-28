#include "balance_service.hpp"

balance_service& balance_service::get() 
{
    static balance_service instance;
    return instance;
}

void balance_service::register_balance(uint32_t profile_id, balance&& bal)
{
    m_balances.try_emplace(profile_id, std::move(bal));
}