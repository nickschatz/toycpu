The JT instruction set
===
Revision 0.1

For 16 or 32 bit ops, reference the highest-endian register (BH, DH, FH).
Instruction words are 4 bytes long, an instruction followed by 3 ops. If an op is unused it should be 0.

Registers
---
Address | Assembler Mnemonic | Name | Description
--- | --- | --- | ---
0x0 | MODE | Number mode | 0000 = int8, 0001 = int16, 001X = int32, 01XX = float32
0x1 | CMPF | Compare flag | 0000 = EQ, 0001 = LT, 001X = GT, 01XX = LTE, 1XXX = GTE
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
0x3 | SET | Set register | Register address to set | Value to set to | X |
0x4 | LOAD | Load into a register from memory | Memory address (16 bit) | Number of bytes to load (8 bit) | X |
0x5 | STORE | Store into memory from a register | Memory address (16 bit) | Number of registers to store (8 bit) | X |
0x6 | MOVE | Copy the value of one register to another | Source register | Destination register | X |
0x7 | SHR | Shift a register N bits to the right and discard underflow | Register | Argument | X
0x8 | SHL | Shift a register N bits to the left and discard overflow | Register | Argument | X
0x9 | AND | Store the logical AND of Source 1 and Source 2 into the destination register | Source 1 | Source 2 | Destination register
0xA | OR | Store the logical OR of Source 1 and Source 2 into the destination register | Source 1 | Source 2 | Destination register
0xB | NOT | Store the logical NOT of Source 1 in the destination register | Source 1 | Destination register | X
0xC | XOR | Store the logical XOR of Source 1 and Source 2 into the destination register | Source 1 | Source 2 | Destination register
0xD | CMP | Compare Source 1 to Source 2 and store the result (0 or 1 based on CMPF) to the destination register
0xE | ADD | Add Source 1 to Source 2 and store in a register | Source 1 | Source 2 | Destination register
0xF | SUB | Subtract Source 2 from Source 1 and store in a register | Source 1 | Source 2 | Destination register
0x10 | MUL | Multiply Source 2 by Source 1 and store in a register | Source 1 | Source 2 | Destination register
0x11 | DIV | Divide Source 1 by Source 2 and store in a register | Source 1 | Source 2 | Destination register