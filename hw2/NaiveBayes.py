# Copyright 2018 Austin Ward
from ParseData import * 
from numpy import log


def execute_nb(train, test, remove_stopwords, select_features):
    train_data = get_data(train, remove_stopwords)
    parsed_train = create_dicts(train_data)
    vocab = []
    for word in parsed_train['ham'][0]:
        if word not in vocab: vocab.append(word)
    for word in parsed_train['spam'][0]:
        if word not in vocab: vocab.append(word)
    ham_train, ham_word_count, ham_file_count = parsed_train['ham']
    spam_train, spam_word_count, spam_file_count = parsed_train['spam']
    docs_in_class = {'ham':ham_file_count, 'spam':spam_file_count}
    total_docs = ham_file_count + spam_file_count
    emails = {'ham':train_data['ham'], 'spam':train_data['spam']}
    if select_features: vocab = feature_selection(vocab, emails)
    prior, cond_prob = multinomial_nb(vocab, total_docs, docs_in_class, emails)
    parsed_test_emails = get_data(test, remove_stopwords)
    emails = []
    for email in parsed_test_emails['ham']:
        emails.append((email, 0))
    for email in parsed_test_emails['spam']:
        emails.append((email, 1))
    return nb_accuracy(vocab, prior, cond_prob, emails)


def multinomial_nb(vocab, doc_count, docs_in_class, emails):
    prior = {'ham':0, 'spam':0}
    cond_prob = {'ham':{}, 'spam':{}}
    for class_ in ['ham', 'spam']:
        prior[class_] = docs_in_class[class_] / doc_count
        for word in vocab:
            docs_with_word_and_class = sum([1 for email in emails[class_] if word in email])
            cond_prob[class_][word] = laplace(1, docs_with_word_and_class, docs_in_class[class_], len(vocab))
    return prior, cond_prob


def laplace(k, count, total, unique):
    return (count + k)/(total + k*unique)


def nb_accuracy(vocab, prior, cond_prob, emails):
    correct = total = 0
    for (email, class_) in emails:
        correct += (class_ == nb_predict(vocab, prior, cond_prob, email))
        total += 1
    return correct/total


def nb_predict(vocab, prior, cond_prob, email):
    score = {}
    for class_ in ['ham', 'spam']:
        score[class_] = log(prior[class_])
        for word in vocab:
            prob = cond_prob[class_][word] if word in email else (1 - cond_prob[class_][word])
            score[class_] += log(prob)
    return score['spam'] > score['ham']
