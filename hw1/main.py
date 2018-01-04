from decisionTree import DecisionTree
import sys

def get_data_set(name, start=False):
    with open(sys.argv[1] + "/" + name + "_set.csv") as f:
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

training, t_attr, attrs = get_data_set("training", True)
validation = get_data_set("validation")
test = get_data_set("test")

dt = DecisionTree(training, t_attr, attrs, validation)
root = dt.tree_ctor()

print("Pre-pruning: Predicted " + str(dt.accuracy(root, test)) + "% Correct")
'''
dt.prune(root)
print("Post-pruning: Predicted " + str(dt.accuracy(root, test)) + "% Correct")
'''

dt.print_tree(root)
