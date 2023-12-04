#ifndef FORCE_H
#define FORCE_H

#include "common.h"
#include "util.h"

frc_t *init_forces(pos_t *positions, int n);
frc_t *empty_forces(int n);
void update_forces(dom_t domains[8], int domain, frc_t *forces, pos_t *positions, int n);
void update_forces_2(frc_t *forces, pos_t *positions, int n);

#endif  // FORCE_H
