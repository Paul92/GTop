#include "inout.h"
#include<iostream>

using namespace std;

int main(int argc, char **argv){

    string infileName(argv[1]);

    init(infileName);

    cout<<readStation();
    string point_id;
    long long dist, hz;

    return 0;

}

