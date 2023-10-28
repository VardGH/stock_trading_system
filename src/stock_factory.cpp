#include "stock_factory.hpp"
#include "hot_wallet.hpp"

#include <fstream>
#include <filesystem>

#include <iostream>

namespace {

const std::string whitespaces = " \t";

} // unnamed namespace

stock_factory& stock_factory::get()
{
    static stock_factory instance;
    return instance;
}

bool stock_factory::read_stock_db(const std::string& path) const noexcept
{
    if (path.empty()) {
        return true ;
    }
    if (!std::filesystem::exists(path)) {
        std::cout << "[Warning] provided database with path " << path << " does not exist" << std::endl;
        return false;
    }

    auto file = std::ifstream(path);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        auto start_pos = line.find_first_not_of(whitespaces);
        if (start_pos == std::string::npos) {
            std::cout << "[Error] corrupted stock db" << std::endl;
        }
        auto end_pos = line.find_first_of(whitespaces, start_pos + 1);
        const std::string symbol = line.substr(start_pos, end_pos);

        start_pos = line.find_first_not_of(whitespaces, end_pos + 1);
        end_pos = line.find_first_of(whitespaces, start_pos + 1);
        const std::string amount = line.substr(start_pos, end_pos - start_pos);
        int quantity = 0;
        try {
            quantity = std::stoi(amount);
        } catch (const std::invalid_argument& ) {
            std::cout << "[Error] stock " << symbol << " has invalid amount " << amount << std::endl;
        }

        start_pos = line.find_first_not_of(whitespaces, end_pos + 1);
        end_pos = line.find_first_of(whitespaces, start_pos + 1);
        const std::string price = line.substr(start_pos, end_pos-start_pos);
        double in_price = 0.0;
        try {
            in_price = std::stod(price);
        } catch (const std::invalid_argument&) {
            std::cout << "[Error] stock " << symbol << " has invalid price " << price << std::endl;
        }

        std::cout << "[Info] register stock " << symbol << " price " << in_price << " quantity " << quantity << std::endl;
        hot_wallet::wallet().register_stock(symbol, stock(symbol, in_price, quantity));
    }
    return true;
}