#include "include/radiere.h"
#include "include/drumuire.h"

#include <string.h>
#include <stdio.h>

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
        printf("both");
    }

    return 0;
}
