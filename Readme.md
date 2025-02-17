
# ESP32-C6 ULP Blink example

This project is simple hello world example on how to use ULP in PlatformIO with ESP-IDF. If you would like an overview of the different options for Arduino and ESP-IDF in PlatformIO on ESP32-C6. I have an overview of my different example reposoties on (a GitHub Gist that can be found on this link.)[https://gist.github.com/Graunephar/57a9882cb3a2ab98be8d63a59ab16ef3]
 


The example of two versions of "blink inspired" programs. One running on the high power processor, one running on the low power processor on the ESP32-C6.

## Parts

### src/main.c
This is the high power program. It will start the low power program, and after this it changes the color of the built in on-board LED in an pattern from red to green to blue. 

### ulp/blink.c 
This is the low power program. It will toggl GPIO 3 from high to low. Thereby blinking the led connected there.

# Setup 

## Hardware

Connect an LED between Gnd and GPIO3. The ULP program will blink this LED. 

### Flash size

Before running, make sure your board's flash size is set in `sdkconfig.defaults`. If you are unsure which specific flash size your board has, run the below command to check.

````
▶ esptool.py --port /dev/cu.usbmodem21401 flash_id

````

Expected output:
````
esptool.py v4.8.1
Serial port /dev/cu.usbmodem21401
Connecting...
Detecting chip type... ESP32-C6
Chip is ESP32-C6 (QFN40) (revision v0.1)
Features: WiFi 6, BT 5, IEEE802.15.4
Crystal is 40MHz
MAC: 40:4c:ca:ff:fe:5f:7f:14
BASE MAC: 40:4c:ca:5f:7f:14
MAC_EXT: ff:fe
Uploading stub...
Running stub...
Stub running...
Manufacturer: c8
Device: 4017
Detected flash size: 8MB
Hard resetting via RTS pin...
````

As you can see, mine has 8MB of flash. Therefore, the content of `sdkconfig.defaults` needs to be:
`CONFIG_ESPTOOLPY_FLASHSIZE_8MB=y`

If you have another flash size on your board make sure the line in sdkconfig.defaults matches that flash size. Below is some examples. 

````
CONFIG_ESPTOOLPY_FLASHSIZE_1MB=y
CONFIG_ESPTOOLPY_FLASHSIZE_2MB=y
CONFIG_ESPTOOLPY_FLASHSIZE_4MB=y
CONFIG_ESPTOOLPY_FLASHSIZE_8MB=y
CONFIG_ESPTOOLPY_FLASHSIZE_16MB=y
CONFIG_ESPTOOLPY_FLASHSIZE_32MB=y
CONFIG_ESPTOOLPY_FLASHSIZE_64MB=y
````

Choose only one of the lines above that matches your flash size and put it in `sdkconfig.defaults`. Be aware that a board-specific file will be generated by PlatformIO at build. It will be called `sdkconfig.*` followed by the specific board you have. If you have already tried to build before making this change, this file might already be present, and it might have the wrong flash size. In that case, since the file is auto-generated, you can just delete it.


## Software

In addition to having VSCode with PlatformIO installed you also need ESP-IDF. You can install it by following these steps.  

1. Install ESP-IDF

Follow (the official guide)[https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#manual-installation] to install ESP-IDF on your system.

> [!IMPORTANT]  
> NB: Remember tha you need to run the install for each board that you want to develop for. So that must mean (I assume) that you need to go back and rerun this if you ever want to use this code for another board

2. ESP-IDF extension in VSCode
Make sure you have the ESP-IDF extension installed i visual studio alomngside PlatformIO. After installation run he command `Configure ESP-IDF Extension`. And follow the guide to to install the latest version of ESP-IDF. I used version 5.4

