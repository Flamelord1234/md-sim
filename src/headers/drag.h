#ifndef DRAG_H
#define DRAG_H

#include "common.h"

drg_t init_drag();
drg_t update_drag(drg_t drag, tmp_t temperature, double tdelta);

#endif  // DRAG_H