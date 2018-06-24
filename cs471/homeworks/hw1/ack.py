from sys import argv


def ack(m, n):
    if not m: return n + 1
    if not n and m > 0: return ack(m - 1, 1)
    return ack(m - 1, ack(m, n - 1))

if len(argv) != 3:
    print(argv[0] + " usage: [m] [n]")
    exit()

print(ack(int(argv[1]), int(argv[2])))
