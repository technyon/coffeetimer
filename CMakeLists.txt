cmake_minimum_required(VERSION 3.0.0)

project(coffeetimer CXX)

include_directories(lib/Adafruit_BusIO)
include_directories(lib/Adafruit_GFX)
include_directories(lib/Adafruit_SSD1306)
include_directories(lib/ai-esp32-rotary-encoder)

file(GLOB SRCFILES
#        "Lib/FreeRTOS/src/*.c"
#        "Lib/FreeRTOS/src/*.cpp"
        "lib/Adafruit_BusIO/*.cpp"
        "lib/Adafruit_GFX/*.cpp"
)

add_executable(coffeetimer
        coffeetimer.cpp
        ${SRCFILES}
        Config.h
        lib/Adafruit_SSD1306/Adafruit_SSD1306.cpp
        lib/ai-esp32-rotary-encoder/src/AiEsp32RotaryEncoder.cpp
        lib/ai-esp32-rotary-encoder/src/AiEsp32RotaryEncoderNumberSelector.cpp
        Display.cpp Config.h)

# Arduino.h is included in hello_world.cpp, so link with Arduino core
target_link_arduino_libraries(coffeetimer
    PRIVATE
        core
        SPI
        Wire
)

# This is needed for the generation of HEX binary and uploading it
target_enable_arduino_upload(coffeetimer)

