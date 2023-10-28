#include <iostream>
#include <thread>
#include <csignal>

#include "platform.hpp"
#include "stock_factory.hpp"
#include "trader_factory.hpp"
#include "balance_factory.hpp"

platform::platform()
    : m_platform_alive{false}
{
    stock_factory::get().read_stock_db("stocks.txt");
    trader_factory::get().read_trader_db("traders.txt");
    balance_factory::get().read_balance_db("balances.txt");
}

platform::~platform()
{
    join();
}

platform& platform::get()
{
    static platform instance;
    return instance;
}

void platform::start()
{
    m_platform_alive = true;
    m_main_thread = std::thread([this] {
        while (m_platform_alive) {
        // main thread
        }
    });
}

void platform::stop(int signal)
{
    m_platform_alive = false;
}

void platform::join()
{
    if (m_main_thread.joinable()) {
        m_main_thread.join();
    }
}
