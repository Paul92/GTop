/**
 *  Handles input and output
 *
 *  Macro constants:
 *      EOS - End Of Station. Value is 0.
 *
 *  Functions:
 *      void init(string filename)
 *      Opens filename file; stream redirected to cin
 *
 *      int readStation()
 *      Reads and returns a new station id
 *
 *      int readPoint(string &point_id, double &distance, double &hz)
 *      Reads new point data. 
 *      If the point is valid, returns 1, else returns EOS.
**/

#include "inout.h"
#include<iostream>
#include<string>
#include<cstdio>

#define EOS 0 //End Of Station

using namespace std;

void init(string filename){
    freopen(filename.c_str(), "r", stdin);
}

int readStation(){
    int station_id;
    cin>>station_id;
    return station_id;
}

int readPoint(string &point_id, double &distance, double &hz){

    cin>>point_id>>distance>>hz;

    if(point_id=="9999" && distance==0 && hz==0)
        return 0;
    else
        return 1;

}

