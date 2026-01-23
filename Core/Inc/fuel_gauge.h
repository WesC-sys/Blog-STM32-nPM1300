/*
 * Fuel_Guage.h
 *
 *  Created on: Dec 4, 2025
 *      Author: wech
 */

#ifndef INC_FUEL_GAUGE_H_
#define INC_FUEL_GAUGE_H_

#include 	<npmx.h>
#include 	<npmx_core.h>
#include 	<npmx_instance.h>
#include 	"nrf_fuel_gauge.h"

// WRC Dont believe it is necessary  #include <npmx_driver.h>

/**
 * @brief Function for initializing the fuel gauge module.
 *
 * @param[in] p_pm Pointer to the instance of PMIC device.
 *
 * @retval 0     On success.
 * @retval other Errno codes.
 */
int fuel_gauge_init(npmx_instance_t *const p_pm);

/**
 * @brief Function for periodically updating the fuel gauge module with battery voltage, current and temperature.
 *
 * @param[in] p_pm Pointer to the instance of PMIC device.
 *
 * @retval 0     On success.
 * @retval other Errno codes.
 */
int fuel_gauge_update(npmx_instance_t *const p_pm);



#endif /* INC_FUEL_GAUGE_H_ */
