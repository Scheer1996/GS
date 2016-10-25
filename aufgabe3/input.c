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
#include "my_vla.h"
#include <stdbool.h>

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

    ColorTableEntry *colorTable = (ColorTableEntry*) calloc(
    COLOR_TABLE_SIZE, sizeof(ColorTableEntry));
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

/**
 *
 * @param file
 * @param image_data
 * @return
 */
static int read_pixels_24bit(FILE* file, VLA* image_data) {
    size_t readSize;
    PixelData pData;

    // allocate memory for all pixels
    PixelData *data = (PixelData*) calloc(
            image_data->width * image_data->height, sizeof(PixelData));
    if (data == NULL) {
        return E_FAILED_TO_READ;
    }

    image_data->data = data;

    // Read image
    for (int i = 0; i < image_data->width; i++) {
        for (int j = 0; j < image_data->height; j++) {
            readSize = fread(&pData, sizeof(pData), 1, file);
            if (readSize != 1) {
                free(data);
                return E_FAILED_TO_READ;
            }

            // write to VLA
            if (vla_set(i, j, image_data, pData) != 0) {
                free(data);
                return E_INDEX_OUT_OF_BOUNDS;
            }
        }
    }

    return 0;
}

/**
 *
 * @param file
 * @param color_table
 * @param image_data
 * @return
 */
static int read_pixels_8bit(FILE* file, ColorTableEntry* color_table,
        VLA* image_data) {
    size_t readSize;
    unsigned char index;

    // allocate memory for all pixels
    PixelData *data = (PixelData*) calloc(
            image_data->width * image_data->height, sizeof(PixelData));
    if (data == NULL) {
        return E_FAILED_TO_READ;
    }

    image_data->data = data;

    // Read image
    for (int i = 0; i < image_data->width; i++) {
        for (int j = 0; j < image_data->height; j++) {
            readSize = fread(&index, sizeof(index), 1, file);
            if (readSize != 1) {
                free(data);
                return E_FAILED_TO_READ;
            }
            //create color from pixel data
            ColorTableEntry c = color_table[index];
            PixelData p = { c.blue, c.green, c.red };

            if (vla_set(i, j, image_data, p) != 0) {
                free(data);
                return E_INDEX_OUT_OF_BOUNDS;
            }
        }
    }

    return 0;
}

/**
 *
 * @param b1
 * @param b2
 * @param file
 * @return
 */
static int read_two_bytes(unsigned char *b1, unsigned char *b2, FILE* file) {
    size_t readSize;
    readSize = fread(b1, sizeof(*b1), 1, file);
    if (readSize != 1) {
        return E_FAILED_TO_READ;
    }

    readSize = fread(b2, sizeof(*b2), 1, file);
    if (readSize != 1) {
        return E_FAILED_TO_READ;
    }
    return 0;
}

/**
 *
 * @param file
 * @param color_table
 * @param image_data
 * @return
 */
static int read_pixels_8bit_rle(FILE* file, ColorTableEntry* color_table,
        VLA* image_data) {

    // allocate memory for all pixels
    PixelData *data = (PixelData*) calloc(
            image_data->width * image_data->height, sizeof(PixelData));
    if (data == NULL) {
        return E_FAILED_TO_READ;
    }

    image_data->data = data;

    // two bytes
    unsigned char b1, b2;

    bool was_absolute = false;
    int current_x = 0;
    int current_y = 0;
    size_t readSize;

    while (1) {
        if (was_absolute) {
            was_absolute = false;

            readSize = fread(&b1, sizeof(b1), 1, file);
            if (readSize != 1) {
                free(data);
                return E_FAILED_TO_READ;
            }

            if (b1 == 0) {
                // EOL
                current_x = 0;
                current_y++;

                // Read two bytes from Image
                if (read_two_bytes(&b1, &b2, file)) {
                    free(data);
                    return E_FAILED_TO_READ;
                }
            } else if (b1 == 1) {
                // EOF
                break;
            } else {
                readSize = fread(&b2, sizeof(b2), 1, file);
                if (readSize != 1) {
                    free(data);
                    return E_FAILED_TO_READ;
                }
            }
        } else {
            // Read two bytes from Image
            if (read_two_bytes(&b1, &b2, file)) {
                free(data);
                return E_FAILED_TO_READ;
            }
        }

        if (b1 == 0) {
            // control sequence
            if (b2 == 0) {
                // EOL
                current_y++;
                current_x = 0;
            } else if (b2 == 1) {
                // EOF
                break;
            } else if (b2 == 2) {
                // delta
                // DEBUG CODE !!!
                printf("\nDELTA found :)\n");
                // DEBUG CODE !!!

                // Read next two bytes (movement instructions)
                if (read_two_bytes(&b1, &b2, file)) {
                    free(data);
                    return E_FAILED_TO_READ;
                }
                current_x += b1;
                current_y -= b2;

            } else {
                // absolute mode
                was_absolute = true;

                //b2 has number of pixels in absolute mode
                for (int i = 0; i < b2; i++) {
                    readSize = fread(&b1, sizeof(b1), 1, file);
                    if (readSize != 1) {
                        free(data);
                        return E_FAILED_TO_READ;
                    }
                    // get color and write it to VLA
                    ColorTableEntry c = color_table[b1];
                    PixelData p = { c.blue, c.green, c.red };

                    if (vla_set(current_y, current_x, image_data, p) != 0) {
                        free(data);
                        return E_INDEX_OUT_OF_BOUNDS;
                    }

                    // increment x
                    current_x++;
                }

                // read next pixel
                readSize = fread(&b1, sizeof(b1), 1, file);
                if (readSize != 1) {
                    free(data);
                    return E_FAILED_TO_READ;
                }
            }
        } else {
            // b1 ist amount, b2 is color index
            ColorTableEntry c = color_table[b2];
            PixelData p = { c.blue, c.green, c.red };

            for (int i = 0; i < b1; i++) {
                // write pixel b1 times
                if (vla_set(current_y, current_x, image_data, p) != 0) {
                    free(data);
                    return E_INDEX_OUT_OF_BOUNDS;
                }
                current_x++;
            }
        }

    }

    return 0;
}

