/**
 *  Handles input and output
 *
 *  Date created: 05.01.2013
 *
 *  Macro constants:
 *      EOS - End Of Station. Value is 0.
 *      precision - values are real values times 10^precision
 *
 *  Functions:
 *      
 *      int getline(FILE *f, char line[LINE_MAX])
 *      Reads a line form the file f. A line ends at /n character or at the end
 *  of the file.
 *
 *      char *readStation(FILE *f)
 *      Reads a station id from file f and returns a pointer to it.
 *
 *      int atoi(char a)
 *      Returns integer value of digit expressed by char a.
 *
 *      bool isblank(char a)
 *      Returns false if a<=32, true otherwise. All blank characters have 
 *  values smaller than 32, but they ar not the only. BE CAUTIOS!
 *
 *      long long readNumber(FILE *f)
 *      Reads from file f a floating point number as a long long. 
 *      The last precision digits are decimals. 
 *      Acutally, his value is equal with Xe4, where X is the number read.
 *
 *      int readPoint(FILE *F, char point_id[100], 
 *                    long long &distance, long long &hz)
 *      Reads new point data from file f. 
 *      If the point is valid, returns 1, else returns EOS.
 *
 *      string itoa(long long nr)
 *      Converts nr to a string.
 *
 *      void printPoint(FILE *f, char point_id[100], 
 *                      long long absoluteX, long long absoluteY)
 *      Prints in file f point_id, absoluteX, absoluteY in this order, separed 
 *  by a whitespace.
**/

#include "./include/inout.h"
#include "include/error.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define EOS 0 //End Of Station
#define precision 4

int getLine(FILE *f, char line[MAX_LINE]){

    int i=0;
    while(!feof(f)){
        fscanf(f, "%c", &line[i++]);
        if(line[i-1]=='\n')
            break;
    }

    line[--i]='\0';

    return i;
}

int isBlank(char a){

    if(a==' ' || a=='\t')
        return 1;
    return 0;

}

char* readStation(FILE *f){

    static char station_id[100];
    char temp[100];
    getLine(f, temp);

    int i=0;

    do{
        station_id[i]=temp[i];
    }while(temp[++i] && !isBlank(temp[i]));
    station_id[i]='\0';

    return station_id;
}

double readNumber(char line[MAX_LINE]){

    //check for errors
    double number;
    sscanf(line, "%lf", &number);
    return number;

}

int readPoint(FILE *f, char point_id[100], 
              double *distance, double *hz, double *hv){

    char line[MAX_LINE];
    getLine(f, line);

    *distance=NOT_FOUND;
    *hz=NOT_FOUND;
    *hv=NOT_FOUND;

    sscanf(line, "%s %lf %lf %lf", distance, hz, hv);

    //TO DO: error checking

    if(!strcmp(point_id, "9999") && *distance==0 && *hz==0)
        return 0;
    else 
        return 1;
}

void printPoint(FILE *f, char point_id[100], 
                double absoluteX, double absoluteY, double height){

    fprintf(f, "%s %lf %lf", point_id, absoluteX, absoluteY);
    if(height>=0){
        fprintf(f, " %lf\n", height);
    }

}
