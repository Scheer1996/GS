/** ****************************************************************
 * @file    aufgabe4/bus.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    15.11.2016
 * @brief   Implementation of the Bus module
 ******************************************************************
 */
 
#include "bus.h"
#include "errors.h"
#include "hal.h"
#include "timer.h"

/**
 * @brief The pin used for data transfer
 */
#define DATA_PIN 0

/**
 * @brief The pin used for providing power
 */
#define POWER_PIN 1

/**
 * @brief How many bytes is the romcode
 */
#define ROMCODE_SIZE 8

/**
 * @brief How long the bus should be in powered state
 */
#define POWER_ON_TIME_US 750 * 1000

#define ZERO_64BIT (uint64_t)0

#define ONE_64BIT (uint64_t)1

/**
 * @brief Waits for the specified amount of time
 *
 * @param us time to wait (in microseconds)
 */
static void wait(int us){
	uint32_t ts = getTimeStamp();
	while(timerDiffToNsec(ts, getTimeStamp()) < (us * 1000)){
		// do nothing
	}
}

static void send_bit(int bit){
    if(bit){
        // send 1
		hal_set_pin_low(DATA_PIN);
		wait(6);
		hal_set_pin_high(DATA_PIN);
		wait(64);
    } else {
        // send 0
		hal_set_pin_low(DATA_PIN);
		wait(60);
		hal_set_pin_high(DATA_PIN);
		wait(10);
    }
}

/**
 * @brief Sends a byte on the bus
 *
 * @param b the byte to send
 */
static void send_byte(BYTE b){
	for(int i = 0; i < BYTE_SIZE; i++){
		if(b & 1 << i){
			send_bit(1);
		} else {
			send_bit(0);
		}
	}
}

static int read_bit(){
    int result = 0;
    hal_set_pin_low(DATA_PIN);
	wait(6);
	hal_set_pin_high(DATA_PIN);
	wait(9);
	// lesen
	if(hal_get_pin(DATA_PIN) == 1){
		result = 1;
	}
	wait(55);
    return result;
}

static void jump_to(int current_index, uint64_t romcode){
    bus_reset();
    bus_send_command(BUS_SEARCH_ROM_CMD);
    read_bit(); 
    read_bit();
    
    for(int i = 0; i < current_index; i++){
        send_bit(romcode & 1 << i);
        read_bit(); 
        read_bit();
    }
}


static void search_recursive(List* list, int current_index, uint64_t romcode){
    if(current_index >= 64){
        // add sensor and quit recursion
        list_append(list, romcode);
        return;
    }
    
    int bit, inverse;
    bit = read_bit();
    inverse = read_bit();
    
    if(bit == !inverse){
        send_bit(bit);
        romcode |= ((uint64_t)bit << current_index);
        search_recursive(list, current_index + 1, romcode);        
    } else if( bit == 0 && inverse == 0){
        // Need to decide
        // try 0 first
        send_bit(0);
        romcode |= (ZERO_64BIT << current_index);
        search_recursive(list, current_index + 1, romcode);
        
        // restart from the beginning
        jump_to(current_index, romcode);
        
        // try 1
        send_bit(1);
        romcode |= (ONE_64BIT << current_index);
        search_recursive(list, current_index + 1, romcode);   
    } else {
        return;
    }
}

/*
 * Reads a byte from the bus
 */
void bus_read_byte(BYTE *b){
	*b = 0;
	for(int i = 0; i < BYTE_SIZE; i++){
		*b |= (read_bit() << i);
	}	
}

/*
 * Checks CRC checksum to verify the data
 */
