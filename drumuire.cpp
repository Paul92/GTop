#include "inout.h"
#include "error.h"
#include "maths.h"
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<cstdio>

extern long long errors;

using namespace std;


struct point{
    char point_id[100];
    long long nextDist;
    long long nextHz;
    long long beforeDist;
    long long beforeHz;
    long long theta;
};

void printPoints(point a[100], int n){

    cout<<"A"<<n;

    for(int i=0; i<n; i++){
        cout<<i;
        cout<<a[i].point_id;//<<' '<<a[i].nextDist<<' '<<a[i].nextHz<<'\n';
    }

}

void copy(char dest[100], char a[100]){
    int i=0;
    do{
        dest[i]=a[i];
        i++;

    }while(a[i]!=0);

}

int drumuire(int argc, char **argv){

    char* inputFileName=argv[1];
    char* outputFileName=argv[2];

    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "w");

    char line[MAX_LINE];
    char point_id[100];
    long long dist, hz;

    point points[100];
    int pointsIndex=0;

    long long dummy=0;

    char currentPoint_id[100];

    long long count;

    while(!feof(inputFile)){
        char* station_id=readStation(inputFile);
        if(!feof(inputFile)){
            strcpy(points[pointsIndex].point_id, station_id);
            count=0;
            if(pointsIndex>0 && strcmp(currentPoint_id, points[pointsIndex].point_id)!=0)
                errors=errors|(1<<6);
            count+=readPoint(inputFile, currentPoint_id, 
                      points[pointsIndex].beforeDist, points[pointsIndex].beforeHz, dummy);
            //pointsIndex++;
            if(pointsIndex>0 && strcmp(currentPoint_id, points[pointsIndex-1].point_id)!=0)
                errors=errors|(1<<6);
            count+=readPoint(inputFile, currentPoint_id,
                      points[pointsIndex].nextDist, points[pointsIndex].nextHz, dummy);

            pointsIndex++;
            count+=readPoint(inputFile, currentPoint_id, dummy, dummy, dummy);
            if(count!=2){
                errors=errors|(1<<7);
            }
        }
    }

    for(int i=0; i<pointsIndex-1; i++){
       printf("%s %lld %lld %lld %lld\n", points[i].point_id, points[i].nextDist, points[i].nextHz,
                                            points[i].beforeDist, points[i].beforeHz );
    }


    return 0;

}
