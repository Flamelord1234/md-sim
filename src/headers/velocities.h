#ifndef VELOCITIES_H
#define VELOCITIES_H

#include "common.h"
#include "util.h"

vel_t *init_velocities(int n);
vel_t *empty_velocities(int n);
void update_velocities_first(dom_t domains[8], int domain, vel_t *velocities, frc_t *forces, drg_t drag, int n, bool thermostat, double tdelta);
void update_velocities_second(dom_t domains[8], int domain, vel_t *velocities, frc_t *forces, drg_t drag, int n, bool thermostat, double tdelta);

#endif  // VELOCITIES_H
