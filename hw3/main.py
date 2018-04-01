#!/usr/local/bin/python3
# Copyright 2018 Austin Ward
from Perceptron import *
import sys


if len(sys.argv) != 3:
    print("./main <train> <test>")
    sys.exit()
train = sys.argv[1]
test = sys.argv[2]
print("P w/ stopwords: {:0.2f}".format(execute_p(train, test, False, False)))
print("P w/out stopwords: {:0.2f}".format(execute_p(train, test, True, False)))
