/** ****************************************************************
 * @file    aufgabe2/rotary_encoder.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    14.10.2016
 * @brief   Implementation of the Rotary Encoder module
 ******************************************************************
 */
#include "rotary_encoder.h"
#include "errors.h"
#include "hardware_io.h"
#include <stdbool.h>
#include <stdio.h>

// Constants *********************************************************
/**
 * how many cycles per revolution
 */
#define CPR 300

/**
 * how many pulses per revolution (always 4x CPR)
 */
#define PPR (CPR * 4)

/**
 * how many degrees in one revolution
 */
#define DEGREES_PER_REVOLUTION 360

// Globals ***********************************************************
/**
 * the direction the encoder is turning
 */
static Direction direction;

/**
 * the position of the encoder in pulses relative to the last reset
 */
static int position;

/**
 * is the encoder in a valid state
 */
static bool valid_state;

/* ******************************************************************
 * Resets the encoder position
 * ******************************************************************
 */
void encoder_reset() {
    direction = UNKNOWN;
    valid_state = true;
    position = 0;
}

/* ******************************************************************
 * Returns the Direction the encoder is currently turning in
 * ******************************************************************
 */
Direction encoder_get_direction() {
    return direction;
}

/* ******************************************************************
 * Returns the position in pulses
 * ******************************************************************
 */
int encoder_get_position_raw(){
	return position;
}

/* ******************************************************************
 * Returns the position in 0.1 degrees
 * ******************************************************************
 */
int encoder_get_position() {
    // x10 for returning tenth of degrees
    return position * DEGREES_PER_REVOLUTION * 10 / PPR;
}

/**
 * @brief Reads the inputs and calculates the phase
 *
 * @return the phase
 */
static int get_phase() {
    bool channel_a;
    bool channel_b;

    // read from hardware io
	channel_a = hwio_get_encoder_channel_A();
	channel_b = hwio_get_encoder_channel_B();

    int phase;
    if (channel_a) {
        if (channel_b) {
            // both on high ==> c
            phase = 2;
        } else {
            //b
            phase = 1;
        }
    } else {
        if (channel_b) {
            // d
            phase = 3;
        } else {
            //both on low ==> a
            phase = 0;
        }
    }

    return phase;
}

/* ******************************************************************
 * Updates the encoder
 * ******************************************************************
 */
int encoder_update() {
    static int current_phase;

    // read inputs
    int next_phase = get_phase();

    if (!valid_state) {
        // remember current phase for next time
        current_phase = next_phase;
        
        return E_INVALID_STATE;
    }
    
    if (current_phase == next_phase) {
        // stationary ==> do nothing
    } else if (((current_phase + 1) % 4) == next_phase) {
        //turned forwards one
        direction = FORWARD;
        position++;
    } else if (((current_phase + 3) % 4) == next_phase) {
        //turned backwards one
        direction = BACKWARD;
        position--;
    } else {
        // invalid (we skipped a step)
        valid_state = false;
        
        // remember current phase for next time
        current_phase = next_phase;
        
        return E_INVALID_STATE;
    }

    // remember current phase for next time
    current_phase = next_phase;
    return 0;

}

/* ******************************************************************
 * Initializes the encoder
 * ******************************************************************
 */
void encoder_init() {
    encoder_reset();
    // update once to initialize static variable current_phase
    encoder_update();
    encoder_reset();
}
