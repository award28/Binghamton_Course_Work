#!/usr/bin/python3
# Copyright 2018 Austin Ward

from os.path import isfile, join
from nltk.corpus import stopwords
from nltk.stem.porter import *
from nb import smooth, predict
from os import listdir
import pandas as pd
import pickle
import sys


def clean_message(text, remove_stopwords):
    numbers = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    special = ['-', ':', '/', '@', '#', '$', '.', ',', '(', ')', ';', \
               "'", '"', '!', '$', '%', '^', '&', '*', '?', '|', '+', '\n']
    to_remove = numbers + special
    if remove_stopwords:
        to_remove += pickle.load(open('stopwords.pickle', 'rb'))
    for c in to_remove:
        text = text.replace(c, ' ')
    return [word for word in text.split(' ') if word]


def get_data(name, remove_stopwords=False):
    stemmer = PorterStemmer()
    ham = name + '/ham/'
    spam = name + '/spam/'
    ham_files = [f for f in listdir(ham) if isfile(join(ham, f))]
    ham_data = [] 
    ham_file_count = 0
    spam_files = [f for f in listdir(spam) if isfile(join(spam, f))]
    spam_data = [] 
    spam_file_count = 0
    for type_, files_ in {ham : ham_files, spam : spam_files}.items():
        for file_ in files_:
            with open(type_ + file_) as f:
                try:
                    data = f.read()
                    subject = data.split('\n')[0]
                    data = data[data.find('\n') + 1:]
                    clean_subject = clean_message(subject[subject.find(':') + 1:], remove_stopwords)
                    clean_data = clean_message(data, remove_stopwords)
                    stemmed_subject = [stemmer.stem(word) for word in clean_subject]
                    stemmed_data = [stemmer.stem(word) for word in clean_data]
                    if type_ == ham:
                        ham_data.append(stemmed_subject + stemmed_data)
                        ham_file_count += 1
                    else:
                        spam_data.append(stemmed_subject + stemmed_data)
                        spam_file_count += 1
                except:
                    print("Could not read " + type_ + file_)
    return {'ham':ham_data, 'spam':spam_data, 'ham_file_count':ham_file_count, 'spam_file_count':spam_file_count}


def get_count(d):
    hams = d['ham']
    spams = d['spam']
    ham_file_count = d['ham_file_count']
    spam_file_count = d['spam_file_count']
    ham_dict = {}
    ham_word_count = 0
    spam_dict = {}
    spam_word_count = 0
    unique_words = 0
    for ham in hams:
        for word in ham:
            ham_word_count += 1
            if word in ham_dict:
                ham_dict[word] += 1
            else:
                ham_dict[word] = 1
                unique_words += 1
    for spam in spams:
        for word in spam:
            spam_word_count += 1
            if word in spam_dict:
                spam_dict[word] += 1
            else:
                spam_dict[word] = 1
                if word not in ham_dict:
                    unique_words += 1
    return {'ham':(ham_dict, ham_word_count, ham_file_count), 
            'spam':(spam_dict, spam_word_count, spam_file_count), 
            'unique_words':unique_words}

    
if len(sys.argv) != 3:
    print("./main <train> <test>")
    sys.exit()
pn = "parsed_train.pickle"
train = sys.argv[1]
test = sys.argv[2]

parsed_train = get_count(get_data(train, True))
smoothed_train = smooth(parsed_train)

ham_train, ham_word_count, ham_file_count = parsed_train['ham']
spam_train, spam_word_count, spam_file_count = parsed_train['spam']
unique_words = parsed_train['unique_words']

parsed_test_emails = get_data(test, True)
ham_test_emails = parsed_test_emails['ham']
spam_test_emails = parsed_test_emails['spam']

correct = total = 0
for email in ham_test_emails:
    correct += predict(smoothed_train, email, ham_word_count, unique_words, 'ham')
    total += 1
for email in spam_test_emails:
    correct += predict(smoothed_train, email, spam_word_count, unique_words, 'spam')
    total += 1

print("Predicted correctly: " + str(correct/total))
