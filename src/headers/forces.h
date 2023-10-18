#ifndef FORCE_H
#define FORCE_H

#include "common.h"
#include "util.h"

frc_t *init_forces(pos_t *positions, int n);
void update_forces(frc_t *forces, pos_t *positions, int n);

#endif  // FORCE_H
