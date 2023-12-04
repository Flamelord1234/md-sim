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

pos_t *empty_positions(int n) {
    return malloc(n * sizeof(pos_t));
}

void update_positions(dom_t domains[8], int domain, pos_t *positions, vel_t *velocities, int n, double tdelta) {
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < domains[domain].within_num; i++) {
        positions[domains[domain].within[i]].x += tdelta * velocities[domains[domain].within[i]].x;
        positions[domains[domain].within[i]].y += tdelta * velocities[domains[domain].within[i]].y;
        positions[domains[domain].within[i]].z += tdelta * velocities[domains[domain].within[i]].z;

        while (positions[domains[domain].within[i]].x > sidelen) positions[domains[domain].within[i]].x -= sidelen;
        while (positions[domains[domain].within[i]].x < 0) positions[domains[domain].within[i]].x += sidelen;
        while (positions[domains[domain].within[i]].y > sidelen) positions[domains[domain].within[i]].y -= sidelen;
        while (positions[domains[domain].within[i]].y < 0) positions[domains[domain].within[i]].y += sidelen;
        while (positions[domains[domain].within[i]].z > sidelen) positions[domains[domain].within[i]].z -= sidelen;
        while (positions[domains[domain].within[i]].z < 0) positions[domains[domain].within[i]].z += sidelen;
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

pos_t *empty_displacements(int n) {
    return malloc(n * sizeof(pos_t));
}

void update_displacements(dom_t domains[8], int domain, pos_t *displacements, vel_t *velocities, int n, double tdelta) {
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < domains[domain].within_num; i++) {
        displacements[domains[domain].within[i]].x += tdelta * velocities[domains[domain].within[i]].x;
        displacements[domains[domain].within[i]].y += tdelta * velocities[domains[domain].within[i]].y;
        displacements[domains[domain].within[i]].z += tdelta * velocities[domains[domain].within[i]].z;
    }
}

void print_displacements(FILE *file, pos_t *displacements, int n, double time) {
    double msd = 0;
    #pragma clang loop vectorize(enable) interleave(enable)
    for (int i = 0; i < n; i++) {
        msd += displacements[i].x * displacements[i].x;
        msd += displacements[i].y * displacements[i].y;
        msd += displacements[i].z * displacements[i].z;
    }
   fprintf(file, "%.20lf,%.20lf\n", time, msd / n);
}
