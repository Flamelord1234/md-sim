#include "headers/drag.h"

drg_t init_drag() {
    return 0;
}

drg_t update_drag(drg_t drag, tmp_t temperature, double tdelta) {
    return drag + ((tdelta / (tdamp * tdamp)) * (temperature / tempdes - 1));
}