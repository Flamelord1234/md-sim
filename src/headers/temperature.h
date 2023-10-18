#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "common.h"

tmp_t calc_temperature(nrg_t *kinetics, int n);
void print_temperature(FILE *file, tmp_t temperature, double time);

#endif  // TEMPERATURE_H
