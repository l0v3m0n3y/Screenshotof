# Screenshotof
api for Screenshotof.com json site archive
# cpp
```nim
#include "Screenshotof.h"
#include <iostream>

int main() {
   Screenshotof api;
    
    // Поиск выборов
    auto photos = api.get_screenshot_by_data("github.com","2024-04").then([](json::value result) {
        std::cout << "Search results: " << result.serialize() << std::endl;
    });
    photos.wait();
    
    return 0;
}
```

# Launch (your script)
```
g++ -std=c++11 -o main main.cpp -lcpprest -lssl -lcrypto -lpthread -lboost_system -lboost_chrono -lboost_thread
./main
```
