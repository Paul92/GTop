#include "inout.h"
#include "error.h"
#include "maths.h"

extern long long errors;

using namespace std;

struct point{
    point* before=NULL;
    char point_id[100];
    long long theta;
    point* after=NULL;
    point* orient=NULL;
};

int drumuire(int argc, char **argv){

    char* inputFileName=argv[1];
    char* outputFileName=argv[2];

    FILE *inputFile=fopen(inputFileName, "r");
    FILE *outputFile=fopen(outputFileName, "w");

    char line[MAX_LINE];
    char point_id[100];
    long long dist, hz;

    

}
