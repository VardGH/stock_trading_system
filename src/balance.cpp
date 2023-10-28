#include "balance.hpp"

balance::balance(uint32_t profile_id, double init_balance)
    : m_profile_id(profile_id) 
    , m_balance (init_balance)
{}