/** ****************************************************************
 * @file    aufgabe3/input.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    24.10.2016
 * @brief   Header for the Input module
 ******************************************************************
 */
#ifndef _INPUT_H
#define _INPUT_H

#include "bitmap_types.h"

/**
 * Reads a file and writes the data to bitmap.
 *
 * @param[in] path the path to the file to be read
 * @param[out] bitmap pointer to where the bitmap data is supposed to be written to
 * @return error code
 * @retval 0 no error
 */
int input_read_file(char* path, Bitmap* bitmap);


#endif /* _INPUT_H */
