#ifndef POSITIONS_H
#define POSITIONS_H

#include "common.h"
#include "util.h"

pos_t *init_positions(char *run_name, int n);
void update_positions(pos_t *positions, vel_t *velocities, int n, double tdelta);
void output_positions(pos_t *positions, int n, int step, FILE *file);

#endif  // POSITIONS_H
