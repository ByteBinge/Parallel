#include <stdio.h>

int main(int argc, char **argv) {
	printf("X -> %s\n", *(argv+1));
	char *t = "test";
	printf("%s", &t);
	return 0;
}
