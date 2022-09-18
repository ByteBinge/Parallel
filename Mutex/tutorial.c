// Create one mutex per critical section.
// store pthread_mutex_t sum_lock; asa global variable
// so that theres only 1 shared amongst the threads.
//
// Otherwise you would also have to pass it into the function
// being called by the threads.
//
// pthread_mutex_lock -
// the critical section, lock the door
// allows a single thread to enter the critical section
// stopping a 2nd thread from entering and will be held at the
// mutex lock.
// This solves the race conditions.
//
// leaving the critical section, open the door.
// The next thread that had called mutex_lock that has been waiting
// will go next, unless you do prioritization.
//
// The critical section for summing, would be the for loop.
//
// Not the most efficient way to solve this problem
// as only one thread would be able to run at a time.
// for (i = start; i <= end; i++) {
//     pthread_mutex_lock(&sum_lock);
//     sum+=i;
//     pthread_mutex_unlock(&sum_lock);
// }
// one way to fix this:
// make another variable for each individual thread. then inside the loop
// set mysum += i, so each thread computes its part of the sum.
// The have a critical section just adding a global sum from the local sums.
//
// unsigned long i;
// unsigned long mySum;
// for (int i = start; i<= end; i++) {
//     mySum += i;
// }
// pthread_mutex_lock(&sum_lock);
// sum += mySum;
// pthread_mutex_unlock(&sum_lock);
//
// Next: we will make parallel sum program have command-line arguments.
// storing it as int threads, as a global variable.
//
// int argc, char** argv -> a.out is parameter 0, whatever next would be argument 1
// then set the number of threads to atoi(argv[i])
//
// search.c example
// an array of strings in C is a 2d array.
// length of string set to 64 
// calculating starting point and ending point
// strstr in c is a string matching function
// main reads file into the array
//
// sometimes a thread will start its print before a previous thread.
// one thread calls printf, another thread will call printf.
//
// pthread_mutex_lock 
// if you forget to unlock the lock, you will only have 1 thread operate a function
// and it wont unlock.
