#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* routine() {
	printf("Test from threads\n");
	sleep(3); // from the unistd library.
	printf("Ending thread\n");
}

int main(int argc, char* argv[]) {
	pthread_t t1, t2; // define where the api can store information about the thread.
	if (pthread_create(&t1, NULL, &routine, NULL) != 0) {
		return 1;
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)j{
		return 1;
	}
	// need to wait for the processess to finish execution.
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
