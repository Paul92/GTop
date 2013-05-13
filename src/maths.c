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
 *      double roundFirstDecimal(double x)
 *      Rounds first decimal of x.
 *
 *      double degToRad(double x)
 *      Converts x from degrees to radians.
 *
 *      double graToRad(double x)
 *      Converts x from grades to radians.
 *
 *      double radToDeg(double x)
 *      Converts x from radians to degrees.
 *
 *      double radToGra(double x)
 *      Converts x from radians to grades.
 *
 *      double theta(double stationX, double stationY,
 *                      double orientX, double orientY)
 *      Computes theta angle between station located at coordinates 
 *  stationX, stationY and orientation point located at coordinates
 *  orientX, orientY.
 *
 *	double omega(double orientHZ, double pointHZ)
 *	Computes omega.
 *
 *      double orientation(double theta, double omega)
 *      Computes orientation of a point.
 *
 *      double relativeX(double dist, double orientation)
 *      Computes relative position X of a point, based on distance and
 *  orientation.
 *
 *      double relativeY(long long dist, long long orientation)
 *      Computes relative position y of a point, based on distance and
 *  orientation.
 *      
 *      double absoluteX(double relativeX, double stationX)
 *      Computes absolute position X of a point, based on his relative
 *  X position and the X position of station.
 *
 *      double absoluteY(double relativeY, double stationY)
 *      Computes absolute position Y of a point, based on his relative
 *  Y position and the Y position of station.
 *
 *      double repairAngle(double angle)
 *      If angle isn't between 0 and 400, this function brings it to this
 *  interval. CAUTION: It only adds or subtracts 400, so this works only for
 *  one full circle.
 *
 */

#include <math.h>
#include "include/maths.h"
#include "include/error.h"
#include <stdio.h>

#define PI 3.1415926535897932384626433
#define precision 4

double roundFirstDecimal(double x){

//    printf("%lf\n", x);
    long long p=x*pow(10, precision+1);
    if(p%10>=5){ 
        x=(x*pow(10, precision)+1);///pow(10, precision);
    }else{
        x=x*pow(10, precision);
    }

    return ((int)(x))/pow(10, precision);
}

double degToRad(double x){
    return x*PI/180.;
}

double graToRad(double x){
    return x*PI/200.;
}

double radToDeg(double x){
    return x*180./PI;
}

double radToGra(double x){
    return x*200./PI; 
}

double theta(double stationX, double stationY, 
             double orientX,  double orientY){

    double top=orientY-stationY;
    double bot=orientX-stationX;

    double theta;

    if(bot==0){
        if(orientY > stationY)
            theta=100;
        else
            theta=300;
        return theta;
    }

    double fraction=top/bot;

    double alpha=atan(fraction);
    alpha=roundFirstDecimal(radToGra(alpha));
 
    if(alpha<0)
        alpha*=(-1);
    if(top>=0 && bot>0){
        theta=alpha;
    }else if(top<0 && bot>0){
        theta=400-alpha;
    }else if(top>=0 && bot<0){
        theta=200-alpha;
    }else if(top<0 && bot<0){
        theta=200+alpha;
    }
    return theta;
}

double omega(double orientHz, double pointHz){
    double diff=orientHz-pointHz;
    if(diff<0)
        diff+=400;
    return diff;
}

double orientation(double theta, double omega){
	double orientation=theta-omega;
	if(orientation<0)
		orientation+=400;
	return orientation;  
}

double relativeX(double dist, double orientation){
    return roundFirstDecimal(dist*cos(graToRad(orientation)));
}

double relativeY(double dist, double orientation){
    return roundFirstDecimal(dist*sin(graToRad(orientation)));
}

double absoluteX(double relativeX, double stationX){
    return relativeX+stationX;
}

double absoluteY(double relativeY, double stationY){
    return relativeY+stationY;
}

double height(double stationHeight, double distance, double hv){

    if(hv>=0){
        long long phi=100*pow(10., precision)-hv;
        return distance*tan(graToRad(phi)/pow(10., precision))+stationHeight;
    }else{
        return -1;
    }

}

double repairAngle(double angle){

    if(angle<0){
        angle+=400;
    }else if(angle>=400){
        angle-=400;
    }

    return angle;

}
