#ifndef ENERGIES_H
#define ENERGIES_H

#include "common.h"
#include "util.h"

nrg_t *init_potentials(pos_t *positions, int n);
void update_potentials(nrg_t *potentials, pos_t *positions, int n);

nrg_t *init_kinetics(mom_t *momentums, int n);
void update_kinetics(nrg_t *kinetics, mom_t *momentums, int n);

void print_total_energies(nrg_t *kinetics, nrg_t *potentials, int n, double time);

#endif  // ENERGIES_H
