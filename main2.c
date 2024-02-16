#include <stdio.h>
#include <assert.h>


typedef unsigned char   Byte;
typedef unsigned short  Word;


// CPU
static Word PC;      // Program Counter - 16 bits
static Byte SP;      // Stack Pointer - 8 bits
static Byte A, X, Y; // the only 3 Registers :P

// Processor Status Flags
static Byte C : 1; // Carry Flag
static Byte Z : 1; // Zero Flag
static Byte I : 1; // Interrupt Disable
static Byte D : 1; // Decimal Mode
static Byte B : 1; // Break Command
static Byte O : 1; // Overflow Flag
static Byte N : 1; // Negative Flag
