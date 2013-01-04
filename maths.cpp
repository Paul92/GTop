#include<cmath>
#include"maths.h"

#define PI 3.1415926535897932384626433
#define precision 4

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


long long theta(long long stationX, long long stationY, 
                long long orientX,  long long orientY){

    long long top=orientY-stationY;
    long long bot=orientX-stationX;

    long long alpha=roundFirstDecimal(atan2((long double)top, (long double)bot));
    alpha*=pow(10, precision);

    long long theta;
    if(top>=0 && bot>=0){
        theta=alpha;
    }else if(top<0 && bot>=0){
        theta=400-alpha;
    }else if(top=>0 && top<0){
        theta=200-alpha;
    }else if(top<0 && bot<0){
        theta=200+alpha;
    }

    return theta;
}


