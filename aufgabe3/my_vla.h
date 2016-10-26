/** ****************************************************************
 * @file    aufgabe3/my_vla.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    26.10.2016
 * @brief   Header for My VLA Module
 ******************************************************************
 */
#ifndef _MY_VLA_H
#define _MY_VLA_H

#include "bitmap_types.h"

/**
 * Gets a value from the VLA
 *
 * @param x the x position
 * @param y the y postition
 * @param vla the VLA to read from
 * @param ref pointer to where the result should be stored
 * @return error code
 * @retval 0 no error
 * @retval E_INDEX_OUT_OF_BOUNDS the index (x/y) is out of bounds
 */
int vla_get(int x, int y, VLA *vla, PixelData *ref);

/**
 * Sets a value in the VLA
 *
 * @param x the x position
 * @param y the y position
 * @param vla the VLA to read from
 * @param data the data to insert
 * @return error code
 * @retval 0 no error
 * @retval E_INDEX_OUT_OF_BOUNDS the index (x/y) is out of bounds
 */
int vla_set(int x, int y, VLA *vla, PixelData data);

#endif /* _MY_VLA_H */
