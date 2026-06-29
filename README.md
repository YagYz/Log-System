# C++ Thread-Safe Logger

[![Language](https://img.shields.io/badge/Language-C++11%20%26%20Above-blue.svg)](#)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](#)

*[🇹🇷 Türkçe açıklamalar için aşağı kaydırın. / Scroll down for Turkish.]*

A minimalist, thread-safe, and highly customizable logging engine built for C++ projects. Designed to be a drop-in solution for game engines, simulations, and backend systems where safe concurrent logging is critical.

## 🚀 Features
- **Thread-Safe by Design:** Utilizes `std::mutex` to prevent race conditions and data corruption across multiple threads.
- **Dynamic Formatting:** Easily shape your log outputs using tags (`[%TIME%] [%LEVEL%] %MESSAGE%`).
- **Dual Output:** Simultaneously stream logs to the console and physical files (`.log`).
- **Level Filtering:** Supports hierarchical log levels (`INFO`, `DEBUG`, `WARNING`, `ERROR`) to control verbosity.

## 📂 Directory Structure
- `include/`: Header files (`.h` / `.hpp`).
- `src/`: Core implementation files (`.cpp`).
- `config/`: JSON configuration files.
- `examples/`: Basic usage scenarios and tests.

## 💻 Quick Start

```cpp
#include "logger.h"

int main() {
    Logger log;
    log.init("config/loggerCfg.json");

    log.info("System initialized successfully.");
    log.debug("This is a debug message.");
    log.warning("Memory usage is approaching the limit!");
    log.error("Database connection lost.");
    
    return 0;
}
```

## TODO

- [ ] Integrate `nlohmann/json` for dynamic configuration parsing from `loggerCfg.json`.

- [ ] Refactor architecture to the Singleton design pattern for global access.

# 🇹🇷 C++ İş Parçacığı Güvenli (Thread-Safe) Logger

C++ projelerinde kullanılmak üzere geliştirilmiş; iş parçacığı güvenliğine (thread-safe) sahip, minimal ve yapılandırılabilir bir loglama motorudur. Oyun motorları, simülasyonlar ve eşzamanlı loglamanın kritik olduğu arka plan sistemleri için "drop-in" (hemen ekle-kullan) bir çözüm olarak tasarlanmıştır.

## 🚀 Özellikler

- **İş Parçacığı Güvenliği (Thread-Safe):** Çoklu thread yapılarında veri bozulmasını ve yarış durumlarını (race conditions) önlemek için `std::mutex` kullanır.

- **Dinamik Formatlama:** Log çıktılarını etiketler yardımıyla `([%TIME%] [%LEVEL%] %MESSAGE%)` istenilen şablona göre şekillendirme imkanı sunar.

- **Çift Yönlü Çıktı:** Logları eşzamanlı olarak hem terminale (konsol) hem de fiziksel dosyalara yazar.

- **Seviye Filtreleme:** İhtiyaca göre gereksiz çıktıları engellemek için `INFO`, `DEBUG`, `WARNING`, `ERROR` seviyelerini destekler.

## 📂 Klasör Yapısı
- `include/`: Başlık (Header) dosyaları. (`.h` / `.hpp`).
- `src/`: Kaynak (Source) dosyaları. (`.cpp`).
- `config/`: JSON formatındaki yapılandırma dosyaları.
- `examples/`: Örnek kullanım senaryoları.

## 💻 Hızlı Başlangıç

```cpp
#include "logger.h"

int main() {
    Logger log;
    log.init("config/loggerCfg.json");

    log.info("Sistem başarıyla başlatıldı.");
    log.debug("Bu bir debug mesajıdır.");
    log.warning("Bellek kullanımı sınıra yaklaştı!");
    log.error("Veritabanı bağlantısı koptu.");
    
    return 0;
}
```

## 📋 Geliştirilecekler (TODO)

- [ ] `loggerCfg.json` dosyasından dinamik ayar okuma işlemi için `nlohmann/json` entegrasyonu.

- [ ] Global erişim için Singleton tasarım desenine (Design Pattern) geçiş.