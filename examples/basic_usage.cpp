#include "../include/logger.h"

int main() {
    Logger myLogger;
    
    myLogger.init("test"); 
    
    myLogger.info("Logger basariyla baslatildi.");
    myLogger.debug("Bu bir debug mesajidir.");
    myLogger.warning("Bellek kullanimi sinira yaklasti!");
    myLogger.error("Veritabani baglantisi koptu.");
    
    return 0;
}