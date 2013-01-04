#include<cmath>
#include"maths.h"
#define PI 3.1415926535897932384626433

using namespace std;

long long roundFirstDecimal(long double x){

    long long p=x*10;

    if(p%10>=5){
        x++;
    }

    return x;

}

long long degToRad(long long x){

    return roundFirstDecimal(PI*x/180);

}

long long graToRad(long long x){

    return roundFirstDecimal(PI*x/200);

}

long long radToDeg(long long x){

    return roundFirstDecimal(180*x/PI);

}

long long radToGra(long long x){

    return roundFirstDecimal(200*x/PI);

}

