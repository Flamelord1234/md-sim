#include "headers/energies.h"

/* Potential */

nrg_t calc_potential(pos_t *positions, int n) {
    double potential = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dis_t distance = calc_nearest_distance(positions[i], positions[j]);
            if (distance.agg > cutoff) continue;
            potential += (4.0 / pow(distance.agg, 12.0) - 4.0 / pow(distance.agg, 6.0)) - pcut - (distance.agg - cutoff) * fcut;
        }
    }
    return potential;
}

/* Kinetic */

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

void print_kinetic(FILE *file, nrg_t *kinetics, int n, double time) {
    double kinetic = 0;
    for (int i = 0; i < n; i++) kinetic += kinetics[i];
    fprintf(file, "%.20lf,%.20lf\n", time, kinetic);
}

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
