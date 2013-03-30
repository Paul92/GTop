#include "include/error.h"
#include <stdio.h>

struct errors{

    int foundError;

    void (*bizzareChars)();
    void (*negativeValue)();
    void (*zeroValue)();
    void (*angleTooBig)();
    void (*notEnoughArgs)();
    void (*tooManyArgs)();

};

long long errors=0;

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

struct errors initErrors(struct errors){
    
    errors.foundError=0;

    errors.bizzareChars=bizzareChars;
    errors.negativeValue=negativeValue;
    errors.zeroValue=zeroValue;
    errors.angleTooBig=angleTooBig;
    errors.notEnoughArgs=notEnoughArgs;
    errors.tooManyArgs=tooManyArgs;

    return errors;
}


void clearErrorBuff(){
    errors=0;
}
