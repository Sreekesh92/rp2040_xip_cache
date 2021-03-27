cmake_minimum_required(VERSION 3.13)

# Initialise SDK based on pico SDK path
include(pico_sdk_import.cmake)

project(blinky)

# Initialise the SDK
pico_sdk_init()

# Add source files to target executable
add_executable(blinky blink.c)

# Link to libraries
target_link_libraries(blinky pico_stdlib)

pico_add_extra_outputs(blinky)
