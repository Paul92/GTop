#include "include/inout.h"
#include "include/maths.h"
#include "include/error.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern long long errors;

int radiere(int argc, char **argv){

    char* inputFileName=argv[1];
    char* outputFileName=argv[2];

    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "w");

    char line[MAX_LINE];
    char point_id[100];
    double dist, hz, hv;

    double stationX, stationY, stationHeight;
    double orientX, orientY, orientHz, orientDist, orientHv;
    char orient_id[100];

    while(!feof(inputFile)){
        char* station_id=readStation(inputFile);
        if(!feof(inputFile)){

            printf("STATION ID: %s\n", station_id);

            printf("Coordonata X a statiei %s este: ", station_id);
            fscanf(stdin, "%s", line);
            stationX=readNumber(line);

            printf("Coordonata Y a statiei %s este: ", station_id);
            fscanf(stdin, "%s", line);
            stationY=readNumber(line);

            printf("Coordonata Z a statiei %s este: ", station_id);
            fscanf(stdin, "%s", line);
            stationHeight=readNumber(line);

            printPoint(outputFile, station_id, stationX, stationY, stationHeight);

            readPoint(inputFile, orient_id, &orientDist, &orientHz, &orientHv);


            printf("Coordonata X a punctului de orientare %s este: ", orient_id);
            fscanf(stdin, "%s", line);
            orientX=readNumber(line);

            printf("Coordonata Y a punctului de orientare %s este: ", orient_id);
            fscanf(stdin, "%s", line);
            orientY=readNumber(line);

            printPoint(outputFile, orient_id, orientX, orientY, orientHv);
            fprintf(outputFile, "\n");

            if(orientDist==NOT_FOUND || orientHz==NOT_FOUND){
                errors=errors | (1<<5);
            }
           
            if(!checkErrors())
                printf("%s\n", orient_id);

            double th=theta(stationX, stationY, orientX, orientY);

            while(int ok=readPoint(inputFile, point_id, &dist, &hz, &hv)){
                if(ok){
                    if(dist==NOT_FOUND || hz==NOT_FOUND){
                        errors=errors | (1<<5);
                    }
                    double orien=orientation(th, omega(orientHz, hz));
                    double pointX=absoluteX(relativeX(dist, orien), stationX);
                    double pointY=absoluteY(relativeY(dist, orien), stationY);

                    double pointHeight=height(stationHeight, dist, hv);

                    if(checkErrors()){
                        printPoint(outputFile, point_id, pointX, pointY, pointHeight);
                    }else
                        printf("%s\n", point_id);
                    clearErrorBuff();
                }
            }
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
    
}
