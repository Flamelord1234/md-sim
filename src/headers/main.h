#ifndef MAIN_H
#define MAIN_H

#include "md.h"

/* Length of each time step */
const double tstep = 0.002L;

/* Number of time steps to perform */
const int steps = 500 * 200;

/* Side length of bounding box */
const double sidelen = 6.8L;

/* Scaling factor for random velocity generation */
const double velstd = 0.1;

#define CUTOFF 1L
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
const double tempdes = 0.8L;

#endif  // MAIN_H