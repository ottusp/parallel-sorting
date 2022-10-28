#include <stdio.h>
#include <stdlib.h>

#include "country.h"

void processInput() {
	scanf("%d %d %d %d", &r, &c, &a, &seed);

	srand(seed);
}

int *** generateCountry() {
	int *** country = (int ***) malloc(r * sizeof(int **));

	for (int i = 0; i < r; i++) {
		country[i] = (int **) malloc(c * sizeof(int *));

		for (int j = 0; j < c; j++) {
			country[i][j] = (int *) malloc(a * sizeof(int));

			for (int k = 0; k < a; k++) {
				country[i][j][k] = rand() % GRADE_THRESHOLD + 1;
			}
		}
	}

	return country;
}

void destroyArray(int ** array) {
	free(*array);

	*array = NULL;
}

void destroyCountry(int **** country) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			free((*country)[i][j]);
		}

		free((*country)[i]);
	}

	free(*country);
	*country = NULL;
}

int * regionToArray(int ** region) {
	int * array = (int *) malloc(c * a * sizeof(int));

	for (int i = 0; i < c; i++) {
		for (int j = 0; j < a; j++) {
			int index = (i * a) + j;
			array[index] = region[i][j];
		}
	}

	return array;
}

int * countryToArray(int *** country) {
	int * array = (int *) malloc(r * c * a * sizeof(int));

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (int k = 0; k < a; k++) {
				int index = (i * c * a) + (j * a) + k;
				array[index] = country[i][j][k];
			}
		}
	}

	return array;
}

void printArray(int * array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void printCountry(int *** country) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			for (int k = 0; k < a; k++) {
				printf("%d ", country[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
}