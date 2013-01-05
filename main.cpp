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

            readPoint(inputFile, orient_id, orientHz, orientDist);

            cout<<"Coordonata X a punctului de orientare ";
            cout<<orient_id<<" este: ";
            orientX=readNumber(stdin);

            cout<<"Coordonata Y a punctului de orientare ";
            cout<<orient_id<<" este: ";
            orientY=readNumber(stdin);

            long long th=theta(stationX, stationY, orientX, orientY);

            while(readPoint(inputFile, point_id, dist, hz)){
                if(strcmp(point_id, "9999")!=0 && dist==0 && hz==0){
                    long long orien=orientation(th, omega(orientHz, hz));
                    long long pointX=absoluteX(relativeX(dist, orien), stationX);
                    long long pointY=absoluteY(relativeY(dist, orien), stationY);
                }
            }
        }
    }

    return 0;
    
}

