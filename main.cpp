#include "inout.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv){

    string infileName(argv[1]);

    init(infileName);

    cout<<readStation();
    string point_id;
    double dist, hz;

    cout<<readPoint(point_id, dist, hz)<<' ';
    cout<<point_id<<' '<<dist<<' '<<hz<<'\n';

    return 0;

}

