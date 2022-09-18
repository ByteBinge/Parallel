#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>

#define LENGTH 2
#define START 0
#define THROWS 100000000
volatile int THREADS;
// ran function to throw random darts each thread and return number in circle.
void* ran(void* seed) {
	struct timeval current;
	gettimeofday(&current, NULL);
	unsigned long ms_start = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	int id = * (int *) seed;
	int start = ((THROWS - START) / THREADS) * id;
	int end = ((THROWS - START) / THREADS) * (id + 1);

	if (id == (THREADS - 1)) {
		end++;
	}

	double x;
	double y;
	double distance;
	int* count = malloc(sizeof(int));

	// For each throw, calculate the x and y values of each dart to see if its inside the circle.
	for (int i = start; i < end; i++) {
		// why does rand_r affect my id variable?
		x = ((double) rand_r(&id) / (double) RAND_MAX) * 2.0 - 1.0;
		y = ((double) rand_r(&id) / (double) RAND_MAX) * 2.0 - 1.0;
		distance = (x*x) + (y*y);
		if (distance <= 1) {
			*count += 1;
		}
	}
	gettimeofday(&current, NULL);
	unsigned long ms_end = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	printf("Thread %d took, %ld ms.\n", * (int *) seed, ms_end - ms_start);
	return (void*) count;
}

// double character pointer, basically a char array
int main(int argc, char **argv) {
	if (argv[1] != NULL) {	
		THREADS = atoi(argv[1]);
	} else {
		printf("Rerun the program with Threads parameter: ./program_name <Thread_Count>\n");
		return 1;
	}
	pthread_t threads[THREADS];
	int ids[THREADS];
	int* result;
	int total;
	double pi_result;
	
	// Spawning threads
	for (int i = 0; i < THREADS; i++) {
		ids[i] = i;
		pthread_create(&threads[i], NULL, ran, &ids[i]);
	}

	// joining threads
	for (int i = 0; i < THREADS; i++) {
		pthread_join(threads[i], (void**) &result);
		total = total + *result;
	}

	pi_result = 4.0 * ((double) total / THROWS);
	printf("Pi is roughly %lf.\n", pi_result);
	free(result);
	pthread_exit(NULL);

}
