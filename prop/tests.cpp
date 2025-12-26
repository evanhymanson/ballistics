#include "prop.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void test_props() {
     vector<double> euler_res = propogate_sin(10);

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

    vector<vector<double>> res = propagate_sin_rk(10);

    for (int i = 0; i < ther.size(); i++) {
        double diff = abs(ther[i] - euler_res[i]);
        cout << "Euler Diff : " << diff << endl;
        diff = abs(res[0][i] - res[1][i]);
        cout << "RK Diff: " << diff << endl;
    }
}

// void test_rk() {

//     for (int i = 0; i < res[0].size(); i++) {
//         double diff = abs(res[0][i] - res[1][i]);
//         cout << "RK diff : " << diff << endl;
//     }
// }
int main() {
    cout << "========================================" << endl;
    cout << "  PROP FOLDER TESTS" << endl;
    cout << "========================================\n" << endl;

    test_props();
    // test_rk();
    
    return 0;
}
