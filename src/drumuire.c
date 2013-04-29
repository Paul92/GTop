#include "include/inout.h"
#include "include/error.h"
#include "include/maths.h"
#include "include/list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

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
    double orientHz, orientDist;

    readPoint(inputFile, orient_id, &orientDist, &orientHz, NULL);

    struct point *firstPoint=(struct point*)malloc(sizeof(struct point));

    readPoint(inputFile, firstPoint->point_id, &firstPoint->nextDist, 
              &firstPoint->nextHz, NULL);

    points = firstPoint;

    readPoint(inputFile, NULL, NULL, NULL, NULL);
    fscanf(inputFile, "%s", line);
//actually make all argument optional. I don't like dummys. This is for the
//first stop

//here goes some error checking, based on return value of readPoint

    double alpha;
    alpha=(points->nextHz-orientHz);
    alpha=repairAngle(alpha);
    
    double betaSum=0;
    int noOfPoints=0; //so in input file should be n+1 points
                      //station twice

    char beforeCurrent_id[100], afterCurrent_id[100]; //used for error check
    
    while(!feof(inputFile)){
        struct point *newPoint=(struct point*)malloc(sizeof(struct point));
        strcpy(newPoint->point_id, readStation(inputFile));
        if(!feof(inputFile)){

            readPoint(inputFile, beforeCurrent_id, &newPoint->beforeDist, 
                      &newPoint->beforeHz, NULL);

            readPoint(inputFile, afterCurrent_id, &newPoint->nextDist,
                      &newPoint->nextHz, NULL);

            newPoint->beta=(newPoint->beforeHz-newPoint->nextHz);
            newPoint->beta=repairAngle(newPoint->beta);

            betaSum+=newPoint->beta;

            readPoint(inputFile, NULL, NULL, NULL, NULL);    //check for stop
                                            //and for other damn errors

            fscanf(inputFile, "%s", line);  //skip newline
            addPoint(points, newPoint);
            noOfPoints++;
        }
    }

    betaSum-=alpha;
    double epsBeta = betaSum - 200*(noOfPoints-2);

    printf("Pe unghiurile interioare ai avut o eroare de %lf grade\n", epsBeta);
    printf("Vrei sa continui? (y/n) ");
    char accept;
    
    fscanf(stdin, " %c", &accept);
    if(!(accept=='y' || accept=='Y')){
        printf("Ai ales sa nu continui.\n");
        exit(EXIT_SUCCESS);
    }

    double CTbeta = -epsBeta;
    double CUbeta = CTbeta / noOfPoints;   //right?

    subtractAlpha(points, alpha);
    correctBeta(points, CUbeta);

    double th = theta(stationX, stationY, orientX, orientY);
    th = roundFirstDecimal(th);
    
    points->theta = th+alpha;
    computeThetas(points, points->next);

    printList(points);
    return 0;

}
