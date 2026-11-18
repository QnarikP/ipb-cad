/*
 (approximate PI via a simple sum - take 2) (on-class)
          (protecting shared global variables with mutexes)
Revisit exercise PT10c1. It involves a situation in which a global vector is being used 
to deposit/share the contributions of worker threads, with a specific cell per thread. 
Adapt the code to take advantage of mutex variables. Explore two approaches: a) 
coarse-grain: a variable shared by many threads is minimally accessed by each thread 
(e.g., to account only for the local contribution of the thread); b) fine-grain: a variable 
shared by many threads is intensively accessed by each thread (e.g., inside a loop). 
Compare the execution time of the three approaches (PT10c1, PT22a, PT22b).
Note: you can apply/adapt the same techniques in/to exercises PT6, PT12 to PT14
*/

homework