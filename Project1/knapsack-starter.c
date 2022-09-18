/* knapsack-starter.c
 * starter code for the parallel knapsack solver
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/* this code creates a global array of Item objects
 * each contains a weight and a value
 * the number of items we actually have is also global
 */
#define MAX_ITEMS 256
struct Item {
    int weight;
    int value;
};
struct Item items[MAX_ITEMS];
int num_items;

/* we also store the total weight limit allowed in a
 * global variable
 */
int weight_limit;

/* the number of threads in the program
 * this must be a power of two
 */
unsigned int num_threads;

/* this function tests if a number is a power of two
 * this can be used for determining if the number of
 * threads is valid
 */
unsigned int power_of_two(unsigned int num) {
    while (((num % 2) == 0) && (num > 1)) {
        num >>= 1;
    }
    if (num == 1) {
        return 1;
    } else {
        return 0;
    } 
}

/* this function finds the log base 2 of an unsigned int
 * it assumes the number is in fact a power of two
 * this can be used for finding how many items are "fixed"
 * for each thread, given the number of threads we have
 */
unsigned int log_2(unsigned int num) {
    int l = 0;
    while (num != 0) {
        num >>= 1;
        l++;
    }
    return l - 1;
}

/* this function should "increment" an array of binary numbers
 * for example, given [0, 0, 1] it should modify the array to
 * be [0, 1, 0] (which would be binary 1 to 2)
 *
 * this function will allow a thread to move from one possible set
 * of items onto the next
 */
void increment(unsigned char* bits) {
    /* TODO */
    
}


/* this function should check if an array of bits has wrapped
 * all the way around back to all zeroes - e.g. it should return
 * whether every bit in the range of the array is 0 or not
 */
int finished(unsigned char* bits, int start, int end) {
    /* TODO */
    
}

/* this function should evaluate the total cost and weight of the
 * single item indicated by the array of bits
 * it should update the "total" struct so that it's weight and
 * value represent those of the bit combination passed in
 */
void evaluate(unsigned char* bits, struct Item* total) {
    /* TODO */

}

/* this function is the entry point for each thread created
 * it is passed in the thread id as in the sum example
 * it should:
 *      - keep track of the best weight/value it has found
 *      - make an array of bits which represent the items it's looking at
 *      - find out how many "fixed" bits there are, given the number of threads
 *      - set the "fixed" bits to the thread id as a binary number
 *        e.g. if there are 8 threads, thread 6 should use [1, 1, 0, ...
 *      - set the rest of the bits to 0
 *      - loop through all the possibilites using the increment and finished functions
 *          - for each possibility, evaluate it, and see if it's the best so far
 *      - return the best weight/value combination seen so far (this can be done with
 *          an Item object using weight and value fields)
 */
void* knapsack_worker(void* idp) {
    /* TODO */

}

/* the main method
 * it should:
 *      - check that the two command line arguments have been passed in
 *      - check that the number of threads is a positive power of two
 *      - open the file, giving an error if it does not exist
 *      - read the input file into the global array
 *      - spawn the threads, giving each an id
 *      - keep track of the best weight/value combo in any thread
 *      - join each thread, checking if the thread found a better result than
 *        what we have so far
 *      - print the optimal result to the screen
 */
int main(int argc, char** argv) {
    // first parameter: input file name.
    // second parameter: number of threads to use (power of 2).
    // first argument is executing the program...
    unsigned int threads = (unsigned int) argv[1]; 
    if (power_of_two(threads)) {
        printf("true"); 
    } else {
        printf("false");
    }

    return 0;
}

