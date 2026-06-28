#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR
};

class logger
{
private:
    bool m_logToConsole;
    bool m_logToFile;
    
    std::ofstream m_fileStream;
    std::mutex m_mutex;
    std::string m_formatPattern;

    // Replace output message
    void replace_all(std::string& str, const std::string& from, const std::string& to);

public:
    // Constructer and Deconstructer
    logger();
    ~logger();

    // Inital Fonk.
    void init(const std::string& configPath);

    // Main logging Fonk.
    void log(LogLevel level, const std::string& message);

    // Logger Fonks.
    void info(const std::string& message);
    void debug(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
};

#endif