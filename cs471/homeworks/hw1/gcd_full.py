#! /usr/bin/env python
import sys


def gcdI(i, j):
    while i != j:
        if i > j:
            i = i - j
        else:
            j = j - i
    return i


def gcdF(i, j):
    if not i % j: return j 
    return gcdF(j, i % j)


if len(sys.argv) != 3:
    print(sys.argv[0] + " usage: [I] [J]")
    exit()

gcd = gcdI(int(sys.argv[1]), int(sys.argv[2]))
print(gcd)
