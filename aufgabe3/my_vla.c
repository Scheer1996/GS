/** ****************************************************************
 * @file    aufgabe3/my_vla.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    25.10.2016
 * @brief   Implementation for VLA
 ******************************************************************
 */
#include "my_vla.h"
#include "errors.h"

/*
 * Gets a value from the VLA
 */
int vla_get(int x, int y, VLA *vla, PixelData *ref) {
    // Check for valid indices
    if (x < 0 || x > vla->width) {
        return E_INDEX_OUT_OF_BOUNDS;
    }
    if (y < 0 || y > vla->height) {
        return E_INDEX_OUT_OF_BOUNDS;
    }

    // calculate offset
    int offset = x * vla->height + y;

    *ref = vla->data[offset];
    return 0;
}

/*
 * Sets a value in the VLA
 */
int vla_set(int x, int y, VLA *vla, PixelData data) {
    // Check for valid indices
    if (x < 0 || x > vla->width) {
        return E_INDEX_OUT_OF_BOUNDS;
    }
    if (y < 0 || y > vla->height) {
        return E_INDEX_OUT_OF_BOUNDS;
    }

    // calculate offset
    int offset = x * vla->height + y;

    vla->data[offset] = data;
    return 0;
}

