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
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "my_vla.h"
#include "errors.h"

static bool equal(PixelData p1, PixelData p2) {
    return p1.red == p2.red && p1.green == p2.green && p1.blue == p2.blue;
}

/**
 * program entry
 *
 * @return exit code
 */
int main(void) {
    Bitmap bm;
    int res;

    //char* path = "C:\\Users\\abz254\\Downloads\\testBilder\\Eigene\\";
    //char* path = "C:\\Users\\Moritz\\Dropbox\\Philip Scheer\\GS\\Aufgabe 3\\testBilder\\Eigene\\";
    char* path = "C:\\Users\\Moritz\\Dropbox\\Philip Scheer\\GS\\Aufgabe 3\\testBilder\\";

    // Eigene
    //char* filename = "Black_Square_256.bmp";
    //char* filename = "RGB_White_Black_256.bmp";
    //char* filename = "Black_Square_256_RLE.bmp";
    //char* filename = "RGB_White_Black_256_RLE.bmp";
    //char* filename = "Black_Square.bmp";
    //char* filename = "RGB_White_Black.bmp";
    //char* filename = "Black_Square_asym.bmp";
    //char* filename = "Black_Square_asym_256.bmp";
    //char* filename = "Black_Square_asym_256_RLE.bmp";

    // TestBilder
    //char* filename = "amrandrle.bmp"; //FAILS (failed to read (510/479))
    //char* filename = "amrandrle_NO_BLUE_LINES.bmp";
    //char* filename = "amrandrleMod.bmp"; //FAILS (failed to read (510/479))
    //char* filename = "anderegroesse.bmp"; // FAILS (index out of bounds (721/256))
    char* filename = "aufgabe3_bild1.bmp";
    //char* filename = "aufgabe3_bild2.bmp"; // FAILS (absolute mode x zu gross (641/426))
    //char* filename = "rotmitlochamrand.bmp"; // FAILS (index out of bounds (641/446))
    //char* filename = "rotmitlochrle.bmp"; // FAILS (absolute mode x zu gross (641/446))
    //char* filename = "rotmitlochrlemod1.bmp"; // FAILS (index out of bounds (129/479)
    //char* filename = "rotmitlochrlemod2.bmp"; // FAILS (failed to read (163/443))
    //char* filename = "rotmitlochrlemod3.bmp"; // FAILS (width is 50.331.776 and malloc fails)
    //char* filename = "rotmitlochrlemod4.bmp"; // FAILS (width is 3.014.656 and malloc fails)
    //char* filename = "rotmitlochrleundpunkt.bmp"; // FAILS (absolute mode x zu gross (641/446))

    // Stand 26.10. ==> 2 / 13 funktionieren

    char filepath[100] = { 0 };
    strcat(filepath, path);
    strcat(filepath, filename);

    res = input_read_file(filepath, &bm);

    printf("W=%d, H=%d\n", bm.infoHeader.biWidth, bm.infoHeader.biHeight);
    printf("Mode=%d, Compression=%d\n", bm.infoHeader.biBitCount,
            bm.infoHeader.biCompression);

    if (res == 0) {
        printf("\nPixel Data\n");

        int red = 0;

        typedef struct {
            int x;
            int y;
        } pos;

        bool firstRed = true;
        pos red_start;
        pos red_end;

        PixelData RED = { 0, 0, 255 };
        PixelData GREEN = { 0, 255, 0 };
        PixelData BLUE = { 255, 0, 0 };
        PixelData WHITE = { 255, 255, 255 };
        PixelData BLACK = { 0, 0, 0 };

        for (int y = 0; y < bm.imageData.height; y++) {
            for (int x = 0; x < bm.imageData.width; x++) {
                PixelData p;
                if (vla_get(x, y, &bm.imageData, &p) != 0) {
                    printf("Oh Oh, gaaaanz schlecht\n");
                    break;
                }

                //printf("(%3d %3d %3d)", p.red, p.green, p.blue);

                if (!red && equal(p, RED)) {
                    red = 1;
                    if (firstRed) {
                        firstRed = false;
                        red_start.x = x;
                        red_start.y = y;
                    }
                } else if (red && !equal(p, RED)) {
                    red = 0;
                    if (x == 0) {
                        red_end.x = bm.imageData.width;
                        red_end.y = y - 1;
                    } else {
                        red_end.x = x - 1;
                        red_end.y = y;
                    }
                }
            }
            //printf("\n");
        }

        free(bm.imageData.data);

        // Red from 56/110 to 280/249
        // Green from 302/192 to 566/436
        printf("Red from (%d | %d) to (%d | %d)\n", red_start.x, red_start.y,
                red_end.x, red_end.y);

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
