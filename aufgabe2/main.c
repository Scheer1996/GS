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
#include "output.h"
#include "rotary_encoder.h"

/**
 * how often should speed be recalculated (in iterations of super loop)
 */
#define SPEED_UPDATE_INTERVAL 40

/**
 * @brief for debugging with oscilloscope
 *
 * could be put in Hardware IO module, but direct access is faster
 */
#define OSCI_HIGH GPIOG->BSRRL = 1

/**
 * @brief for debugging with oscilloscope
 *
 * could be put in Hardware IO module, but direct access is faster
 */
#define OSCI_LOW GPIOG->BSRRH = 1

/** ****************************************************************
 * @brief   Program entry point
 ******************************************************************
 */
int main(void) {
    // local variables
    int res;
    int counter = 0;

    // timer
    uint32_t last_time = getTimeStamp();
    uint32_t new_time = last_time;
    int last_pos = 0;
    int new_pos = 0;
    double speed = 0.0;

    // initialize everything
    Init_TI_Board();
    encoder_init();
    initTimer();
    output_init();

    while (1) {
        if (hwio_is_reset_pressed()) {
            // reset everything
            encoder_reset();
            hwio_clear_error();

            // reset timer
            last_pos = 0;
            last_time = getTimeStamp();
            speed = 0;
        }

        // update encoder
        res = encoder_update();
        if (res == E_INVALID_STATE) {
            // skipped a step => show error and stop output
            hwio_show_error();
        } else {
            // continue with output

            if (counter > SPEED_UPDATE_INTERVAL) {
                // update timer
                counter = 0;
                new_time = getTimeStamp();
                new_pos = encoder_get_position();

                uint64_t time_diff = timerDiffToNsec(last_time, new_time);
                int pos_diff = new_pos - last_pos;

                // (tenth of degree / ns) * 1 * 10^9 ns/s / 10 tenth of degree per degree
                speed = ((double) pos_diff / time_diff) * 1e9 / 10;

                last_time = new_time;
                last_pos = new_pos;
            }

            // make sure that the number LEDS always display a positive number
            int pulses = encoder_get_position_raw();
            if (pulses < 0) {
                pulses *= -1;
            }

            // display on LEDs
            hwio_display_data((char) pulses);
            hardware_io_display_direction(encoder_get_direction());

            // display on display
            OSCI_HIGH;
            output_update_data(encoder_get_position() / 10.0, speed);
            OSCI_LOW;
        }
        counter++;
    }

    return 0;
}

