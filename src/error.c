#include "include/error.h"
#include <stdio.h>

void bizzareChars(){
    fprintf(stderr, "%s", "Bizarre characters at point: ");
}

void negativeValue(){
    fprintf(stderr, "%s", "Negative value at point: ");
}

void zeroValue(){
    fprintf(stderr, "%s", "Zero distance at point: ");
}

void angleTooBig(){
    fprintf(stderr, "%s", "Angle exceeding 400 at point: ");
}

void notEnoughArgs(){
    fprintf(stderr, "%s", "Not enough arguments at point: ");
}

void tooManyArgs(){
    fprintf(stderr, "%s", "Too many arguments at point: ");
}

void clearErrorBuff(){
//    errors=0;
}
