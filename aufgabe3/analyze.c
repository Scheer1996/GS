/** ****************************************************************
 * @file    aufgabe3/analyze.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    31.10.2016
 * @brief   Analization of the bitmap
 ******************************************************************
 */
#include <stdbool.h>
#include <stdio.h>
#include "my_vla.h"
#include "errors.h"
#include "list.h"

#define MIN_SIZE 3

/**
 * The color Red
 */
const PixelData RED = { 0, 0, 255 };

/**
 * The color Green
 */
const PixelData GREEN = { 0, 255, 0 };

/**
 * @brief Checks whether two PixelData structs are equal
 *
 * @param[in] p1 PixelData 1
 * @param[in] p2 PixelData 2
 * @return whether they are equal or not
 */
static bool equal(PixelData p1, PixelData p2) {
    return p1.red == p2.red && p1.green == p2.green && p1.blue == p2.blue;
}

/*
 * Analizes the Bitmap
 */
int analyze_bitmap(Bitmap *bm) {
    // create 2 lists
    List rectangles;
    List *pRects = &rectangles;
    List potential_rectangles;
    List *pPot_rects = &potential_rectangles;
    list_init(pRects);
    list_init(pPot_rects);

    bool is_red = false;
    bool is_green = false;
    Rectangle rect;
    for (int y = 0; y < bm->imageData.height; y++) {
        for (int x = 0; x < bm->imageData.width; x++) {
            PixelData p;
            if (vla_get(x, y, &bm->imageData, &p) != 0) {
                printf("Oh Oh, gaaaanz schlecht\n");
                break;
            }

            // find Red rectangles
            if (equal(p, RED) && !is_red) {
                is_red = true;
                rect.color = RED;
                rect.x_start = x;
                rect.y_start = y;
            } else if (is_red && !equal(p, RED)) {
                is_red = false;
                rect.x_end = x - 1;
                rect.y_end = y;
                if (rect.x_end - rect.x_start >= MIN_SIZE) {
                    // the rectangle is big enough to count
                    // check potential rects:
                    Iterator it = list_get_iterator(pPot_rects);
                    Rectangle r;
                    bool already_there = false;
                    while (iterator_has_next(&it)) {
                        iterator_next(&it, &r);
                        if (equal(r.color, rect.color)
                                && r.x_start == rect.x_start
                                && r.x_end == rect.x_end) {
                            // element is present, update y_end
                            already_there = true;
                            r.y_end = y;
                            iterator_update(&it, r);
                            break;
                        } else {
                            if (r.y_end != y && r.x_start < x - 1) {
                                // the rectangle has passed
                                if (r.y_end - r.y_start >= MIN_SIZE) {
                                    // rectangle is big enough to count
                                    list_append(pRects, r);
                                }
                                iterator_remove(&it);
                            }
                        }
                    }
                    if (!already_there) {
                        list_append(pPot_rects, rect);
                    }
                }
            }

            // find Green rectangles
            if (equal(p, GREEN) && !is_green) {
                is_green = true;
                rect.color = GREEN;
                rect.x_start = x;
                rect.y_start = y;
            } else if (is_green && !equal(p, GREEN)) {
                is_green = false;
                rect.x_end = x - 1;
                rect.y_end = y;
                if (rect.x_end - rect.x_start >= MIN_SIZE) {
                    // the rectangle is big enough to count
                    // check potential rects:
                    Iterator it = list_get_iterator(pPot_rects);
                    Rectangle r;
                    bool already_there = false;
                    while (iterator_has_next(&it)) {
                        iterator_next(&it, &r);
                        if (equal(r.color, rect.color)
                                && r.x_start == rect.x_start
                                && r.x_end == rect.x_end) {
                            // element is present, update y_end
                            already_there = true;
                            r.y_end = y;
                            iterator_update(&it, r);
                            break;
                        } else {
                            if (r.y_end != y && r.x_start < x - 1) {
                                // the rectangle has passed
                                if (r.y_end - r.y_start >= MIN_SIZE) {
                                    // rectangle is big enough to count
                                    list_append(pRects, r);
                                }
                                iterator_remove(&it);
                            }
                        }
                    }
                    if (!already_there) {
                        list_append(pPot_rects, rect);
                    }
                }

            }
        }
        if (is_red) {
            is_red = false;
            rect.x_end = bm->imageData.width - 1;
            rect.y_end = y;
            if (rect.x_end - rect.x_start >= MIN_SIZE) {
                // the rectangle is big enough to count
                // check potential rects:
                Iterator it = list_get_iterator(pPot_rects);
                Rectangle r;
                bool already_there = false;
                while (iterator_has_next(&it)) {
                    iterator_next(&it, &r);
                    if (equal(r.color, rect.color) && r.x_start == rect.x_start
                            && r.x_end == rect.x_end) {
                        // element is present, update y_end
                        already_there = true;
                        r.y_end = y;
                        iterator_update(&it, r);
                        break;
                    } else {
                        if (r.y_end != y) {
                            // the rectangle has passed
                            if (r.y_end - r.y_start >= MIN_SIZE) {
                                // rectangle is big enough to count
                                list_append(pRects, r);
                            }
                            iterator_remove(&it);
                        }
                    }
                }
                if (!already_there) {
                    list_append(pPot_rects, rect);
                }
            }
        }
        if (is_green) {
            is_green = false;
            rect.x_end = bm->imageData.width - 1;
            rect.y_end = y;
            if (rect.x_end - rect.x_start >= MIN_SIZE) {
                // the rectangle is big enough to count
                // check potential rects:
                Iterator it = list_get_iterator(pPot_rects);
                Rectangle r;
                bool already_there = false;
                while (iterator_has_next(&it)) {
                    iterator_next(&it, &r);
                    if (equal(r.color, rect.color) && r.x_start == rect.x_start
                            && r.x_end == rect.x_end) {
                        // element is present, update y_end
                        already_there = true;
                        r.y_end = y;
                        iterator_update(&it, r);
                        break;
                    } else {
                        if (r.y_end != y) {
                            // the rectangle has passed
                            if (r.y_end - r.y_start >= MIN_SIZE) {
                                // rectangle is big enough to count
                                list_append(pRects, r);
                            }
                            iterator_remove(&it);
                        }
                    }
                }
                if (!already_there) {
                    list_append(pPot_rects, rect);
                }
            }
        }
    }
    // finish all pending rectangles
    Iterator it = list_get_iterator(pPot_rects);
    Rectangle r;
    while (iterator_has_next(&it)) {
        iterator_next(&it, &r);
        if (r.y_end - r.y_start >= MIN_SIZE) {
            // rectangle is big enough to count
            list_append(pRects, r);
        }
        iterator_remove(&it);
    }

    it = list_get_iterator(pRects);
    while (iterator_has_next(&it)) {
        iterator_next(&it, &r);
        char* color = equal(r.color, RED) ? "RED" : "GREEN";
        printf("Rectangle [%s from (%d|%d) to (%d|%d)]\n", color, r.x_start,
                r.y_start, r.x_end, r.y_end);
    }

    list_clear(pRects);
    list_clear(pPot_rects);
    return 0;
}
