#include "trader.hpp"

#include <string>
#include <cassert>
#include "iostream"

/// @brief The order class represents a generic order with common attributes and actions.
class order 
{
public:
    order(int id, int trader_ID, std::string sy, double price, int quantity);
    virtual ~order() = default;

public:
    int trader_id() const;
    int order_id() const;
    double price() const;
    int quantity() const;
    std::string symbol() const;
    virtual void buy() = 0;
    virtual void sell() = 0;

public:
    virtual std::ostream& data(std::ostream& os) const;

private:
    int m_order_id;
    int m_trader_id;
    std::string m_symbol;
    double m_price;
    int m_quantity;
};

/// @brief The market_order class represents a market order, a type of order that executes immediately.
class market_order : public order 
{
public:
    market_order(int order_id, int trader_ID, std::string name, double price, int quantity);
    void buy() override;  //
    void sell() override; //

public:
    friend std::ostream& operator<<(std::ostream &os, const market_order& mo)
    {
        os << "market: ";
        mo.data(os);
        return os;
    }
};

/// @brief The limit_order class represents a limit order, a type of order that executes at a specified price or better.
class limit_order : public order 
{
public:
    limit_order(int order_id, int trader_ID, std::string name, double price, int quantity, int limit = 50);

    void buy() override;  //
    void sell() override; //

    inline int limit()
    {
        return m_limit;
    }

public:
    friend std::ostream& operator<<(std::ostream &os, const limit_order& lo)
    {
        os << "limit: " << lo.m_limit;
        lo.data(os);
        return os;
    }

private:
    int m_limit;
};

/// @brief The order_factory class provides a static method to create instances of orders based on the order type.
class order_factory
{
        static order* create_order(const std::string& type, int order_id, int trader_ID, std::string name, double price, int quantity) {
        if(type == "Limit") {
            return new limit_order(order_id, trader_ID, name, price, quantity);
        } else if(type == "Market") {
            return new market_order(order_id, trader_ID, name, price, quantity);
        }
        assert(false);
    }
};