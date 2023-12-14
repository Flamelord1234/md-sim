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
    } else if (position.x < sidelen && position.y < sidelen && position.z < sidelen) {
        return 7;
    }
    
    printf("ERROR!!!\n");
    return -1;
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

double box_distance(double min_x, double min_y, double min_z, pos_t position) {
    double max_x = min_x + sidelen / 2;
    double max_y = min_y + sidelen / 2;
    double max_z = min_z + sidelen / 2;
    double dx = max(min_x - position.x, 0, position.x - max_x);
    double dy = max(min_y - position.y, 0, position.y - max_y);
    double dz = max(min_z - position.z, 0, position.z - max_z);
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double domain_distance(pos_t position, int domain) {
    double min_x = 0 + (sidelen / 2) * ((domain & 0b100) >> 2);
    double min_y = 0 + (sidelen / 2) * ((domain & 0b10) >> 1);
    double min_z = 0 + (sidelen / 2) * (domain & 1);

    double distance = -1.0;

    for (int x1 = 0; x1 < 3; x1++) {
        for (int y1 = 0; y1 < 3; y1++) {
            for (int z1 = 0; z1 < 3; z1++) {
                double x = min_x + (sidelen * (x1 - 1));
                double y = min_y + (sidelen * (y1 - 1));
                double z = min_z + (sidelen * (z1 - 1));
                
                double temp_d = box_distance(x, y, z, position);
                distance = (((distance == -1.0) || (temp_d < distance)) ? temp_d : distance);
            }
        }
    }

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

void populate_domains_2(dom_t domains[8], pos_t *positions, int n) {
    for (int i = 1; i < 8; i++) {
        domains[i].within_num = 0;
        domains[i].cutoff_num = 0;
    }

    domains[0].within_num = n;
    domains[0].cutoff_num = 0;
    for (int i = 0; i < n; i++) {
        domains[0].within[i] = i;
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
