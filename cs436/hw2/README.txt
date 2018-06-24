Name:		Austin Ward
B-Number:	B00518794
Semester:	Spring 2018
Due:		3/02/18

Binghamton University

HOW TO RUN:
  make
  ./main <train> <test>

REMARKS:
  Naive Bayes:
    After implementing stopword removal my accuracy 
    increased to 90%. Since the removed words are 
    causing the data to overfit, it makes sense
    their removal would increase the accuracy.

  Logistic Regression:
    Removal of stopwords actually decreased the 
    accuracy for each iteration of lambda. With 
    that said, the difference in accuracy became
    less apparent with smaller lambda values.

  Extra Credit Feature Selection:
    By implementing a chi-squared feature selection
    the accuracy for NB with stopwords increased by
    2%. No other accuracies were affected in the 
    negative or positive directions. 
    I choose this feature selection method since
    it can compute the importance of a certain
    feature, and if said feature is below a boundary
    we can remove it from our vocabulary. Similar
    to stopword removal, this will remove words of
    lower importance. After testing different boundary
    levels, I found that a higher boundary resulted
    in the change described above. This change can
    be found in the results.txt file.

ACCURACY FILE:
  results.txt

I have done this assignment completely on my own. 
I have not copied it, nor have I given my solution 
to anyone else. I understand that if I am involved 
in plagiarism or cheating I will have to sign an 
official form that I have cheated and that this 
form will be stored in my official university 
record. I also understand that I will receive a 
grade of 0 for the involved assignment for my first 
offense and that I will receive a grade of “F” for 
the course for any additional offense.

E-Sign: Austin Ward
