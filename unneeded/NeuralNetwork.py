import random
from numpy import exp


def net(xs, ws, bias):
    return bias + sum([w*x for w, x in zip(ws, xs)])


def sigmoid(n):
    return 1/(1+exp(-n))


class Node(object):
    def __init__(self, v):
        self.value = v
        self.weights = []


    def set_next(self, layer):
        self.weights = [random.uniform(-0.5, 0.5) for _ in layer]
        self.next = layer


    def set_pred(self, layer):
        self.pred = layer


    def set_value(self, v):
        self.value = v


    def set_delta(self, d):
        self.delta = d


    def update_weight(self, idx, val):
        self.weights[idx] += val


    def get_next(self):
        return self.next


    def get_pred(self):
        return self.pred


    def get_value(self):
        return self.value


    def get_delta(self):
        return self.delta


    def get_weight(self, idx):
        return self.weights[idx]


    def get_weights(self):
        return self.weights


class NeuralNetwork(object):
    def __init__(self, data, hidden_layers, bias=-1):
        self.data = data
        self.bias = bias
        input_nodes = [Node(0) for _ in data[0][0]]
        output_nodes = []
        classifications = []
        for x, y in data:
            if y not in classifications:
                output_nodes.append(Node(y))
                classifications.append(y)
        layers = []
        for num in hidden_layers:
            layers.append([Node(0) for _ in range(num)])

        for node in input_nodes:
            node.set_next(layers[0])
        for node in output_nodes:
            node.set_pred(layers[len(hidden_layers) - 1])
        for node in layers[0]:
            node.set_pred(input_nodes)
        for node in layers[len(layers) - 1]:
            node.set_next(output_nodes)

        for i in range(1, len(layers) - 1):
            for node in layers[i]:
                node.set_pred(layers[i - 1])
                node.set_next(layers[i + 1])
        self.layers = [l for l in [input_nodes] + layers + [output_nodes]]


    def train(self, learning_rate=0.1):
        for _ in range(10000):
            for example, target in self.data:
                output, o = self.run_network(example)
                self.backpropagation(target, o, learning_rate)


    def run_network(self, example):
        highest = -1

        # Input xs
        for x, node in zip(example, self.layers[0]):
            node.set_value(x)
    
        # Traverse network
        for layer in self.layers[1:len(self.layers) - 1]:
            for i, node in zip(range(len(layer)), layer):
                xs = [n.get_value() for n in node.get_pred()]
                ws = [n.get_weight(i) for n in node.get_pred()]
                node.set_value(sigmoid(net(xs, ws, self.bias)))

        # Get highest activation
        last_layer = self.layers[len(self.layers) - 1]
        for i, node in zip(range(len(last_layer)), last_layer):
            xs = [n.get_value() for n in node.get_pred()]
            ws = [n.get_weight(i) for n in node.get_pred()]
            activation = sigmoid(net(xs, ws, self.bias))
            if activation > highest:
                choice = node.get_value()
                highest = activation
        print("="*80)
        for i, node in zip(range(len(last_layer)), last_layer):
            xs = [n.get_value() for n in node.get_pred()]
            ws = [n.get_weight(i) for n in node.get_pred()]
            activation = sigmoid(net(xs, ws, self.bias))
            print(node.get_value(), activation)
        print("="*80)
        return (choice, highest)


    def backpropagation(self, target, o, eta):
        last = len(self.layers) - 1

        # Set deltas for output layer
        for node in self.layers[last]:
            correct_node = int(target == node.get_value())
            delta = o*(1 - o)*(correct_node - o)
            node.set_delta(delta)

        # Update weights and set deltas for hidden layers
        for layer in reversed(self.layers[1:len(self.layers) - 1]):
            for node in layer:
                sum_next = 0
                # Update weights
                for i in range(len(node.get_weights())):
                    delta = node.get_next()[i].get_delta()
                    sum_next += (node.get_weight(i) * delta)
                    node.update_weight(i, eta*delta*node.get_value())

                # Set delta
                o = node.get_value()
                node.set_delta(o*(1 - o)*sum_next)

        # Change weights for first layer
        for node in self.layers[0]:
            for i in range(len(node.get_weights())):
               delta = node.get_next()[i].get_delta()
               node.update_weight(i, eta*delta*node.get_value())
           

    def accuracy(self, test_data):
        total = correct = 0
        for xs, y in test_data:
            output, o = self.run_network(xs)
            correct += int(output == y)
            total += 1
        return correct/total
