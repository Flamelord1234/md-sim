#ifndef MD_H
#define MD_H

#include "common.h"
#include "util.h"
#include "positions.h"
#include "velocities.h"
#include "forces.h"
#include "energies.h"
#include "momentums.h"
#include "temperature.h"
#include "pressure.h"

/* Length of each time step */
const double tstep = 0.002L;

/* Number of time steps to perform */
const int steps = 500 * 200;

/* Side length of bounding box */
const double sidelen = 6.8L;

/* Scaling factor for random velocity generation */
const double velstd = 0.70710678118L;

/* Cutoff distance for force/potential */
const double cutoff = 2.5L;

/* Force at cutoff distance */
double fcut;  // Initialized in `md.c`

/* Potential at cutoff distance */
double pcut;  // Initialized in `md.c`

#endif  // MD_H
