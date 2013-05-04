#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "include/list.h"
#include "include/maths.h"

//testing functions

void printElement(struct point *node){
    printf("next: %lf %lf before: %lf %lf beta: %lf theta: %lf\n relatives: %lf %lf absolutes: %lf %lf", 
            node->nextDist, node->nextHz, 
            node->beforeDist, node->beforeHz, node->beta, node->theta, 
            node->relativeX, node->relativeY, node->absoluteX, node->absoluteY);
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

void computeRelatives(struct point *node, double *sumX, double *sumY){
    node->relativeX=node->beforeDist*cos(graToRad(node->theta)); //okay, i have no
                                                         //idea if this is
                                                         //right
    node->relativeY=node->nextDist*sin(graToRad(node->theta));
    *sumX += node->relativeX;
    *sumY += node->relativeY;
    if(node->next!=NULL){
        computeRelatives(node->next, sumX, sumY);
    }
}

void correctRelatives(struct point* node, double CTx, double CTy){
    node->relativeX+=CTx*node->nextDist;
    node->relativeY+=CTy*node->nextDist;
    if(node->next!=NULL){
        correctRelatives(node->next, CTx, CTy);
    }
}

void computeAbsolutes(struct point *node, double stationX, double stationY){
    node->absoluteX = node->relativeX + stationX;
    node->absoluteY = node->relativeY + stationY;
    if(node->next!=NULL){
        computeAbsolutes(node->next, stationX, stationY);
    }
}
