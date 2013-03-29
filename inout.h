#include<string>
#include<cstdio>

#define MAX_LINE 500
#define NOT_FOUND -1

int getline(FILE *f, char[MAX_LINE]);
char* readStation(FILE *f);
int readPoint(FILE *f, char[100], double &, double &, double &);
double readNumber(char[MAX_LINE]);
void printPoint(FILE *f, char[100], double, double, double);

