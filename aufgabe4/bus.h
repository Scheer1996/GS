/** ****************************************************************
 * @file    aufgabe4/bus.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    10.11.2016
 * @brief   Header for the Bus module
 ******************************************************************
 */
#ifndef BUS_H
#define BUS_H
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

#define BYTE_SIZE 8

#define BUS_READ_ROM_CMD 0x33
#define BUS_MATCH_ROM_CMD 0x55
#define BUS_MEASURE_CMD 0x44
#define BUS_SKIP_ROM_CMD 0xCC
#define BUS_READ_SCRATCHPAD_CMD 0xBE
void bus_init( void );

bool bus_reset( void );

void bus_read_byte(BYTE *b);

void bus_send_command(BYTE command);

void bus_send_romcode(uint64_t romcode);

int bus_read_romcode(uint64_t *romcode);

void bus_provide_power( void );

#endif /* BUS_H */
