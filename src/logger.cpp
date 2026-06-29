#include "logger.h"
#include <nlohmann/json.hpp>
#include <chrono>
#include <ctime>

using json = nlohmann::json;

Logger::Logger() {
    m_logToConsole = true;
    m_logToFile = false;
    m_activeLogLevel = LogLevel::INFO;
    m_formatPattern = "[%TIME%] [%LEVEL%] %MESSAGE%";
}

Logger::~Logger() {
    if (m_fileStream.is_open()) {
        m_fileStream.close();
    }
}

void Logger::replace_all(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void Logger::init(const std::string& configPath) {
    std::ifstream configFile(configPath);
    
    // Fallback mechanism if the configuration file is missing
    if (!configFile.is_open()) {
        std::cerr << "[SYSTEM WARNING] Configuration file not found (" << configPath << "). Using default settings." << std::endl;
        
        m_logToFile = true; // Required to actually write to the default file
        m_fileStream.open("default.log", std::ios::app);
        return;
    }

    try {
        json configJson;
        configFile >> configJson;

        m_logToConsole = configJson["logger"]["logToConsole"];
        m_logToFile = configJson["logger"]["logToFile"];
        m_formatPattern = configJson["logger"]["formatPattern"];
        std::string logFilePath = configJson["logger"]["logFilePath"];
        std::string levelStr = configJson["logger"]["activeLogLevel"];

        // Parse string to Enum
        if (levelStr == "DEBUG") {
            m_activeLogLevel = LogLevel::DEBUG;
        } else if (levelStr == "INFO") {
            m_activeLogLevel = LogLevel::INFO;
        } else if (levelStr == "WARNING") {
            m_activeLogLevel = LogLevel::WARNING;
        } else if (levelStr == "ERROR") {
            m_activeLogLevel = LogLevel::ERROR;
        } else {
            m_activeLogLevel = LogLevel::INFO; // Default fallback
        }

        // Open the target log file if file logging is enabled
        if (m_logToFile) {
            m_fileStream.open(logFilePath, std::ios::app);
            if (!m_fileStream.is_open()) {
                std::cerr << "[CRITICAL ERROR] Failed to create or open log file: " << logFilePath << std::endl;
            }
        }

    } catch (const json::exception& e) {
        std::cerr << "[JSON PARSE ERROR] Configuration file is corrupted: " << e.what() << std::endl;
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    // Level filtering: Skip processing if the message level is below the active threshold
    if (level < m_activeLogLevel) return;

    // Thread-safety: Lock the mutex to prevent race conditions during write operations
    std::lock_guard<std::mutex> lock(m_mutex);

    // Convert Enum to String
    std::string levelStr;
    switch (level) {
        case LogLevel::INFO:    levelStr = "INFO"; break;
        case LogLevel::DEBUG:   levelStr = "DEBUG"; break;
        case LogLevel::WARNING: levelStr = "WARNING"; break;
        case LogLevel::ERROR:   levelStr = "ERROR"; break;
        default:                levelStr = "UNKNOWN"; break;
    }

    // Generate timestamp
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string timeStr = std::ctime(&now_time);
    timeStr.pop_back(); // Remove the trailing newline character from ctime

    // Format the final output string
    std::string output = m_formatPattern;
    replace_all(output, "%TIME%", timeStr);
    replace_all(output, "%LEVEL%", levelStr);
    replace_all(output, "%MESSAGE%", message);

    // Dispatch to console
    if (m_logToConsole) {
        std::cout << output << std::endl;
    }

    // Dispatch to file
    if (m_logToFile && m_fileStream.is_open()) {
        m_fileStream << output << std::endl;
    }
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}