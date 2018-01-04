from math import log
import queue


"""
Class:      Node 
Constructor Parameters:
    N/A

Methods:
    set_label(1)        Sets the label for the current node
    get_label(0)        Returns the label for the current node
    create_child(1)  Creates a new node at the attr value on the current 
                        node
    inject_child(2)      Injects a given node at the attr value on the current
                        node
    get_child(1)         Given an attr value it returns a node
"""
class Node(object):
    def __init__(self):
        self.values = {} 
        self.label = None


    def set_label(self, label):
        self.label = label


    def get_label(self):
        return self.label


    def set_parent(self, p):
        self.parent = p


    def get_parent(self):
        return self.parent


    def create_child(self, value):
        self.values[value] = Node()


    def inject_child(self, value, node):
        self.values[value] = node
    

    def get_child(self, value):
        return self.values[value]


    def get_children(self):
        return self.values.items()


"""
Class:      DecisionTree
Constructor Parameters:
    training_data   A dictionary with attribute-value pairings
    target_attr     The attribute we want the decision tree to decide on
    attrs           A dictionary of attribte to a list of values for said 
                    attribute
(Optional Paramters)
    validate        A dictionary with attribute-value pairings

Methods:
    ID3(1)      Returns ID3(3)
    ID3(3)      Recursively creates a decision tree and returns the root node
    best(2)     Determines which attribute should be used as the label on a 
                given node
    e_gain(2)     Calcuates the reduction in entropy given a list and attribute
    Entropy(1)  Calcuates the entropy of a given integer list
"""
class DecisionTree:
    def __init__(self, training_data, target_attr, attrs, validate):
        self.data = training_data
        self.t_attr = target_attr
        self.attrs = attrs
        self.validate = validate
        self.attr_values = {}
        self.set_values()


    def ID3(self, is_info_gain=True):
        self.is_info_gain = is_info_gain
        root = self.__ID3(self.data, self.t_attr, self.attrs)
        return root


    def __ID3(self, data, t_attr, attrs):
        root = Node()
        num_pos = num_neg = 0
        for item in data:
            num_pos += item[t_attr]
            num_neg += not item[t_attr]
        if num_pos > 0 and not num_neg:     # all positive
            root.set_label(1)
            return root
        elif num_neg > 0 and not num_pos:   # all negative
            root.set_label(0)
            return root
        elif not len(attrs):                # attributes is empty
            root.set_label(num_pos >= num_neg)
            return root
        if self.is_info_gain:
            best_attr = self.best_g_attr(data, attrs)
        else:
            best_attr = self.best_vi_attr(data, attrs)
        root.set_label(best_attr)
        for v in self.get_values(best_attr):
            root.create_child(v)
            subset = []
            for d in data:
                if d[best_attr] == v:
                    subset.append(d)
            if not len(subset):
                p = self.split(data)
                node = Node()
                node.set_label(int(p[0] > p[1]))
                root.inject_child(v, node)
            else:
                attrs.remove(best_attr)
                root.inject_child(v, self.__ID3(subset, t_attr, attrs))
                attrs.append(best_attr)
        return root 


    def set_p(self, root):
        children = root.get_children()
        for val, child in children:
            if type(child) is type(Node()):
                child.set_parent(root)
                self.set_p(child)


    def prune(self, root):
        root.set_parent(None)
        self.set_p(root)
        return self.__prune(root, self.validate)


    def __prune(self, root, data):
        nodes = root.get_children()
        results = []
        while True:
            new_nodes = []
            if not len(nodes):
                break
            for val, node in nodes:
                results.append((val, node))
                
                # replace node
                old_accuracy = self.accuracy(root, self.validate)
                mcv_ = self.mcv(node)
                new_node = Node()
                new_node.set_label(mcv_)
                parent = node.get_parent()
                parent.inject_child(val, new_node)
                # if tree performs better with node change, keep node change
                if self.accuracy(root, self.validate) >= old_accuracy:
                    pass
                # else, add child nodes to new_nodes
                else:
                    parent.inject_child(val, node)
                    for v, child in node.get_children():
                        new_nodes.append((v, child))
                nodes = new_nodes
        return root


    def accuracy(self, root, data):
        correct = total = 0
        for item in data:
            p = self.predict(root, item)
            if p == item[self.t_attr]:
                correct += 1
            total += 1
        return 100 * (correct/total)

    def mcv(self, node):
        k, v = None, 0
        for key, val in self.__mcv(node).items():
            if val >= v:
                v = val
                k = key
        return k


    def __mcv(self, node, d={}):
        if type(node.get_label()) is int:
            if node.get_label() in d:
                d[node.get_label()] += 1
            else: 
                d[node.get_label()] = 1
            return d 

        for val, child in node.get_children():
            for key, val in self.__mcv(child).items():
                if key in d:
                    d[key] += val
                else:
                    d[key] = val
        return d
                

    def best_g_attr(self, s, attrs):
        best, gain = None, 0
        for attr in attrs:
            g = self.e_gain(s, attr)
            if g >= gain:
                best = attr
                gain = g 
        return best
       

    def best_vi_attr(self, s, attrs):
        best, gain = None, 0
        for attr in attrs:
            g = self.vi_gain(s, attr)
            if g >= gain:
                best = attr
                gain = g 
        return best
       
    def variance_impurity(self, s):
        split_ = self.split(s)
        total = 0
        vi = 1 
        for key, value in split_.items():
            total += value
        for key, value in split_.items():
            vi *= value/total
        return vi

    def vi_gain(self, s, a):
        gain_ = 0
        for v in self.get_values(a):
            subset = []
            for item in s:
                if item[a] == v:
                    subset.append(item)
            if len(subset):
                gain_ += (len(subset)/len(s)) * self.variance_impurity(subset)

        return self.variance_impurity(s) - gain_


    def e_gain(self, s, a):
        gain_ = 0
        for v in self.get_values(a):
            subset = []
            for item in s:
                if item[a] == v:
                    subset.append(item)
            if len(subset):
                gain_ += (len(subset)/len(s)) * self.entropy(self.split(subset))

        return self.entropy(self.split(s)) - gain_ 


    def entropy(self, s):
        total = entropy_ = 0
        
        for key, value in s.items():
            total += value 
        for key, value in s.items():
            p = (value/total)
            if p:
                entropy_ -= p*log(p, 2)
        return entropy_ 
 

    def split(self, s):
        split_ = {}
        for attr in self.attr_values[self.t_attr]:
            split_[attr] = 0
        for item in s:
            for attr in self.attr_values[self.t_attr]:
                if item[self.t_attr] == attr:
                    split_[attr] += 1
        return split_ 


    def set_values(self):
        for attr in self.attrs:
            self.attr_values[attr] = []
        self.attr_values[self.t_attr] = []
        for item in self.data:
            for attr in self.attrs:
                if item[attr] not in self.attr_values[attr]:
                    self.attr_values[attr].append(item[attr])
            if item[self.t_attr] not in self.attr_values[self.t_attr]:
                self.attr_values[self.t_attr].append(item[self.t_attr])


    def get_values(self, a):
        return self.attr_values[a] 


    def predict(self, node, item):
        while(type(node) == type(Node()) and len(node.get_children())):
            node = node.get_child(item[node.get_label()])
        return node.get_label()


    def iterate_nodes(self, root):
        nodes = root.get_children()
        results = []
        while True:
            new_nodes = []
            if not len(nodes):
                break
            for val, node in nodes:
                results.append((val, node))
                if len(node.get_children()):
                    for v, child in node.get_children():
                        new_nodes.append((v, child))
            nodes = new_nodes
        return results
