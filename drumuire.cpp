#include "inout.h"
#include "error.h"
#include "maths.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern double errors;

struct point{
    char point_id[100];
    double nextDist;
    double nextHz;
    double beforeDist;
    double beforeHz;
    double beta;
    double theta;      //between this point and the next one
};

int drumuire(int argc, char **argv){

    char* inputFileName=argv[1];
    char* outputFileName=argv[2];

    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "w");

    point points[100];
    int pointsIndex=1;

    char dummyChar[100];
    char line[100];

    double stationX, stationY, orientX, orientY;

    printf("Coordonata X a statiei de plecare %s este: ", stationX);
    fscanf(stdin, "%s", line);
    stationX=readNumber(line);

    printf("Coordonata Y a statiei de plecare %s este: ", stationY);
    fscanf(stdin, "%s", line);
    stationY=readNumber(line);

    printf("Coordonata X a bornei de orientare %s este: ", orientX);
    fscanf(stdin, "%s", line);
    orientX=readNumber(line);

    printf("Coordonata Y a bornei de orientare %s este: ", orientY);
    fscanf(stdin, "%s", line);
    orientY=readNumber(line);

    char currentPoint_id[100];

    int count=0;
    double dummy;

    point orient;

    char* station_id;
    station_id=readStation(inputFile);
    strcpy(points[0].point_id, station_id);
    count+=readPoint(inputFile, currentPoint_id, orient.beforeDist, orient.beforeHz, dummy);
    strcpy(orient.point_id, currentPoint_id);
    count+=readPoint(inputFile, currentPoint_id, points[0].nextDist, points[0].nextHz, dummy);
    count+=readPoint(inputFile, currentPoint_id, dummy, dummy, dummy);

    if(count!=2)
        errors=errors|(1<<7);

    double alpha;
    alpha=abs(points[0].nextHz-orient.beforeHz);
    alpha=repairAngle(alpha);

    double betaSum=0;
    
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
            
            points[pointsIndex].beta=abs(points[pointsIndex].beforeHz-points[pointsIndex].nextHz);
            points[pointsIndex].beta=repairAngle(points[pointsIndex].beta);

            betaSum+=points[pointsIndex].beta;

            pointsIndex++;
            count+=readPoint(inputFile, dummyChar, dummy, dummy, dummy);
            if(count!=2){
                errors=errors|(1<<7);
            }
        }
    }

    for(int i=0; i<pointsIndex; i++){
            cout<<points[i].point_id<<' '<<points[i].beta<<'\n';
    }


/*    points[0].beforeDist=points[pointsIndex-1].nextDist;
    points[0].beforeHz=points[pointsIndex-1].nextHz;
    points[0].beta=abs(points[0].beforeHz-points[0].nextHz);
    points[0].beta=repairAngle(points[0].beta);

    double correction=200*(pointsIndex-2)-betaSum;

    double th=theta(stationX, stationY, orientX, orientY);
    points[0].theta=ac+alpha;

    for(int i=0; i<pointsIndex; i++){
        points[i].beta+=correction;
    }
*/
    return 0;

}
