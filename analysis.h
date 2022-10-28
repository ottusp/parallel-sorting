#ifndef ANALYSIS_H
#define ANALYSIS_H

int * countingSort(int * array, int size);



int getWorstGrade(int * frequency);

int getBestGrade(int * frequency);

float getMedianGrade(int * frequency, int originalSize);

float getMean(int * frequency, long long originalSize);

float getStdDev(int * frequency, float mean, int originalSize);



float * getCityAnalysis(int * city);

float *** initCitiesReport();

void printCityReport(float * cityReport, int region, int city);

void printCitiesReport(float *** citiesReport);

void destroyCitiesReport(float **** citiesReport);

void analyzeCities(int *** country);



float * getRegionAnalysis(int ** region);

float ** initRegionsReport();

void printRegionReport(float * regionReport, int region);

void printRegionsReport(float ** regionsReport);

void destroyRegionsReport(float *** regionsReport);

void analyzeRegions(int *** country);



float * getCountryAnalysis(int *** country);

float ** initCountryReport();

void printCountryReport(float * countryReport);

void destroyCountryReport(float ** countryReport);

void analyzeCountry(int *** country);

#endif