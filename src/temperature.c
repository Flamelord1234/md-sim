#include "headers/temperature.h"

tmp_t calc_temperature(nrg_t *kinetics, int n) {
    double totk = 0;
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) totk += kinetics[i];
    return 2 * totk / (3 * (n - 1));
}

void print_temperature(FILE *file, tmp_t temperature, double time) {
    fprintf(file, "%.20lf,%.20lf\n", time, temperature);
}