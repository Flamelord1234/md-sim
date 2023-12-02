#include "headers/md.h"

void run_md(char *run_name, bool debug) {
    int particles = num_lines(run_name);
    pos_t *positions = init_positions(run_name, particles);

    nrg_t potential = calc_potential(positions, particles);
    prs_t pressure = calc_pressure(tempdes, positions, particles);

    FILE *pressure_file = fopen("debug/mc/liquid256pressure1.txt", "w");
    FILE *potential_file = fopen("debug/mc/liquid256potential1", "w");
    FILE *positions_file = output_file(run_name);

    output_positions(positions, particles, 0, positions_file);
    
    fprintf(pressure_file, "Time,Metric\n");
    fprintf(potential_file, "Time,Metric\n");

    double total_U = potential, total_P = pressure;

    for (int i = 1; i <= steps; i++) {
        if (i % 500 == 0) printf("%d steps...\n", i);

        calc_mc_positions(positions, particles);
        potential = calc_potential(positions, particles);
        pressure = calc_pressure(tempdes, positions, particles);
        print_pressure(pressure_file, pressure, tstep * i);
        print_potential(potential_file, potential, tstep * i);

        total_U += potential;
        total_P += pressure;

        if (i % 10 == 0) output_positions(positions, particles, i, positions_file);
    }
    
    printf("avg U: %lf, avg P: %lf\n", total_U / steps, total_P / steps);

    fclose(pressure_file);
    fclose(positions_file);
    fclose(potential_file);

    free(positions);
}