/**
 *  Provides some mathematical and topological computations
 *
 *  Date crated: 05.01.2013
 *
 *  Macro constants:
 *      PI - the number pi, with many decimals
 *      precision - values are real values times 10^precision
 *
 *  Functions:
 *      long long roundFirstDecimal(long double x)
 *      Rounds first decimal of x.
 *
 *      long long degToRad(long long x)
 *      Converts x from degrees to radians.
 *
 *      long long graToRad(long long x)
 *      Converts x from grades to radians.
 *
 *      long long radToDeg(long long x)
 *      Converts x from radians to degrees.
 *
 *      long long radToGra(long long x)
 *      Converts x from radians to grades.
 *
 *      long long theta(long long stationX, long long stationY,
 *                      long long orientX,  long long orientY)
 *      Computes theta angle between station located at coordinates 
 *  stationX, stationY and orientation point located at coordinates
 *  orientX, orientY.
 *
 *      long long orientation(long long theta, long long omega)
 *      Computes orientation of a point.
 *
 *      long long relativeX(long long dist, long long orientation)
 *      Computes relative position X of a point, based on distance and
 *  orientation.
 *
 *      long long relativeY(long long dist, long long orientation)
 *      Computes relative position y of a point, based on distance and
 *  orientation.
 *      
 *      long long absoluteX(long long relativeX, long long stationX)
 *      Computes absolute position X of a point, based on his relative
 *  X position and the X position of station.
 *
 *      long long absoluteY(long long relativeY, long long stationY)
 *      Computes absolute position Y of a point, based on his relative
 *  Y position and the Y position of station.
 */

#include<cmath>
#include"maths.h"
#include"error.h"
#include<iostream>

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

long double degToRad(long long x){
    return (long double)x*PI/180.;
}

long double graToRad(long long x){
    return (long double)x*PI/200.;
}

long double radToDeg(long long x){
    return (long double)x*180./PI;
}

long double radToGra(long double x){
    return (long double)x*200./PI; 
}

long long theta(long long stationX, long long stationY, 
                long long orientX,  long long orientY){

    long long top=orientY-stationY;
    long long bot=orientX-stationX;
 
    long long theta;

    if (bot==0){
      if (orientY > stationY)
	theta=100*pow(10., precision);
      else
	theta=300*pow(10., precision);
      return theta;
    }

    long double fraction=(long double)top/bot;

    long double alpha=atan(fraction);
    alpha*=pow(10., precision);
    alpha=roundFirstDecimal(radToGra(alpha));

    if(alpha<0) 
      alpha*=(-1);

    if(top>=0 && bot>0){
        theta=alpha;
    }else if(top<0 && bot>0){
        theta=400*pow(10., precision)-alpha;
    }else if(top>=0 && bot<0){
        theta=200*pow(10., precision)-alpha;
    }else if(top<0 && bot<0){
        theta=200*pow(10., precision)+alpha;
    }
    return theta;    
}

long long omega(long long orientHz, long long pointHz){
    long long diff=orientHz-pointHz;
    if(diff<0)
        diff+=400*pow(10., precision);
    return diff;
}

long long orientation(long long theta, long long omega){
	long long orientation=theta-omega;
	if(orientation<0)
		orientation+=400*pow(10., precision);
	return orientation;  
}

long long relativeX(long long dist, long long orientation){	
    return roundFirstDecimal(dist*cos(graToRad(orientation)/pow(10., precision)));
}

long long relativeY(long long dist, long long orientation){
    return roundFirstDecimal(dist*sin(graToRad(orientation)/pow(10., precision)));
}

long long absoluteX(long long relativeX, long long stationX){
    return relativeX+stationX;
}

long long absoluteY(long long relativeY, long long stationY){
    return relativeY+stationY;
}

long long height(long long stationHeight, long long distance, long long hv){

    if(hv>=0){
        long long phi=100*pow(10., precision)-hv;
        return distance*tan(graToRad(phi)/pow(10., precision))+stationHeight;
    }else{
        return -1;
    }

}
