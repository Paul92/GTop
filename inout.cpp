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
#include<string>
#include<cstdio>
#include<fstream>

#define EOS 0 //End Of Station

using namespace std;

FILE *f;

void init(string filename){
    f=fopen(filename.c_str(), "r");
}

int readStation(){
    int station_id;
    fscanf(f, "%d", &station_id);
    return station_id;
}

int atoi(char a){
    return a-48;
}

long long readNumber(){

    long long nr=0;

    char a=0;
    
    while(!isdigit(a))
        fscanf(f, "%c", &a);

    while(a!='.'){
        nr*=10;
        nr+=atoi(a);
        fscanf(f, "%c", &a);
    }

    int decimals=0;
    fscanf(f, "%c", &a);

    while(isdigit(a)){
        decimals++;
        nr*=10;
        nr+=atoi(a);
        fscanf(f, "%c", &a);
    }

    while(decimals++<4)
        nr*=10;

    return nr;
}

int readPoint(string &point_id, long long &distance, long long &hz){

    char point_idC[100];
    fscanf(f, "%s", point_idC);
    point_id=point_idC;
    
    distance=readNumber();
    hz=readNumber();

    if(point_id=="9999" && distance==0 && hz==0)
        return 0;
    else
        return 1;

}

