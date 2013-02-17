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

    char line[MAX_LINE];
    char point_id[100];
    long long dist, hz, hv;

    long long stationX, stationY, stationHeight;
    long long orientX, orientY, orientHz, orientDist, orientHv;
    char orient_id[100];

    int dummy=-1;

    while(!feof(inputFile)){
        char* station_id=readStation(inputFile);
        if(!feof(inputFile)){

            cout<<"STATION ID: "<<station_id<<'\n';

            cout<<"Coordonata X a statiei "<<station_id<<" este: ";
            fscanf(stdin, "%s", line);
            dummy=-1;
            readNumber(line, dummy, stationX);

            cout<<"Coordonata Y a statiei "<<station_id<<" este: ";
            fscanf(stdin, "%s", line);
            dummy=-1;
            readNumber(line, dummy, stationY);

            cout<<"Coordonata Z a statiei "<<station_id<<" este: ";
            fscanf(stdin, "%s", line);
            dummy=-1;
            readNumber(line, dummy, stationHeight);
            
            printPoint(outputFile, station_id, stationX, stationY, stationHeight);

            readPoint(inputFile, orient_id, orientDist, orientHz, orientHv);

            cout<<"Coordonata X a punctului de orientare ";
            cout<<orient_id<<" este: ";
            fscanf(stdin, "%s", line);
            dummy=-1;
            readNumber(line, dummy, orientX);

            cout<<"Coordonata Y a punctului de orientare ";
            cout<<orient_id<<" este: ";
            fscanf(stdin, "%s", line);
            dummy=-1;
            readNumber(line, dummy, orientY);

            printPoint(outputFile, orient_id, orientX, orientY, orientHv);
            fprintf(outputFile, "\n");

            if(orientDist==NOT_FOUND || orientHz==NOT_FOUND){
                errors=errors | (1<<5);
            }
           
            if(!checkErrors())
                printf("%s\n", orient_id);

            long long th=theta(stationX, stationY, orientX, orientY);

            cout<<th<<'\n';

            while(int ok=readPoint(inputFile, point_id, dist, hz, hv)){
                if(ok){
                    if(dist==NOT_FOUND || hz==NOT_FOUND){
                        errors=errors | (1<<5);
                    }
                    cout<<point_id<<' '<<dist<<' '<<hz<<' '<<errors<<'\n';
                    long long orien=orientation(th, omega(orientHz, hz));
                    long long pointX=absoluteX(relativeX(dist, orien), stationX);
                    long long pointY=absoluteY(relativeY(dist, orien), stationY);                  
                    long long pointHeight=height(stationHeight, dist, hv);

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
