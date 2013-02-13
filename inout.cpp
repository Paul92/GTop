/**
 *  Handles input and output
 *
 *  Date created: 05.01.2013
 *
 *  Macro constants:
 *      EOS - End Of Station. Value is 0.
 *      precision - values are real values times 10^precision
 *
 *  Functions:
 *      char *readStation(FILE *f)
 *      Reads a station id from file f and returns a pointer to it.
 *
 *      int atoi(char a)
 *      Returns integer value of digit expressed by char a.
 *
 *      long long readNumber(FILE *f)
 *      Reads from file f a floating point number as a long long. 
 *      The last precision digits are decimals. 
 *      Acutally, his value is equal with Xe4, where X is the number read.
 *
 *      int readPoint(FILE *F, char point_id[100], 
 *                    long long &distance, long long &hz)
 *      Reads new point data from file f. 
 *      If the point is valid, returns 1, else returns EOS.
 *
 *      void printPoint(FILE *f, char point_id[100], 
 *                      long long absoluteX, long long absoluteY)
 *      Prints in file f point_id, absoluteX, absoluteY in this order, separed 
 *  by a whitespace.
**/

#include "inout.h"
#include "error.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>

#define EOS 0 //End Of Station
#define precision 4

using namespace std;

extern long long errors;

int getline(FILE *f, char line[MAX_LINE]){

    int i=0;
    while(!feof(f)){
        fscanf(f, "%c", &line[i++]);
        if(line[i-1]=='\n')
            break;
    }

    line[--i]='\0';

    return i;
}

char* readStation(FILE *f){

    static char station_id[100];
    getline(f, station_id);

    return station_id;
}

int atoi(char a){
    return a-48;
}

bool isblank(char a){
    if(a==' ' || a=='\t')
        return true;
    return false;
}

void readNumber(char line[MAX_LINE], int &i, long long &number){

    bool dummy=(i==-1);
    number=NOT_FOUND;

    int n=strlen(line);

    if(dummy) i=0;

    for(; i<n && isblank(line[i]); i++);

    if(line[i]=='-' && isdigit(line[i+1]))
        errors=errors | (1<<1);

    bool decimalPoint=false;
    int decimals=0;

    while(!isblank(line[i]) && line[i]!='\0'){
        if(isdigit(line[i])){
            if(number==NOT_FOUND)
                number=0;
            if(decimals<=precision)
                number=number*10+atoi(line[i]);
            decimals+=decimalPoint;
        }else if(line[i]=='.' && !decimalPoint){
            decimalPoint=true;
        }else{
            errors=errors | 1;
        }
        i++;
    }


    while(decimals<precision){
        number*=10;
        decimals++;
    }

    if(dummy) i=0;
}

int readPoint(FILE *f, char point_id[100], 
              long long &distance, long long &hz, long long &hv){

    char line[MAX_LINE];
    int n=getline(f, line);

    int i;

    for(i=0; i<n && isblank(line[i]); i++);

    sscanf(line+i, "%s", point_id);
    i+=strlen(point_id);

    distance=NOT_FOUND;
    hz=NOT_FOUND;
    hv=NOT_FOUND;

    readNumber(line, i, distance);
    readNumber(line, i, hz);
    readNumber(line, i, hv);

    if(!strcmp(point_id, "9999") && distance==0 && hz==0)
        return 0;
    else 
        return 1;
}

string itoa(long long nr){

    string a;
    bool negative=false;
    if(nr<0){
        negative=true;
        nr*=-1;
    }

    while(nr){
        a.push_back((nr%10)+48);
        nr/=10;
    }

    while(a.size()<precision)
        a.push_back('0');

    a.insert(precision, ".");

    string b;
    for(int i=a.size()-1; i>=0; i--)
        b.push_back(a[i]);

    if(negative)
        b.insert(0, "-");

    return b;

}

void printNumber(FILE *f, long long number){

    string num=itoa(number);

    fprintf(f, "%s", num.c_str());

}

void printPoint(FILE *f, char point_id[100], 
                long long absoluteX, long long absoluteY){

    fprintf(f, "%s ", point_id);
    printNumber(f, absoluteX);
    fprintf(f, " ");
    printNumber(f, absoluteY);
    fprintf(f, "\n");

}
