#ifndef LOG_H
#define LOG_H

#include <ctime>
#include <iomanip>
#include <iostream>

#define LOG_INFO(msg) { \
    auto now = std::time(nullptr); \
    std::cout << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] [INFO]: " << msg << std::endl; \
}

#define LOG_ERROR(msg) { \
    auto now = std::time(nullptr); \
    std::cerr << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] [ERROR]: " << msg << std::endl; \
}

#define LOG_WARNING(msg) { \
    auto now = std::time(nullptr); \
    std::cerr << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] [WARNING]: " << msg << std::endl; \
}

#ifdef DEBUG
    #define LOG_DEBUG(msg) { \
        auto now = std::time(nullptr); \
        std::cout << "[" << std::   put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] [DEBUG]: " << msg << std::endl; \
}
#else
    #define LOG_DEBUG(msg)
#endif

#endif
