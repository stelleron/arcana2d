#include "utils/Logger.hpp"
#include <iostream>

namespace arcana {
    // Disable log function
    void disabledCallback(const char* message) {

    }

    // Default log function
    void defaultLogCallback(const char* message) {
        std::cout << message << std::endl;
    }

    Logger::Logger() {
        message = "";
        #ifdef ENABLE_ARCANA_LOGGER
            useDefault();
        #else
            disable();
        #endif
    }

    void Logger::disable() {
        setLogCallback(disabledCallback);
        setErrorCallback(disabledCallback);
    }

    void Logger::useDefault() {
        setLogCallback(defaultLogCallback);
        setErrorCallback(defaultLogCallback);
    }

    void Logger::setLogCallback(std::function<void(const char*)> callback) {
        logCallback = callback;
    }

    void Logger::setErrorCallback(std::function<void(const char*)> callback) {
        errorCallback = callback;
    }

    Logger& Logger::operator<<(const std::string& message) {
        this->message += message;
        return *this;
    }

    Logger& Logger::operator<<(const char* message) {
        this->message += message;
        return *this;
    }

    Logger& Logger::operator<<(const int num) {
        this->message += std::to_string(num);
        return *this;
    }

    Logger& Logger::operator<<(const float num) {
        this->message += std::to_string(num);
        return *this;
    }

    Logger& Logger::operator<<(const unsigned long num) {
        this->message += std::to_string(num);
        return *this;
    }

    void Logger::operator<<(const EndLog end) {
        if (end.mType == Message)
            logCallback(message.c_str());
        else
            errorCallback(message.c_str());
        message = "";
    }

    // Internal logger
    Logger logger;
    EndLog endMessage;
    EndLog endError;
}