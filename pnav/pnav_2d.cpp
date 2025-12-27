#include <iostream>
#include <cmath>
#include <vector>
#include "pnav.h"

using namespace std;

struct Target {
    double x, y; // position
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

// relative missile to target: r = x_targ - x_missile
struct Rel {
    double x, y;
    double vx, vy;
    double r;
    double v;
};

class Simulate {
public: 
    void pnav_2d() {
        vector<double> time;
        vector<double> m_x, m_y, t_x, t_y, rel_r, a_cmdvec;
        double h;
        double N = 4;
        double xlamd;
        double a_cmd;
        double betad;
        
        Target targ;
        Missile missile;
        Missile mold;
        Target targold;

        missile.v0 = 3000;
        missile.hd = -20;
        targ.v0 = 1000;
        targ.a = 0;

        missile.x = 0;
        missile.y = 10000;
        missile.ax = 0;
        missile.ay = 0;

        targ.x = 40000;
        targ.y = 10000;

        double beta = 0;
        targ.vx = -targ.v0*cos(beta);
        targ.vy = -targ.v0*sin(beta);
        missile.hd /= 57.3;

        double t = 0;
        double s = 0;

        Rel rel;

        rel.x = targ.x - missile.x;
        rel.y = targ.y - missile.y;
        rel.r = sqrt(pow(rel.x, 2) + pow(rel.y, 2));

        double xlam = atan2(rel.y, rel.x);
        double xlead = asin(targ.v0 * sin(beta + xlam)/missile.v0);
        double theta = xlam + xlead;

        missile.vx = missile.v0 * cos(theta + missile.hd);
        missile.vy = missile.v0 * sin(theta + missile.hd);

        rel.vx = targ.vx - missile.vx;
        rel.vy = targ.vy - missile.vy;

        double vc = -(rel.x*rel.vx + rel.y*rel.vy) / rel.r;
        double betaold;
        while (vc >= 0) {
            if (rel.r > 1000) {
                h = .01;
            } else {
                h = .0002;
            }

            betaold = beta;
            targold.x = targ.x;
            targold.y = targ.y;
            
            mold.x = missile.x;
            mold.y = missile.y;
            mold.vx = missile.vx;
            mold.vy = missile.vy;

            double step = 1;
            double flag = 0;
            
            while (step >= 1) {
                if (flag == 1) {
                    step = 2;
                    beta += h*betad;
                    targ.x += h*targ.vx;
                    targ.y += h*targ.vy;
                    missile.x += h*missile.vx;
                    missile.y += h*missile.vy;
                    missile.vx += h*missile.ax;
                    missile.vy += h*missile.ay;
                    t += h;
                }

                rel.x = targ.x - missile.x;
                rel.y = targ.y - missile.y;
                rel.r = sqrt(pow(rel.x, 2) + pow(rel.y, 2));
                rel.vx = targ.vx - missile.vx;
                rel.vy = targ.vy - missile.vy;
                vc = -(rel.x*rel.vx + rel.y*rel.vy) / rel.r;
                xlam = atan2(rel.y, rel.x);
                xlamd = (rel.x*rel.vy - rel.y*rel.vx)/(rel.r*rel.r);
                a_cmd = N * vc * xlamd;
                missile.ax = -a_cmd*sin(xlam);
                missile.ay = a_cmd*cos(xlam);
                targ.vx = -targ.v0*cos(beta);
                targ.vy = -targ.v0*sin(beta);
                betad = targ.a/targ.v0;
                flag = 1;
            }

            flag = 0;
            beta = 0.5 * (betaold + beta + h*betad);
            targ.x = 0.5 * (targold.x + targ.x + h*targ.vx);
            targ.y = 0.5 * (targold.y + targ.y + h*targ.vy);
            missile.x = 0.5 * (mold.x + missile.x + h*missile.vx);
            missile.y = 0.5 * (mold.y + missile.y + h*missile.vy);
            missile.vx = 0.5 * (mold.vx + missile.vx + h*missile.ax);
            missile.vy = 0.5 * (mold.vy + missile.vy + h*missile.ay);
            s += h;

            if (s > .09999) {
                s = 0;
                time.push_back(t);
                m_x.push_back(missile.x);
                m_y.push_back(missile.y);
                t_x.push_back(targ.x);
                t_y.push_back(targ.y);
                a_cmdvec.push_back(a_cmd);
                rel_r.push_back(rel.r);
            }
        }
    }
};
