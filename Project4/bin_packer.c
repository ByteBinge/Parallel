#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Prints out an array of integers
void printArray(int *array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d, ", array[i]);
	}
}

// Employs the modern Fisher-Yates shuffle algorithm to shuffle an 
// array of integers with all permutations equally likely.
void shuffle(int *array, int size) {
	srand(time(NULL));
	int j;
	int temp;
	for (int i = size-1; i > 0; i--) {
		j = rand() % (i + 1); //0 <= j <= i
	  	temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

// Applies greedy algorithm for determining number of bins for
// current array elelement arrangement sequentially
int greedy_bins(int *array, int size, int max_weight) {
	int bins = 1;
	int weight = 0;
	int j = 0;

	for (int i = 0; i < size; i++) {
		if (weight + array[i] > max_weight) {
			bins++;
			weight = 0;
			weight += array[i];
		} else {
			weight += array[i];
		}
	}
	return bins;
}

int main(int argc, char** argv) {
	char *file_name = argv[1];

	int max_weight = -1; // Max bin weight
	int size = -1; // Number of items to organize
	

	// File handling
	FILE *fp;
	if ((fp = fopen(file_name, "r")) == NULL) {
		printf("File not found.");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d", &max_weight); // Get the max bin weight from file
	fscanf(fp, "%d", &size); // Get the number of items to organize from file
	
	int items[size]; // All item weights to be organized
	
	// Gets all items from the file and stores into array
	for (int i = 0; i < size; i++) {
		fscanf(fp, "%d", &items[i]);
	}

	int **population = malloc(10 * sizeof(int *));
	for (int i = 0; i < 10; i++) {
		population[i] = malloc(size * sizeof(int));
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < size; j++) {
			population[i][j] = items[j];
		}
		printArray(population[i], size);
		shuffle(items, size);
	}

	int best_bins = INT_MAX;
	int bins = INT_MAX;
	for (int i = 0; i < 10; i++) {
		bins = greedy_bins(population[i], size, max_weight);
		printf("bins=%d\n", bins);
		if (bins < best_bins) {
			best_bins = bins;
		}
	}
	
	// Genetic algo
	// get fitness of each member of population
	// eliminate least fit members
	// new members created by modifying members of population
	// 		created by randomly mutating sequences with lowest bin count
	// up to you to determine how many seq in population
	// What percentage die each iteration
	// what percentage of the best solutions are new members based on
	// How exactly are new members mutated
	// Are entirely new random sequences introduced? and how often?
	// When does this process stop?

	printf("Best bin count=%d\n", bins);

	return 0;
}
