import pickle

with open('stopwords.txt', 'r') as f:
    words = f.read()
    words = words.split('\n')
    stopwords = []
    for word in words:
        if word and word not in stopwords:
            stopwords.append(word)
    with open('stopwords.pickle', 'wb') as p:
        pickle.dump(stopwords, p)
