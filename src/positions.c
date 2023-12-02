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

pos_t *init_displacements(int n) {
    return calloc(n, sizeof(pos_t));
}

void update_displacements(pos_t *displacements, vel_t *velocities, int n, double tdelta) {
    for (int i = 0; i < n; i++) {
        displacements[i].x += tdelta * velocities[i].x;
        displacements[i].y += tdelta * velocities[i].y;
        displacements[i].z += tdelta * velocities[i].z;
    }
}

void print_displacements(FILE *file, pos_t *displacements, int n, double time) {
    double msd = 0;
    for (int i = 0; i < n; i++) {
        msd += displacements[i].x * displacements[i].x;
        msd += displacements[i].y * displacements[i].y;
        msd += displacements[i].z * displacements[i].z;
    }
   fprintf(file, "%.20lf,%.20lf\n", time, msd / n);
}

void calc_mc_positions(pos_t *positions, int n) {
    for (int i = 0; i < n; i++) {
        nrg_t curr_potential = calc_elem_potential(positions, i, n);
        pos_t curr_position = positions[i];

        positions[i].x = rnorm(positions[i].x, 0.4);
        positions[i].y = rnorm(positions[i].y, 0.4);
        positions[i].z = rnorm(positions[i].z, 0.4);

        while (positions[i].x > sidelen) positions[i].x -= sidelen;
        while (positions[i].x < 0) positions[i].x += sidelen;
        while (positions[i].y > sidelen) positions[i].y -= sidelen;
        while (positions[i].y < 0) positions[i].y += sidelen;
        while (positions[i].z > sidelen) positions[i].z -= sidelen;
        while (positions[i].z < 0) positions[i].z += sidelen;

        nrg_t trial_potential = calc_elem_potential(positions, i, n);

        if (trial_potential >= curr_potential) {
            double prob = exp(-((1.0L / tempdes) * (trial_potential - curr_potential)));
            if (((double) rand()) / ((double) (RAND_MAX / 1.0L)) > prob) positions[i] = curr_position;
        }
    }
}