bool bus_check_crc(uint64_t *data, BYTE crc) {
    // lookup table for checking
    static BYTE lookup_table[] = { 0, 94, 188, 226, 97, 63, 221, 131, 194, 156,
            126, 32, 163, 253, 31, 65, 157, 195, 33, 127, 252, 162, 64, 30, 95,
            1, 227, 189, 62, 96, 130, 220, 35, 125, 159, 193, 66, 28, 254, 160,
            225, 191, 93, 3, 128, 222, 60, 98, 190, 224, 2, 92, 223, 129, 99,
            61, 124, 34, 192, 158, 29, 67, 161, 255, 70, 24, 250, 164, 39, 121,
            155, 197, 132, 218, 56, 102, 229, 187, 89, 7, 219, 133, 103, 57,
            186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154, 101, 59, 217,
            135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36, 248, 166,
            68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185, 140,
            210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
            17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236,
            14, 80, 175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12,
            82, 176, 238, 50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18,
            145, 207, 45, 115, 202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180,
            234, 105, 55, 213, 139, 87, 9, 235, 181, 54, 104, 138, 212, 149,
            203, 41, 119, 244, 170, 72, 22, 233, 183, 85, 11, 136, 214, 52, 106,
            43, 117, 151, 201, 74, 20, 246, 168, 116, 42, 200, 150, 21, 75, 169,
            247, 182, 232, 10, 84, 215, 137, 107, 53 };
    
    BYTE test = 0;
    for(int i = 0; i < ROMCODE_SIZE; i++){
        BYTE input = (BYTE)(*data >> (i * BYTE_SIZE));
        test = lookup_table[test ^ input];
    }
    // romcode is valid if crc matches
    return crc == test;
}

/*
 * initializes the bus
 */
void bus_init(){
    // initialize input pin
	hal_set_pin_opendrain(DATA_PIN);
	hal_set_pin_high(DATA_PIN);
    
	// initialize output pin
    hal_set_pin_opendrain(POWER_PIN);
    hal_set_pin_high(POWER_PIN);
    
    // initialize timer
	initTimer();
}

/*
 * resets the bus
 */
bool bus_reset(){
    bool there = false;
	hal_set_pin_opendrain(DATA_PIN);
	
	hal_set_pin_low(DATA_PIN);
	wait(480);
	hal_set_pin_high(DATA_PIN);
	wait(70);

	// check if someone's there
    if(hal_get_pin(DATA_PIN) == 0){
        there = true;
    }

	wait(410);
    return there;
}

/*
 * send a commmand via the bus
 */
void bus_send_command(BYTE command){
	send_byte(command);
}

/*
 * send a romcode via the bus
 */
void bus_send_romcode(uint64_t romcode){
    for(int i = 0; i < ROMCODE_SIZE; i++){
        send_byte((BYTE)(romcode >> (i * BYTE_SIZE)));
    }
}

/*
 * read a romcode from the bus
 */
int bus_read_romcode(uint64_t *romcode){
	*romcode = 0;

	for(int i = 0; i < ROMCODE_SIZE; i++){
		BYTE b;
		bus_read_byte(&b);
        uint64_t dummes_c = b;
		*romcode |= (dummes_c << (i * BYTE_SIZE));
	}
    
    // CRC check
    if(bus_check_crc(romcode, 0)){
        return 0;
    } else {
        return E_CRC_FAILED;
    }
}

/*
 * use bus to provide parasite power to the sensor
 */
void bus_provide_power(){
    // enable push-pull mode
    hal_set_pin_pushpull(POWER_PIN);
	hal_set_pin_pushpull(DATA_PIN);

    // turn on the pins
    hal_set_pin_high(DATA_PIN);
    hal_set_pin_high(POWER_PIN);

    wait(POWER_ON_TIME_US);

    // back to safety (open-drain)
    hal_set_pin_opendrain(POWER_PIN);
	hal_set_pin_opendrain(DATA_PIN);
}

List bus_search(){
    List sensors;
    list_init(&sensors);
    
    bus_reset();
    bus_send_command(BUS_SEARCH_ROM_CMD);
    search_recursive(&sensors, 0, 0);
    
    return sensors;
}
