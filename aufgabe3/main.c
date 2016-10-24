/** ****************************************************************
 * @file    aufgabe3/main.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    24.10.2016
 * @brief   Main Program
 ******************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include "input.h"

/**
 * program entry
 *
 * @return exit code
 */
int main(void) {
    Bitmap bm;
    int res;

    res = input_read_file("E:\\Desktop\\testBilder\\aufgabe3_bild1.bmp", &bm);
    if (res == 0) {
        printf("W=%d, H=%d, P=%d\n", bm.infoHeader.biWidth,
                bm.infoHeader.biHeight, bm.infoHeader.biPlanes);
        printf("Mode=%d, Compression=%d\n", bm.infoHeader.biBitCount,
                bm.infoHeader.biCompression);
        printf("Color Used=%d, Important=%d\n", bm.infoHeader.biClrUsed,
                bm.infoHeader.biClrImportant);
        printf("\nPixel Data\n");

        // Red from 55/110 to 281/250
        int red = 0;

        for (int i = 0; i < bm.imageData.width; i++) {
            for (int j = 0; j < bm.imageData.height; j++) {
                PixelData p = ((PixelData*) bm.imageData.data)[i
                        * bm.imageData.height + j];
                if (!red && p.red == 255 && p.green == 0 && p.blue == 0) {
                    red = 1;
                    printf("Red starts at (%3d %3d) ", i, j);
                } else if (red && p.red != 255) {
                    red = 0;
                    printf("Red ends at (%3d %3d)\n ", i, j);
                }
            }
        }

        free(bm.imageData.data);
    }

    return 0;
}
