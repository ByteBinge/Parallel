#include <stdio.h>
#include <sys/time.h>

int main() {
	struct timeval current;
	gettimeofday(NULL, NULL);
	printf("Seconds : %ld \nMicroseconds : %ld", current.tv_sec, current.tv_usec);
	return 0;
}
