Name:		Austin Ward
B-Number:	B00518794
Semester:	Spring 2018
Due:		3/28/18

Binghamton University

HOW TO RUN:
  if needed, create stopwords pickle with:
    python3 create_stopwords_pickle.py
  make
  ./main <train> <test>

PART 3 ANSWER:
           w1,1
      (x1) --> (h1)
      	\   /    \
     w2,1\ /      \w3,1
      	  X       (y)-------> Output
     w1,2/ \      /w3,2
      	/   \    /
      (x2) --> (h2)
           w2,2

  where:
    bias1 = -1.5
    bias2 = -0.5
    w1,1 = 1
    w2,1 = -1
    w1,2 = 1
    w2,2 = -1
    w3,1 = 1
    w3,2 = 1
  and
    h1 = sigmoid(bias1 + (w1,1)*x1 + (w1,2)*x2)
    h2 = sigmoid(bias1 + (w2,1)*x1 + (w2,2)*x2)
    y  = sigmoid(bias2 + (w3,1)*h1 + (w3,2)*h2)
    
  This Nueral network is x if the output > 0 and ◇ otherwise
  

PART 4 ANSWER:
  It's relatively easy to change this from a sigmoid to a tanh.
  Replace:
    T4.3 with delta(k) <- (1 - o(k)^2)(t(k) - o(k))
    T4.4 with delta(h) <- (1 - o(h)^2) * sum_outputs
      where sum_outputs = sum for all outputs k (w(k,h)delta(k))
REMARKS:
    

WEKA RESULTS:
  weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 60 -V 0 -S 0 -E 20 -H 5
  === Summary ===
  
  Correctly Classified Instances         348               72.8033 %
  Incorrectly Classified Instances       130               27.1967 %
  Kappa statistic                          0     
  Mean absolute error                      0.3788
  Root mean squared error                  0.4466
  Relative absolute error                 96.2473 %
  Root relative squared error            100.3509 %
  Total Number of Instances              478     
  
  === Detailed Accuracy By Class ===
  
                   TP Rate  FP Rate  Precision  Recall   F-Measure  MCC      ROC Area  PRC Area  Class
                   1.000    1.000    0.728      1.000    0.843      ?        0.512     0.707     HAM
                   0.000    0.000    ?          0.000    ?          ?        0.512     0.352     SPAM
  Weighted Avg.    0.728    0.728    ?          0.728    ?          ?        0.512     0.611     
  
  === Confusion Matrix ===
  
     a   b   <-- classified as
   348   0 |   a = HAM
   130   0 |   b = SPAM

  weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.0 -N 60 -V 0 -S 0 -E 20 -H 5
  === Summary ===
  
  Correctly Classified Instances         348               72.8033 %
  Incorrectly Classified Instances       130               27.1967 %
  Kappa statistic                          0     
  Mean absolute error                      0.3778
  Root mean squared error                  0.4468
  Relative absolute error                 95.993  %
  Root relative squared error            100.3937 %
  Total Number of Instances              478     
  
  === Detailed Accuracy By Class ===
  
                   TP Rate  FP Rate  Precision  Recall   F-Measure  MCC      ROC Area  PRC Area  Class
                   1.000    1.000    0.728      1.000    0.843      ?        0.455     0.680     HAM
                   0.000    0.000    ?          0.000    ?          ?        0.455     0.292     SPAM
  Weighted Avg.    0.728    0.728    ?          0.728    ?          ?        0.455     0.574     
  
  === Confusion Matrix ===
  
     a   b   <-- classified as
   348   0 |   a = HAM
   130   0 |   b = SPAM


  weka.classifiers.functions.MultilayerPerceptron -L 0.1 -M 0.3 -N 30 -V 0 -S 0 -E 20 -H a
  === Summary ===
  
  Correctly Classified Instances         341               73.6501 %
  Incorrectly Classified Instances       122               26.3499 %
  Kappa statistic                          0.0119
  Mean absolute error                      0.3655
  Root mean squared error                  0.4436
  Relative absolute error                 93.5562 %
  Root relative squared error            100.4447 %
  Total Number of Instances              463     
  
  === Detailed Accuracy By Class ===
  
                   TP Rate  FP Rate  Precision  Recall   F-Measure  MCC      ROC Area  PRC Area  Class
                   1.000    0.992    0.736      1.000    0.848      0.077    0.674     0.830     HAM
                   0.008    0.000    1.000      0.008    0.016      0.077    0.674     0.522     SPAM
  Weighted Avg.    0.737    0.728    0.806      0.737    0.627      0.077    0.674     0.748     
  
  === Confusion Matrix ===
  
     a   b   <-- classified as
   340   0 |   a = HAM
   122   1 |   b = SPAM
  
  
  weka.classifiers.functions.MultilayerPerceptron -L 0.3 -M 0.2 -N 500 -V 0 -S 0 -E 20 -H 20 -R
  === Summary ===
  
  Correctly Classified Instances         340               73.4341 %
  Incorrectly Classified Instances       123               26.5659 %
  Kappa statistic                          0     
  Mean absolute error                      0.3615
  Root mean squared error                  0.4459
  Relative absolute error                 92.548  %
  Root relative squared error            100.9521 %
  Total Number of Instances              463     
  
  === Detailed Accuracy By Class ===
  
                   TP Rate  FP Rate  Precision  Recall   F-Measure  MCC      ROC Area  PRC Area  Class
                   1.000    1.000    0.734      1.000    0.847      ?        0.478     0.687     HAM
                   0.000    0.000    ?          0.000    ?          ?        0.478     0.293     SPAM
  Weighted Avg.    0.734    0.734    ?          0.734    ?          ?        0.478     0.583     
  
  === Confusion Matrix ===
  
     a   b   <-- classified as
   340   0 |   a = HAM
   123   0 |   b = SPAM


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
