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
#include "output.h"
#include "errors.h"




/*
 * Writes a file to the file System
 */
int output_write_file(char* path, Bitmap* bitmap) {
	FILE *save = fopen(path, "r+b");
	fwrite(&bitmap, sizeof(bitmap), 1, save);
	if(save == NULL) {
		return E_FAILED_TO_WRITE;
	}


	return 0;
}
