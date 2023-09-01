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

#include <assert.h>
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
    Word SP;        // Stack Pointer - 8 bits    
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

Byte CPU_FetchByte(CPU *cpu, Mem *mem, unsigned int *Cycles)
{
    assert(cpu->PC < MAX_MEM);
    Byte Data = mem->Data[cpu->PC];
    cpu->PC++;
    (*Cycles)--;
    return Data;
}

// opcodes
enum {
    INS_LDA_IM = 0xA9
};

void CPU_Execute(CPU *cpu, Mem *mem, unsigned int Cycles)
{
    while (Cycles > 0)
    {
        Byte Ins = CPU_FetchByte(cpu, mem, &Cycles);
        switch (Ins) {
            case INS_LDA_IM:
            {
                Byte Value = CPU_FetchByte(cpu, mem, &Cycles);
                cpu->A = Value;
                cpu->Z = (cpu->A == 0);             // Set if A == 0
                cpu->N = (cpu->A & 0b10000000) > 0; // Set if bit 7 of A is set
                break;
            }
            default:
            {
                printf("Instruction not handled: %x\n", Ins);
                break;
            }
        }
    }
}

int main() {
    Mem mem;
    CPU cpu;
    CPU_Reset(&cpu, &mem);
    CPU_Execute(&cpu, &mem, 2);
    return 0;
}