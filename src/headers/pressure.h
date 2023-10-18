#ifndef PRESSURE_H
#define PRESSURE_H

#include "common.h"
#include "util.h"

prs_t calc_pressure(tmp_t temperature, pos_t *positions, int n);
void print_pressure(FILE *file, prs_t pressure, double time);

#endif  // TEMPERATURE_H
