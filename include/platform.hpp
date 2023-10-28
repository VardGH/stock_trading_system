#pragma once

#include <memory>
#include <thread>
#include <atomic>

class platform
{
public:
    ///@brief function setups platform and starts it
    void start();

    ///@brief stop the program
    void stop(int signal);

    ///@brief static functionalities
    static platform& get();
    ///@}

private:
    ///@brief join the platform
    void join();

    platform();
    ~platform();

    ///@brief constructors ans assignment operators
    ///@{
private:
    platform(const platform& other) = delete;
    platform(platform&& other) = delete;

    platform& operator= (const platform&& other) = delete;
    platform& operator= (platform&& other) = delete;
    ///@}

private:
    std::atomic<bool> m_platform_alive;
    std::thread m_main_thread;
};