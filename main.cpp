#include "inout.h"
#include "maths.h"
#include<iostream>
#include<cstdlib>
#include<cstring>

using namespace std;

int main(int argc, char **argv){

    char* inputFileName=argv[1];

    FILE *inputFile=fopen(inputFileName, "r");

    char point_id[100], station_id[100];
    long long dist, hz;

    long long stationCoordX, stationCoordY;

    while(!feof(inputFile)){
        char* station_id=readStation(inputFile);
        if(!feof(inputFile)){

            cout<<"Coordonata X a statiei "<<station_id<<" este: ";
            stationCoordX=readNumber(stdin);

            cout<<"Coordonata Y a statiei "<<station_id<<" este: ";
            stationCoordY=readNumber(stdin);

            while(readPoint(inputFile, point_id, dist, hz)){
                cout<<point_id<<' '<<dist<<' '<<hz<<'\n';
            }
        }
    }

    return 0;

}

