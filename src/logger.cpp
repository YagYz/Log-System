#include "logger.h"
#include <chrono>
#include <ctime>

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
    while ((start_pos = str.find(from,start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void Logger::init(const std::string& configPath) {
    m_logToFile = true;
    m_logToConsole = true;

    m_fileStream.open("lastest.log", std::ios::app);

    if (!m_fileStream.is_open()) {
        std::cerr << "[CRITICAL ERROR] Log Folder Not Found!" << std::endl;
    }
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < m_activeLogLevel) return;

    std::lock_guard<std::mutex> lock(m_mutex);

    std::string levelStr;
    switch (level)
    {
    case LogLevel::INFO:    levelStr = "INFO"; break;
    case LogLevel::DEBUG:   levelStr = "DEBUG"; break;
    case LogLevel::WARNING: levelStr = "WARNING"; break;
    case LogLevel::ERROR:   levelStr = "ERROR"; break;
    default:                levelStr = "UNKNOWN"; break;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string timeStr = std::ctime(&now_time);
    timeStr.pop_back();

    std::string output = m_formatPattern;
    replace_all(output, "%TIME%", timeStr);
    replace_all(output, "%LEVEL%", levelStr);
    replace_all(output, "%MESSAGE%", message);

    if (m_logToConsole) {
        std::cout << output << std::endl;
    }

    if (m_logToFile) {
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