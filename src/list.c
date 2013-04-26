#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"

//testing functions

void printElement(struct point *node){
    printf("next: %lf %lf before: %lf %lf beta: %lf\n", 
            node->nextDist, node->nextHz, 
            node->beforeDist, node->beforeHz, node->beta);
}

void printList(struct point *node){
    printElement(node);
    if(node->next!=NULL){
        printList(node->next);
    }else{
        printf("END");
    }
}

//End of testing functions

struct point *newPoint(double nextAngle, double nextDist, 
                       double beforeAngle, double beforeDist, double beta){

    struct point *new = (struct point *)malloc(sizeof(struct point));
    
    new->nextHz = nextAngle;
    new->nextDist = nextDist;
    new->beforeHz = beforeAngle;
    new->beforeDist = beforeDist;
    new->beta = beta;
    new->next = NULL;
    
    return new;       
}

void addPoint(struct point *curr, struct point *pt){
    if(curr->next == NULL){
        curr->next = pt;
    }else{
        addPoint(pt, curr->next);
    }
}

void applyFunc(struct point *node, void (*func)(struct point *pt)){

    (*func)(node);
    if(node->next!=NULL){
        applyFunc(node->next, func);
    }
}

void correctBeta(struct point *node, double val){

    node->beta += val;
    if(node->next!=NULL){
        correctBeta(node->next, val);
    }
}

