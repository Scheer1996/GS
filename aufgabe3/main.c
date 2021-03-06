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
#include "analyze.h"

/*
 * I want Pixeldata output
 */
#define DEBUG_PRINT_PIXELDATA 0

/**
 * program entry
 *
 * @return exit code
 */
int main(void) {
    Bitmap bm;
    int res;

    char* path = "C:\\Users\\abz254\\Downloads\\testBilder\\";
    //char* path = "C:\\Users\\Moritz\\Dropbox\\Philip Scheer\\GS\\Aufgabe 3\\testBilder\\Eigene\\";
    //char* path = "C:\\Users\\Moritz\\Dropbox\\Philip Scheer\\GS\\Aufgabe 3\\testBilder\\";
    //char* path = "/Users/Philip/Dropbox/Studium/Moritz Höwer/GS/Aufgabe 3/testBilder/";
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
    //char* filename = "aufgabe3_bild1.bmp";
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

    //superloop
    while(1)
    {
    	printf("Please select a File:\n");
    	printf("[1] amrandrle.bmp              [2] amrandrle_NO_BLUE_LINES.bmp \n");
    	printf("[3] amrandrleMod.bmp           [4] anderegroesse.bmp \n");
    	printf("[5] aufgabe3_bild1.bmp         [6] aufgabe3_bild2.bmp \n");
    	printf("[7] rotmitlochamrand.bmp       [8] rotmitlochrle.bmp \n");
    	printf("[9] rotmitlochrlemod1.bmp      [10] rotmitlochrlemod2.bmp \n");
    	printf("[11] rotmitlochrlemod3.bmp     [12] rotmitlochrlemod4.bmp \n");
    	printf("[13] rotmitlochrleundpunkt.bmp \n");

    	printf("File with Index: ");
    	int menuIndex;
    	scanf("%i", &menuIndex);
    	fflush(stdin);
    	char * filename;

    	switch(menuIndex) {
    		case 1: filename = "amrandrle.bmp";
    			break;
    		case 2: filename = "amrandrle_NO_BLUE_LINES.bmp";
    			break;
    		case 3: filename = "amrandrleMod.bmp";
    			break;
    		case 4: filename = "anderegroesse.bmp";
    			break;
    		case 5: filename = "aufgabe3_bild1.bmp";
    			break;
    		case 6: filename = "aufgabe3_bild2.bmp";
    			break;
    		case 7: filename = "rotmitlochamrand.bmp";
    			break;
    		case 8: filename = "rotmitlochrle.bmp";
    			break;
    		case 9: filename = "rotmitlochrlemod1.bmp";
    			break;
    		case 10: filename = "rotmitlochrlemod2.bmp";
    			break;
    		case 11: filename = "rotmitlochrlemod3.bmp";
    			break;
    		case 12: filename = "rotmitlochrlemod4.bmp";
    			break;
    		case 13: filename = "rotmitlochrleundpunkt.bmp";
    			break;

    		default: return EXIT_SUCCESS;
    	}

		char filepath[200] = { 0 };
		strcat(filepath, path);
		strcat(filepath, filename);

		res = input_read_file(filepath, &bm);

		printf("W=%d, H=%d\n", bm.infoHeader.biWidth, bm.infoHeader.biHeight);
		printf("Mode=%d, Compression=%d\n", bm.infoHeader.biBitCount,
				bm.infoHeader.biCompression);

		if (res == 0) {
#if DEBUG_PRINT_PIXELDATA
		    printf("\nPixel Data\n");
			for (int y = 0; y < bm.imageData.height; y++) {
				for (int x = 0; x < bm.imageData.width; x++) {
					PixelData p;
					if (vla_get(x, y, &bm.imageData, &p) != 0) {
						printf("Oh Oh, gaaaanz schlecht\n");
						break;
					}

					printf("(%3d %3d %3d)", p.red, p.green, p.blue);
				}
				printf("\n");

			}
#endif
			printf("Analyse:\n");
			analyze_bitmap(&bm);

			char saveFilePath[200] = { 0 };
			strcat(saveFilePath, path);
			strcat(saveFilePath, "saved_");
            strcat(saveFilePath, filename);

			res = output_write_file(saveFilePath, &bm);

			if(res == E_FAILED_TO_WRITE) {
				printf("Failed to Write");
			} else if (res == E_INDEX_OUT_OF_BOUNDS) {
				printf("Index out of Bounds");
			}

			free(bm.imageData.data);

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
			} else {
				printf("Irgendein Fehler");
			}

		}

		printf("\n--------------------------------------------------------\n\n");
	}

    return EXIT_SUCCESS;
}
