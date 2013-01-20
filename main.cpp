#include "inout.h"
#include "maths.h"
#include "error.h"
#include<iostream>
#include<cstdlib>
#include<cstring>

extern long long errors;

using namespace std;

int main(int argc, char **argv){

    char* inputFileName=argv[1];
    char* outputFileName=argv[2];

    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "w");

    char point_id[100];
    long long dist, hz;

    long long stationX, stationY;
    long long orientX, orientY, orientHz, orientDist;
    char orient_id[100];

    while(!feof(inputFile)){
        char* station_id=readStation(inputFile);
        if(!feof(inputFile)){

            cout<<"Coordonata X a statiei "<<station_id<<" este: ";
            stationX=readNumber(stdin);

            cout<<"Coordonata Y a statiei "<<station_id<<" este: ";
            stationY=readNumber(stdin);

            printPoint(outputFile, station_id, stationX, stationY);

            readPoint(inputFile, orient_id, orientDist, orientHz);

            cout<<"Coordonata X a punctului de orientare ";
            cout<<orient_id<<" este: ";
            orientX=readNumber(stdin);

            cout<<"Coordonata Y a punctului de orientare ";
            cout<<orient_id<<" este: ";
            orientY=readNumber(stdin);

            printPoint(outputFile, orient_id, orientX, orientY);
            fprintf(outputFile, "\n");

            long long th=theta(stationX, stationY, orientX, orientY);

            while(int ok=readPoint(inputFile, point_id, dist, hz)){
                if(ok){
                    long long orien=orientation(th, omega(orientHz, hz));
                    long long pointX=absoluteX(relativeX(dist, orien), stationX);
                    long long pointY=absoluteY(relativeY(dist, orien), stationY);
                    if(checkErrors()){
                        printPoint(outputFile, point_id, pointX, pointY);
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
