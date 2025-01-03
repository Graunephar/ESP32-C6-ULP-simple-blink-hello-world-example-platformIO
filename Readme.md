
# Setup 

1. Install ESP-IDF

Follow (the official guide)[https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#manual-installation] to install ESP-IDF on your system.

> [!IMPORTANT]  
> NB: Remember tha tyou need to run the install for each board that you want to develop for. So that must mean (I assume) that you need to go back and rerun this if you ever want to use this code for another board

2. ESP-IDF extension in VSCode
Make sure you have the ESP-IDF extension installed i visual studio alomngside PlatformIO. After installation run he command `Configure ESP-IDF Extension`. And follow the guide to to install the latest version of ESP-IDF. I used version 5.4


## ULP


If you want to make changes to the ULP by menu config

´´´´
▶ pio run -t menuconfig
´´´´

Enable Ultra Low Power (ULP) Co-processor

Found in: Component config > Ultra Low Power (ULP) Co-processor