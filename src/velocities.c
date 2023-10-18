#include "headers/velocities.h"

vel_t *init_velocities(int n) {
    vel_t *velocities = malloc(n * sizeof(vel_t));
    double totx = 0;
    double toty = 0;
    double totz = 0;
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

void update_velocities(vel_t *velocities, frc_t *forces, int n, double tdelta) {
    for (int i = 0; i < n; i++) {
        velocities[i].x += tdelta * forces[i].x;
        velocities[i].y += tdelta * forces[i].y;
        velocities[i].z += tdelta * forces[i].z;
    }
}
