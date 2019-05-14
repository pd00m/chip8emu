cmake_minimum_required (VERSION 2.6)
project (Chip8Emu)
file(GLOB SOURCES "*.cpp")
add_executable(chip8emu ${SOURCES})
