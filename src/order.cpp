#include <iostream>

#include "order.hpp"
#include "stock.hpp"
#include "trader.hpp"

order::order(int id, int trader_id, std::string name, double price, int quantity)
    : m_order_id(id)
    , m_trader_id(trader_id)
    , m_symbol(name)
    , m_price(price)
    , m_quantity(quantity)
{ 
}


int order::trader_id() const 
{
    return m_trader_id;
}

int order::order_id() const 
{
    return m_order_id;
}

std::string order::symbol() const
{
    return m_symbol;
}

double order::price() const
{
    return m_price;
}

int order::quantity() const 
{
    return m_quantity;
}

std::ostream& order::data(std::ostream& os) const
{
    os << "oid: " << m_order_id 
        << " tid: " << m_trader_id
        << " sym: " << m_symbol
        << " prc: " << m_price
        << " qty: " << m_quantity;
    return os;
}

market_order::market_order(int id, int trader_id, std::string name, double price, int quantity)
    : order(id, trader_id, name, price, quantity) 
{ 
}


void market_order::buy() 
{

}

void market_order::sell() 
{ 

}

limit_order::limit_order(int id, int trader_id, std::string name, double price, int quantity, int limit)
    : order(id, trader_id, name, price, quantity)
    , m_limit(limit)
{ 
}

void limit_order::buy() 
{ 

}

void limit_order::sell() 
{ 

}
