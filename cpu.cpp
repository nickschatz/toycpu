#include <iostream>
#include <fstream>

#define RAM_SIZE 512
#define INSTR_REG 2

// Instruction names
#define NOP   0x0
#define STOP  0x1
#define JUMP  0x2
#define LOAD  0x3
#define STORE 0x4
#define MOVE  0x5
#define DADD  0x6
#define DSUB  0x7
#define DMUL  0x8
#define DDIV  0x9
#define FADD  0xA
#define FSUB  0xB
#define FMUL  0xC
#define FDIV  0xD
#define EQ    0xE
#define GT    0xF
#define LT    0x10
#define GTE   0x11
#define LTE   0x12
#define OR    0x13
#define AND   0x14
#define XOR   0x15
#define NOT   0x16


void dumpram(uint8_t* ram) {
    std::ofstream dump;
    dump.open("cpu.bin");
    for (int i=0; i < RAM_SIZE; i++)
        dump << ram[i];
    dump.close();
}


int main() {
    uint8_t* ram = new uint8_t[RAM_SIZE]; 
    bool halted = false;
    uint8_t* registers = new uint8_t[9];
    registers[1] = 1;
    registers[2] = 0x20;

    // Read contents of ram from stdin
    int iread = 0;
    while (std::cin >> ram[iread++]) {}
    dumpram(ram);
    return 0;

    while (!halted) {
        int8_t wordLocation = registers[INSTR_REG];
        int8_t func = ram[wordLocation];
        int8_t op1 = ram[wordLocation+1];
        int8_t op2 = ram[wordLocation+2];
        int8_t op3 = ram[wordLocation+3];
        registers[INSTR_REG] += 4;

        switch(func) {
            case NOP: break;
            case STOP: halted = true; break;
            case LOAD: registers[op1] = ram[op2]; break;
            case STORE: ram[op2] = registers[op1]; break;
            case MOVE: registers[op2] = registers[op1]; break;
            case JUMP:
                if (registers[op2]) registers[INSTR_REG] = op1;
                break;

            case DADD: registers[op3] = registers[op1] + registers[op2]; break;
            case DSUB: registers[op3] = registers[op1] - registers[op2]; break;
            case DMUL: registers[op3] = registers[op1] * registers[op2]; break;
            case DDIV: registers[op3] = registers[op1] / registers[op2]; break;
            // todo implement floating point arithmetic BC DE FG
            case FADD: 
            {
                uint16_t a = registers[op1] << 8 + registers[op1+1]; 
                uint16_t b = registers[op2] << 8 + registers[op2+1]; 
                
                break;
            }
            case FSUB: registers[op3] = registers[op1] - registers[op2]; break;
            case FMUL: 
            {
                uint16_t a = registers[op1] << 8 + registers[op1+1]; 
                uint16_t b = registers[op2] << 8 + registers[op2+1];
                uint16_t aM = a & 0xFFFFF;
                uint16_t bM = b & 0xFFFFF;
                uint16_t aS = (a>>15) & 0b1;
                uint16_t bS = (b>>15) & 0b1;
                uint16_t aE = (a>>10) & 0b11111;
                uint16_t bE = (b>>10) & 0b11111;
                uint16_t sign = aS ^ bS;
                uint16_t exp = aE + bE - 15;
                uint32_t mantissa = aM * bM;
                if (mantissa & 0xFFFF0000) {
                    mantissa <<= 1;
                    exp -= 1;
                }
                mantissa &= 0xFFFFF;
                uint16_t result = (sign << 15) & (exp << 10) & mantissa;
                registers[op3] = result >> 8;
                registers[op3+1] = result & 0xFFFF;
                break;
            }
            case FDIV: registers[op3] = registers[op1] / registers[op2]; break;

            case EQ: registers[op3] = (registers[op1] == registers[op2] ? 1 : 0); break;
            case GT: registers[op3] = (registers[op1] > registers[op2] ? 1 : 0); break;
            case LT: registers[op3] = (registers[op1] < registers[op2] ? 1 : 0); break;
            case GTE: registers[op3] = (registers[op1] >= registers[op2] ? 1 : 0); break;
            case LTE: registers[op3] = (registers[op1] <= registers[op2] ? 1 : 0); break;

            case OR: registers[op3] = (registers[op1] | registers[op2]); break;
            case AND: registers[op3] = (registers[op1] & registers[op2]); break;
            case XOR: registers[op3] = (registers[op1] ^ registers[op2]); break;
            case NOT: registers[op2] = ~registers[op1]; break;
            default:
            std::cout << "Op " << std::hex << (int)func << " not valid at " << (int)wordLocation << ". Halting execution & dumping RAM to cpu.bin" << std::endl;
            dumpram(ram);
            halted = true;
        }
        std::cout << std::hex << (int)registers[0] << " " << (int)registers[1] << " "
                  << (int)registers[2] << " " << (int)registers[3] << " "
                  << (int)registers[4] << " " << (int)registers[5] << " "
                  << (int)registers[6] << " " << (int)registers[7] << " "
                  << (int)registers[8] << std::endl;
    }
    
}