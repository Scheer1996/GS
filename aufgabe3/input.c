/** ****************************************************************
 * @file    aufgabe3/input.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    26.10.2016
 * @brief   Implementation for the Input module
 ******************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "errors.h"
#include "my_vla.h"
#include <stdbool.h>


/*
 * I want debug messages
 */
#define DEBUG_RLE 0

/**
 * reads the bitmap headers from a file
 *
 * @param[in]  file       the file to read from
 * @param[out] fileHeader pointer to where the file header should be stored
 * @param[out] infoHeader pointer to where the info header should be stored
 * @return error code
 * @retval 0                no error
 * @retval E_FAILED_TO_READ there was an error reading from the file
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
 * reads the color table from a file
 *
 * @param[in] file the file to read from
 * @return pointer to where the color table is stored on the heap
 * @retval NULL there was an error
 */
static ColorTableEntry* read_color_table(FILE* file) {
    size_t readSize;

    ColorTableEntry *colorTable = (ColorTableEntry*) calloc(
    COLOR_TABLE_SIZE, sizeof(ColorTableEntry));
    if (colorTable == NULL) {
        return NULL;
    }

    // read table
    readSize = fread(colorTable, sizeof(ColorTableEntry), COLOR_TABLE_SIZE,
            file);
    if (readSize != COLOR_TABLE_SIZE) {
        free(colorTable);
        return NULL;
    }
    return colorTable;
}

/**
 * reads pixel data from a file, assuming 24bit per pixel
 *
 * @param[in]      file       the file to read from
 * @param[in, out] image_data pointer to a structure containing width and
 *                            height of the image. Will contain pointer to
 *                            where pixel data is stored on the heap when done
 * @return error code
 * @retval 0                     no error
 * @retval E_FAILED_TO_READ      there was an error reading from the file
 * @retval E_NO_MEMORY           couldn't allocate sufficient memory
 * @retval E_INDEX_OUT_OF_BOUNDS tried to write to invalid indices in VLA
 */
static int read_pixels_24bit(FILE* file, VLA* image_data) {
    size_t readSize;
    PixelData pData;

    // allocate memory for all pixels
    PixelData *data = (PixelData*) calloc(
            image_data->width * image_data->height, sizeof(PixelData));
    if (data == NULL) {
        return E_NO_MEMORY;
    }

    image_data->data = data;

    // Read image
    for (int y = image_data->height - 1; y >= 0; y--) {
        for (int x = 0; x < image_data->width; x++) {
            readSize = fread(&pData, sizeof(pData), 1, file);
            if (readSize != 1) {
                free(data);
                return E_FAILED_TO_READ;
            }

            // write to VLA
            if (vla_set(x, y, image_data, pData) != 0) {
                free(data);
                return E_INDEX_OUT_OF_BOUNDS;
            }
        }
    }

    return 0;
}

/**
 * reads pixel data from a file, assuming 8bit per pixel
 *
 * @param[in]      file        the file to read from
 * @param[in]      color_table the color table for converting from color index to actual color
 * @param[in, out] image_data  pointer to a structure containing width and
 *                             height of the image. Will contain pointer to
 *                             where pixel data is stored on the heap when done
 * @return error code
 * @retval 0                     no error
 * @retval E_FAILED_TO_READ      there was an error reading from the file
 * @retval E_NO_MEMORY           couldn't allocate sufficient memory
 * @retval E_INDEX_OUT_OF_BOUNDS tried to write to invalid indices in VLA
 */
static int read_pixels_8bit(FILE* file, ColorTableEntry* color_table,
        VLA* image_data) {
    size_t readSize;
    unsigned char index;

    // allocate memory for all pixels
    PixelData *data = (PixelData*) calloc(
            image_data->width * image_data->height, sizeof(PixelData));
    if (data == NULL) {
        return E_NO_MEMORY;
    }

    image_data->data = data;

    // Read image
    for (int y = image_data->height - 1; y >= 0; y--) {
        for (int x = 0; x < image_data->width; x++) {
            readSize = fread(&index, sizeof(index), 1, file);
            if (readSize != 1) {
                free(data);
                return E_FAILED_TO_READ;
            }
            //create color from pixel data
            ColorTableEntry c = color_table[index];
            PixelData p = { c.blue, c.green, c.red };

            if (vla_set(x, y, image_data, p) != 0) {
                free(data);
                return E_INDEX_OUT_OF_BOUNDS;
            }
        }
    }

    return 0;
}

/**
 * reads two bytes from a file
 *
 * @param[out] b1   pointer to the first byte to read
 * @param[out] b2   pointer to the second byte to read
 * @param[in]  file the file to read from
 * @return error code
 * @retval 0                no error
 * @retval E_FAILED_TO_READ there was an error reading from the file
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
 * reads pixel data from a file, assuming 8 bit per pixel compressed with RLE encoding
 *
 * @param[in]      file        the file to read from
 * @param[in]      color_table the color table for converting from color index to actual color
 * @param[in, out] image_data  pointer to a structure containing width and
 *                             height of the image. Will contain pointer to
 *                             where pixel data is stored on the heap when done
 * @return error code
 * @retval 0                     no error
 * @retval E_FAILED_TO_READ      there was an error reading from the file
 * @retval E_NO_MEMORY           couldn't allocate sufficient memory
 * @retval E_INDEX_OUT_OF_BOUNDS tried to write to invalid indices in VLA
 */
