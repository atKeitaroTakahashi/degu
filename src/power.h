/*
 * Copyright (c) 2018 Nordic Semiconductor ASA.
 * Copyright (c) 2019 Atmark Techno, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef DEGU_DEVICE_POWER_H
#define DEGU_DEVICE_POWER_H

#include <gpio.h>

#include <device.h>

void ext_device_power(bool enable)
{
	struct device *gpio0 = device_get_binding(DT_GPIO_P0_DEV_NAME);
	struct device *gpio1 = device_get_binding(DT_GPIO_P1_DEV_NAME);
	struct device *i2c0 = device_get_binding(DT_I2C_0_NAME);
	struct device *i2c1 = device_get_binding(DT_I2C_1_NAME);

	if (enable) {
		gpio_pin_configure(gpio1, 6, GPIO_DIR_OUT|GPIO_PUD_PULL_UP);
		gpio_pin_write(gpio1, 6, 1);
		gpio_pin_configure(gpio1, 2, GPIO_DIR_OUT|GPIO_PUD_PULL_UP);
		gpio_pin_write(gpio1, 2, 1);
		gpio_pin_configure(gpio0, 26, GPIO_DIR_OUT|GPIO_PUD_PULL_UP);
		gpio_pin_write(gpio0, 26, 1);

		device_set_power_state(i2c1, DEVICE_PM_ACTIVE_STATE);
		device_set_power_state(i2c0, DEVICE_PM_ACTIVE_STATE);
	} else {
		device_set_power_state(i2c0, DEVICE_PM_SUSPEND_STATE);
		device_set_power_state(i2c1, DEVICE_PM_SUSPEND_STATE);

		gpio_pin_configure(gpio0, 26, GPIO_DIR_OUT|GPIO_PUD_PULL_DOWN);
		gpio_pin_write(gpio0, 26, 0);
		gpio_pin_configure(gpio1, 2, GPIO_DIR_OUT|GPIO_PUD_PULL_DOWN);
		gpio_pin_write(gpio1, 2, 0);
		gpio_pin_configure(gpio1, 6, GPIO_DIR_OUT|GPIO_PUD_PULL_DOWN);
		gpio_pin_write(gpio1, 6, 0);
	}

}

#endif // DEGU_DEVICE_POWER_H
