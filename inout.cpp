/**
 *  Handles input and output
 *
 *  Macro constants:
 *      EOS - End Of Station. Value is 0.
 *
 *  Functions:
 *      void init(string filename)
 *      Opens filename file; stream redirected to cin
 *
 *      int readStation()
 *      Reads and returns a new station id
 *
 *      long long readNumber()
 *      Reads a floating point number as a long long. 
 *      The last 4 digits are decimals. 
 *      Acutally, his value is equal with Xe4, where X is the number read.
 *
 *      int readPoint(string &point_id, double &distance, double &hz)
 *      Reads new point data. 
 *      If the point is valid, returns 1, else returns EOS.
**/

#include "inout.h"
#include<iostream>
#include<cstdio>
#include<cstring>

#define EOS 0 //End Of Station
#define precision 4

using namespace std;

char* readStation(FILE *f){
    
    static char station_id[100];
    fscanf(f, "%s", station_id);
   
    if(!feof(f))
        cout<<"STATION ID: "<<station_id<<'\n';
    
    return station_id;
}

int atoi(char a){
    return a-48;
}

long long readNumber(FILE *f){

    long long nr=0;

    char a=0;
    
    while(!isdigit(a))
        fscanf(f, "%c", &a);

    while(a!='.' && a!=' ' && a!='\t' && a!='\n'){
        nr*=10;
        nr+=atoi(a);
        fscanf(f, "%c", &a);
    }

    if(a==' ' || a=='\t' || a=='\n')
        return nr;

    int decimals=0;
    fscanf(f, "%c", &a);

    while(isdigit(a)){
        decimals++;
        nr*=10;
        nr+=atoi(a);
        fscanf(f, "%c", &a);
    }

    while(decimals++<precision)
        nr*=10;

    return nr;
}

int readPoint(FILE *f, char point_id[100], long long &distance, long long &hz){

    fscanf(f, "%s", point_id);

    distance=readNumber(f);
    hz=readNumber(f);

    if(!strcmp(point_id, "9999") && distance==0 && hz==0){
        return 0;
    }else{
        return 1;
    }

}

