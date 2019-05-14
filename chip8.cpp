#include "chip8.hpp"

void(*Chip8::_basicInstruction[16])(void){          Chip8::_interpret00XXInstruction,     //0x0XXX
                                                    Chip8::_cpu_1NNN,                     //0x1XXX
                                                    Chip8::_cpu_2XNN,                     //0x2XXX
                                                    Chip8::_cpu_3XNN,                     //0x3XXX
                                                    Chip8::_cpu_4XNN,                     //0x4XXX        
                                                    Chip8::_cpu_5YX0,                     //0x5XXX
                                                    Chip8::_cpu_6XNN,                     //0x6XXX
                                                    Chip8::_cpu_7XNN,                     //0x7XXX
                                                    Chip8::_interpret8XXNInstruction,     //0x8XXX
                                                    Chip8::_cpu_9XY0,                     //0x9XXX
                                                    Chip8::_cpu_ANNN,                     //0xAXXX
                                                    Chip8::_cpu_BNNN,                     //0xBXXX
                                                    Chip8::_cpu_CXNN,                     //0xCXXX
                                                    Chip8::_cpu_DXYN,                     //0xDXXX
                                                    Chip8::_interpretEXXXInstruction,     //0xEXXX
                                                    Chip8::_interpretFXXXInstruction      //0xFXXX 
    };

void(*Chip8::_8XXN_Instruction[16])(void){          Chip8::_cpu_8XY0,                    //0x0XXX
                                                    Chip8::_cpu_8XY1,                    //0x1XXX
                                                    Chip8::_cpu_8XY2,                    //0x2XXX
                                                    Chip8::_cpu_8XY3,                    //0x3XXX
                                                    Chip8::_cpu_8XY4,                    //0x4XXX        
                                                    Chip8::_cpu_8XY5,                    //0x5XXX
                                                    Chip8::_cpu_8XY6,                    //0x6XXX
                                                    Chip8::_cpu_8XY7,                    //0x7XXX
                                                    Chip8::_cpu_NOP,                     //0x8XXX
                                                    Chip8::_cpu_NOP,                     //0x9XXX
                                                    Chip8::_cpu_NOP,                     //0xAXXX
                                                    Chip8::_cpu_NOP,                     //0xBXXX
                                                    Chip8::_cpu_NOP,                     //0xCXXX
                                                    Chip8::_cpu_NOP,                     //0xDXXX
                                                    Chip8::_cpu_8XYE,                    //0xEXXX
                                                    Chip8::_cpu_NOP                      //0xFXXX 
    };
    



void Chip8::Init(void)
{

}

void Chip8::loadRom(const char* file)
{

}

bool Chip8::emulate(void)
{

}

void Chip8::parseInstruction(unsigned short instruction)
{
    // concatenate 2 memory locations to one 16 bit instruction by shifting the first byte 8 bits
    // 0xA1 0xB2 -> 0xA1B2
    _opcode = _mem[_pc] << 8 | _mem[_pc+1];
   (*Chip8::_basicInstruction[(_opcode & 0xF000) >> 12])();   
}

void Chip8::_interpret8XXNInstruction(void)
{
    (*Chip8::_8XXN_Instruction[(_opcode & 0x000F)])(); 
}

void Chip8::_interpret00XXInstruction(void)
{
    if(_opcode == 0x00E0){
         _cpu_00E0();
    }
    else{
        _cpu_0NNN();
    }
}

void Chip8::_interpretEXXXInstruction(void)
{

}


void Chip8::_interpretFXXXInstruction(void)
{

}


void Chip8::checkKeys(void)
{

}

 // CPU function opcodes
// For reference see: https://en.wikipedia.org/wiki/CHIP-8#Opcode_table


