#include "headers/forces.h"

void calc_forces(frc_t *forces, pos_t *positions, int n) {
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) {
        #pragma clang loop vectorize(enable) interleave(enable)
        for (int j = i + 1; j < n; j++) {
            dis_t distance = calc_nearest_distance(positions[i], positions[j]);
            frc_t force = calc_force(distance);

            forces[i].x += force.x;
            forces[i].y += force.y;
            forces[i].z += force.z;

            forces[j].x -= force.x;
            forces[j].y -= force.y;
            forces[j].z -= force.z;
        }
    }
}

frc_t *init_forces(pos_t *positions, int n) {
    frc_t *forces = calloc(n, sizeof(frc_t));
    calc_forces(forces, positions, n);
    return forces;
}

frc_t *empty_forces(int n) {
    return malloc(n * sizeof(frc_t));
}

void update_forces(dom_t domains[8], int domain, frc_t *forces, pos_t *positions, int n) {
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < domains[domain].within_num; i++) {
        #pragma clang loop vectorize(enable) interleave(enable)
        for (int j = i + 1; j < domains[domain].within_num; j++) {
            dis_t distance = calc_nearest_distance(positions[domains[domain].within[i]], positions[domains[domain].within[j]]);
            frc_t force = calc_force(distance);

            forces[domains[domain].within[i]].x += force.x;
            forces[domains[domain].within[i]].y += force.y;
            forces[domains[domain].within[i]].z += force.z;

            forces[domains[domain].within[j]].x -= force.x;
            forces[domains[domain].within[j]].y -= force.y;
            forces[domains[domain].within[j]].z -= force.z;
        }

        #pragma clang loop vectorize(enable) interleave(enable)
        for (int j = 0; j < domains[domain].cutoff_num; j++) {
            dis_t distance = calc_nearest_distance(positions[domains[domain].within[i]], positions[domains[domain].cutoff[j]]);
            frc_t force = calc_force(distance);

            forces[domains[domain].within[i]].x += force.x;
            forces[domains[domain].within[i]].y += force.y;
            forces[domains[domain].within[i]].z += force.z;
        }
    }
}
