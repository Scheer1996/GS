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
#include "TI_Lib.h"
#include "input.h"
#include "output_display.h"
#include "rpn.h"
#include "tokens.h"

/** ****************************************************************
 * @brief   Program entry point
 ******************************************************************
 */
int main(void) {
    Init_TI_Board();

    /*
     * Idee bevor ich es vergesse: Da wir ja weiter unten in der Aufgabe
     * mit der Problemstellung konfrontiert werden, dass das Display langsam ist
     * koennte man es doch einfach nur alle 10 durchlauufe aktualisieren
     */

    return 0;
}

