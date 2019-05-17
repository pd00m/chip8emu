#include "chip8.hpp"
#include <unistd.h>

int main(void){
    Chip8 emu;
    emu.Init();
    emu.loadRom("rng.ch8");

    while(1){
        emu.emulate();
        usleep(250000);
        //getchar();
    }

    return 0;
}