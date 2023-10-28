#include "balance_factory.hpp"
#include "balance_service.hpp"
#include "balance.hpp"

#include <fstream>
#include <filesystem>
#include <sstream>

#include <iostream>

namespace {

const std::string whitespaces = " \t";

} // unnamed namespace

balance_factory& balance_factory::get()
{
    static balance_factory instance;
    return instance;
}

bool balance_factory::read_balance_db(const std::string& path) const noexcept
{
    if (path.empty()) {
        return true;
    }

    if (!std::filesystem::exists(path)) {
        std::cerr << "[Error] Database file with path " << path << " does not exist." << std::endl;
        return false;
    }

    auto file = std::ifstream(path);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        size_t start_pos = line.find_first_not_of(whitespaces);
        size_t end_pos = line.find_first_of(whitespaces, start_pos + 1);

        // profile_id: balance: symbol quantity, symbol quantity
        if (start_pos == std::string::npos || end_pos == std::string::npos) {
            std::cerr << "[Error] Invalid balance line format: " << line << std::endl;
            continue;
        }

        // profile_id and balance
        std::string profile_id_str = line.substr(start_pos, end_pos - start_pos);
        start_pos = line.find_first_not_of(":", end_pos + 1);
        end_pos = line.find_first_of(":", start_pos + 1);
        std::string balance_str = line.substr(start_pos, end_pos - start_pos);

        uint32_t profile_id {};
        double init_balance {};
        try {
            profile_id = std::stoi(profile_id_str);
            init_balance = std::stoi(balance_str);
            std::string stock_data = line.substr(end_pos + 1);

            balance profile_balance = balance(profile_id, init_balance);
            process_stock_data(profile_balance, stock_data);
            balance_service::get().register_balance(profile_id, std::move(profile_balance));
        } catch (const std::invalid_argument&) {
            std::cout << "[Error] Invalid profile_id or balance in line: " << line << std::endl;
        }
    }

    return true;
}

void balance_factory::process_stock_data(balance& bal, std::string& stock_data) const
{
    std::stringstream ss(stock_data);

    while (ss.good()) {
        std::string str;
        getline(ss, str, ',');
        auto start_pos = str.find_first_not_of(whitespaces);
        auto end_pos = str.find_first_of(whitespaces, start_pos + 1);
        auto symbol = str.substr(start_pos, end_pos-start_pos);

        if (end_pos == std::string::npos) {
            std::cout << "[Warning] quantity for the symbol " << symbol << " is not provided skipping" << std::endl;
        }
        auto quantity_str = str.substr(end_pos + 1);

        int quantity = 0;
        try {
            quantity = std::stoi(quantity_str);
            bal.add_stock(symbol, quantity);
        } catch (const std::invalid_argument&) {
            std::cerr << "[Error] Invalid quantity in stock data: " << symbol << std::endl;
        } catch (const std::out_of_range&) {
            std::cerr << "[Error] Quantity out of range in stock data: " << symbol << std::endl;
        }
    }
}