from math import log


class Node(object):
    def __init__(self):
        self.values = {} 
        self.label = None


    def set_label(self, label):
        self.label = label


    def get_label(self):
        return self.label


    def add_value(self, value):
            self.values[value] = Node()


    def add_values(self, values):
        for value in values:
            self.values[value] = Node()


    def get_values(self):
        return self.values


    def add_node(self, value, node):
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
    gain(2)     Calcuates the reduction in entropy given a list and attribute
    Entropy(1)  Calcuates the entropy of a given integer list
"""
class DecisionTree:
    def __init__(self, training_data, target_attr, attrs, validate=None):
        self.data = training_data
        self.t_attr = target_attr
        self.attrs = attrs
        self.validate = validate


    def ID3(self):
        return self._ID3(self.data, self.t_attr, self.attrs)


    def _ID3(self, data, t_attr, attrs):
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
        best_attr = self.best_attr(data, attrs)

        root.set_label(best_attr)
        
        for v in self.values(best_attr):
            root.add_value(v)
            subset = []
            for d in data:
                if d[best_attr] == v:
                    subset.append(d)
            if not len(subset):
                p = self.pos_vs_neg(data)
                root.add_node(v, p[0] > p[1])
            else:
                attrs.remove(best_attr)
                root.add_node(v, self._ID3(subset, t_attr, attrs))
                attrs.append(best_attr)

        return root 

    def best_attr(self, s, attrs):
        best, val = None, 0
        for attr in attrs:
            g = self.gain(s, attr)
            if g > val:
                best = attr
                val = g 
        return best
            

    def values(self, a):
        return [0, 1]
    

    def gain(self, s, a):
        val_entropy = 0
        for v in self.values(a):
            subset = []
            for item in s:
                if item[a] == v:
                    subset.append(item)
            if len(subset):
                val_entropy += (len(subset)/len(s)) * self.entropy(self.pos_vs_neg(subset))
            else:
                val_entropy += 0

        return self.entropy(self.pos_vs_neg(s)) - val_entropy


    def pos_vs_neg(self, s):
        pos = 0
        for item in s:
            pos += item[self.t_attr]
        return [pos, len(s) - pos]


    def entropy(self, s):
        total = ret_val = 0
        for num in s:
            total += num
        for num in s:
            p = (num/total)
            if not p:
                ret_val -= 0
            else: 
                ret_val -= p*log(p, 2)
        return ret_val


    def predict(self, node, item):
        print("predicting...")
        while(type(node.get_label()) != int):
            print(item[node.get_label()])
            node = node.get_node(item[node.get_label()])
        return node.get_label()
            
