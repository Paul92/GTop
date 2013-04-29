struct point{
    char point_id[100];
    double nextHz;
    double nextDist;
    double beforeHz;
    double beforeDist;
    double beta;
    double theta;
    struct point *next;
};

struct point *newPoint(double, double, double, double, double);
void addPoint(struct point *, struct point *);
void applyFunc(struct point *, void (*)(struct point *pt));
void printList(struct point *);
void correctBeta(struct point *, double);
void printElement(struct point*);
void subtractAlpha(struct point *, double alpha);
void computeThetas(struct point *, struct point *);
