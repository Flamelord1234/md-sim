#include "headers/md.h"

void run_md(char *run_name, bool debug) {
    int particles = num_lines(run_name);
    pos_t *positions = init_positions(run_name, particles);
    vel_t *velocities = init_velocities(particles);
    frc_t *forces = init_forces(positions, particles);
    mom_t *momentums = init_momentums(velocities, particles);
    nrg_t *kinetics = init_kinetics(momentums, particles);
    nrg_t potential = calc_potential(positions, particles);

    tmp_t temperature = calc_temperature(kinetics, particles);
    prs_t pressure = calc_pressure(temperature, positions, particles);

    FILE *temp_file = fopen("debug/liquid256temp6.txt", "w");
    FILE *pressure_file = fopen("debug/liquid256pressure6.txt", "w");
    FILE *positions_file = output_file(run_name);

    output_positions(positions, particles, 0, positions_file);

    // printf("Time,Metric\n");
    // print_total_momentum(momentums, n);
    // print_x_momentum(momentums, particles, 0.0);
    // print_y_momentum(momentums, n, 0.0);
    // print_z_momentum(momentums, n, 0.0);
    fprintf(temp_file, "Time,Metric\n");
    fprintf(pressure_file, "Time,Metric\n");
    // print_total_energies(kinetics, potentials, n, 0.0);
    
    print_temperature(temp_file, temperature, 0.0);
    print_pressure(pressure_file, pressure, 0.0);

    for (int i = 1; i <= steps; i++) {
        if (i % 500 == 0) printf("%d steps...\n", i);
        update_velocities(velocities, forces, particles, tstep / 2);
        update_positions(positions, velocities, particles, tstep);
        update_forces(forces, positions, particles);
        update_velocities(velocities, forces, particles, tstep / 2);

        update_momentums(momentums, velocities, particles);
        update_kinetics(kinetics, momentums, particles);
        potential = calc_potential(positions, particles);
        
        temperature = calc_temperature(kinetics, particles);
        print_temperature(temp_file, temperature, tstep * i);
        pressure = calc_pressure(temperature, positions, particles);
        print_pressure(pressure_file, pressure, tstep * i);

        // print_total_momentum(momentums, n);
        // print_x_momentum(momentums, particles, tstep * i);
        // print_y_momentum(momentums, n, tstep * i);
        // print_z_momentum(momentums, n, tstep * i);
        // print_total_energies(kinetics, potentials, n, tstep * i);

        if (i % 10 == 0) output_positions(positions, particles, i, positions_file);
    }
    // temperature = calc_temperature(kinetics, n);
    // pressure = calc_pressure(temperature, positions, n);
    // print_temperature(temperature, tstep * steps);
    // print_pressure(pressure, tstep * steps);

    fclose(temp_file);
    fclose(pressure_file);
    fclose(positions_file);

    free(positions);
    free(velocities);
    free(forces);
    free(momentums);
    free(kinetics);
}