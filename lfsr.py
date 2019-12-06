# Compute code to shift LFSR by arbitrary amounts

def simplify(list):
    list.sort()
    last = -1
    copy = list.copy()
    for i in copy:
        if(i == last):
            list.remove(i);
            list.remove(i)
            last = -1
        else:
            last = i

def lfsr_forward(lfsr,degree,poly):
    # shift down
    lsb = lfsr.pop(0)
    lfsr.append([])

    for i in range(degree):
        if ((poly>>i)&1):
            lfsr[i] += lsb
            simplify(lfsr[i])
    return lfsr

def main():
    poly = 0x80004
    degree = 20    
    #count = 1
    #count = (0x100000-2)
    count = 1024
    #count = (0x100000-1)-1024

    lfsr = [[i] for i in range(degree)]
    for i in range(count):
        lfsr_forward(lfsr,degree,poly)
    print("lfsr:",list(reversed(lfsr)))

    masks = [0 for i in range(degree)]
    for i in reversed(lfsr):
        for b in range(degree):
            masks[b] *= 2
        for b in i:
            masks[b] += 1
    for i in range(degree):
        print("{:2d}:{:020b}({:05x})".format(i,masks[i],masks[i]))

    print("prev = lfsr;")
    for i in range(degree):
        print("if (prev & 0x{:05x}) lfsr ^= 0x{:05x};".format(1<<i,masks[i]))

if __name__ == "__main__":
    main()
