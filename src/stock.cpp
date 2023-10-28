#include "stock.hpp"

#include <ctime>
#include <random>


stock::stock(const std::string& symbol, double initial_price, int quantity) 
    : m_symbol(symbol)
    , m_current_price(initial_price)
    , m_quantity(quantity)
{}

// std::string Stock::get_stock_name() const 
// {
//     return m_name;
// }

// double Stock::get_current_price() const 
// {
//     return m_current_price;
// }

// void Stock::set_quantity(int quantity) 
// {
//     m_quantity = quantity;
// }

// int Stock::get_quantity() const 
// {
//     return m_quantity;
// }

void stock::randomize_price() 
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    double percentage_change = (rand() % 11 - 5) / 100.0;

    m_current_price = (1.0 + percentage_change);
}
