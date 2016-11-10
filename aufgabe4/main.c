/** ****************************************************************
 * @file    aufgabe2/main.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    14.10.2016
 * @brief   Main module and program entry point
 ******************************************************************
 */
#include "main.h"
#include "errors.h"
#include "timer.h"
#include "TI_Lib.h"
#include "hardware_io.h"
#include "bus.h"
#include "output.h"

/** ****************************************************************
 * @brief   Program entry point
 ******************************************************************
 */
int main(void) {
    // initialize everything
    Init_TI_Board();
	
	bus_init();
    output_init();

	bus_reset();
	bus_send_command(BUS_READ_ROM_CMD);
	
	uint64_t rom;
	bus_read_romcode(&rom);
	
	output_display_number(rom);	
	
    while (1) {
        
    }
}

