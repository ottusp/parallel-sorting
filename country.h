#ifndef COUNTRY_H
#define COUNTRY_H

#define GRADE_THRESHOLD 100

int r, c, a;
int seed;

void processInput();

int *** generateCountry();

void destroyArray(int ** array);

void destroyCountry(int **** country);

int * regionToArray(int ** region);

int * countryToArray(int *** country);

void printArray(int * array, int size);

void printCountry(int *** country);

#endif