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
#include "output.h"
#include "my_vla.h"
#include "errors.h"

/*
 * I want Pixeldata output
 */
#define DEBUG_PRINT_PIXELDATA 0

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
    //char* path = "C:\\Users\\Moritz\\Dropbox\\Philip Scheer\\GS\\Aufgabe 3\\testBilder\\";
    char* path = "/Users/Philip/Dropbox/Studium/Moritz Höwer/GS/Aufgabe 3/testBilder/";
    //char* path = "/Users/Philip/Dropbox/Studium/Moritz Höwer/GS/Aufgabe 3/testBilder/Eigene/";

    // Eigene
    //char* filename = "Black_Square_256.bmp";
    //char* filename = "RGB_White_Black_256.bmp";
    //char* filename = "Black_Square_256_RLE.bmp";
    //char* filename = "RGB_White_Black_256_RLE.bmp";
    //char* filename = "Black_Square.bmp"; //writing works
    //char* filename = "RGB_White_Black.bmp";
    //char* filename = "Black_Square_asym.bmp";
    //char* filename = "Black_Square_asym_256.bmp";
    //char* filename = "Black_Square_asym_256_RLE.bmp"; // ?!

    // TestBilder
    //char* filename = "amrandrle.bmp";
    //char* filename = "amrandrle_NO_BLUE_LINES.bmp";
    //char* filename = "amrandrleMod.bmp"; //FAILS (index out of bounds)
    //char* filename = "anderegroesse.bmp";
    char* filename = "aufgabe3_bild1.bmp";
    //char* filename = "aufgabe3_bild2.bmp";
    //char* filename = "rotmitlochamrand.bmp";
    //char* filename = "rotmitlochrle.bmp";
    //char* filename = "rotmitlochrlemod1.bmp"; // FAILS (index out of bounds)
    //char* filename = "rotmitlochrlemod2.bmp";
    //char* filename = "rotmitlochrlemod3.bmp"; // FAILS (width is 50.331.776 and malloc fails)
    //char* filename = "rotmitlochrlemod4.bmp"; // FAILS (width is 3.014.656 and malloc fails)
    //char* filename = "rotmitlochrleundpunkt.bmp";

    // Stand 26.10. ==> 2 / 13 funktionieren
    // Stand 29.10. ==> 9 / 13 funktionieren (die beiden OOM sind nicht unsere schuld)

    char filepath[200] = { 0 };
    strcat(filepath, path);
    strcat(filepath, filename);

    res = input_read_file(filepath, &bm);

    printf("W=%d, H=%d\n", bm.infoHeader.biWidth, bm.infoHeader.biHeight);
    printf("Mode=%d, Compression=%d\n", bm.infoHeader.biBitCount,
            bm.infoHeader.biCompression);

    if (res == 0) {
        printf("\nPixel Data\n");

        int red = 0;
        int green = 0;

        typedef struct {
            int x;
            int y;
        } pos;

        bool firstRed = true;
        pos red_start;
        pos red_end;

        bool firstGreen = true;
        pos green_start;
        pos green_end;

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
#if DEBUG_PRINT_PIXELDATA
                printf("(%3d %3d %3d)", p.red, p.green, p.blue);
#endif

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


                /**
                 * das selbe in Grün hahahaha
                 */
                if (!green && equal(p, GREEN)) {
                    green = 1;
                    if (firstGreen) {
                        firstGreen = false;
                        green_start.x = x;
                        green_start.y = y;
                    }
                } else if (green && !equal(p, GREEN)) {
                	green = 0;
                    if (x == 0) {
                    	green_end.x = bm.imageData.width;
                        green_end.y = y - 1;
                    } else {
                    	green_end.x = x - 1;
                        green_end.y = y;
                    }
                }
            }
#if DEBUG_PRINT_PIXELDATA
            printf("\n");
#endif
        }

        //free(bm.imageData.data);
        // Red from 56/110 to 280/249
        // Green from 302/192 to 566/436
        printf("Red from (%d | %d) to (%d | %d)\n", red_start.x, red_start.y,
                red_end.x, red_end.y);
        printf("Green from (%d | %d) to (%d | %d)\n", green_start.x, green_start.y,
                green_end.x, green_end.y);


        char saveFilePath[100] = { 0 };
        strcat(saveFilePath, path);
        strcat(saveFilePath, "testSpeichern.bmp");

        res = output_write_file(saveFilePath, &bm);

    } else {
        if (res == E_BAD_BITMAP) {
            printf("Bad Bitmap");
        } else if (res == E_FAILED_TO_READ) {
            printf("Failed to Read");
            perror("Deswegen");
        } else if (res == E_INDEX_OUT_OF_BOUNDS) {
            printf("Index out of Bounds");
        } else if (res == E_NO_MEMORY) {
            printf("Out of memory");
        } else if (res == E_FAILED_TO_WRITE) {
            printf("Failed to Write");
        } else {
            printf("Irgendein Fehler");
        }

    }

    return EXIT_SUCCESS;
}
