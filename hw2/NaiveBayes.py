from math import log


def get_docs_containing_word(docs, word):
    count = 0
    for email in emails:
        if word in email:
            count += 1


def multinomial_nb(vocab, doc_count, docs_in_class, emails):
    prior = {'ham':0, 'spam':0}
    cond_prob = {'ham':{}, 'spam':{}}
    for class_ in ['ham', 'spam']:
        prior[class_] = docs_in_class[class_] / doc_count
        for word in vocab:
            docs_with_word_and_class = sum([1 for email in emails[class_] if word in email])
            cond_prob[class_][word] = laplace(1, docs_with_word_and_class, docs_in_class[class_], len(vocab))
    return prior, cond_prob


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


def laplace(k, count, total, unique):
    return (count + k)/(total + k*unique)


def smooth(data):
    ham_dict, ham_word_count, ham_file_count = data['ham']
    spam_dict, spam_word_count, spam_file_count  = data['spam']
    total_prior = ham_file_count + spam_file_count
    ham_prior = ham_file_count/total_prior
    spam_prior = spam_file_count/total_prior
    unique_words = data['unique_words']
    new_ham_dict = {}
    new_spam_dict = {}
    for (h_word, h_count), (s_word, s_count) in zip(ham_dict.items(), spam_dict.items()):
        new_ham_dict[h_word] =  laplace(1, h_count, ham_word_count, unique_words)
        new_spam_dict[s_word] =  laplace(1, s_count, spam_word_count, unique_words)
    return {'ham':(new_ham_dict, ham_prior), 'spam':(new_spam_dict, spam_prior)}


def predict(data, email, word_count, unique, type_):
    (ham, ham_p), (spam, spam_p) = (data['ham'], data['spam'])
    for word in email:
        ham_p *= ham[word] if word in ham else laplace(1, 0, word_count, unique)
        spam_p *= spam[word] if word in spam else laplace(1, 0, word_count, unique)
    return (type_ == 'ham' and ham_p > spam_p) or (type_ == 'spam' and spam_p > ham_p)


def accuracy(data):
    correct = total = 0
    ham_emails, ham_word_count = data['ham']
    spam_emails, spam_word_count  = data['spam']
    smoothed_train = data['smoothed_train']
    unique_words = data['unique_words']
    for email in ham_emails:
        correct += predict(smoothed_train, email, ham_word_count, unique_words, 'ham')
        total += 1
    for email in spam_emails:
        correct += predict(smoothed_train, email, spam_word_count, unique_words, 'spam')
        total += 1
    return correct/total
