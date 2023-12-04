#ifndef ENERGIES_H
#define ENERGIES_H

#include "common.h"
#include "util.h"

nrg_t calc_potential(pos_t *positions, int n);

nrg_t *init_kinetics(mom_t *momentums, int n);
nrg_t *empty_kinetics(int n);
void update_kinetics(dom_t domains[8], int domain, nrg_t *kinetics, mom_t *momentums, int n);

void print_total_energies(nrg_t *kinetics, nrg_t *potentials, int n, double time);
void print_kinetic(FILE *file, nrg_t *kinetics, int n, double time);

#endif  // ENERGIES_H
