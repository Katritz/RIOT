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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#include "log.h"
#include "periph/i2c.h"
#include "ezo_ph.h"

// Timer
#include "xtimer.h"
#include "timex.h"

#define ENABLE_DEBUG                (0)
#include "debug.h"

#include "ezo_ph_params.h"


#define I2C_SPEED                   I2C_SPEED_NORMAL
#define BUS                         (dev->p.i2c)
#define ADDR                        (dev->p.addr)

#define WRITE_BYTES_MAX             7
#define READ_BYTES_MAX              15


int ezo_ph_init(ezo_ph_t *dev, const ezo_ph_params_t *params)
{
    char write[] = "i";
    char read[READ_BYTES_MAX];
    /* check parameters */
    assert(dev && params);
    
    /* initialize the device descriptor */
    memcpy(&dev->p, params, sizeof(ezo_ph_params_t));

    /* setup the I2C bus */
    i2c_acquire(BUS);
    if (i2c_init_master(BUS, I2C_SPEED) < 0) {
        i2c_release(BUS);
        LOG_ERROR("ezo_ph_init: error initializing I2C bus\n");
        return -EZO_PH_ERROR_BUS;
    }
    i2c_release(BUS);

    /* try if we can interact with the device by reading its firmware */
    i2c_acquire(BUS);
    i2c_write_bytes(BUS, ADDR, write, sizeof(WRITE_BYTES_MAX-1));  
    /* wait for 300 us */
    xtimer_usleep(300*1000);
    i2c_read_bytes(BUS, ADDR, read, sizeof(READ_BYTES_MAX-1));
    /* wait for 300 us */
    xtimer_usleep(300*1000);

    if (read[0] != 1)
    {
        LOG_ERROR("ezo_ph_init: error reading data! Resp. code: %i\n", read[0]);
        i2c_release(BUS);
        return -EZO_PH_ERROR_BUS;
    }

    i2c_release(BUS);

    /* wait for 300 us */
    xtimer_usleep(300*1000);


    return EZO_PH_OK;
}

int ezo_ph_reset(const ezo_ph_t *dev)
{
    i2c_acquire(BUS);
    i2c_write_bytes(BUS, ADDR, EZO_PH_RESET, sizeof(EZO_PH_RESET)-1);
    xtimer_usleep(300*1000);
  
    i2c_release(BUS);
    return EZO_PH_OK;
}

int ezo_ph_set_standby(const ezo_ph_t *dev)
{
    ezo_ph_write(dev, EZO_PH_SLEEP);
    return EZO_PH_OK;
}

int ezo_ph_write(const ezo_ph_t *dev, char *write)
{
    i2c_acquire(BUS);
     // write command
    i2c_write_bytes(BUS, ADDR, write, sizeof(write)-1);
    xtimer_usleep(900*1000);
    i2c_release(BUS);

    printf("Command: 0x%x, %s\n", *write, write);

    return EZO_PH_OK;
}

int ezo_ph_read(const ezo_ph_t *dev, uint8_t bytes, char *write, char *data)
{
    ezo_ph_write(dev, write);

    //read
    i2c_read_bytes(BUS, ADDR, data, bytes);
    xtimer_usleep(300*1000);
    i2c_release(BUS);
  
    if (data[0] == 254)
    {
        puts("still processing, not ready");
        return -EZO_PH_ERROR;
    }else if (data[0]==255)
    {
        puts("no data to send");
        return -EZO_PH_ERROR;
    }else if (data[0] == 2)
    {
        puts("ERROR!");
        return -EZO_PH_ERROR;
    }else if (data[0] == 1)
    {
        memmove(data, data+1, strlen(data)); //remove first character ("1" = start of heading)
        printf("Datenbyte: %s\n",  data);
        return EZO_PH_OK;
    }else{
        puts("ERROR!");   
        LOG_ERROR("ezo_ph_read: error reading data! Resp. code: %i\n", data[0]);
    }

    return EZO_PH_OK;
}


int ezo_ph_read_ph(const ezo_ph_t *dev, char *ph)
{
    printf("pH Value:\n");
    ezo_ph_read(dev, EZO_PH_VALUE_LENGTH, EZO_PH_GET_VALUE, ph);
    return EZO_PH_OK;
}

int ezo_ph_calibration(const ezo_ph_t *dev, char *cal_type)
{
    printf("Calibration:\n");
    if(EZO_PH_CAL_ACT){
        char *act_cal = "";
        ezo_ph_read(dev, READ_BYTES_MAX, cal_type, act_cal);
        printf("Actual Calibration: %s\n", act_cal);
    }else{
        ezo_ph_write(dev, cal_type);
    }
    
    return EZO_PH_OK;
}