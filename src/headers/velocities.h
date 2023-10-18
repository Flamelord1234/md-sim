#ifndef VELOCITIES_H
#define VELOCITIES_H

#include "common.h"
#include "util.h"

vel_t *init_velocities(int n);
void update_velocities(vel_t *velocities, frc_t *forces, int n, double tdelta);

#endif  // VELOCITIES_H
