
// Preprocessor defines for assembler mmenomics
#ifndef JTIS_H
#define JTIS_H

// Registers
#define MODE 0x0
#define CMPF 0x1
#define AH 0x2
#define AL 0x3
#define BH 0x4
#define BL 0x5
#define CH 0x6
#define CL 0x7
#define DH 0x8
#define DL 0x9
#define EH 0xA
#define EL 0xB
#define FH 0xC
#define FL 0xD
#define GH 0xE
#define GL 0xF

// Instructions
#define NOP   0x0
#define STOP  0x1
#define JUMP  0x2
#define SET   0x3
#define LOAD  0x4
#define STORE 0x5
#define MOVE  0x6
#define SHR   0x7
#define SHL   0x8
#define AND   0x9
#define OR    0xA
#define NOT   0xB
#define XOR   0xC
#define CMP   0xD
#define ADD   0xE
#define SUB   0xF
#define MUL   0x10
#define DIV   0x11


#endif