#include "prop.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


int main() {
    cout << "========================================" << endl;
    cout << "  PROP FOLDER TESTS" << endl;
    cout << "========================================\n" << endl;

    vector<double> res = propogate_sin(10);

    // analytical
    double t = 0;
    double h = .01;
    double s = 0;
    double w = 2;

    vector<double> ther;

    // theor
    while (t < 10) {
        s += h;
        t += h;

        if (s > .09999) {
            s = 0;
            ther.push_back(sin(w * t));
        }
    }

    for (int i = 0; i < ther.size(); i++) {
        double diff = abs(ther[i] - res[i]);
        cout << "Diff : " << diff << endl;
    }
    
    return 0;
}
