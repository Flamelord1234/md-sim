#ifndef MOMENTUMS_H
#define MOMENTUMS_H

#include "common.h"

mom_t *init_momentums(vel_t *velocities, int n);
mom_t *empty_momentums(int n);
void update_momentums(dom_t domains[8], int domain, mom_t *momentums, vel_t *velocities, int n);

void print_x_momentum(mom_t *momentums, int n, double time);
void print_y_momentum(mom_t *momentums, int n, double time);
void print_z_momentum(mom_t *momentums, int n, double time);
void print_total_momentum(mom_t *momentums, int n);

#endif  // MOMENTUMS_H
