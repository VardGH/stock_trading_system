#include "trader_factory.hpp"
#include "trader_service.hpp"

#include <fstream>
#include <filesystem>

// #include <stdexcept>

#include <iostream>

namespace {

const std::string whitespaces = " \t";

} // unnamed namespace

trader_factory& trader_factory::get()
{
    static trader_factory instance;
    return instance;
}

bool trader_factory::read_trader_db(const std::string& path) const noexcept
{
    if (path.empty()) {
        return true;
    }
    if (!std::filesystem::exists(path)) {
        std::cout << "[Warning] Provided database with path " << path << " does not exist" << std::endl;
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
        const std::string trader_id_str = line.substr(start_pos, end_pos);

        uint32_t trader_id {};
        try {
            trader_id = std::stoul(trader_id_str);
        } catch (const std::invalid_argument&) {
            std::cout << "[Error] Invalid trader ID in line: " << line << std::endl;
        }

        start_pos = line.find_first_not_of(whitespaces, end_pos + 1);
        end_pos = line.find_first_of(whitespaces, start_pos + 1);
        const std::string name = line.substr(start_pos, end_pos-start_pos);

        std::cout << "[Info] register trader ID " << trader_id << " name " << name << std::endl;
        trader_service::get().register_trader(trader_id, trader(trader_id, name));
    }
    return true;
}