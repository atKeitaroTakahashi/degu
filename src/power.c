/*
 * Copyright (c) 2018 Nordic Semiconductor ASA.
 * Copyright (c) 2019 Atmark Techno, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */



#include <clock_control.h>

#include <nrfx/hal/nrf_radio.h>

#include "power.h"

void device_power(bool enable)
{
	if (enable) {
		sys_pm_resume_devices();

		ext_device_power(true);

		nrf_radio_task_trigger(NRF_RADIO_TASK_TXEN);
	} else {
		NRF_RADIO->SHORTS = 0;
		nrf_radio_task_trigger(NRF_RADIO_TASK_DISABLE);

		ext_device_power(false);

		sys_pm_suspend_devices();
	}
}

void sys_pm_notify_lps_entry(enum power_states state)
{
	switch (state) {
	case SYS_POWER_STATE_CPU_LPS_1:
		device_power(false);
		k_cpu_idle();
		break;

	case SYS_POWER_STATE_CPU_LPS_2:
		device_power(false);
		k_cpu_idle();
		break;

	case SYS_POWER_STATE_DEEP_SLEEP:
		device_power(false);
		break;

	default:
		break;
	}
}

void sys_pm_notify_lps_exit(enum power_states state)
{
	switch (state) {
	case SYS_POWER_STATE_CPU_LPS_1:
		device_power(true);
		break;

	case SYS_POWER_STATE_CPU_LPS_2:
		device_power(true);
		break;

	case SYS_POWER_STATE_DEEP_SLEEP:
		device_power(true);
		break;

	default:
		break;
	}
}
