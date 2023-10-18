#include "headers/energies.h"

/* Potentials */

void calc_potentials(nrg_t *potentials, pos_t *positions, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dis_t distance = calc_nearest_distance(positions[i], positions[j]);
            if (distance.agg > cutoff) continue;
            potentials[i] += (4.0 / pow(distance.agg, 12.0) - 4.0 / pow(distance.agg, 6.0)) - pcut - (distance.agg - cutoff) * fcut;
        }
    }
}

nrg_t *init_potentials(pos_t *positions, int n) {
    nrg_t *potentials = calloc(n, sizeof(nrg_t));
    calc_potentials(potentials, positions, n);
    return potentials;
}

void update_potentials(nrg_t *potentials, pos_t *positions, int n) {
    memset(potentials, 0, n * sizeof(nrg_t));
    calc_potentials(potentials, positions, n);
}

/* Kinetics */

void calc_kinetics(nrg_t *kinetics, mom_t *momentums, int n) {
    for (int i = 0; i < n; i++) {
        double mx2 = momentums[i].x * momentums[i].x;
        double my2 = momentums[i].y * momentums[i].y;
        double mz2 = momentums[i].z * momentums[i].z;
        kinetics[i] = (mx2 + my2 + mz2) / 2;
    }
}

nrg_t *init_kinetics(mom_t *momentums, int n) {
    nrg_t *kinetics = malloc(n * sizeof(nrg_t));
    calc_kinetics(kinetics, momentums, n);
    return kinetics;
}

void update_kinetics(nrg_t *kinetics, mom_t *momentums, int n) {
    calc_kinetics(kinetics, momentums, n);
}

/* Printing */

void print_total_energies(nrg_t *kinetics, nrg_t *potentials, int n, double time) {
    double kin = 0;
    double pot = 0;
    for (int i = 0; i < n; i++) {
        kin += kinetics[i];
        pot += potentials[i];
    }
    printf("%.20lf,%.20lf\n", time, kin + pot);
    // printf("%.20lf,%.20lf\n", time, pot);
    // printf("%.20lf,%.20lf\n", time, kin);
}
