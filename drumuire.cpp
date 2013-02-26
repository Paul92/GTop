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
    long long beta;
};

int drumuire(int argc, char **argv){

    char* inputFileName=argv[1];
    char* outputFileName=argv[2];

    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "w");

    char line[MAX_LINE];
    char point_id[100];
    long long dist, hz;

    point points[100];
    int pointsIndex=1;

    long long dummy=0;
    char dummyChar[100];

    char currentPoint_id[100];

    long long count;

    point orient;

    char* station_id;
    station_id=readStation(inputFile);
    strcpy(points[0].point_id, station_id);
    count+=readPoint(inputFile, currentPointId, orient.beforeDist, orient.beforeHz, dummy);
    strcpy(orient.point_id, currentPointId);
    count+=readPoint(inputFile, currentPointId, points[0].afterDist, points[0].afterHz, dummy);
    count+=readPoint(inputfile, currentPointId, dummy, dummy, dummy);

    if(count!=2)
        errors=errors|(1<<7);

    long long alpha;
    alpha=abs(points[0].afterHz, orient.beforeHz);
    repairAngle(alpha);

    while(!feof(inputFile)){
        station_id=readStation(inputFile);
        if(!feof(inputFile)){
            strcpy(points[pointsIndex].point_id, station_id);
            count=0;

            if(pointsIndex>0 && strcmp(currentPoint_id, points[pointsIndex].point_id)!=0)
                errors=errors|(1<<6);
            count+=readPoint(inputFile, currentPoint_id, 
                      points[pointsIndex].beforeDist, points[pointsIndex].beforeHz, dummy);
            
            if(pointsIndex>0 && strcmp(currentPoint_id, points[pointsIndex-1].point_id)!=0)
                errors=errors|(1<<6);
            count+=readPoint(inputFile, currentPoint_id,
                      points[pointsIndex].nextDist, points[pointsIndex].nextHz, dummy);
            
            points[pointsIndex].beta=abs(points[pointsIndex].beforeHz-points[pointsIndex].afterHz);
            repairAngle(points[pointIndex].beta);

            pointsIndex++;
            count+=readPoint(inputFile, dummyChar, dummy, dummy, dummy);
            if(count!=2){
                errors=errors|(1<<7);
            }
        }
    }



    return 0;

}
