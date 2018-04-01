import sys
import os
import re
import math
import nltk
import collections
import random
from nltk.stem import *
from nltk.tokenize import RegexpTokenizer
from nltk.corpus import stopwords
nltk.download('stopwords')

def get_tokens(fp, all_words):
    file_path = fp
    if(file_path[-1] != '/'):
        file_path = file_path + '/'
    paths = [file_path + "ham/", file_path + "spam/"]
    stemmer = PorterStemmer()
    count = 0
    lst = []
    stop_words = set(stopwords.words('english'))
    for path in paths:
        print(path)
        for filename in os.listdir(path):
            if(filename.endswith(".txt")):
                #f = open(path + filename, "r")
                tokens = {}
                with open(path + filename) as line:
                    lines = line.readlines()
        
                for line in lines:
                    line = re.sub('[^A-Za-z ]+', '', line)
                    doc = line.split()
                    words = [stemmer.stem(p) for p in doc]
                    words = [w for w in words if not w in stop_words]
                    for word in words:
                        if word in tokens.keys():
                            tokens[word] += 1
                        else:
                            tokens[word] = 1
                    for word in words:
                        if word not in all_words:
                            all_words.append(word)
                if "class" in tokens.keys():
                    del tokens["class"]
                if "spam" in path:
                    tokens["OBJ_class"] = "SPAM"
                else:
                    tokens["OBJ_class"] = "HAM"
                lst.append(tokens)
    if "class" in all_words:
        all_words.remove("class")
    return all_words, lst

def make_arff(path, attrs, docs):
    with open(path, 'w') as arff:
        arff.write("@RELATION emails\n\n")
        for word in attrs:
            arff.write("@ATTRIBUTE " + word + "\tNUMERIC\n")
        arff.write("@ATTRIBUTE class\t{HAM, SPAM}\n")
        arff.write("@DATA\n")
        for doc in docs:
            for word in attrs:
                if word in doc.keys():
                    arff.write(str(doc[word]) + ",")
                else:
                    arff.write("0,")
            arff.write(doc["OBJ_class"] + "\n")

train_path = sys.argv[1]
test_path = sys.argv[2]
train_output = sys.argv[3]
test_output = sys.argv[4]
words = []
words, train_data = get_tokens(train_path, words)
words, test_data = get_tokens(test_path, words)
random.shuffle(train_data)
random.shuffle(train_data)
make_arff(train_output, words, train_data)
make_arff(test_output, words, test_data)
