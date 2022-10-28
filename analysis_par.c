#include "analysis.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "country.h"

int * countingSort(int * array, int size) {
	int * frequency = (int *) calloc((GRADE_THRESHOLD + 1), sizeof(int));

	for (int i = 0; i < size; i++) {
		frequency[array[i]]++;
	}
	
	return frequency;
}

int getWorstGrade(int * frequency) {
	for (int i = 0; i < GRADE_THRESHOLD + 1; i++) {
		if(frequency[i] > 0) {
			return i;
		}
	}

	return -1;
}

int getBestGrade(int * frequency) {
	for (int i = GRADE_THRESHOLD; i >= 0; i--) {
		if(frequency[i] > 0) {
			return i;
		}
	}

	return -1;
}

float getMedianGrade(int * frequency, int originalSize) {
	float sum = 0;
	int lastNonBlank = 0;
	for (int i = 0; i < GRADE_THRESHOLD + 1; i++) {
		sum += frequency[i];

		if(sum > ((float) originalSize / 2)) {
			if(originalSize % 2 == 0) {
				return ((float) (lastNonBlank + i)) / 2;
			}
			return i;
		}

		if(frequency[i] != 0) {
			lastNonBlank = i;
		}
	}

	return -1;
}

float getMean(int * frequency, long long originalSize) {
	long long sum = 0;

	for (int i = 0; i < GRADE_THRESHOLD + 1; i++) {
		sum += frequency[i] * i;
	}
	
	return sum / originalSize;
}

float getStdDev(int * frequency, float mean, int originalSize) {
	float sum = 0;

	for (int i = 0; i < GRADE_THRESHOLD + 1; i++) {
		float part = i - mean;
		float partSquared = part * part;
		sum += partSquared * frequency[i];
	}
	
	return sqrt(sum / (originalSize - 1));
}



float * getCityAnalysis(int * city) {
	int * frequency = countingSort(city, a);

	float * report = (float *) malloc(5 * sizeof(float));

	report[0] = getWorstGrade(frequency);
	report[1] = getBestGrade(frequency);
	report[2] = getMedianGrade(frequency, a);

	report[3] = getMean(frequency, a);
	report[4] = getStdDev(frequency, report[3], a);

	destroyArray(&frequency);

	return report;
}

float *** initCitiesReport() {
	float *** citiesReport = (float ***) malloc(r * sizeof(float **));

	for (int i = 0; i < r; i++) {
		citiesReport[i] = (float **) malloc(c * sizeof(float *));
	}

	return citiesReport;
}

void printCityReport(float * cityReport, int region, int city) {
	printf("Reg %d - Cid %d: ", region, city);
	printf("menor: %.0f, maior: %.0f, mediana: %.2f, média: %.2f, DP: %.2f\n", 
		cityReport[0], cityReport[1], cityReport[2], cityReport[3], cityReport[4]);
}

void printCitiesReport(float *** citiesReport) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printCityReport(citiesReport[i][j], i, j);
		}
		printf("\n");
	}
}

void destroyCitiesReport(float **** citiesReport) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			free((*citiesReport)[i][j]);
		}

		free((*citiesReport)[i]);
	}

	free(*citiesReport);
	*citiesReport = NULL;
}

void analyzeCities(int *** country) {
	float *** citiesReport = initCitiesReport();

	#pragma omp parallel for
	for (int i = 0; i < r; i++) {
		#pragma omp parallel for
		for (int j = 0; j < c; j++) {
			citiesReport[i][j] = getCityAnalysis(country[i][j]);
		}
	}

	printCitiesReport(citiesReport);
	destroyCitiesReport(&citiesReport);
}



float * getRegionAnalysis(int ** region) {
	int size = c * a;

	int * regionArray = regionToArray(region);
	int * frequency = countingSort(regionArray, size);

	float * report = (float *) malloc(5 * sizeof(float));

	report[0] = getWorstGrade(frequency);
	report[1] = getBestGrade(frequency);
	report[2] = getMedianGrade(frequency, size);

	report[3] = getMean(frequency, size);
	report[4] = getStdDev(frequency, report[3], size);

	destroyArray(&regionArray);
	destroyArray(&frequency);

	return report;
}

float ** initRegionsReport() {
	float ** regionsReport = (float **) malloc(r * sizeof(float *));

	return regionsReport;
}

void printRegionReport(float * regionReport, int region) {
	printf("Reg %d: ", region);
	printf("menor: %.0f, maior: %.0f, mediana: %.2f, média: %.2f, DP: %.2f\n", 
		regionReport[0], regionReport[1], regionReport[2], regionReport[3], regionReport[4]);
}

void printRegionsReport(float ** regionsReport) {
	for (int i = 0; i < r; i++) {
		printRegionReport(regionsReport[i], i);
	}
	printf("\n");
}

void destroyRegionsReport(float *** regionsReport) {
	for (int i = 0; i < r; i++) {
		free((*regionsReport)[i]);
	}

	free(*regionsReport);
	*regionsReport = NULL;
}

void analyzeRegions(int *** country) {
	float ** regionsReport = initRegionsReport();
	for (int i = 0; i < r; i++) {
		regionsReport[i] = getRegionAnalysis(country[i]);
	}

	printRegionsReport(regionsReport);
	destroyRegionsReport(&regionsReport);
}



float * getCountryAnalysis(int *** country) {
	int size = r * c * a;

	int * countryArray = countryToArray(country);
	int * frequency = countingSort(countryArray, size);

	float * report = (float *) malloc(5 * sizeof(float));

	report[0] = getWorstGrade(frequency);
	report[1] = getBestGrade(frequency);
	report[2] = getMedianGrade(frequency, size);

	report[3] = getMean(frequency, size);
	report[4] = getStdDev(frequency, report[3], size);

	destroyArray(&countryArray);
	destroyArray(&frequency);

	return report;
}

void printCountryReport(float * countryReport) {
	printf("Brasil: ");
	printf("menor: %.0f, maior: %.0f, mediana: %.2f, média: %.2f, DP: %.2f\n", 
		countryReport[0], countryReport[1], countryReport[2], countryReport[3], countryReport[4]);
}

void destroyCountryReport(float ** countryReport) {
	free(*countryReport);
	*countryReport = NULL;
}

void analyzeCountry(int *** country) {
	float * countryReport = getCountryAnalysis(country);

	printCountryReport(countryReport);
	destroyCountryReport(&countryReport);
}
