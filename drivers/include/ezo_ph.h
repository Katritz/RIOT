/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_ezo_ph AtlasScientific EZO^TM pH Circuit Sensor
 * @ingroup     drivers_sensors
 * @brief       Driver for the AtlasScientific EZO^TM pH Circuit Sensor.
 *
 * @{
 *
 * @file
 * @brief       Interface definition for the ezo_ph sensor driver.
 *
 * @author      Katrin Moritz <katrin.moritz@haw-hambirg.de>
 */

#ifndef EZO_PH_H
#define EZO_PH_H

#include <stdint.h>
#include <stdbool.h>
#include "periph/i2c.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief   EZO_PH Default Address
 */
#ifndef EZO_PH_I2C_ADDRESS
#define EZO_PH_I2C_ADDRESS         (0x63)
#endif

/**
 * @brief   Default Conversion Time in us
 */
#define EZO_PH_CONVERSION_TIME     (1E6)

/**
 * @name    Constants for EZO_PH calibration
 * @{
 */

/** @} */

/**
 * @brief   Parameters needed for device initialization
 */
typedef struct {
    i2c_t   i2c;        /**< I2C device, the sensor is connected to */
    uint8_t addr;       /**< the sensor's slave address on the I2C bus */
    //uint8_t rate;       /**< number of averaged samples */
} ezo_ph_params_t;

/**
 * @brief   Device descriptor for EZO_PH sensors.
 */
typedef struct {
    ezo_ph_params_t p;  /**< Configuration parameters */
} ezo_ph_t;

/**
 * @brief   EZO_PH specific return values
 */
enum {
    EZO_PH_OK,          /**< Success, no error */
    EZO_PH_ERROR_BUS,   /**< I2C bus error */
    EZO_PH_ERROR_DEV,   /**< internal device error */
    EZO_PH_ERROR_CONF,  /**< invalid device configuration */
    EZO_PH_ERROR,       /**< general error */
};

/**
 * @brief   Initialize the EZO_PH sensor driver.
 *
 * @param[out] dev          device descriptor of sensor to initialize
 * @param[in]  params       configuration parameters
 *
 * @return                  0 on success
 * @return                  -EZO_PH_ERROR_BUS on I2C bus error
 * @return                  -EZO_PH_ERROR_DEV if sensor test failed
 * @return                  -EZO_PH_ERROR_CONF if sensor configuration failed
 */
int ezo_ph_init(ezo_ph_t *dev, const ezo_ph_params_t *params);

/**
 * @brief   Reset the EZO_PH sensor, afterwards it should be reinitialized.
 *
 * @param[out] dev          device descriptor of sensor
 *
 * @return                  0 on success
 * @return                  -1 on error
 */
int ezo_ph_reset(const ezo_ph_t *dev);


/**
 * @brief   Set standby mode.
 *
 * @param[in]  dev          device descriptor of sensor
 *
 * @return                  0 on success
 * @return                  -1 on error
 */
int ezo_ph_set_standby(const ezo_ph_t *dev);

/**
 * @brief   Write to sensor.
 *
 * @param[in]  dev          device descriptor of sensor
 * @param[in]  Write 		command to write
 *
 * @return                  0 on success
 * @return                  -1 on error
 */
int ezo_ph_write(const ezo_ph_t *dev, char *write);

/**
 * @brief   Read sensor's data.
 *
 * @param[in]  dev          device descriptor of sensor
 * @param[in]  bytes		number of bytes to read
 * @param[in]  command 		command
 * @param[out] data			read data
 *
 * @return                  0 on success
 * @return                  -1 on error
 */
int ezo_ph_read(const ezo_ph_t *dev, char *command, char *data, uint8_t bytes);


/**
 * @brief   Convenience function to get pH values 
 *
 * @note    
 *
 * @param[in]  dev          device descriptor of sensor
 * @param[out] ph           pH value
 */
int ezo_ph_read_ph(const ezo_ph_t *dev, char *ph);


/**
 * @brief   Convenience function to cet pH calibration
 *
 * @note    
 *
 * @param[in]  dev          device descriptor of sensor
 * @param[out] ph           pH value
 */
int ezo_ph_calibration(const ezo_ph_t *dev, char *cal_type);


#ifdef __cplusplus
}
#endif

#endif /* EZO_PH_H */
/** @} */
