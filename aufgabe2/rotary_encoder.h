/** ****************************************************************
 * @file    aufgabe2/rotary_encoder.h
 * @author  Moritz Hoewer (Moritz.Hoewer@haw-hamburg.de)
 * @author  Philip Scheer (Philip.Scheer@haw-hamburg.de)
 * @version 1.0
 * @date    09.10.2016
 * @brief   Header for the Rotary Encoder module
 ******************************************************************
 */

/**
 * @brief Represents the possible directions of rotation for the encoder
 */
typedef enum {
    FORWARD, //!< the encoder is turning forwards
    BACKWARD, //!< the encoder is turning backwards
    UNKNOWN  //!< the encoder is stationary or the direction is unknown
} Direction;

/**
 * @brief Returns the direction the encoder is currently turning in
 *
 * @return the direction
 */
Direction encoder_get_direction();

/**
 * @brief Returns the position in 0.1 degrees
 *
 * Position is relative to last reset, negative values indicate that the
 * encoder turned backwards
 *
 * @return position in 0.1 degrees
 */
int encoder_get_position();

/**
 * @brief Resets the encoder position
 */
void encoder_reset();

/**
 * @brief Initializes the encoder
 */
void encoder_init();

/**
 * @brief Updates the encoder
 *
 * This method will read the two inputs calculating the current phase. It then
 * updates the position and Direction variables accordingly. If an invalid
 * phase transition is detected, an error is returned.
 *
 * @returns error code
 * @retval 0 no error
 * @retval E_INVALID_STATE the encoder has moved too much - state is now unknown
 */
int encoder_update();