static int read_pixels_8bit_rle(FILE* file, ColorTableEntry* color_table,
        VLA* image_data) {

    // allocate memory for all pixels
    PixelData *data = (PixelData*) calloc(
            image_data->width * image_data->height, sizeof(PixelData));
    if (data == NULL) {
        return E_NO_MEMORY;
    }

    image_data->data = data;

    unsigned char b1, b2;
    int current_x = 0;
    int current_y = image_data->height - 1; // image is stored "upside down"
    size_t readSize;

    while (1) {
        // Read two bytes from Image
        if (read_two_bytes(&b1, &b2, file)) {
            free(data);
            return E_FAILED_TO_READ;
        }
#if DEBUG_RLE
        printf("%02x %02x ", b1, b2);
#endif

        if (b1 == 0) {
            // control sequence
            if (b2 == 0) {
                // EOL
#if DEBUG_RLE
                printf("\n");
#endif
                current_y--;
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
                current_y += b2;

            } else {
                // absolute mode
#if DEBUG_RLE
                printf("ABS [");
#endif

                //b2 has number of pixels in absolute mode
                for (int i = 0; i < b2; i++) {

                    // read next byte
                    readSize = fread(&b1, sizeof(b1), 1, file);
                    if (readSize != 1) {
                        free(data);
                        return E_FAILED_TO_READ;
                    }
#if DEBUG_RLE
                    printf(" %02x", b1);
#endif

                    // get color and write it to VLA
                    ColorTableEntry c = color_table[b1];
                    PixelData p = { c.blue, c.green, c.red };

                    if (vla_set(current_x, current_y, image_data, p) != 0) {
                        free(data);
                        return E_INDEX_OUT_OF_BOUNDS;
                    }

                    // increment x
                    current_x++;
                }
#if DEBUG_RLE
                printf(" ] ");
#endif

                int align = b2 % WORD_SIZE;
                if (align != 0) {
                    // need to throw away some bits for aligning
                    align = WORD_SIZE - align;
#if DEBUG_RLE
                    printf("IGNORING %d FOR ALIGN ", align);
#endif
                    if (fseek(file, align, SEEK_CUR) != 0) {
                        free(data);
                        return E_FAILED_TO_READ;
                    }
                }

            }
        } else { /* if(b1 == 0) */
            // normal RLE mode
            // b1 ist amount, b2 is color index
            ColorTableEntry c = color_table[b2];
            PixelData p = { c.blue, c.green, c.red };

            for (int i = 0; i < b1; i++) {
                // write pixel b1 times
                if (vla_set(current_x, current_y, image_data, p) != 0) {
                    free(data);
                    return E_INDEX_OUT_OF_BOUNDS;
                }
                current_x++;
            }
        }

    }

    return 0;
}
/**
 * checks header fields for validity
 *
 * @param[in] fileHeader the bitmap file header
 * @param[in] infoHeader the buitmap info header
 * @retval true  bitmap is valid
 * @retval false bitmap is invalid
 */
static bool is_valid(BitmapFileHeader *fileHeader, BitmapInfoHeader *infoHeader) {
    // check file header
    // type must be BM (ASCII)
    if (fileHeader->bfType != BF_TYPE) {
        return false;
    }

    // reserved must be 0
    if (fileHeader->bfReserved1 != 0 || fileHeader->bfReserved2 != 0) {
        return false;
    }

    // check info header
    // info header size must be 40
    if (infoHeader->biSize != INFO_HEADER_SIZE) {
        return false;
    }

    // images width and height must be positive
    if (infoHeader->biWidth < 0 || infoHeader->biHeight < 0) {
        return false;
    }

    // planes must be one
    if (infoHeader->biPlanes != 1) {
        return false;
    }

    // bit count must be 8 or 24
    if (infoHeader->biBitCount != BITMAP_8BIT
            && infoHeader->biBitCount != BITMAP_24BIT) {
        return false;
    }

    // compression must be 0 or 1
    if (infoHeader->biCompression != COMPRESSION_RLE
            && infoHeader->biCompression != COMPRESSION_NONE) {
        return false;
    }

    // color used and color important must be 0
    if (infoHeader->biClrUsed != 0 || infoHeader->biClrImportant != 0) {
        return false;
    }

    // still with me? well seems like everything is good then
    return true;
}

/*
 * Reads a file and writes the data to bitmap.
 */
int input_read_file(char* path, Bitmap* bitmap) {
    FILE* bmpFile;

    // Open file
    bmpFile = fopen(path, "rb");
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

    // create structure for image data
    VLA image_data;
    image_data.width = infoHeader.biWidth;
    image_data.height = infoHeader.biHeight;

    // check type for choosing the correct read() method
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

        // we no longer need the color table, so free it before we forget
        free(color_table);

        // check whether reading worked
        if (res != 0) {
            fclose(bmpFile);
            return res;
        }
    } else {
        // 24 bit bitmap
        res = read_pixels_24bit(bmpFile, &image_data);
        if (res != 0) {
            fclose(bmpFile);
            return res;
        }

    }
    //everything went well ==> we can clean up now
    fclose(bmpFile);

    // Copy structures to return them
    bitmap->fileHeader = fileHeader;
    bitmap->infoHeader = infoHeader;
    bitmap->imageData = image_data;
    return 0;
}