// 0x0XXX
void Chip8::_cpu_NOP(void)    // 0NNN 	Call 		Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
{
    _pc += 2;
}
void Chip8::_cpu_0NNN(void)    // 0NNN 	Call 		Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
{
    
}
void Chip8::_cpu_00E0(void)    // 00E0 	Display 	disp_clear() 	Clears the screen.
{
    
}    
// 0x1XXX
void Chip8::_cpu_1NNN(void)     // 1NNN 	Flow 	goto NNN; 	Jumps to address NNN.
{
    
}     
// 0x2XXX
void Chip8::_cpu_2XNN(void)     // 2NNN 	Flow 	*(0xNNN)() 	Calls subroutine at NNN. 
{
    
}    
// 0x3XXX
void Chip8::_cpu_3XNN(void)     // 3XNN 	Cond 	if(Vx==NN) 	Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block) 
{
    if (_V[_opcode & 0x0F00] == _opcode & 0x00FF)
    {
        _pc += 4;
    }
    else 
    {
        _pc += 2;
    } 
}                     
// 0x4XXX
void Chip8::_cpu_4XNN(void)     // 4XNN 	Cond 	if(Vx!=NN) 	Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)  
{
   if (_V[_opcode & 0x0F00] != _opcode & 0x00FF)
    {
        _pc += 4;
    }
    else 
    {
        _pc += 2;
    } 
}   
// 0x5XXX
void Chip8::_cpu_5YX0(void)     // 5XY0 	Cond 	if(Vx==Vy) 	Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block) 
{
    if (_V[_opcode & 0x0F00] == _V[_opcode & 0x00F0])
    {
        _pc += 4;
    }
    else 
    {
        _pc += 2;
    }
}   
// 0x6XXX
void Chip8::_cpu_6XNN(void)     // 6XNN 	Const 	Vx = NN 	Sets VX to NN.   
{
    _V[_opcode & 0x0F00] = _opcode & 0x00FF;
    _pc += 2;
}   
// 0x7XXX
void Chip8::_cpu_7XNN(void)     // 7XNN 	Const 	Vx += NN 	Adds NN to VX. (Carry flag is not changed)   
{
    _V[_opcode & 0x0F00] += _opcode & 0x00FF;
    _pc += 2;
}   
// 0x8XXX
void Chip8::_cpu_8XY0(void)     // 8XY0 	Assign 	Vx=Vy 	Sets VX to the value of VY.
{
    _V[_opcode & 0x0F00] = _V[_opcode & 0x00F0];
    _pc += 2;
}     
void Chip8::_cpu_8XY1(void)     // 8XY1 	BitOp 	Vx=Vx|Vy 	Sets VX to VX or VY. (Bitwise OR operation)
{
    _V[_opcode & 0x0F00] = _V[(_opcode & 0x0F00)] | _V[(_opcode & 0x00F0)];
    _pc += 2;
}

void Chip8::_cpu_8XY2(void)     // 8XY2 	BitOp 	Vx=Vx&Vy 	Sets VX to VX and VY. (Bitwise AND operation)
{
   _V[_opcode & 0x0F00] = _V[(_opcode & 0x0F00)] & _V[(_opcode & 0x00F0)];
   _pc += 2; 
}
void Chip8::_cpu_8XY3(void)     // 8XY3 	BitOp 	Vx=Vx^Vy 	Sets VX to VX xor VY.
{
    _V[_opcode & 0x0F00] = _V[(_opcode & 0x0F00)] ^ _V[(_opcode & 0x00F0)];
    _pc += 2;
}
void Chip8::_cpu_8XY4(void)     // 8XY4 	Math 	Vx += Vy 	Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
{
    // CARRY!
    _V[_opcode & 0x0F00] += _V[(_opcode & 0x00F0)];
    _pc += 2;
}
void Chip8::_cpu_8XY5(void)    // 8XY5 	Math 	Vx -= Vy 	VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
{
    // BORROW!
     _V[_opcode & 0x0F00] -= _V[(_opcode & 0x00F0)];
     _pc += 2;
}

