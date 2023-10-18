#ifndef UTIL_H
#define UTIL_H

#include "common.h"

int num_lines(char *filepath);

dis_t calc_nearest_distance(pos_t p1, pos_t p2);
frc_t calc_force(dis_t distance);
double rnorm(double mean, double stdev);

#endif  // UTIL_H
