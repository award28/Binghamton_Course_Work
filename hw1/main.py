#!/usr/local/bin/python3
from decisionTree import DecisionTree
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
    print(".\main.py <training-set> <validation-set> <test-set> <to-print> <prune>\
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
if sys.argv[5] == 'yes':
    print("==================Pre Pruning===================")
print("Info Gain:\t\tPredicted {:0.2f}% Correct".format(ig_pre))
print("Variance Impurity:\tPredicted {:0.2f}% Correct".format(vi_pre))
if sys.argv[5] == 'yes':
    ig.prune(ig_root)
    vi.prune(vi_root)
    ig_post = ig.accuracy(ig_root, test)
    vi_post = vi.accuracy(vi_root, test)
    print("==================Post Pruning==================")
    print("Info Gain:\t\tPredicted {:0.2f}% Correct".format(ig_post))
    print("Variance Impurity:\tPredicted {:0.2f}% Correct".format(vi_post))
if sys.argv[4] == 'yes':
    print('==============Info Gain Tree==============')
    ig.print_tree(ig_root)
    print('==========Variance Impurity Tree==========')
    vi.print_tree(vi_root)
