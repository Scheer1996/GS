/** ****************************************************************
 * @file    aufgabe4/bus.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    10.11.2016
 * @brief   Implementation of the Bus module
 ******************************************************************
 */
 
#include "bus.h"
#include "hardware_io.h"
#include "timer.h"

#define PIN 0

#define BYTE_SIZE 8
#define ROMCODE_SIZE 8

static void wait(int us){
	uint32_t ts = getTimeStamp();
	while(timerDiffToNsec(ts, getTimeStamp()) < (us * 1000)){
		// do nothing
	}
}

static void send_byte(BYTE b){
	for(int i = 0; i < BYTE_SIZE; i++){
		if(b & 1 << i){
			// send 1
			hwio_set_pin_low(PIN);
			wait(6);
			hwio_set_pin_high(PIN);
			wait(64);
		} else {
			// send 0
			hwio_set_pin_low(PIN);
			wait(60);
			hwio_set_pin_high(PIN);
			wait(10);
		}
	}
}

static void read_byte(BYTE *b){
	*b = 0;
	for(int i = 0; i < BYTE_SIZE; i++){
		hwio_set_pin_low(PIN);
		wait(6);
		hwio_set_pin_high(PIN);
		wait(9);
		// lesen
		if(hwio_get_pin(PIN) == 1){
			*b |= 1 << i;
		}
		wait(55);
	}	
}

void bus_init(){
	hwio_set_pin_opendrain(PIN);
	hwio_set_pin_high(PIN);
	initTimer();
}

void bus_reset(){
	hwio_set_pin_opendrain(PIN);
	
	hwio_set_pin_low(PIN);
	wait(480);
	hwio_set_pin_high(PIN);
	wait(70);
	// abfrage
	wait(410);
}

void bus_send_command(BYTE command){
	send_byte(command);
}

void bus_send_romcode(uint64_t romcode){
}

void bus_read_romcode(uint64_t *romcode){
	*romcode = 0;
	for(int i = 0; i < ROMCODE_SIZE; i++){
		BYTE b;
		read_byte(&b);
		*romcode |= (b << (i * BYTE_SIZE));
	}
}
