struct point{
    double nextAngle;
    double nextDist;
    double beforeAngle;
    double beforeDist;
    double beta;
    struct point *next;
};

struct point *newPoint(double, double, double, double, double);
void addPoint(struct point *, struct point *);
void applyFunc(struct point *, void (*)(struct point *pt));
