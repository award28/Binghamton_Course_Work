from math import log


"""
Class:      Node 
Constructor Parameters:
    N/A

Methods:
    set_label(1)        Sets the label for the current node
    get_label(0)        Returns the label for the current node
    create_sub_node(1)  Creates a new node at the attr value on the current 
                        node
    inject_node(2)      Injects a given node at the attr value on the current
                        node
    get_node(1)         Given an attr value it returns a node
"""
class Node(object):
    def __init__(self):
        self.values = {} 
        self.label = None


    def set_label(self, label):
        self.label = label


    def get_label(self):
        return self.label


    def create_sub_node(self, value):
            self.values[value] = Node()


    def inject_node(self, value, node):
        self.values[value] = node
    

    def get_node(self, value):
        return self.values[value]


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
    def __init__(self, training_data, target_attr, attrs, validate=None):
        self.data = training_data
        self.t_attr = target_attr
        self.attrs = attrs
        self.validate = validate
        self.attr_values = {}
        self.set_values()


    def ID3(self, is_info_gain=True, prune=False):
        self.is_info_gain = is_info_gain
        return self.__ID3(self.data, self.t_attr, self.attrs)


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
            root.create_sub_node(v)
            subset = []
            for d in data:
                if d[best_attr] == v:
                    subset.append(d)
            if not len(subset):
                p = self.split(data)
                root.inject_node(v, p[0] > p[1])
            else:
                attrs.remove(best_attr)
                root.inject_node(v, self.__ID3(subset, t_attr, attrs))
                attrs.append(best_attr)

        return root 

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
        while(type(node.get_label()) != int):
            node = node.get_node(item[node.get_label()])
        return node.get_label()
