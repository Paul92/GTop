#include "include/inout.h"
#include "include/error.h"
#include "include/maths.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern double errors;

struct point{
    char point_id[100];
    double nextDist;
    double nextHz;
    double beforeHz;
    double beforeDist;
    double beta;
    double theta;      //between this point and the next one
    struct point* next;
    struct point* before;
};

void nodeInit(struct point *node){
    node->next=NULL;
    node->before=NULL;
}

void addElement(struct point *node, struct point *data){
    
    while(node->next!=NULL){
        addElement(node->next, data);
    }
    node->next=data;
    data->before=node;
}

int drumuire(int argc, char **argv){

    char* inputFileName=argv[1];
    char* outputFileName=argv[2];

    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "w");

    struct point *points=(struct point*)malloc(sizeof(struct point));

    char line[100];
    int errors=0;

    double stationX, stationY, orientX, orientY;

    char* station_id;
    station_id=readStation(inputFile);

    printf("Coordonata X a statiei de plecare %s este: ", station_id);
    fscanf(stdin, "%s", line);
    stationX=readNumber(line);

    printf("Coordonata Y a statiei de plecare %s este: ", station_id);
    fscanf(stdin, "%s", line);
    stationY=readNumber(line);

    strcpy(station_id, points->point_id);

    printf("Coordonata X a bornei de orientare este: ");
    fscanf(stdin, "%s", line);
    orientX=readNumber(line);

    printf("Coordonata Y a bornei de orientare este: ");
    fscanf(stdin, "%s", line);
    orientY=readNumber(line);

    char orient_id[100];
    double orientHz;

    readPoint(inputFile, orient_id, orientHz);

    struct point *firstPoint=(struct point*)malloc(sizeof(struct point));

    readPoint(inputFile, firstPoint->point_id, &firstPoint->beforeDist, 
              &firstPoint->nextHz);
// hv is optional argument

    readPoint(inputFile);
//actually make all argument optional. I don't like dummys. This is for the
//first stop

//here goes some error checking, based on return value of readPoint

    double alpha;
    alpha=abs(points->nextHz-orientHz);
    alpha=repairAngle(alpha);

    double betaSum=0;

    char beforeCurrent_id[100], afterCurrent_id[100]; //used for error check

    while(!feof(inputFile)){
        struct point *newPoint=(struct point*)malloc(sizeof(struct point));
        newPoint->point_id=readStation(inputFile);
        if(!feof(inputFile)){
            
            readPoint(inputFile, beforeCurrent_id, &newPoint->beforeDist, 
                      &newPoint->beforeHz);
            
            readPoint(inputFile, afterCurrent_id, &newPoint->nextDist,
                      &newPoint->nextHz);
            
            newPoint->beta=abs(newPoint->beforeHz-newPoint->nextHz);
            newPoint->beta=repairAngle(newPoint->beta);

            betaSum+=newPoint->beta;

            count+=readPoint(inputFile);    //check for stop
                                            //and for other damn errors
            addElement(points, newPoint);
        }
    }


    return 0;

}
