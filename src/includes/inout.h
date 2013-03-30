#include<stdio.h>

#define MAX_LINE 500
#define NOT_FOUND -1

int getLine(FILE*, char[MAX_LINE]);
char* readStation(FILE*);
int readPoint(FILE*, char[100], double*, double*, double*);
double readNumber(char[MAX_LINE]);
void printPoint(FILE*, char[100], double, double, double);

