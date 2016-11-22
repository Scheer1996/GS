/** ****************************************************************
 * @file    aufgabe4/sensor.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    10.11.2016
 * @brief   Implementation of the Sensor module
 ******************************************************************
 */

#include "sensor.h"
#include "bus.h"
#include "errors.h"

#define SCRATCHPAD_SATA_SIZE 8
#define TEMP_RESOLUTION 0.0625

static int read_temp_from_scratchpad(double *temp){
    uint64_t data = 0;
    BYTE crc = 0;
    BYTE b = 0;
        
    // read data
    for(int i = 0; i < SCRATCHPAD_SATA_SIZE; i++){
        bus_read_byte(&b);
        uint64_t dummes_c = b;
        data |= dummes_c << (i * BYTE_SIZE);
    }
    // read crc
    bus_read_byte(&crc);
    
    //CRC verify
    
    int16_t temp_raw = (int16_t)data;
    *temp = temp_raw * TEMP_RESOLUTION;
    return 0;
}

int sensor_measure(uint64_t romcode, double *temp){
    if(bus_reset()){
        bus_send_command(BUS_MATCH_ROM_CMD);
        bus_send_romcode(romcode);
        bus_send_command(BUS_MEASURE_CMD);
        bus_provide_power();
        
        if(bus_reset()){
            bus_send_command(BUS_MATCH_ROM_CMD);
            bus_send_romcode(romcode);
            bus_send_command(BUS_READ_SCRATCHPAD_CMD);
            read_temp_from_scratchpad(temp);
            return 0;
        } else {
            return E_NO_SENSOR;
        }
    } else {
        return E_NO_SENSOR;
    }
}



int sensor_search(){
    
    //rekursiv durchgehen
    /*
    2 Parameter
    Scan Tiefe
    bestehenden 64 bit Romcode
    
    
    2. hilfsmethode für fall das beide zweige gescannt werden müssen - 00
    setz System auf höhe der verzweiggung, startet Suche danach wieder
    
    
    */
    
    
}
