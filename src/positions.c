#include "headers/positions.h"

pos_t *init_positions(char *run_name, int n) {
    pos_t *positions = malloc(n * sizeof(pos_t));
    FILE *file = input_file(run_name);

    for (int i = 0; i < n; i++) {
        double x, y, z;
        fscanf(file, "%lf", &x);
        fscanf(file, "%lf", &y);
        fscanf(file, "%lf", &z);
        positions[i].x = x;
        positions[i].y = y;
        positions[i].z = z;
    }

    fclose(file);
    return positions;
}

void update_positions(pos_t *positions, vel_t *velocities, int n, double tdelta) {
    for (int i = 0; i < n; i++) {
        positions[i].x += tdelta * velocities[i].x;
        positions[i].y += tdelta * velocities[i].y;
        positions[i].z += tdelta * velocities[i].z;

        while (positions[i].x > sidelen) positions[i].x -= sidelen;
        while (positions[i].x < 0) positions[i].x += sidelen;
        while (positions[i].y > sidelen) positions[i].y -= sidelen;
        while (positions[i].y < 0) positions[i].y += sidelen;
        while (positions[i].z > sidelen) positions[i].z -= sidelen;
        while (positions[i].z < 0) positions[i].z += sidelen;
    }
}

void output_positions(pos_t *positions, int n, int step, FILE *file) {
    fprintf(file, "%d\n Frame %d\n", n, step);
    for (int i = 0; i < n; i++) {
        fprintf(file, "a\t%.20lf\t%.20lf\t%.20lf\n", positions[i].x, positions[i].y, positions[i].z);
    }
}
