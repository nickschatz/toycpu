The JT instruction set
===
Revision 0.1

For 16 or 32 bit ops, reference the highest-endian register (BH, DH, FH)

Registers
---
Address | Assembler Mnemonic | Name | Description
--- | --- | --- | ---
0x0 | MODE | Addressing mode | X123 where 0 = register and 1 = literal for op1,2,3
0x1 | CMP | Compare flag | 0000 = EQ, XXX1 = LT, XX1X = GT, X1XX = LTE, 1XXX = GTE in order of increasing priority
0x2 | AH | Instruction pointer high |
0x3 | AL | Instruction pointer low |
0x4 | BH | B register high | Starts 32 bit word
0x5 | BL | B register low | 
0x6 | CH | C register high |
0x7 | CL | C register low | 
0x8 | DH | D register high | Starts 32 bit word
0x9 | DL | D register low | 
0xA | EH | E register high |
0xB | EL | E register low | 
0xC | FH | F register high | Starts 32 bit word
0xD | FL | F register low | 
0xE | GH | G register high |
0xF | GL | G register low | 


Instructions
---
Instruction | Assembler Mnemonic | Description | OP1 | OP2 | OP3
--- | --- | --- | --- | --- | ---
0x0 | NOP | No Operation | X | X | X |
0x1 | STOP | Stop execution | X | X | X |
0x2 | JUMP | Jump if | Address to jump to (16 bit) | Condition (0x00 to continue, any other to jump) | X |
0x3 | LOAD | Load into a register from memory | Memory address (16 bit) | Number of bytes to load (8 bit) | X |
0x4 | STORE | Store into memory from a register | Memory address (16 bit) | Number of registers to store (8 bit) | X |