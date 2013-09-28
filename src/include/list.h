struct point{
    char point_id[100];
    double nextHz;
    double nextDist;
    double beforeHz;
    double beforeDist;
    double beta;
    double theta;
    double relativeX;
    double relativeY;
    double absoluteX;
    double absoluteY;
    struct point *next;
};

struct point *newPoint(double, double, double, double, double); //BC. Correct 
void addPoint(struct point *, struct point *);
void applyFunc(struct point *, void (*)(struct point *pt));
void printList(FILE*, struct point *);
void correctBeta(struct point *, double);  //these are too specialised for 
                                           //a list. Do something, or call it
                                           //otherwise
void printElement(struct point*);
void subtractAlpha(struct point *, double alpha);
void computeThetas(struct point *, struct point *);
void computeRelatives(struct point *, double *, double *);
void correctRelatives(struct point *, double, double);
void computeAbsolutes(struct point *, double, double);
void echoList(struct point*);
void freeList(struct point*);
