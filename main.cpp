#include "chip8.hpp"
#include <unistd.h>

int main(void){
    Chip8 emu;
    emu.Init();
    emu.loadRom("roms/life.ch8");

    while(1){
        emu.emulate();
        usleep(500000);
    }

    return 0;
}