void Chip8::_cpu_8XY6(void)    // 8XY6 	BitOp 	Vx>>=1 	Stores the least significant bit of VX in VF and then shifts VX to the right by 1.[2]
{
    _V[15] = _V[_opcode & 0x0F00] & 0x0001;
    _V[_opcode & 0x0F00] = _V[_opcode & 0x0F00] >> 1;
    _pc += 2;
}
void Chip8::_cpu_8XY7(void)     // 8XY7 	Math 	Vx=Vy-Vx 	Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
{
    _V[_opcode & 0x0F00] = _V[_opcode & 0x00F0] - _V[_opcode & 0x0F00];
    _pc += 2;
}
void Chip8::_cpu_8XYE(void)    // 8XYE 	BitOp 	Vx<<=1 	Stores the most significant bit of VX in VF and then shifts VX to the left by 1.[3]  
{
    _V[15] = _V[_opcode & 0x0F00] & 0x8000;
    _V[_opcode & 0x0F00] = _V[_opcode & 0x0F00] << 15;
    _pc += 2;
}  
// 0x9XXX
void Chip8::_cpu_9XY0(void)     // 9XY0 	Cond 	if(Vx!=Vy) 	Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)    
{
    if (_V[_opcode & 0x0F00] != _V[_opcode & 0x00F0])
    {
        _pc += 4;
    }
    else 
    {
        _pc += 2;
    }
}  
// 0xAXXX
void Chip8::_cpu_ANNN(void)     // ANNN 	MEM 	I = NNN 	Sets I to the address NNN.      
{
    _I = _opcode & 0x0FFF;
    _pc += 2;
}
// 0xBXXX
void Chip8::_cpu_BNNN(void)     // BNNN 	Flow 	PC=V0+NNN 	Jumps to the address NNN plus V0.  
{
    _pc = _V[0] + _opcode & 0x0FFF;
}
// 0xCXXX
void Chip8::_cpu_CXNN(void)     // CXNN 	Rand 	Vx=rand()&NN 	Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
{
    _V[_opcode & 0x0F00] = (rand() % 0xFF) & (_opcode & 0x00FF);
    _pc += 2;
}
// 0xDXXX
void Chip8::_cpu_DXYN(void)     // DXYN 	Disp 	draw(Vx,Vy,N) 	Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
{
    
}
// 0xEXXX
void Chip8::_cpu_EX9E(void)     // EX9E 	KeyOp 	if(key()==Vx) 	Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
{
     // ???
    if(_key[_opcode & 0x0F00] == true)
    {
           
    }
    _pc += 2;
}
void Chip8::_cpu_EXA1(void)     // EXA1 	KeyOp 	if(key()!=Vx) 	Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
{
    
}
// 0xFXXX
void Chip8::_cpu_FX07(void)     // FX07 	Timer 	Vx = get_delay() 	Sets VX to the value of the delay timer.
{
    
}
void Chip8::_cpu_FX0A(void)     // FX0A 	KeyOp 	Vx = get_key() 	A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
{
    
}
void Chip8::_cpu_FX15(void)     // FX15 	Timer 	delay_timer(Vx) 	Sets the delay timer to VX.
{
    
}
void Chip8::_cpu_FX18(void)     // FX18 	Sound 	sound_timer(Vx) 	Sets the sound timer to VX.
{
    
}
void Chip8::_cpu_FX1E(void)     // FX1E 	MEM 	I +=Vx 	Adds VX to I.[4]
{
    
}
void Chip8::_cpu_FX29(void)     // FX29 	MEM 	I=sprite_addr[Vx] 	Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
{
    
}
void Chip8::_cpu_FX33(void)     // FX33 	BCD 	set_BCD(Vx);
{
    
}
void Chip8::_cpu_FX55(void)     // FX55 	MEM 	reg_dump(Vx,&I) 	Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
{
    
}
void Chip8::_cpu_FX65(void)     // FX65 	MEM 	reg_load(Vx,&I) 	Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
{
    
} 
