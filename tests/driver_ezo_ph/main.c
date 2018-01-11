/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 */

/**
 * @ingroup     drivers_ezo_ph
 * @{
 *
 * @file
 * @brief       Driver for the Atlas Scientific EZO^TM pH Circuit Sensor.
 *
 * @author      Katrin Moritz <katrin.moritz@haw-hamburg.de>
 *
 * @}
 */


#include <stdio.h>
#include <string.h>

//#include "thread.h"
/*#include "shell.h"
#include "shell_commands.h"
*/
#include <stdint.h>

#include "ezo_ph.h"
#include "ezo_ph_params.h"

#include "cpu.h"
#include "irq.h"
#include "mutex.h"
#include "periph_conf.h"
#include "periph/i2c.h"
// Timer
#include "xtimer.h"
#include "timex.h"


int main(void)
{

	ezo_ph_t dev;
	char ph[EZO_PH_VALUE_LENGTH] = "";
	//char data[15] = "";

	//gitkraken

	
    //puts("Welcome to RIOT!");
    puts("EZO pH sensor driver test application\n");
    printf("Initializing EZO_PH sensor at I2C_%i ... \n", ezo_ph_params[0].i2c);
    ezo_ph_init(&dev, ezo_ph_params);
    //ezo_ph_read(&dev, EZO_PH_DEVICE_FIRMWARE, data, 15);
	//ezo_ph_calibration(&dev, EZO_PH_CAL_ACT);

    ezo_ph_read_ph(&dev, ph);
    
    //ezo_ph_set_standby(&dev);

/*
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
*/

    puts("---ENDE---");
    return 0;
}
