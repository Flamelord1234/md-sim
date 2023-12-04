#ifndef POSITIONS_H
#define POSITIONS_H

#include "common.h"
#include "util.h"

pos_t *init_positions(char *run_name, int n);
pos_t *empty_positions(int n);
void update_positions(dom_t domains[8], int domain, pos_t *positions, vel_t *velocities, int n, double tdelta);
void output_positions(pos_t *positions, int n, int step, FILE *file);

pos_t *init_displacements(int n);
pos_t *empty_displacements(int n);
void update_displacements(dom_t domains[8], int domain, pos_t *displacements, vel_t *velocities, int n, double tdelta);
void print_displacements(FILE *file, pos_t *displacements, int n, double time);

#endif  // POSITIONS_H
