/** ****************************************************************
 * @file    aufgabe2/main.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Main module and program entry point
 ******************************************************************
 */
#include "main.h"
#include "config.h"
#include "errors.h"
#include "sensor.h"
#include "timer.h"
#include "TI_Lib.h"
#include "bus.h"
#include "hal.h"
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
#elif MODE == AUTO_MODE
    List sensors = bus_search();
    while(1) {
        Iterator it = list_get_iterator(&sensors);
        uint64_t id;
        double temp;
        int offset = 0;
        
        while(iterator_has_next(&it)){    
            iterator_next(&it, &id);
            if(sensor_measure(id, &temp) == 0){
                output_display_temp_offset(temp, offset);
            } else {
                output_display_error_offset("Sensor disconnected!", offset);
            }
            offset++;
        }
        
    }
#else
    while (1) {
        
    }
#endif
}

