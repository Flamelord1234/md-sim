#include "headers/pressure.h"

prs_t calc_pressure(tmp_t temperature, pos_t *positions, int n) {
    double base = (n * temperature) / (sidelen * sidelen * sidelen);
    double add = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dis_t distance = calc_nearest_distance(positions[i], positions[j]);
            frc_t force = calc_force(distance);
            add -= distance.x * force.x + distance.y * force.y + distance.z * force.z;
        }
    }
    add /= 3 * sidelen * sidelen * sidelen;

    return base + add;
}

void print_pressure(FILE *file, prs_t pressure, double time) {
    fprintf(file, "%.20lf,%.20lf\n", time, pressure);
}