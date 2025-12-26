#include "prop.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

// Runge-Kutta Numerical Integration

vector<vector<double>> propagate_sin_rk(double time) {
    vector<vector<double>> res;
    vector<double> ther;
    vector<double> numer;

    double w = 2;
    double t = 0;
    double s = 0;
    double x = 0;
    double xd = w;
    double h = .01;

    while (t <= time) {
        s += h;
        double xold = x;
        double xdold = xd;
        double xddold = -w*w*xold;

        // RK2 (Heun's method)
        // Predictor step (Euler)
        double x_pred = xold + h * xdold;
        double xd_pred = xdold + h * (-w*w*x_pred);
        double xdd_pred = -w*w*x_pred;

        // Corrector step (average of slopes)
        x = xold + h * 0.5 * (xdold + xd_pred);
        xd = xdold + h * 0.5 * (xddold + xdd_pred);

        t += h;

        if (s > .0999) {
            s = 0;
            double xther = sin(w * t);
            ther.push_back(xther);
            numer.push_back(x);
        }
    }

    res.push_back(ther);
    res.push_back(numer);
    return res;
}