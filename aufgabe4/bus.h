/** ****************************************************************
 * @file    aufgabe4/bus.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Header for the Bus module
 ******************************************************************
 */
#ifndef BUS_H
#define BUS_H
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

/**
 * @brief Size of one byte in bits
 */
#define BYTE_SIZE 8

// Commands -------------------------------------------------------------------
/**
 * @brief Ask sensor to send its romcode
 */
#define BUS_READ_ROM_CMD 0x33

/**
 * @brief Announce that a romcode to target a sensor will be provided
 */
#define BUS_MATCH_ROM_CMD 0x55

/**
 * @brief Ask sensor to mesaure temperature
 */
#define BUS_MEASURE_CMD 0x44

/**
 * @brief Next command will be for everyone listening
 */
#define BUS_SKIP_ROM_CMD 0xCC

/**
 * @brief Ask sensor to send the contents of its scratchpad
 */
#define BUS_READ_SCRATCHPAD_CMD 0xBE

// Functions ------------------------------------------------------------------

/**
 * @brief Initializes bus module
 */
void bus_init( void );

/**
 * @brief Resets the bus
 *
 * @return true, if there is at least one slave
 */
bool bus_reset( void );

/**
 * @brief Reads one byte from the bus
 *
 * @param[out] b pointer to where the byte should be stored
 */
void bus_read_byte(BYTE *b);

/**
 * @brief Sends a command via the bus
 *
 * @param[in] command the comand to send
 */
void bus_send_command(BYTE command);

/**
 * @brief Sends a romcode via the bus
 *
 * @param[in] romcode the romcode to send
 */
void bus_send_romcode(uint64_t romcode);

/**
 * @brief Reads a romcode from the bus
 *
 * @param[out] romcode pointer to where the romcode should be stored
 * @return error code
 * @retval 0            no error
 * @retval E_CRC_FAILED the CRC check failed
 */
int bus_read_romcode(uint64_t *romcode);

/**
 * @brief Provide power through the bus (will prevent data transfer)
 */
void bus_provide_power( void );

#endif /* BUS_H */
