#include "headers/velocities.h"

vel_t *init_velocities(int n) {
    vel_t *velocities = malloc(n * sizeof(vel_t));
    double totx = 0;
    double toty = 0;
    double totz = 0;
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n - 1; i++) {
        double vx = rnorm(0, velstd);
        double vy = rnorm(0, velstd);
        double vz = rnorm(0, velstd);
        velocities[i].x = vx;
        velocities[i].y = vy;
        velocities[i].z = vz;
        totx += vx;
        toty += vy;
        totz += vz;
    }
    velocities[n - 1].x = -totx;
    velocities[n - 1].y = -toty;
    velocities[n - 1].z = -totz;

    return velocities;
}

vel_t *empty_velocities(int n) {
    return malloc(n * sizeof(vel_t));
}

void update_velocities_first(dom_t domains[8], int domain, vel_t *velocities, frc_t *forces, drg_t drag, int n, bool thermostat, double tdelta) {
    if (thermostat) {
        #pragma clang loop vectorize(enable) interleave(enable)
        for (int i = 0; i < domains[domain].within_num; i++) {
            velocities[domains[domain].within[i]].x += tdelta * (forces[domains[domain].within[i]].x - drag * velocities[domains[domain].within[i]].x);
            velocities[domains[domain].within[i]].y += tdelta * (forces[domains[domain].within[i]].y - drag * velocities[domains[domain].within[i]].y);
            velocities[domains[domain].within[i]].z += tdelta * (forces[domains[domain].within[i]].z - drag * velocities[domains[domain].within[i]].z);
        }
    } else {
        #pragma clang loop vectorize(enable) interleave(enable)
        for (int i = 0; i < domains[domain].within_num; i++) {
            velocities[domains[domain].within[i]].x += tdelta * forces[domains[domain].within[i]].x;
            velocities[domains[domain].within[i]].y += tdelta * forces[domains[domain].within[i]].y;
            velocities[domains[domain].within[i]].z += tdelta * forces[domains[domain].within[i]].z;
        }
    }
}

void update_velocities_second(dom_t domains[8], int domain, vel_t *velocities, frc_t *forces, drg_t drag, int n, bool thermostat, double tdelta) {
    if (thermostat) {
        #pragma clang loop vectorize(enable) interleave(enable)
        for (int i = 0; i < domains[domain].within_num; i++) {
            velocities[domains[domain].within[i]].x += tdelta * forces[domains[domain].within[i]].x;
            velocities[domains[domain].within[i]].x /= 1 + tdelta * drag;
            velocities[domains[domain].within[i]].y += tdelta * forces[domains[domain].within[i]].y;
            velocities[domains[domain].within[i]].y /= 1 + tdelta * drag;
            velocities[domains[domain].within[i]].z += tdelta * forces[domains[domain].within[i]].z;
            velocities[domains[domain].within[i]].z /= 1 + tdelta * drag;
        }
    } else {
        #pragma clang loop vectorize(enable) interleave(enable)
        for (int i = 0; i < domains[domain].within_num; i++) {
            velocities[domains[domain].within[i]].x += tdelta * forces[domains[domain].within[i]].x;
            velocities[domains[domain].within[i]].y += tdelta * forces[domains[domain].within[i]].y;
            velocities[domains[domain].within[i]].z += tdelta * forces[domains[domain].within[i]].z;
        }
    }
}
