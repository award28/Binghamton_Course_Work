# Copyright 2018 Austin Ward
from ParseData import *
from random import random


def get_ex_and_dict(data, select_features):
    examples = []
    for ham in data['ham']:
        examples.append((ham, -1))
    for spam in data['spam']:
        examples.append((spam, 1))
    old_dict_ = create_dicts(data)
    dict_ = old_dict_['ham'][0]
    for word, values in old_dict_['spam'][0].items():
        if word not in dict_:
            dict_[word] = values
        else:
            dict_[word] += values
    if select_features:
        temp_dict = {'ham': old_dict_['ham'][0], 'spam': old_dict_['spam'][0]}
        new_vocab = feature_selection([word for word in dict_], temp_dict)
        for word in dict_:
            if word not in new_vocab:
                del dict_[word]
    return (examples, dict_)


def execute_p(train, test, remove_stopwords, select_features, eta, it):
    parsed_train = get_data(train, remove_stopwords)
    parsed_test = get_data(test, remove_stopwords)
    train_ex, train_dict_ = get_ex_and_dict(parsed_train, select_features)
    test_ex, test_dict_ = get_ex_and_dict(parsed_test, select_features)
    features, weights = perceptron_ctor(eta, test_ex, test_dict_, it, bias=2)
    return p_accuracy(test_ex, features, weights, bias=2)


def perceptron_ctor(learning_rate, examples, dict_, it, bias=-5):
    features = [word for word in dict_]
    classifications = [random() for i in range(len(examples))]
    weights = [random() for i in range(len(features))]
    converged = 10
    prev_accuracy = -1
    for z in range(it):
        for i in range(len(examples)):
            email, type_ = examples[i]
            classifications[i] = classify(bias, email, features, weights)
        for i in range(len(features)):
            for j in range(len(examples)):
                email, type_ = examples[j]
                freq = 0 if features[i] not in email else email.count(features[i])/len(email)
                weights[i] = weights[i] + learning_rate * (type_ - classifications[j]) * freq
        accuracy = p_accuracy(examples, features, weights, bias)
        if (abs(accuracy - prev_accuracy) <= 0.00001):
            converged -= 1
        else:
            converged = 10
        prev_accuracy = accuracy
    return (features, weights)


def weight_sum(bias, email, features, weights):
    return bias + sum([weights[features.index(word)]*(1/len(email)) for word in email])


def classify(bias, email, features, weights):
    return (1 if weight_sum(bias, email, features, weights) > 0 else -1)


def p_accuracy(examples, features, weights, bias=-20):
    correct = total = 0
    for j in range(len(examples)):
        email, type_ = examples[j]
        if classify(bias, email, features, weights) == type_:
            correct += 1
        total += 1
    return correct/total
