#!/usr/bin/python

import sys

class CPU:
    def asm_to_machine(self, asm, ram_size):
        # Map for register literals to machine code ids
        reglist = ["MODE", "CMPF", "AH", "AL", "BH", "BL", "CH", "CL", "DH", "DL", "EH", "EL", "FH", "FL", "GH", "GL"]
        instrlist = ["NOP", "STOP", "JUMP", "SET", "LOAD", "STORE", "MOVE", 
                     "SHR", "SHL", "AND", "OR", "NOT", "XOR", "CMP", "ADD",
                     "SUB", "MUL", "DIV"]
        regmap = {x: i for i,x in enumerate(reglist)}
        instrmap = {x: i for i,x in enumerate(instrlist)}
        labelmap = {}
        machine = []

        # Find memory locations of labels
        memloc = ram_size
        for line in asm:
            if len(line) == 0 or line[0] == ";":
                continue
            if line.endswith(":"):
                labelmap[line[:-1]] = memloc
            else:
                memloc += 4
        for line in asm:
            # Ignore blank lines, comments, and labels
            if len(line) == 0 or line[0] == ";" or line.endswith(":"):
                continue
            machine_line = []
            data = line.split(" ")
            # Get the instruction
            machine_line += [instrmap[data[0].upper()]]
            for dat in data[1:]:
                # Parse each op part
                if dat.startswith(":"):
                    # Label
                    machine_line += [labelmap[dat[1:]]]
                elif dat in regmap:
                    # Register
                    machine_line += [regmap[dat]]
                else:
                    # Literal
                    machine_line += [int(dat, base=16)]
            # Pad into 4 byte word
            machine_line += [0] * (4-len(machine_line))
            machine += machine_line
        return machine

if __name__ == '__main__':
    cpu = CPU()
    fname = sys.argv[1]
    with open(fname, "r") as f:
        asm = f.readlines()
        asm = list(map(lambda x: x.strip(), asm))
        ram_size = 32
        machine = cpu.asm_to_machine(asm, ram_size)
        machine = [0] * ram_size + machine
        sys.stdout.buffer.write(bytes(machine))
