# Copyright 2018 Austin Ward
from os.path import isfile, join
from nltk.stem.porter import PorterStemmer
from os import listdir
import pickle


stemmer = PorterStemmer()
STOPWORDS = pickle.load(open('stopwords.pickle', 'rb'))
NUMBERS = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
SPECIAL = ['_', '-', ':', '/', '@', '#', '$', '.', ',', '(', ')', ';', \
           "'", '"', '!', '$', '%', '^', '&', '*', '?', '|', '+', '\n']
BOUNDRY = 200 


def clean_message(text, remove_stopwords):
    for c in NUMBERS + SPECIAL:
        text = text.replace(c, ' ')
    data = [word for word in text.split(' ') if word]
    if remove_stopwords:
        for c in STOPWORDS:
            while c in data:
                data.remove(c)
    return data


def best_features(vocab, L):
    for class_ in ['ham', 'spam']:
        for word in vocab:
            if L[class_][word] <= BOUNDRY:
                del L[class_][word]
    return L


def compute_feature_utility(emails, word):
    res = []
    pop = sum([len(email) for email in emails])
    for email in emails:
        if word in email:
            observed = email.count(word)
            prob = observed/len(email)
            res.append((observed/pop - prob)**2/prob)
    return pop * sum(res)


def feature_selection(vocab, emails):
    L = {'ham':{}, 'spam':{}}
    for class_ in ['ham', 'spam']:
        for word in vocab:
            L[class_][word] = compute_feature_utility(emails[class_], word)
    best_ = best_features(vocab, L)
    new_vocab = []
    for class_ in ['ham', 'spam']:
        for word in vocab:
            if word in L[class_] and word not in new_vocab:
                new_vocab.append(word)
    return new_vocab


def get_data(name, remove_stopwords=False):
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
            try:
                with open(type_ + file_) as f:
                    data = f.read()
            except:
                continue
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
    return {
            'ham':ham_data, 
            'spam':spam_data, 
            'ham_file_count':ham_file_count, 
            'spam_file_count':spam_file_count
            }


def create_dicts(d):
    hams = d['ham']
    spams = d['spam']
    ham_file_count = d['ham_file_count']
    spam_file_count = d['spam_file_count']
    ham_dict = {}
    ham_word_count = 0
    spam_dict = {}
    spam_word_count = 0
    unique_words = 0
    for email in hams:
        for word in email:
            ham_word_count += 1
            if word in ham_dict:
                ham_dict[word] += 1
            else:
                ham_dict[word] = 1
                unique_words += 1
    for email in spams:
        for word in email:
            spam_word_count += 1
            if word in spam_dict:
                spam_dict[word] += 1
            else:
                spam_dict[word] = 1
                if word not in ham_dict:
                    unique_words += 1
    return {
            'ham':(ham_dict, ham_word_count, ham_file_count), 
            'spam':(spam_dict, spam_word_count, spam_file_count)
            }
