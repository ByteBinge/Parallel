/* This program presents a problem whereby when using 4 threads, the order of the threads is incorrect.
 * */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// macro never gets stored in memory, because preprocessor gets to it before compiler.
// It then finds all instances of THREADS and replaces it with 4.
// THEN the compiler runs.
#define THREADS 3

struct test {
	int id;
	char word[10]; 
};

// TODO: when do I need to use malloc()?
// void* is a wildcard pointer.
// ppthreads does this to allow any information to be past in, but then you need to cast it.
void* f(void* data) {
	// create a struct test pointer, store a type-casted void* data (not dereferenced).
	struct test *struct_ptr = (struct test*) data;

	// depends on the compiler and machine how big an int is.
	// allocate memory, for each thread, to contain the exponent of the thread id.
	// t1 can reach into malloc, store the result, then main can reach into malloc
	// and pull the result.
	int *id_exponent = malloc(sizeof(int));
	*id_exponent = struct_ptr->id * struct_ptr->id;

	// select the word field, store the char *s from address + id.
	strcpy(struct_ptr->word, "hello"+struct_ptr->id);
	sleep(3);
	printf("%d: %s\n", struct_ptr->id, struct_ptr->word);
	// can you pthread_exit to return, or actually use a return statement.
	// gets returned as a pointer to your value.
	// have to be careful because, inside your process, each thread gets its own stack
	// main gets its own stack.
	// so if main point to something in t1, and t1 finishes its function call
	// that variable will be deallocated after function completion.
	// its better to use the heap - to store results that persist across function calls.
	pthread_exit((void *) id_exponent); // return the exponent of the thread's id.
}

// main uses its own thread, correct?
int main(void) {
	// need to change the address of result, which is why we pass in the 
	// address of result in pthread_join.
	int *result; // to store results returned by threads.
	struct test args[THREADS]; // struct that is unique to each thread.
	pthread_t t[THREADS];
	int id[THREADS];
	
	// Creating threads
	for (int i = 0; i < THREADS; i++) {
		args[i].id = i;
		pthread_create(&t[i], NULL, f, &args[i]);
	}
	
	// if you want to join them all you need to use a for loop.
	// Join a thread, then print out its id squared, then repeat for the rest of the threads.
	for (int i = 0; i < THREADS; i++) {
		pthread_join(t[i], (void **) &result);
		printf("Return result for thread: %d = %d.\n", args[i].id, *result);
	}
	
	printf("Collective threads return result: %d.\n", *result);
	printf("Completion of threads.\n");

	pthread_exit(0);
}
