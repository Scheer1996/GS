/** ****************************************************************
 * @file    aufgabe2/main.c
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    07.10.2016
 * @brief   Main module and program entry point
 ******************************************************************
 */
#include "main.h"
#include "errors.h"
#include "timer.h"
#include "TI_Lib.h"
#include "hardware_io.h"
#include "rotary_encoder.h"
#include "output_display.h"

/** ****************************************************************
 * @brief   Program entry point
 ******************************************************************
 */
int main(void) {
    Init_TI_Board();
	
	encoder_init();
	initTimer();
	
	int res;
	int counter = 0;
	
	// timer
	uint32_t last_time = getTimeStamp();
	uint32_t new_time = last_time;
	int last_pos = 0;
	int new_pos = 0;
	double speed = 0.0;
	
	while(1){
		if(hardware_io_is_reset_pressed()){
			encoder_reset();
			hardware_io_clear_error();
			last_pos = 0;
			last_time = getTimeStamp();
		}
		res = encoder_update();
		if(res == E_INVALID_STATE){
			hardware_io_display_error();
		} else {
			// update timer every 40 cycles
			if(counter > 40){
				counter = 0;
				new_time = getTimeStamp();
				new_pos = encoder_get_position();
				
				uint64_t time_diff = timerDiffToNsec(last_time, new_time);
				int pos_diff = new_pos - last_pos;
				
				// (tenth of degree / ns) * 1 * 10^9 ns/s / 10 tenth of degree per degree 
				speed = ((double)pos_diff / time_diff) * 1e9 / 10;
				
				last_time = new_time;
				last_pos = new_pos;
			}
			
			// continue with output			
			int pulses = encoder_get_position_raw();
			if(pulses < 0){
				pulses *= -1;
			}
			hardware_io_display_number((char)pulses);
			hardware_io_display_direction(encoder_get_direction());
			
			GPIOG->BSRRL = 1;
			output_display_data(encoder_get_position() / 10.0, speed);
			GPIOG->BSRRH = 1;
		}
		counter++;
	}
	
    return 0;
}

