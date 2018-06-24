#!/usr/local/bin/python3
# Copyright 2018 Austin Ward
from Perceptron import *
import sys


if len(sys.argv) != 3:
    print("./main <train> <test>")
    sys.exit()
train = sys.argv[1]
test = sys.argv[2]
w_stop = "P w/ stopwords "
wo_stop = "P w/out stopwords "
i = 1
for j in range(10, 101, 10):
    print(w_stop+"iter {} learning_rate {}: {:0.2f}".format(
        j, i, execute_p(train, test, False, False, i, j))
        )
    print(wo_stop+"iter {} learning_rate {}: {:0.2f}".format(
        j, i, execute_p(train, test, True, False, i, j))
        )
