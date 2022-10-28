#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "country.h"
#include "analysis.h"

int main() {
	processInput();
	int *** country = generateCountry();

	clock_t start = clock();

	// analyzeCities(country);
	// analyzeRegions(country);
	analyzeCountry(country);

	clock_t end = clock();
	double elapsedTime = ((double) (end - start))/CLOCKS_PER_SEC;

	printf("O processamento levou %.2f segundos.\n", elapsedTime);

	destroyCountry(&country);

	return 0;
}