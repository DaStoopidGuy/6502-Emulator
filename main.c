/*
Making an emulator?
6502 Processor

Links:
----------------------------
https://youtu.be/qJgsuQoy9bc
https://github.com/davepoo/6502Emulator
https://sta.c64.org/cbm64mem.html

-> 6502
http://6502.org/users/obelisk/6502/registers.html
----------------------------
*/

#include <stdio.h>

#define Byte unsigned char
#define Word unsigned short

#define MAX_MEM 1024*64
typedef struct
{
    // static constexpr unsigned int MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];
} Mem;

void Mem_Initialize(Mem *mem)
{
    for (unsigned int i = 0; i < MAX_MEM; i++)
    {
        mem->Data[i] = 0;
    }
}

typedef struct
{
    Word PC;        // Program Counter - 16 bits
    Byte SP;        // Stack Pointer - 8 bits    
    Byte A, X, Y;   // the only 3 Registers :P

    // Processor Status Flags
    Byte C :1;      // Carry Flag
    Byte Z :1;      // Zero Flag
    Byte I :1;      // Interrupt Disable
    Byte D :1;      // Decimal Mode
    Byte B :1;      // Break Command
    Byte O :1;      // Overflow Flag
    Byte N :1;      // Negative Flag
} CPU;

void CPU_Reset(CPU *cpu, Mem *mem)
{
    cpu->PC = 0xFFFC;   // execution address of cold reset
    cpu->SP = 0x0100;   // initialize stack ptr
   
    cpu->C = 0;
    cpu->Z = 0;
    cpu->I = 0;
    cpu->D = 0;
    cpu->B = 0;
    cpu->O = 0;
    cpu->N = 0;
   
    cpu->A = cpu->X = cpu->Y = 0;

    Mem_Initialize(mem);
}

int main() {
    Mem mem;
    CPU cpu;
    CPU_Reset(&cpu, &mem);

    return 0;
}