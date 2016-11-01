/** ****************************************************************
 * @file    aufgabe3/analyze.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    31.10.2016
 * @brief   Analization of the bitmap
 ******************************************************************
 */

#ifndef ANALYZE_H_
#define ANALYZE_H_

#include "bitmap_types.h"

/**
 * Structure for a Rectangle
 */
typedef struct {
    PixelData color;
    int x_start;
    int x_end;
    int y_start;
    int y_end;

} Rectangle;

/**
 * @brief Analizes the Bitmap
 *
 * @param[in] bm the Bitmap to analyse
 * @return error code
 * @retval 0 no error
 */
int analyze_bitmap(Bitmap *bm);

#endif /* ANALYZE_H_ */
