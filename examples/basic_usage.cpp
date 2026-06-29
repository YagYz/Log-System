#include "../include/logger.h"

int main() {
    Logger myLogger;
    
    // Initialize the logger with the JSON configuration
    myLogger.init("config/loggerCfg.json"); 
    
    myLogger.info("Logger initialized successfully.");
    myLogger.debug("This is a debug message.");
    myLogger.warning("Memory usage is approaching the limit!");
    myLogger.error("Database connection lost.");
    
    return 0;
}