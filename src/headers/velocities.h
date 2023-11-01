#ifndef VELOCITIES_H
#define VELOCITIES_H

#include "common.h"
#include "util.h"

vel_t *init_velocities(int n);
void update_velocities_first(vel_t *velocities, frc_t *forces, drg_t drag, int n, bool thermostat, double tdelta);
void update_velocities_second(vel_t *velocities, frc_t *forces, drg_t drag, int n, bool thermostat, double tdelta);

#endif  // VELOCITIES_H
