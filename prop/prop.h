#ifndef PROP_H
#define PROP_H

#include <vector>

std::vector<double> propogate_sin(double time);
std::vector<std::vector<double>> propagate_sin_rk(double time);

#endif