#include "headers/md.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s <run name>\n", argv[0]);
        return 0;
    }

    srand(time(NULL));

    char *run_name = argv[1];

    fcut = -(48.0 / pow(cutoff, 13.0) - 24.0 / pow(cutoff, 7.0));
    pcut = 4.0 / pow(cutoff, 12.0) - 4.0 / pow(cutoff, 6.0);

    int n = num_lines(run_name);
    pos_t *positions = init_positions(run_name, n);
    vel_t *velocities = init_velocities(n);
    frc_t *forces = init_forces(positions, n);
    mom_t *momentums = init_momentums(velocities, n);
    nrg_t *potentials = init_potentials(positions, n);
    nrg_t *kinetics = init_kinetics(momentums, n);

    tmp_t temperature = calc_temperature(kinetics, n);
    prs_t pressure = calc_pressure(temperature, positions, n);

    FILE *temp_file = fopen("debug/liquid256temp5.txt", "w");
    FILE *pressure_file = fopen("debug/liquid256pressure5.txt", "w");
    FILE *positions_file = output_file(run_name);

    output_positions(positions, n, 0, positions_file);

    // printf("Time,Metric\n");
    // print_total_momentum(momentums, n);
    // print_x_momentum(momentums, n, 0.0);
    // print_y_momentum(momentums, n, 0.0);
    // print_z_momentum(momentums, n, 0.0);
    fprintf(temp_file, "Time,Metric\n");
    fprintf(pressure_file, "Time,Metric\n");
    // print_total_energies(kinetics, potentials, n, 0.0);
    
    print_temperature(temp_file, temperature, 0.0);
    print_pressure(pressure_file, pressure, 0.0);

    for (int i = 1; i <= steps; i++) {
        update_velocities(velocities, forces, n, tstep / 2);
        update_positions(positions, velocities, n, tstep);
        update_forces(forces, positions, n);
        update_velocities(velocities, forces, n, tstep / 2);

        update_momentums(momentums, velocities, n);
        update_potentials(potentials, positions, n);
        update_kinetics(kinetics, momentums, n);
        
        temperature = calc_temperature(kinetics, n);
        print_temperature(temp_file, temperature, tstep * i);
        pressure = calc_pressure(temperature, positions, n);
        print_pressure(pressure_file, pressure, tstep * i);

        // print_total_momentum(momentums, n);
        // print_x_momentum(momentums, n, tstep * i);
        // print_y_momentum(momentums, n, tstep * i);
        // print_z_momentum(momentums, n, tstep * i);
        // print_total_energies(kinetics, potentials, n, tstep * i);

        output_positions(positions, n, i, positions_file);
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
    free(potentials);
    free(kinetics);
    return 0;
}