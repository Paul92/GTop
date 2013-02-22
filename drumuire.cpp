#include "inout.h"
#include "error.h"
#include "maths.h"

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

    char lastPoint_id[100];
    char currentPoint_id[100];

    long long count;

    while(!feof(inputFile)){
        points[pointsIndex].point_id=readStation(inputFile);
        if(!feof(inputFile)){
            count=0;
            if(pointsIndex>0 && strcmp(currentPoint_id, points[pointsIndex].point_id)!=0)
                errors=errors|(1<<6);
            count+=readPoint(inputFile, currentPoint_id, 
                      points[pointsIndex].beforeDist, points[pointsIndex].beforeHz, dummy);
            pointsIndex++;
            if(pointsIndex>0 && strcmp(currentPoint_id, points[pointsIndex-1].point_id)!=0)
                errors=errors|(1<<6);
            count+=readPoint(inputFile, currentPoint_id,
                      points[pointsIndex].nextDist, points[pointsIndex].nextHz, dummy);
            pointsIndex++;
            count+=readPoint(inputFile, currentPoint_id, dummy, dummy);
            if(count!=2){
                errors=errors|(1<<7);
            }
        }
    }

    

}
