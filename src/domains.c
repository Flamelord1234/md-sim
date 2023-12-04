#include "headers/domains.h"

void init_domains(dom_t domains[8], int n) {
    for (int i = 0; i < 8; i++) {
        domains[i].within = malloc(n * sizeof(int));
        domains[i].within_num = 0;
        domains[i].cutoff = malloc(n * sizeof(int));
        domains[i].cutoff_num = 0;
    }
}

void push_domain_within(dom_t *domain, int index) {
    domain->within[domain->within_num] = index;
    domain->within_num++;
}

void push_domain_cutoff(dom_t *domain, int index) {
    domain->cutoff[domain->cutoff_num] = index;
    domain->cutoff_num++;
}

int get_domain_within(pos_t position) {
    if (position.x < sidelen / 2 && position.y < sidelen / 2 && position.z < sidelen / 2) {
        return 0;
    } else if (position.x < sidelen / 2 && position.y < sidelen / 2 && position.z < sidelen) {
        return 1;
    } else if (position.x < sidelen / 2 && position.y < sidelen && position.z < sidelen / 2) {
        return 2;
    } else if (position.x < sidelen / 2 && position.y < sidelen && position.z < sidelen) {
        return 3;
    } else if (position.x < sidelen && position.y < sidelen / 2 && position.z < sidelen / 2) {
        return 4;
    } else if (position.x < sidelen && position.y < sidelen / 2 && position.z < sidelen) {
        return 5;
    } else if (position.x < sidelen && position.y < sidelen && position.z < sidelen / 2) {
        return 6;
    } else {
        return 7;
    }
}

double max(double a, double b, double c) {
    if (a > b) {
        return c > a ? c : a;
    } else {
        return c > b ? c : b;
    }
}

double min(double a, double b) {
    return a > b ? b : a;
}

double box_distance(double min_x, double max_x, double min_y, double max_y, double min_z, double max_z, pos_t position) {
    double dx = max(min_x - position.x, 0, position.x - max_x);
    double dy = max(min_y - position.y, 0, position.y - max_y);
    double dz = max(min_z - position.z, 0, position.z - max_z);
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double domain_distance(pos_t position, int domain) {
    double min_x = 0 + (sidelen / 2) * ((domain & 0b100) >> 2);
    double max_x = (sidelen / 2) + (sidelen / 2) * ((domain & 0b100) >> 2);
    double min_y = 0 + (sidelen / 2) * ((domain & 0b10) >> 1);
    double max_y = (sidelen / 2) + (sidelen / 2) * ((domain & 0b10) >> 1);
    double min_z = 0 + (sidelen / 2) * (domain & 1);
    double max_z = (sidelen / 2) + (sidelen / 2) * (domain & 1);

    double distance = box_distance(min_x, max_x, min_y, max_y, min_z, max_z, position);
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y, max_y, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y, max_y, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y - sidelen, max_y - sidelen, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y - sidelen, max_y - sidelen, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y - sidelen, max_y - sidelen, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y + sidelen, max_y + sidelen, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y + sidelen, max_y + sidelen, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x, max_x, min_y + sidelen, max_y + sidelen, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);
    
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y, max_y, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y, max_y, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y, max_y, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y - sidelen, max_y - sidelen, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y - sidelen, max_y - sidelen, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y - sidelen, max_y - sidelen, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y + sidelen, max_y + sidelen, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y + sidelen, max_y + sidelen, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x - sidelen, max_x - sidelen, min_y + sidelen, max_y + sidelen, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);

    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y, max_y, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y, max_y, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y, max_y, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y - sidelen, max_y - sidelen, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y - sidelen, max_y - sidelen, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y - sidelen, max_y - sidelen, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y + sidelen, max_y + sidelen, min_z, max_z, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y + sidelen, max_y + sidelen, min_z - sidelen, max_z - sidelen, position));
    // printf("%lf\n", distance);
    distance = min(distance, box_distance(min_x + sidelen, max_x + sidelen, min_y + sidelen, max_y + sidelen, min_z + sidelen, max_z + sidelen, position));
    // printf("%lf\n", distance);

    return distance;
}

void populate_cutoffs(dom_t domains[8], int domain, pos_t position, int index) {
    for (int i = 0; i < 8; i++) {
        if (i == domain) continue;
        if (domain_distance(position, i) < cutoff) push_domain_cutoff(&domains[i], index);
    }
}

void populate_domains(dom_t domains[8], pos_t *positions, int n) {
    for (int i = 0; i < 8; i++) {
        domains[i].within_num = 0;
        domains[i].cutoff_num = 0;
    }

    for (int i = 0; i < n; i++) {
        int domain = get_domain_within(positions[i]);
        push_domain_within(&domains[domain], i);

        populate_cutoffs(domains, domain, positions[i], i);
    }
}

void print_domains(dom_t domains[8]) {
    printf("PRINTING DOMAINS -------------------------------------------------\n");
    for (int i = 0; i < 8; i++) {
        printf("Domain %d: cutoff num = %d, within num = %d\n", i, domains[i].cutoff_num, domains[i].within_num);
        printf("- Within: ");
        for (int j = 0; j < domains[i].within_num; j++) printf("%d, ", domains[i].within[j]);
        printf("\n- Cutoff: ");
        for (int j = 0; j < domains[i].cutoff_num; j++) printf("%d, ", domains[i].cutoff[j]);
        printf("\n\n");
    }
}
