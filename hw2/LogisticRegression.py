from numpy import log, exp
from random import random


def logistic_regression(learning_rate, lambda_, examples, dict_, bias=-5):
    features = [word for word in dict_]
    probs = [random() for i in range(len(examples))]
    weights = [random() for i in range(len(features))]
    converged = 10
    prev_accuracy = -1
    z = 0
    while z < 100 and not converged == 0:
        z += 1
        for i in range(len(examples)):
            email, type_ = examples[i]
            probs[i] = prob_spam(bias, email, features, weights)
        deriv_weights = [0] * len(features)
        for i in range(len(features)):
            for j in range(len(examples)):
                email, type_ = examples[j]
                freq = 0 if features[i] not in email else email.count(features[i])/len(email)
                deriv_weights[i] = deriv_weights[i] + freq * ((type_ - probs[j]))
        for i in range(len(features)):
            weights[i] = weights[i] + learning_rate * (deriv_weights[i] - lambda_ * weights[i])
        accuracy = lr_accuracy(examples, features, weights, bias)
        if (abs(accuracy - prev_accuracy) <= 0.00001):
            converged -= 1
        else:
            converged = 10
        prev_accuracy = accuracy
    return (features, weights)


def weight_sum(bias, email, features, weights):
    return bias + sum([weights[features.index(word)]*(1/len(email)) for word in email])


def prob_spam(bias, email, features, weights):
    s = weight_sum(bias, email, features, weights)
    try:
        e = exp(s)
        rv = e/(1 + e)
        return rv
    except:
       return 1


def classify(bias, email, features, weights):
    return weight_sum(bias, email, features, weights) > 0


def lr_accuracy(examples, features, weights, bias=-20):
    correct = total = 0
    for j in range(len(examples)):
        email, type_ = examples[j]
        if classify(bias, email, features, weights) == type_:
            correct += 1
        total += 1
    return correct/total
