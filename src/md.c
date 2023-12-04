#include "headers/md.h"

void run_md(char *run_name, bool debug) {
    int particles = num_lines(run_name);

    dom_t domains[8];

    pos_t *positions = init_positions(run_name, particles);
    pos_t *displacements = init_displacements(particles);
    vel_t *velocities = init_velocities(particles);
    frc_t *forces = init_forces(positions, particles);
    frc_t *temp_forces = malloc(particles * sizeof(frc_t));
    mom_t *momentums = init_momentums(velocities, particles);
    nrg_t *kinetics = init_kinetics(momentums, particles);
    drg_t drag = init_drag();

    nrg_t potential = calc_potential(positions, particles);
    tmp_t temperature = calc_temperature(kinetics, particles);
    prs_t pressure = calc_pressure(temperature, positions, particles);

    FILE *msd_file = fopen("debug/liquid256disp10.txt", "w");
    FILE *temp_file = fopen("debug/liquid256temp10.txt", "w");
    FILE *pressure_file = fopen("debug/liquid256pressure10.txt", "w");
    FILE *kinetic_file = fopen("debug/liquid256kinetic10.txt", "w");
    FILE *positions_file = output_file(run_name);

    output_positions(positions, particles, 0, positions_file);

    // printf("Time,Metric\n");
    // print_total_momentum(momentums, n);
    // print_x_momentum(momentums, particles, 0.0);
    // print_y_momentum(momentums, n, 0.0);
    // print_z_momentum(momentums, n, 0.0);
    fprintf(msd_file, "Time,Metric\n");
    fprintf(temp_file, "Time,Metric\n");
    fprintf(pressure_file, "Time,Metric\n");
    fprintf(kinetic_file, "Time,Metric\n");
    // print_total_energies(kinetics, potentials, n, 0.0);
    
    if (thermostat_steps == 0) {
        print_displacements(msd_file, displacements, particles, 0.0);
        print_temperature(temp_file, temperature, 0.0);
        print_pressure(pressure_file, pressure, 0.0);
        print_kinetic(kinetic_file, kinetics, particles, 0.0);
    }

    double total_K = 0, total_U = 0, total_T = 0, total_P = 0;

    init_domains(domains, particles);
    populate_domains(domains, positions, particles);
    // print_domains(domains);

    // printf("%lf\n", domain_distance(positions[2], 0));
    // return;

    for (int i = 1; i <= steps; i++) {
        if (i % 500 == 0) printf("%d steps...\n", i);

        for (int dom = 0; dom < 8; dom++) {
            update_velocities_first(domains, dom, velocities, forces, drag, particles, i <= thermostat_steps, tstep / 2);  // v(t + dt/2)
            update_positions(domains, dom, positions, velocities, particles, tstep);  // r(t + dt)
            update_displacements(domains, dom, displacements, velocities, particles, tstep);
            update_momentums(domains, dom, momentums, velocities, particles);  // m(t + dt/2)
            update_kinetics(domains, dom, kinetics, momentums, particles);  // K(t + dt/2)
        }

        populate_domains(domains, positions, particles);
        // print_domains(domains);

        temperature = calc_temperature(kinetics, particles);  // T(t + dt/2)
        drag = update_drag(drag, temperature, tstep);  // d(t + dt)

        memset(temp_forces, 0, particles * sizeof(frc_t));
        for (int dom = 0; dom < 8; dom++) {
            update_forces(domains, dom, temp_forces, positions, particles);  // F(t + dt)
            update_velocities_second(domains, dom, velocities, temp_forces, drag, particles, i <= thermostat_steps, tstep / 2);  // v(t + dt)
            update_momentums(domains, dom, momentums, velocities, particles);  // m(t + dt)
            update_kinetics(domains, dom, kinetics, momentums, particles);  // K(t + dt)
        }

        memcpy(forces, temp_forces, particles * sizeof(frc_t));
        potential = calc_potential(positions, particles);  // U(t + dt)
        temperature = calc_temperature(kinetics, particles);  // T(t + dt)
        pressure = calc_pressure(temperature, positions, particles);  // p(t + dt)

        // print_total_momentum(momentums, n);
        // print_x_momentum(momentums, particles, tstep * i);
        // print_y_momentum(momentums, n, tstep * i);
        // print_z_momentum(momentums, n, tstep * i);
        // print_total_energies(kinetics, potentials, n, tstep * i);

        if (i > thermostat_steps) {
            for (int i = 0; i < particles; i++) total_K += kinetics[i];
            total_U += potential;
            total_T += temperature;
            total_P += pressure;
            print_displacements(msd_file, displacements, particles, tstep * i);
            print_kinetic(kinetic_file, kinetics, particles, tstep * i);
            print_temperature(temp_file, temperature, tstep * i);
            print_pressure(pressure_file, pressure, tstep * i);

            if (i % 10 == 0) output_positions(positions, particles, i, positions_file);
        }
    }
    // temperature = calc_temperature(kinetics, n);
    // pressure = calc_pressure(temperature, positions, n);
    // print_temperature(temperature, tstep * steps);
    // print_pressure(pressure, tstep * steps);

    printf("avg K: %lf, avg U: %lf, avg T: %lf, avg P: %lf\n", total_K / (steps - thermostat_steps), total_U / (steps - thermostat_steps), total_T / (steps - thermostat_steps), total_P / (steps - thermostat_steps));

    fclose(msd_file);
    fclose(temp_file);
    fclose(pressure_file);
    fclose(kinetic_file);
    fclose(positions_file);

    free(positions);
    free(displacements);
    free(velocities);
    free(forces);
    free(momentums);
    free(kinetics);
}