#include "headers/forces.h"

void calc_forces(frc_t *forces, pos_t *positions, int n) {
    for (int i = 0; i < n; i++) {
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

void update_forces(frc_t *forces, pos_t *positions, int n) {
    memset(forces, 0, n * sizeof(frc_t));
    calc_forces(forces, positions, n);
}
