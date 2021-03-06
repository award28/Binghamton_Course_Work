#!/usr/local/bin/python3
# Copyright 2018 Austin Ward
from LogisticRegression import *
from NaiveBayes import * 
import sys


if len(sys.argv) != 3:
    print("./main <train> <test>")
    sys.exit()
train = sys.argv[1]
test = sys.argv[2]
print("NB w/ stopwords: {:0.2f}".format(execute_nb(train, test, False, False)))
print("NB w/out stopwords: {:0.2f}".format(execute_nb(train, test, True, False)))
for l in [0.2, 0.15, 0.1, 0.05, 0.01]:
    print("LR w/ stopwords:\t{:0.2f}\tw/ lambda {:0.2f}".format(execute_lr(l, train, test, False, False), l))
    print("LR w/out stopwords:\t{:0.2f}\tw/ lambda {:0.2f}".format(execute_lr(l, train, test, True, False), l))
print("="*80)
print("="*25 + " Chi-squared Feature Selection " + "="*24)
print("="*80)
print("NB w/ stopwords: {:0.2f}".format(execute_nb(train, test, False, True)))
print("NB w/out stopwords: {:0.2f}".format(execute_nb(train, test, True, True)))
for l in [0.2, 0.15, 0.1, 0.05, 0.01]:
    print("LR w/ stopwords:\t{:0.2f}\tw/ lambda {:0.2f}".format(execute_lr(l, train, test, False, True), l))
    print("LR w/out stopwords:\t{:0.2f}\tw/ lambda {:0.2f}".format(execute_lr(l, train, test, True, True), l))
