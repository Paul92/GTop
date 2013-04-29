#include <stdio.h>
#include <stdlib.h>
#include "include/list.h"
#include "include/maths.h"

//testing functions

void printElement(struct point *node){
    printf("next: %lf %lf before: %lf %lf beta: %lf theta: %lf\n", 
            node->nextDist, node->nextHz, 
            node->beforeDist, node->beforeHz, node->beta, node->theta);
}

void printList(struct point *node){
    printElement(node);
    printf("%d\n", (node->next!=NULL));
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
        addPoint(curr->next, pt);
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

void subtractAlpha(struct point *node, double alpha){
    if(node->next!=NULL){
        subtractAlpha(node->next, alpha);
    }else{
        node->beta-=alpha;
    }
}

void computeThetas(struct point *node, struct point* curr){
//    printf("%lf %lf %lf\n", curr->theta, curr->beta, node->beta);
    curr->theta=roundFirstDecimal(node->theta+(200-curr->beta));
    if(curr->next != NULL){
        computeThetas(curr, curr->next);
    }
}

