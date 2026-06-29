#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>

// Log levels ordered by severity (DEBUG is the lowest, capturing everything)
enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    bool m_logToConsole;
    bool m_logToFile;
    
    std::ofstream m_fileStream;
    std::mutex m_mutex;
    std::string m_formatPattern;
    LogLevel m_activeLogLevel;

    // Internal helper to format the output string
    void replace_all(std::string& str, const std::string& from, const std::string& to);

public:
    // Constructor and Destructor
    Logger();
    ~Logger();

    // Initializes the logger using a JSON configuration file
    void init(const std::string& configPath);

    // Core logging function
    void log(LogLevel level, const std::string& message);

    // Wrapper functions for specific log levels
    void info(const std::string& message);
    void debug(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
};

#endif