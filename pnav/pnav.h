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
    // Constructor
    Simulate() : time(), m_x(), m_y(), t_x(), t_y(), rel_r(), a_cmdvec() {
    // Empty body - vectors initialized in the initializer list
    }

    std::vector<double> time;
    std::vector<double> m_x, m_y, t_x, t_y, rel_r, a_cmdvec;

    Target targ;
    Missile missile;
    Missile mold;
    Target targold;

    void pnav_2d();
};