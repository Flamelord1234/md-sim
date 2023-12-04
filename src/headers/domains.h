#ifndef DOMAINS_H
#define DOMAINS_H

#include "common.h"
#include "util.h"

void init_domains(dom_t domains[8], int n);
double domain_distance(pos_t position, int domain);
void populate_domains(dom_t domains[8], pos_t *positions, int n);
void populate_domains_2(dom_t domains[8], pos_t *positions, int n);
void print_domains(dom_t domains[8]);

#endif  // DOMAINS_H