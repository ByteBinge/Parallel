#include<stdio.h>

void decompose(double x, long *int_part, double *frac_part) {
	*int_part = (long) x;
	*frac_part = x - *int_part;
	printf("%lu %f", *int_part, *frac_part);
}

int main(void) {

	long i = 0;
	double x = 0.0; 
	decompose(3.14159, &i, &x);
	return 0;
}
