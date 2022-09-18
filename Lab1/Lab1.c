#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define THREADS 1
#define LENGTH 2
#define START 0
#define THROWS 100000000

// Area of circle: A = pi * r^2
// Area of the square here is 2ft^2.
// Throw number of darts in circle
// can now calculate pi.
// random number between -1 and 1.
// Want to throw millions and millions of darts.
// so we can parallelize it.

// Each thread can average pi, then each thread returns its estimation
// Then in main you can average them.

// Value of pi: 3.1415926

// ran function to throw random darts each thread and return number in circle.
void* ran(void* seed) {
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
		x = ((double) rand_r(&id) / (double) RAND_MAX) * 2.0 - 1.0;
		y = ((double) rand_r(&id) / (double) RAND_MAX) * 2.0 - 1.0;
		distance = (x*x) + (y*y);
		if (distance <= 1) {
			*count += 1;
		}
	}
	return (void*) count;
}

int main(void) {
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
