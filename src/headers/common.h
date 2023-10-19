#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/* Globals initialized and defined in `main.h` or `main.c` */

/* Length of each time step */
extern const double tstep;

/* Number of time steps to perform */
extern const int steps;

/* Side length of bounding box */
extern const double sidelen;

/* Scaling factor for random velocity generation */
extern const double velstd;

/* Cutoff distance for force/potential */
extern const double cutoff;

/* Force at cutoff distance */
extern const double fcut;

/* Potential at cutoff distance */
extern const double pcut;

typedef double nrg_t;
typedef double tmp_t;
typedef double prs_t;

struct triple {
    double x;
    double y;
    double z;
};
typedef struct triple pos_t;
typedef struct triple vel_t;
typedef struct triple mom_t;
typedef struct triple frc_t;

struct aggregate {
    double x;
    double y;
    double z;
    double agg;
};
typedef struct aggregate dis_t;

#endif  // COMMON_H
