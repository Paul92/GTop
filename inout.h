#include<string>
#include<cstdio>

char* readStation(FILE *f);
int readPoint(FILE *f, char[100], long long &, long long &);
long long readNumber(FILE *f);
void printPoint(FILE *f, char[100], long long, long long);
