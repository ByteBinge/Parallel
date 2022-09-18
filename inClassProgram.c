#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define THREADS 4
#define START 0
#define END 100000000000

void* partial_sum(void* idp) {
	// Each thread needs to know where its beginning and where its ending.
	int id = * (int *) idp;
	int start = ((END - START)/THREADS) * id;
	int end = ((END - START)/THREADS) * (id + 1);
	if (id == (THREADS - 1)) {
		end++;
	}
	printf("Thread %d does %d to %lu.\n", id, start, end);

	// since we want to return sum, we need to allocate memory for it.
	// instead of making sum a locaiul variable, we alocate it to memory.
	unsigned long* sum = malloc(sizeof(unsigned long)); 
	*sum = 0;
	for (int i = start; i < end; i++) {
		*sum = *sum + i;
	}
	sleep(3);
	pthread_exit(sum);
}

int main() {
	// old convention to have _t stand for type.
	pthread_t threads[THREADS]; // array of threads 

	// array of thread ids
	int ids[THREADS];

	for (int i = 0; i < THREADS; i++) {
		ids[i] = i;
		pthread_create(&threads[i], NULL, &partial_sum, &ids[i]);
	}
	unsigned long grand_total = 0;
	for (int i = 0; i < THREADS; i++) {
		unsigned long* partial;
		pthread_join(threads[i], (void**) &partial);
		grand_total = grand_total + *partial;
		free(partial); // clean up memory used after tha value has been used.
	}

	pthread_exit(0);
}
