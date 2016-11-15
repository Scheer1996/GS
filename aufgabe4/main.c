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
#include "config.h"
#include "errors.h"
#include "sensor.h"
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
#if MODE == READ_SINGLE_ROM
    while(1){
        if(bus_reset()){
            bus_send_command(BUS_READ_ROM_CMD);
        
            uint64_t rom;
            if(bus_read_romcode(&rom) == E_CRC_FAILED){
                output_display_error("CRC failed!");
            } else {
                output_display_romcode(rom);		
            }
        } else {
            output_display_error("Nothing connected!");
        }
    }
#elif MODE == MEASURE_TEMP
    double temp = 0;
    while(1){
        if(sensor_measure(S1, &temp) == E_NO_SENSOR){
            output_display_error("Sensor not connected!"); 
        } else {
            output_display_temp(temp);
        }
    }
#else
    while (1) {
        
    }
#endif
}

