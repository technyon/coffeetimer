# coffeetimer
My coffee grinder, the Macap M2D has an adjustable timer built-in. However, some genius of product designer but the knob to adjust the time at the bottom side of the grinder. To adjust it you have to lift the device (which is quite heave), and then adjust it, usually holding it in an awkward position.

To remedy this, I added a microcontroller with a display and a rotary encoder. As a plus, time can now be adjusted with 100 millisecond accuracy, as opposed to the unreliable built-in method which uses an analog potentiometer.

This project includes the firmware for the microcontroller and 3D-printed parts which replace the bottom part of the grinder. The display and rotary encoder are mounted on the right side of the grinder.

If you need help building this, don't hesitate to ask.

# A word of caution

Modding your grinder requires working on the motor power system, which works with mains power. Mains power is dangerous and there's danger to receive a potentially lethal electric shock. Furthermore, fire can be the result of incorrectly wiring the motor. Only do this mod if you know what you are doing! If not, ask someone who does.

Also, please read the paragraph about liability in the provided LICENSE file.

# Compilation

### Prerequisites
- Arduino SDK. Unpack and set ARDUINO_SDK_PATH to its location (e. g. export ARDUINO_SDK_PATH="/usr/share/arduino-1.8.13/")
- ESP32 SDK for Arduino: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json. Add the URL in the Arduino SDK board manager and enable the ESP32 SDK (Version 1.0.6 as ofo the time of writing)
- Arduino cmake toolchain: https://github.com/a9183756-gh/Arduino-CMake-Toolchain/. Unpack to a location of your choice
- cmake

### Running cmake
In the pzemctl directory, create a cmake build directory in change into it.

- cmake -D CMAKE_TOOLCHAIN_FILE=/path/to/Arduino-toolchain.cmake ..
- You will get an error that the board is not selected.
- Run "ccmake ..". As ARDUINO_BOARD, select "ESP32 Dev Module [esp32.esp32]"
- Press c to configure. New options for the ESP32 appear
- Set "Arduino(esp32.esp32)/Partition" to "No OTA (1MB APP/3MB SPIFFS)"
- cmake -D CMAKE_TOOLCHAIN_FILE=/usr/share/Arduino-CMake-Toolchain/Arduino-toolchain.cmake -D ARDUINO_BOARD_OPTIONS_FILE=BoardOptions.cmake ..

cmake should now be setup. Run make to compile.

# Hardware
You need:

- An ESP32
- A Relais
- A USB Power Supply.
- An SSD1306 OLED display
- A rotary encoder
- A big capacitor to stabilize the power supply for the ESP (I used 4700 µF, less might work)
- Cold appliance socket
- M3 and M2 screws, nuts and washers
- Copper tape for EMI shielding
- Feet for the new base

These are the parts I used:
- ESP32 D1 mini: https://www.amazon.de/gp/product/B08BTLYSTM/
- SSD1306 OLED: https://www.amazon.de/gp/product/B0777HHQDT/
- Relais: https://www.amazon.de/gp/product/B07V1X2RSP/
- Rotary encoder: https://www.ebay.de/itm/283974309391 (any other should work, just check it's the right size)
- Cold appliance socket: https://www.amazon.de/gp/product/B004S7RWSY/
- Base feet: https://www.amazon.de/gp/product/B07D4GHGR3/

# Wiring

- The rotary encoder connects to 3.3V and Pins 26 and 27
- The rotary encoder push button connects to ground and pin 33
- The Relais connects to 5v, GND and pin 25
- The grinders switch connects to GND and pin 32
- The display connects to 3.3v, GND, and I2c (Pin 21 for SDA, Pin 22 for SCL)

# 3D Parts

Print all parts. The temporary support can be used to attach the controls part to the lower base.
The upper base part needs to be EMI shielded. Cover all of the underside with copper tape and connect it to ground (Mains power PE). Also cover the capacitor support upper side and connect to PE.