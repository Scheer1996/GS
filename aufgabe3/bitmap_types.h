/** ****************************************************************
 * @file    aufgabe3/bitmap_types.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    26.10.2016
 * @brief   Typedefs for the Bitmaps
 ******************************************************************
 */
#ifndef _BITMAP_TYPES_H
#define _BITMAP_TYPES_H

#include "ms_types.h"


/**
 * the size of the color table in the bitmap
 */
#define COLOR_TABLE_SIZE 256

/**
 * type "BM" for File Header
 */
#define BF_TYPE 0x4d42

/**
 * Info header Size
 */
#define INFO_HEADER_SIZE 40

/**
 * Bit count for 8 Bit
 */
#define BITMAP_8BIT 8

/**
 * Bit count for 24 Bit
 */
#define BITMAP_24BIT 24

/**
 * Info Header Bi Compression True
 */
#define COMPRESSION_RLE 1

/**
 * Info Header Bi Compression False
 */
#define COMPRESSION_NONE 0

/**
 * size of WORD for aligning in RLE absolute mode
 */
#define WORD_SIZE 2

/**
 * @brief The file header of the bitmap
 */
typedef struct __attribute__((__packed__)) {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BitmapFileHeader;

/**
 * @brief The info header of the bitmap
 */
typedef struct __attribute__((__packed__)){
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BitmapInfoHeader;


/**
 * @brief The data (RGB values) of a single pixel
 */
typedef struct __attribute__((__packed__)){
 unsigned char blue;
 unsigned char green;
 unsigned char red;
} PixelData;

/**
 * @brief Wraps the pointer to the memory containing data and array size
 */
typedef struct {
    int width;
    int height;
    PixelData* data;
}VLA;

/**
 * @brief Representation of a bitmap
 */
typedef struct {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    VLA imageData;

} Bitmap;

/**
 * @brief The data in the color table
 */
typedef struct __attribute__((__packed__)){
 unsigned char blue;
 unsigned char green;
 unsigned char red;
 unsigned char reserved;
} ColorTableEntry;


#endif /* _BITMAP_TYPES_H */
