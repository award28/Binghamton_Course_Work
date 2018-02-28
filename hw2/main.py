#!/usr/bin/python3
# Copyright 2018 Austin Ward


from LogisticRegression import *
from NaiveBayes import * 
from read_data import *
import sys


def execute_nb(train, test, remove_stopwords):
    parsed_train = create_dicts(get_data(train, remove_stopwords))
    smoothed_train = smooth(parsed_train)
    ham_train, ham_word_count, ham_file_count = parsed_train['ham']
    spam_train, spam_word_count, spam_file_count = parsed_train['spam']
    unique_words = parsed_train['unique_words']
    parsed_test_emails = get_data(test, remove_stopwords)
    ham_test_emails = parsed_test_emails['ham']
    spam_test_emails = parsed_test_emails['spam']
    accuracy_data = {
            'ham': (ham_test_emails, ham_word_count), 
            'spam': (spam_test_emails, spam_word_count),
            'smoothed_train': smoothed_train, 
            'unique_words':unique_words
            }
    return accuracy(accuracy_data)

def get_ex_and_dict(data):
    examples = []
    for ham in data['ham']:
        examples.append((ham, 0))
    for spam in data['spam']:
        examples.append((spam, 1))
    weight_dict = create_dicts(data)
    dict_ = weight_dict['ham'][0]
    for word, values in weight_dict['spam'][0].items():
        if word not in dict_:
            dict_[word] = values
        else:
            dict_[word][0] += values[0]
    return (examples, dict_)


def execute_lr(l, train, test, remove_stopwords):
    parsed_train = get_data(train, remove_stopwords)
    parsed_test = get_data(test, remove_stopwords)
    train_ex, train_dict_ = get_ex_and_dict(parsed_train)
    test_ex, test_dict_ = get_ex_and_dict(parsed_test)
    features, weights = logistic_regression(1, l, test_ex, test_dict_, bias=2)
    test_accuracy = lr_accuracy(test_ex, features, weights, bias=2)
    return test_accuracy

if len(sys.argv) != 3:
    print("./main <train> <test>")
    sys.exit()
train = sys.argv[1]
test = sys.argv[2]

print("NB w/ stopwords: {:0.2f}".format(execute_nb(train, test, False)))
print("NB w/out stopwords: {:0.2f}".format(execute_nb(train, test, True)))
for l in [0.01, 0.05, 0.1, 0.15, 0.2]:
    print("LR w/ stopwords:\t{:0.2f}\tw/ lambda {:0.2f}".format(execute_lr(l, train, test, False), l))
    print("LR w/out stopwords:\t{:0.2f}\tw/ lambda {:0.2f}".format(execute_lr(l, train, test, True), l))
