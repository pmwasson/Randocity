#----------------------------------------
# Imports
#----------------------------------------

import random

width = 16
height = 10
tiles = [
            [   " | ",
                "-+-",
                " | "
            ],
            [   " | ",
                "-+-",
                " | "
            ],
            [   " | ",
                "/|\\",
                " | "
            ],
            [   " \\ ",
                "---",
                " / "
            ],
            [   " | ",
                "\\|/",
                " | "
            ],
            [   " / ",
                "---",
                " \\ "
            ],
            [   " \\ ",
                "\\ \\",
                " \\ "
            ],
            [   " / ",
                "/ /",
                " / "
            ],
]

lfsr = 1

def lfsr_forward(lfsr,count):
    result = 0;
    for i in range(count):
        poly = 0xb400
        lsb = lfsr & 0b00001
        lfsr = ((lfsr>>1) ^ ((-lsb) & poly))
    return lfsr

def lfsr_backward(lfsr,count):
    for i in range(count):
        poly = (0xb400 << 1) | 1
        msb = (lfsr & 0x8000) == 0x8000
        lfsr = 0xffff & ((lfsr<<1) ^ ((-msb) & poly))
    return lfsr

def getTile(x,y):
    return (x^y) % len(tiles)

def main():
    lfsr_x = random.randrange(0x10000)
    rowTile = [0] * width

    print("seed={:04x}".format(lfsr_x))

    for row in range(height):
        for col in range(width):
            lfsr_x = lfsr_forward(lfsr_x,3)
            rowTile[col] = lfsr_x % len(tiles)
        for line in range(3):
            result = ""
            for col in range(width):
                result += tiles[rowTile[col]][line]
            print(result)

if __name__ == "__main__":
    main()
