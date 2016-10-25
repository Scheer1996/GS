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
#include "my_vla.h"
#include "errors.h"

/**
 * program entry
 *
 * @return exit code
 */
int main(void) {
    Bitmap bm;
    int res;

    //char* filename = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\Black_Square_256.bmp";
    //char* filename = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\RGB_White_Black_256.bmp";
    char* filename = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\Black_Square_256_RLE.bmp";
    //char* filename = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\RGB_White_Black_256_RLE.bmp";
    //char* filename = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\Black_Square.bmp";
    //char* filename = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\RGB_White_Black.bmp";
    //char* filename = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\aufgabe3_bild1_kleiner.bmp";

    res = input_read_file(filename, &bm);

    printf("W=%d, H=%d\n", bm.infoHeader.biWidth, bm.infoHeader.biHeight);
    printf("Mode=%d, Compression=%d\n", bm.infoHeader.biBitCount,
            bm.infoHeader.biCompression);

    if (res == 0) {
        printf("\nPixel Data\n");

        // Red from 55/110 to 281/250
        /*int red = 0;*/

        for (int i = 0; i < bm.imageData.width; i++) {
            for (int j = 0; j < bm.imageData.height; j++) {
                PixelData p;
                if (vla_get(i, j, &bm.imageData, &p) != 0) {
                    printf("Oh Oh, gaaaanz schlecht\n");
                    break;
                }

                printf("(%3d %3d %3d) ", p.red, p.green, p.blue);
                /*if (!red && p.red == 255 && p.green == 0 && p.blue == 0) {
                 red = 1;
                 printf("Red starts at (%3d %3d) ", i, j);
                 } else if (red && p.red != 255) {
                 red = 0;
                 printf("Red ends at (%3d %3d)\n ", i, j);
                 }*/
            }
            printf("\n");
        }

        free(bm.imageData.data);
    } else {
        if (res == E_BAD_BITMAP) {
            printf("Bad Bitmap");
        } else {
            if (res == E_FAILED_TO_READ) {
                printf("Failed to read");
            }
        }
    }

    return EXIT_SUCCESS;
}
