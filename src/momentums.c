#include "headers/momentums.h"

void calc_momentums(mom_t *momentums, vel_t *velocities, int n) {
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) {
        momentums[i] = velocities[i];
    }
}

mom_t *init_momentums(vel_t *velocities, int n) {
    mom_t *momentums = calloc(n, sizeof(mom_t));
    calc_momentums(momentums, velocities, n);
    return momentums;
}

mom_t *empty_momentums(int n) {
    return malloc(n * sizeof(mom_t));
}

void update_momentums(dom_t domains[8], int domain, mom_t *momentums, vel_t *velocities, int n) {
    memset(momentums, 0, n * sizeof(mom_t));
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < domains[domain].within_num; i++) {
        momentums[domains[domain].within[i]] = velocities[domains[domain].within[i]];
    }
}

void print_x_momentum(mom_t *momentums, int n, double time) {
    double mx = 0;
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) mx += momentums[i].x;
    printf("%.20lf,%.20lf\n", time, mx);
}

void print_y_momentum(mom_t *momentums, int n, double time) {
    double my = 0;
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) my += momentums[i].y;
    printf("%.20lf,%.20lf\n", time, my);
}

void print_z_momentum(mom_t *momentums, int n, double time) {
    double mz = 0;
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) mz += momentums[i].z;
    printf("%.20lf,%.20lf\n", time, mz);
}

void print_total_momentum(mom_t *momentums, int n) {
    double mx = 0;
    double my = 0;
    double mz = 0;
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) {
        mx += momentums[i].x;
        my += momentums[i].y;
        mz += momentums[i].z;
    }
    printf("%.20lf\t%.20lf\t%.20lf\n", mx, my, mz);
}