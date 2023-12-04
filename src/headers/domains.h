#ifndef DOMAINS_H
#define DOMAINS_H

#include "common.h"
#include "util.h"

void init_domains(dom_t domains[8], int n);
void populate_domains(dom_t domains[8], pos_t *positions, int n);

#endif  // DOMAINS_H