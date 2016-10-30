/** ****************************************************************
 * @file    aufgabe3/output.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    29.10.2016
 * @brief   Implementation for the Output module
 ******************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors.h"
#include "my_vla.h"
#include "output.h"




/*
 * Writes a file to the file System
 */
int output_write_file(char* path, Bitmap* bitmap) {
	FILE *save = fopen(path, "r+b");
	if(save == NULL) {
		save = fopen(path, "w+b");
		if(save == NULL) {
			return E_FAILED_TO_WRITE;
		}
	}
	bitmap->fileHeader.bfOffBits = sizeof(bitmap->fileHeader) + sizeof(bitmap->infoHeader);



	bitmap->infoHeader.biBitCount = 8;
	bitmap->infoHeader.biCompression = 0;


	fwrite(&bitmap->fileHeader, sizeof(bitmap->fileHeader), 1, save);
	fwrite(&bitmap->infoHeader, sizeof(bitmap->infoHeader), 1, save);

	VLA* image_data = &bitmap->imageData;

    // Readout VLA
    for (int y = image_data->height - 1; y >= 0; y--) {
        for (int x = 0; x < image_data->width; x++) {
            PixelData p;
            if(vla_get(x, y, image_data, &p) != 0) {
            	return E_INDEX_OUT_OF_BOUNDS;
            }
            fwrite(&p, sizeof(p), 1, save);
        }
    }

	fclose(save);

	return 0;
}
