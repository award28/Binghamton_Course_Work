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
    
    for word, count in ham_dict.items():
        new_ham_dict[word] =  laplace(1, count, ham_word_count, unique_words)
    for word, count in spam_dict.items():
        new_spam_dict[word] =  laplace(1, count, spam_word_count, unique_words)
    
    return {'ham':(new_ham_dict, ham_prior), 'spam':(new_spam_dict, spam_prior)}

def predict(data, email, word_count, unique, type_):
    ham, ham_p = data['ham']
    spam, spam_p = data['spam']

    for word in email:
        if word in ham:
            ham_p *= ham[word]
        else:
            ham_p *= laplace(1, 0, word_count, unique)
        if word in spam:
            spam_p *= spam[word]
        else:
            spam_p *= laplace(1, 0, word_count, unique)
    if(type_ == 'ham' and ham_p > spam_p):
        return 1
    elif(type_ == 'ham'):
        return 0
    if(type_ == 'spam' and spam_p > ham_p):
        return 1
    elif(type_ == 'spam'):
        return 0
