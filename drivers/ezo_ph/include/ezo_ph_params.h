/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_ezo_ph
 *
 * @{
 * @file
 * @brief       Default configuration for EZO pH devices
 *
 * @author      Katrin Moritz <katrin.moritz@haw-hamburg.de>
 */

#ifndef EZO_PH_PARAMS_H
#define EZO_PH_PARAMS_H

#include "board.h"
#include "ezo_ph.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters for the EZO pH driver
 * @{
 */
#ifndef EZO_PH_PARAM_I2C
#define EZO_PH_PARAM_I2C           I2C_DEV(0)
#endif
#ifndef EZO_PH_PARAM_ADDR
#define EZO_PH_PARAM_ADDR          (EZO_PH_I2C_ADDRESS)
#endif
/*#ifndef EZO_PH_PARAM_RATE
#define EZO_PH_PARAM_RATE           (EZO_PH_CONFIG_CR_DEF)
#endif
*/

#define EZO_PH_DEVICE_FIRMWARE    	"i" /**< Device firmware */
#define EZO_PH_STATUS             	"Status" /**< Status Register*/
#define EZO_PH_RESET			  	"Factory" /**< Set device to factory settings*/
#define EZO_PH_VALUE_LENGTH 		6
#define EZO_PH_GET_VALUE			"R"		/**< Read pH value*/
#define EZO_PH_SLEEP				"Sleep"

#define EZO_PH_CAL_ACT				"Cal,?" /**< device calibrated?*/
#define EZO_PH_CAL_SINGLE			"Cal,mid,7.00" /**< single point calibration at midpoint*/
#define EZO_PH_CAL_TWO_POINT		"Cal,low,4.00" /**<two point calibration at lowpoint*/
#define EZO_PH_CAL_THREE_POINT		"Cal,high,10.00" /**<  three point calibration at highpoint*/
#define EZO_PH_CAL_CLEAR			"Cal,clear" /**< clear calibration data*/



#define EZO_PH_PARAMS_DEFAULT    {  .i2c  = EZO_PH_PARAM_I2C, \
                                    .addr = EZO_PH_PARAM_ADDR}/*, \
                                    .rate = EZO_PH_PARAM_RATE }*/
/**@}*/

/**
 * @brief   EZO pH configuration
 */
static const ezo_ph_params_t ezo_ph_params[] =
{
#ifdef EZO_PH_PARAMS_BOARD
    EZO_PH_PARAMS_BOARD,
#else
    EZO_PH_PARAMS_DEFAULT,
#endif
};

/**
 * @brief   Additional meta information to keep in the SAUL registry
 */
static const saul_reg_info_t ezo_ph_saul_info[] =
{
    { .name = "ezo_ph" }
};

#ifdef __cplusplus
}
#endif

#endif /* EZO_PH_PARAMS_H */
/** @} */
