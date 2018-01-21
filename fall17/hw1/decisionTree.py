from math import log
import copy

"""
Class:          Node
Description:    Node object for creating new nodes in the decision tree
"""
class Node(object):
    def __init__(self):
        self.values = {} 
        self.label = None


    def set_label(self, label):
        self.label = label


    def get_label(self):
        return self.label


    def __set_parent(self, p):
        self.parent = p


    def get_parent(self):
        return self.parent


    def create_child(self, value):
        self.values[value] = Node()
        self.values[value].__set_parent(self)


    def inject_child(self, value, node):
        self.values[value] = node
        self.values[value].__set_parent(self)

    def get_child(self, value):
        return self.values[value]


    def get_children(self):
        return self.values.items()


"""
Class:          DecisionTree
Description:    Creates a decision tree with methods for predicting
                accuracy and printing the tree
Constructor Parameters:
    training_data   A dictionary with attribute-value pairings
    target_attr     The attribute we want the decision tree to decide on
    attrs           A dictionary of attribte to a list of values for said 
                    attribute
    validate        A dictionary with attribute-value pairings

"""
class DecisionTree:
    def __init__(self, training_data, target_attr, attrs, validate):
        self.data = training_data
        self.t_attr = target_attr
        self.attrs = attrs
        self.validate = validate
        self.attr_values = {}
        self.__set_values()


    def __set_values(self):
        for attr in self.attrs:
            self.attr_values[attr] = []
        self.attr_values[self.t_attr] = []
        for item in self.data:
            for attr in self.attrs:
                if item[attr] not in self.attr_values[attr]:
                    self.attr_values[attr].append(item[attr])
            if item[self.t_attr] not in self.attr_values[self.t_attr]:
                self.attr_values[self.t_attr].append(item[self.t_attr])


    def tree_ctor(self, is_info_gain=True):
        self.is_info_gain = is_info_gain
        root = self.__tree_ctor(self.data, self.t_attr, self.attrs)
        return root


    def __tree_ctor(self, data, t_attr, attrs):
        root = Node()
        num_pos = num_neg = 0
        split_ = self.split(data)
        most_common_label_ = self.most_common_label(split_)
        all_same = True
        for label, amount in split_.items():
            if label != most_common_label_ and amount > 0:
                all_same = False
                break
        if all_same or not len(attrs):
            root.set_label(most_common_label_)
            return root
        if self.is_info_gain:
            best_attr = self.best_ig_attr(data, attrs)
        else:
            best_attr = self.best_vi_attr(data, attrs)
        root.set_label(best_attr)
        for v in self.attr_values[best_attr]:
            root.create_child(v)
            subset = []
            for d in data:
                if d[best_attr] == v:
                    subset.append(d)
            if not len(subset):
                node = Node()
                node.set_label(self.most_common_label(self.split(data)))
                root.inject_child(v, node)
            else:
                attrs.remove(best_attr)
                root.inject_child(v, self.__tree_ctor(subset, t_attr, attrs))
                attrs.append(best_attr)
        return root 


    def prune(self, root):
        nodes = []
        for val, node in root.get_children():
            label = node.get_parent().get_label()
            nodes.append(({label : val}, (node, val)))
        while True:
            new_nodes = []
            if not len(nodes):
                break
            for item in nodes:
                old_accuracy = self.accuracy(root, self.validate)
                av_pairings, (node, val) = item
                satisfies_attrs_data = self.get_validation_data(av_pairings)
                label = self.most_common_label(self.split(satisfies_attrs_data))
                new_node = Node()
                new_node.set_label(label)
                parent = node.get_parent()
                parent.inject_child(val, new_node)
                # if tree performs worse with node change, remove node change
                if self.accuracy(root, self.validate) < old_accuracy:
                    parent.inject_child(val, node)
                    for val, child in node.get_children():
                        av_pairings[node.get_label()] = val
                        new_nodes.append((av_pairings, (child, val)))
                nodes = new_nodes
        return root


    def get_validation_data(self, attrs):
        ret_data = copy.deepcopy(self.validate)
        for attr, val in attrs.items():
            for item in ret_data:
                if item[attr] != val:
                    ret_data.remove(item)
        return ret_data


    def most_common_label(self, split_):
        label_, amount_ = None, 0
        for label, amount in split_.items():
            if amount >= amount_:
                label_ = label
                amount_ = amount
        return label_


    def best_vi_attr(self, set_, attrs):
        best, gain = None, 0
        for attr in attrs:
            gain_ = self.vi_gain(set_, attr)
            if gain_ >= gain:
                best = attr
                gain = gain_
        return best
       

    def vi_gain(self, set_, attr):
        gain_ = 0
        for val in self.attr_values[attr]:
            subset = []
            for item in set_:
                if item[attr] == val:
                    subset.append(item)
            if len(subset):
                gain_ += (len(subset)/len(set_)) * self.variance_impurity(subset)
        return self.variance_impurity(set_) - gain_


    def variance_impurity(self, set_):
        split_ = self.split(set_)
        total = 0
        vi = 1 
        for value in split_.values():
            total += value
        for value in split_.values():
            vi *= value/total
        return vi


    def best_ig_attr(self, set_, attrs):
        best, gain = None, 0
        for attr in attrs:
            gain_ = self.e_gain(set_, attr)
            if gain_ >= gain:
                best = attr
                gain = gain_
        return best
       

    def e_gain(self, set_, attr):
        gain_ = 0
        for val in self.attr_values[attr]:
            subset = []
            for item in set_:
                if item[attr] == val:
                    subset.append(item)
            if len(subset):
                gain_ += (len(subset)/len(set_)) * self.entropy(self.split(subset))
        return self.entropy(self.split(set_)) - gain_ 


    def entropy(self, set_):
        total = entropy_ = 0
        for value in set_.values():
            total += value 
        for value in set_.values():
            p = (value/total)
            if p:
                entropy_ -= p*log(p, 2)
        return entropy_ 
 

    def split(self, set_):
        split_ = {}
        for attr in self.attr_values[self.t_attr]:
            split_[attr] = 0
        for item in set_:
            for attr in self.attr_values[self.t_attr]:
                if item[self.t_attr] == attr:
                    split_[attr] += 1
        return split_ 


    def print_tree(self, root, level=0):
        if not len(root.get_children()):
            print(root.get_label())
            return
        print()
        for value, node in root.get_children():
            for i in range(level):
                print("| ", end='')
            print(str(root.get_label()) + " = " + str(value) + " : ", end='')
            self.print_tree(node, level + 1)


    def accuracy(self, root, data):
        correct = total = 0
        for item in data:
            if self.predict(root, item) == item[self.t_attr]:
                correct += 1
            total += 1
        return 100 * (correct/total)


    def predict(self, node, item):
        while(type(node) == type(Node()) and len(node.get_children())):
            node = node.get_child(item[node.get_label()])
        return node.get_label()
