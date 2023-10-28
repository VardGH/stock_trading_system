#include "platform.hpp"

#include <iostream>
#include <csignal>

void signalHandler(int signal)
{
    platform::get().stop(signal);
}

int main()
{
    signal(SIGABRT, signalHandler);
    signal(SIGINT,  signalHandler);
    signal(SIGTERM, signalHandler);

    try {
        platform::get().start();
    } catch (const std::exception& ex) {
        std::cout << "Exception happened: " << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Exception happened" << std::endl;
    }

    return 0;
}