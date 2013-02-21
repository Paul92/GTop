#include "radiere.h"
//#include "drumuire.h"

#include<cstring>
#include<cstdio>

#include<iostream>

using namespace std;

int main(int argc, char **argv){

    if(argc<4){
        printf("Prea putine argumente\n");
    }else if(argc>4){
        printf("Prea multe argumente\n");
    }
    
    if(strcmp(argv[1], "-r")==0){
        return radiere(0, argv+1);
    }else if(strcmp(argv[1], "-d")==0){
        return drumuire(0, argv+1);
    }else if(strcmp(argv[1], "-dr")==0){
        cout<<"both";
    }

    return 0;
}
