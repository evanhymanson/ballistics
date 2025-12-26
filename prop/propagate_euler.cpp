/*
Numerical Integration: Euler 
*/

#include "prop.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

// x = sinwt

vector<double> propogate_sin(double time) {

    vector<double> res;
    double w = 2;
    double t = 0;
    double s = 0;
    double x = 0;
    double xd = w;
    double h = .01;

    while (t < time) {
        s += h;
        double xdd = -w * w * x;
        xd += h*xdd;
        x += h*xd;
        t += h;
        
        if (s > .09999) {
            res.push_back(x);
            s = 0; // reset counter
        }

    }

    return res;

}