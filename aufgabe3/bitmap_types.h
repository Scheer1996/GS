/** ****************************************************************
 * @file    aufgabe3/bitmap_types.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    24.10.2016
 * @brief   Typedefs for the Bitmaps
 ******************************************************************
 */
#ifndef _BITMAP_TYPES_H
#define _BITMAP_TYPES_H

#include "ms_types.h"

/**
 * @brief The file header of the Bitmap
 */
typedef struct __attribute__((__packed__)) {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BitmapFileHeader;

/**
 * @brief The info header of the Bitmap
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
 * @brief Wraps the pointer to the memory containing the pixel data and array size
 */
typedef struct {
    int width;
    int height;
    void* data;
}ImageData;

/**
 * @brief Representation of a Bitmap
 */
typedef struct {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    ImageData imageData;

} Bitmap;

/**
 * @brief The data (RGB values) of a single pixel
 */
typedef struct {
 unsigned char blue;
 unsigned char green;
 unsigned char red;
} PixelData;

/**
 * @brief The data in the pallete
 */
typedef struct __attribute__((__packed__)){
 unsigned char blue;
 unsigned char green;
 unsigned char red;
 unsigned char reserved;
} ColorTableEntry;


#endif /* _BITMAP_TYPES_H */
