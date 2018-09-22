import sys

class CPU:
    def asm_to_machine(self, asm, ram_size):
        # Map for register literals to machine code ids
        regmap = {"0": 0, "1": 1, "A": 2, "B": 3, "C": 4, "D": 5, "E": 6, "F": 7, "G": 8}
        instrmap = {"nop": 0x0, 
                    "stop": 0x1, 
                    "jump": 0x2, 
                    "load": 0x3, 
                    "store": 0x4,
                    "move": 0x5, 
                    "add": 0x6, 
                    "sub": 0x7, 
                    "mul": 0x8, 
                    "div": 0x9, 
                    "fadd": 0xA, 
                    "fsub": 0xB,
                    "fmul": 0xC, 
                    "fdiv": 0xD, 
                    "eq": 0xE, 
                    "gt": 0xF, 
                    "lt": 0x10,
                    "gte": 0x11,
                    "lte": 0x12,
                    "or": 0x13,
                    "and": 0x14,
                    "xor": 0x15,
                    "not": 0x16,}
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
            machine_line += [instrmap[data[0]]]
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
        machine[0] = 0xA
        machine[1] = 0x2
        machine[2] = 0x2
        sys.stdout.buffer.write(bytes(machine))
