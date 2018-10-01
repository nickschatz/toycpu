#include <iostream>
#include <fstream>
#include <unistd.h>
#include "jt-is.h"
#include <stdint.h>
#include <variant>
#include <cstring>
#include "numbers.h"


#define RAM_SIZE 512
#define MTS_MASK 0x3FF

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
    // Set instruction pointer
    registers[AH] = 0x0;
    registers[AL] = 0x20;

    // Read contents of ram from stdin
    char c;
    int iread = 0;
    while (std::cin.get(c)) {
        ram[iread++] = c;
    }
    dumpram(ram);

    while (!halted) {
        uint16_t pt = (registers[AH] << 8) | registers[AL];
        uint8_t func = ram[pt];
        uint8_t op1 = ram[pt+1];
        uint8_t op2 = ram[pt+2];
        uint8_t op3 = ram[pt+3];

        // Increment pointer register
        pt += 4;
        registers[AH] = (pt >> 8) & 0xFF;
        registers[AL] = pt & 0xFF;

        switch(func) {
            case NOP: break;
            case STOP: halted = true; break;
            case JUMP: {
                if (registers[op2]) {
                    registers[AH] = op1 >> 8; 
                    registers[AL] = op1 & 0xFF;
                } 
                break;
            }
            case SET: registers[op1] = op2; break;
            case LOAD: registers[op1] = ram[op2]; break;
            case STORE: ram[op2] = registers[op1]; break;
            case MOVE: registers[op2] = registers[op1]; break;
            case SHR: registers[op1] >>= registers[op2]; break;
            case SHL: registers[op1] <<= registers[op2]; break;
            case AND: registers[op3] = registers[op1] & registers[op2]; break;
            case OR: registers[op3] = registers[op1] | registers[op2]; break;
            case NOT: registers[op2] = ~registers[op1]; break;
            case XOR: registers[op3] = registers[op1] ^ registers[op2]; break;
            case CMP: registers[op3] = do_cmp(registers + op1, registers + op2, registers[CMPF], registers[MODE]); break;
            case ADD: do_add(registers + op1, registers + op2, registers + op3, registers[MODE]); break;
            case SUB: do_sub(registers + op1, registers + op2, registers + op3, registers[MODE]); break;
            case MUL: do_mul(registers + op1, registers + op2, registers + op3, registers[MODE]); break;
            case DIV: do_div(registers + op1, registers + op2, registers + op3, registers[MODE]); break;
            default:
            std::cout << "Op " << std::hex << (int)func << " not valid at " << (int)pt << ". Halting execution & dumping RAM to cpu.bin" << std::endl;
            dumpram(ram);
            halted = true;
        }
        std::cout << std::hex;
        for (int i = 0; i <= 0xF; i++) {
            std::cout << (int)registers[i] << " ";
        }
        std::cout << std::endl;
    }
    
}