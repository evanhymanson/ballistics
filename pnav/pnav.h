#include <vector>

void Simpnav_2d();

struct Target {
    double x, y;
    double vx, vy;
    double v0;
    double a;
};

struct Missile {
    double x, y;
    double vx, vy;
    double ax, ay;
    double v0;
    double hd;
};

struct Rel {
    double x, y;
    double vx, vy;
    double r;
    double v;
};

class Simulate {
public:
    void pnav_2d();
};