#!/usr/bin/python3
# Copyright 2018 Austin Ward

from DecisionTree import DecisionTree
import sys


def get_data_set(name, start=False):
    with open(name) as f:
        data = []
        attrs = f.readline().replace('\n','').split(',')

        for line in f:
            item = {}
            values = line.replace('\n', '').split(',')
            for attr, value in zip(attrs, values):
                item[attr] = value
            data.append(item)

        target_attr = attrs[-1]
        attrs = attrs[:-1]
    return ((data, target_attr, attrs) if start else data)


if len(sys.argv) != 6:
    print("./main.py <training-set> <validation-set> <test-set> <to-print> <prune>\
            \nto-print:{yes,no} prune:{yes, no}")
    sys.exit()
training, t_attr, attrs = get_data_set(sys.argv[1], True)
validation = get_data_set(sys.argv[2])
test = get_data_set(sys.argv[3])
ig = DecisionTree(training, t_attr, attrs, validation)
ig_root = ig.tree_ctor()
vi = DecisionTree(training, t_attr, attrs, validation)
vi_root = vi.tree_ctor(is_info_gain=False)
ig_pre = ig.accuracy(ig_root, test)
vi_pre = vi.accuracy(vi_root, test)

# INFO GAIN

print("H1 NP Training\t\t{:0.2f}".format(ig.accuracy(ig_root, training)))
print("H1 NP Validation\t{:0.2f}".format(ig.accuracy(ig_root, validation)))
print("H1 NP Test\t\t{:0.2f}".format(ig.accuracy(ig_root, test)))
if sys.argv[5] == 'yes':
    ig.prune(ig_root)
    print("H1 P  Training\t\t{:0.2f}".format(ig.accuracy(ig_root, training)))
    print("H1 P  Validation\t{:0.2f}".format(ig.accuracy(ig_root, validation)))
    print("H1 P  Test\t\t{:0.2f}".format(ig.accuracy(ig_root, test)))

# VARIANCE IMPURITY

print("H2 NP Training\t\t{:0.2f}".format(vi.accuracy(vi_root, training)))
print("H2 NP Validation\t{:0.2f}".format(vi.accuracy(vi_root, validation)))
print("H2 NP Test\t\t{:0.2f}".format(vi.accuracy(vi_root, test)))
if sys.argv[5] == 'yes':
    vi.prune(vi_root)
    print("H2 P  Training\t\t{:0.2f}".format(vi.accuracy(vi_root, training)))
    print("H2 P  Validation\t{:0.2f}".format(vi.accuracy(vi_root, validation)))
    print("H2 P  Test\t\t{:0.2f}".format(vi.accuracy(vi_root, test)))
if sys.argv[4] == 'yes':
    print('==============Info Gain Tree==============')
    ig.print_tree(ig_root)
    print('==========Variance Impurity Tree==========')
    vi.print_tree(vi_root)
