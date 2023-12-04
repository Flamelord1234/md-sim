#ifndef MAIN_H
#define MAIN_H

#include "md.h"

/* Length of each time step */
const double tstep = 0.002L;

/* Number of time steps to perform */
const int steps = 40;

/* Number of time steps until thermostat turns off */
const int thermostat_steps = 500 * 0;

/* Side length of bounding box */
const double sidelen = 6.8L;

/* Scaling factor for random velocity generation */
const double velstd = 0.70710678118L;

#define CUTOFF 2.5L
#define CUTOFF6 (CUTOFF * CUTOFF * CUTOFF * CUTOFF * CUTOFF * CUTOFF)
/* Cutoff distance for force/potential */
const double cutoff = CUTOFF;

/* Force at cutoff distance */
const double fcut = -(48.0 / (CUTOFF6 * CUTOFF6 * CUTOFF) - 24.0 / (CUTOFF6 * CUTOFF));

/* Potential at cutoff distance */
const double pcut = 4.0 / (CUTOFF6 * CUTOFF6) - 4.0 / CUTOFF6;
#undef CUTOFF
#undef CUTOFF6

/* Thermostat dampening constant */
const double tdamp = 0.05;

/* Desired system temperature */
const double tempdes = 1.38L / 1.66L;  // 100 K for argon

#endif  // MAIN_H