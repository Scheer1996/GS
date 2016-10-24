/** ****************************************************************
 * @file    aufgabe3/input.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    24.10.2016
 * @brief   Implementation for the Input module
 ******************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "errors.h"

#define COLOR_TABLE_SIZE 256

/**
 *
 * @param file
 * @param fileHeader
 * @param infoHeader
 * @return
 */
static int read_headers(FILE* file, BitmapFileHeader *fileHeader,
        BitmapInfoHeader *infoHeader) {
    size_t readSize;

    //Read file header
    readSize = fread(fileHeader, sizeof(BitmapFileHeader), 1, file);
    if (readSize != 1) {
        return E_FAILED_TO_READ;
    }

    // Read info header
    readSize = fread(infoHeader, sizeof(BitmapInfoHeader), 1, file);
    if (readSize != 1) {
        return E_FAILED_TO_READ;
    }

    return 0;
}
/**
 *
 * @param file
 * @return
 */
static ColorTableEntry* read_color_table(FILE* file) {
    size_t readSize;

    ColorTableEntry *colorTable = (ColorTableEntry*) malloc(
            sizeof(ColorTableEntry) * COLOR_TABLE_SIZE);
    if (colorTable == NULL) {
        return NULL;
    }

    readSize = fread(colorTable, sizeof(ColorTableEntry), 256, file);
    if (readSize != 256) {
        free(colorTable);
        return NULL;
    }
    return colorTable;
}

static int read_pixels_24bit(FILE* file, ImageData* image_data) {
    return 0;
}

static int read_pixels_8bit(FILE* file, ColorTableEntry* color_table,
        ImageData* image_data) {
    size_t readSize;
    unsigned char index;

    // allocate memory for all pixels
    PixelData *data = (PixelData*) malloc(
            sizeof(PixelData) * image_data->width * image_data->height);
    if (data == NULL) {
        return E_FAILED_TO_READ;
    }

    // Read image
    for (int i = 0; i < image_data->width; i++) {
        for (int j = 0; j < image_data->height; j++) {
            readSize = fread(&index, sizeof(index), 1, file);
            if (readSize != 1 || index < 0 || index > COLOR_TABLE_SIZE) {
                free(data);
                return E_FAILED_TO_READ;
            }
            //create color from pixel data
            ColorTableEntry c = color_table[index];
            PixelData p = {c.blue, c.green, c.red};
            data[image_data->height * i + j] = p;
        }
    }
    image_data->data = data;
    return 0;
}

/*
 * Reads a file and writes the data to bitmap.
 */
int input_read_file(char* path, Bitmap* bitmap) {
    FILE* bmpFile;

    // Open file
    printf("Opening %s...", path);
    bmpFile = fopen(path, "r");
    if (bmpFile == NULL) {
        return E_FAILED_TO_READ;
    }
    printf("Success!\n");

    // Read Headers
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    int res;
    res = read_headers(bmpFile, &fileHeader, &infoHeader);
    if (res != 0) {
        fclose(bmpFile);
        return E_FAILED_TO_READ;
    }

    // TODO: Check if it actually has a color table...

    // Read color table
    ColorTableEntry *color_table;
    color_table = read_color_table(bmpFile);
    if (color_table == NULL) {
        fclose(bmpFile);
        return E_FAILED_TO_READ;
    }

    printf("Color Table:\n");
    for (int i = 0; i < 256; i++) {
        printf("R=%d, G=%d, B=%d\n", color_table[i].red, color_table[i].green,
                color_table[i].blue);
    }

    ImageData image_data;
    image_data.width = infoHeader.biWidth;
    image_data.height = infoHeader.biHeight;

    res = read_pixels_8bit(bmpFile, color_table, &image_data);
    if (res != 0) {
        free(color_table);
        fclose(bmpFile);
        return E_FAILED_TO_READ;
    }

    free(color_table);

    fclose(bmpFile);

    // Copy structures to return them
    bitmap->fileHeader = fileHeader;
    bitmap->infoHeader = infoHeader;
    bitmap->imageData = image_data;
    return 0;
}
