#ifndef _MY_CHIP8_H_
#define _MY_CHIP8_H_
#include <iostream>

class Chip8{

    private:
        // 4k System Memory
        // 0x000 - 0x1FF - Font data (emulator)
        // 0x050 - 0x0A0 - Font data (builtin)
        // 0x200 - 0xFFF - Program ROM and work RAM
        // Program Memory begins at 0x0200
        static char _mem[0x1000];

        // Data registers (V0 - VF)
        // The VF register doubles as a flag for some instructions.
        // In addition operation VF is for carry flag. While in subtraction, it is the "no borrow" flag. 
        // In the draw instruction the VF is set upon pixel collision. 
        static char _V[16];

        // Address register
        // 16 bits wide and is used with several opcodes that involve memory operations
        static unsigned short _I;

        // Program counter
        static unsigned short _pc;

        // Graphic output
        static unsigned char _gfx[64*32];

        // Interrupts 
        static unsigned char _sound_timer, _delay_timer;

        // Stack, Stackpointer
        static unsigned short _stack[16];
        static unsigned short _sp;

        // Keymap
        static unsigned char _key[16];

        // Opcode
        // Consists of 2*8 bit values from program memory
        static unsigned char _opcode;

        // Fontset
        unsigned char fontset[80];
        
        // Function pointer lookup tables
        static void(*_basicInstruction[16])(void);      
        static void(*_8XXN_Instruction[16])(void);

        static void parseInstruction(unsigned short instruction);
   
       // CPU function opcodes
       // For reference see: https://en.wikipedia.org/wiki/CHIP-8#Opcode_table

        static void _interpret00XXInstruction(void);
        static void _interpret8XXNInstruction(void);   
        static void _interpretEXXXInstruction(void);
        static void _interpretFXXXInstruction(void);

        static void _cpu_NOP(void);     // NOP
        static void _cpu_0NNN(void);    // 0NNN 	Call 		                    Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
        static void _cpu_00E0(void);    // 00E0 	Display     disp_clear()        lears the screen.  
        static void _cpu_00EE(void);    // 00EE 	Flow        Return from a subroutine. The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.      
        static void _cpu_1NNN(void);    // 1NNN 	Flow 	    goto NNN; 	        Jumps to address NNN.     
        static void _cpu_2XNN(void);    // 2NNN 	Flow 	    *(0xNNN)() 	        Calls subroutine at NNN.     
        static void _cpu_3XNN(void);    // 3XNN 	Cond 	    if(Vx==NN) 	        Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)                      
        static void _cpu_4XNN(void);    // 4XNN 	Cond 	    if(Vx!=NN) 	        Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)     
        static void _cpu_5YX0(void);    // 5XY0 	Cond 	    if(Vx==Vy) 	        Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)    
        static void _cpu_6XNN(void);    // 6XNN 	Const 	    Vx = NN 	        Sets VX to NN.      
        static void _cpu_7XNN(void);    // 7XNN 	Const 	    Vx += NN 	        Adds NN to VX. (Carry flag is not changed)      
        static void _cpu_8XY0(void);    // 8XY0 	Assign 	    Vx=Vy 	            Sets VX to the value of VY.
        static void _cpu_8XY1(void);    // 8XY1 	BitOp 	    Vx=Vx|Vy 	        Sets VX to VX or VY. (Bitwise OR operation)
        static void _cpu_8XY2(void);    // 8XY2 	BitOp 	    Vx=Vx&Vy 	        Sets VX to VX and VY. (Bitwise AND operation)
        static void _cpu_8XY3(void);    // 8XY3 	BitOp 	    Vx=Vx^Vy 	        Sets VX to VX xor VY.
        static void _cpu_8XY4(void);    // 8XY4 	Math 	    Vx += Vy 	        Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
        static void _cpu_8XY5(void);    // 8XY5 	Math 	    Vx -= Vy 	        VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
        static void _cpu_8XY6(void);    // 8XY6 	BitOp 	    Vx>>=1 	            Stores the least significant bit of VX in VF and then shifts VX to the right by 1.[2]
        static void _cpu_8XY7(void);    // 8XY7 	Math 	    Vx=Vy-Vx 	        Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
        static void _cpu_8XYE(void);    // 8XYE 	BitOp 	    Vx<<=1 	            Stores the most significant bit of VX in VF and then shifts VX to the left by 1.[3]    
        static void _cpu_9XY0(void);    // 9XY0 	Cond 	    if(Vx!=Vy) 	        Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)      
        static void _cpu_ANNN(void);    // ANNN 	MEM 	    I = NNN 	        Sets I to the address NNN.      
        static void _cpu_BNNN(void);    // BNNN 	Flow 	    PC=V0+NNN 	        Jumps to the address NNN plus V0.  
        static void _cpu_CXNN(void);    // CXNN 	Rand 	    Vx=rand()&NN 	    Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
        static void _cpu_DXYN(void);    // DXYN 	Disp 	    draw(Vx,Vy,N) 	    Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
        static void _cpu_EX9E(void);    // EX9E 	KeyOp 	    if(key()==Vx) 	    Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
        static void _cpu_EXA1(void);    // EXA1 	KeyOp 	    if(key()!=Vx) 	    Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
        static void _cpu_FX07(void);    // FX07 	Timer 	    Vx = get_delay() 	Sets VX to the value of the delay timer.
        static void _cpu_FX0A(void);    // FX0A 	KeyOp 	    Vx = get_key() 	    A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
        static void _cpu_FX15(void);    // FX15 	Timer 	    delay_timer(Vx) 	Sets the delay timer to VX.
        static void _cpu_FX18(void);    // FX18 	Sound 	    sound_timer(Vx) 	Sets the sound timer to VX.
        static void _cpu_FX1E(void);    // FX1E 	MEM 	    I +=Vx 	            Adds VX to I.[4]
        static void _cpu_FX29(void);    // FX29 	MEM 	    I=sprite_addr[Vx] 	Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
        static void _cpu_FX33(void);    // FX33 	BCD 	    set_BCD(Vx);
        static void _cpu_FX55(void);    // FX55 	MEM 	    reg_dump(Vx,&I) 	Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
        static void _cpu_FX65(void);    // FX65 	MEM 	    reg_load(Vx,&I) 	Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified. 
        
    public:

        bool drawFlag;

        void Init(void);
        int loadRom(const char *);
        bool emulate(void);
        void checkKeys(void);
        
};
#endif