static bool is_valid(BitmapFileHeader *fileHeader, BitmapInfoHeader *infoHeader) {
    // check file header
    if (fileHeader->bfType != 0x4d42) {
        return false;
    }

    if (fileHeader->bfReserved1 != 0 || fileHeader->bfReserved2 != 0) {
        return false;
    }

    // check info header
    if (infoHeader->biSize != 40) {
        return false;
    }

    if (infoHeader->biWidth < 0 || infoHeader->biHeight < 0) {
        return false;
    }

    if (infoHeader->biPlanes != 1) {
        return false;
    }

    if (infoHeader->biBitCount != 8 && infoHeader->biBitCount != 24) {
        return false;
    }

    if (infoHeader->biCompression != 1 && infoHeader->biCompression != 0) {
        return false;
    }

    if (infoHeader->biClrUsed != 0 && infoHeader->biClrImportant != 0) {
        return false;
    }

    return true;
}

/*
 * Reads a file and writes the data to bitmap.
 */
int input_read_file(char* path, Bitmap* bitmap) {
    FILE* bmpFile;

    // Open file
    bmpFile = fopen(path, "r");
    if (bmpFile == NULL) {
        return E_FAILED_TO_READ;
    }

    // Read Headers
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    int res;
    res = read_headers(bmpFile, &fileHeader, &infoHeader);
    if (res != 0) {
        fclose(bmpFile);
        return E_FAILED_TO_READ;
    }

    // Check integrity
    if (!is_valid(&fileHeader, &infoHeader)) {
        fclose(bmpFile);
        return E_BAD_BITMAP;
    }

    // DEBUG CODE!!!
    bitmap->fileHeader = fileHeader;
    bitmap->infoHeader = infoHeader;
    // DEBUG CODE!!!

    VLA image_data;
    image_data.width = infoHeader.biWidth;
    image_data.height = infoHeader.biHeight;

    if (infoHeader.biBitCount == 8) {
        // 256 color Bitmap (8 bit)

        // Read color table
        ColorTableEntry *color_table;
        color_table = read_color_table(bmpFile);
        if (color_table == NULL) {
            fclose(bmpFile);
            return E_FAILED_TO_READ;
        }

        if (infoHeader.biCompression == 0) {
            // Bitmap is uncompressed
            res = read_pixels_8bit(bmpFile, color_table, &image_data);
        } else {
            // Bitmap is compressed
            res = read_pixels_8bit_rle(bmpFile, color_table, &image_data);
        }
        free(color_table);
        if (res != 0) {
            fclose(bmpFile);
            return E_FAILED_TO_READ;
        }
    } else {
        // 24 bit bitmap
        res = read_pixels_24bit(bmpFile, &image_data);
        if (res != 0) {
            fclose(bmpFile);
            return E_FAILED_TO_READ;
        }

    }
    fclose(bmpFile);

    // Copy structures to return them
    bitmap->fileHeader = fileHeader;
    bitmap->infoHeader = infoHeader;
    bitmap->imageData = image_data;
    return 0;
}
