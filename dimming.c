#include "dimming.h"

#include <stdlib.h>
#include <string.h>

#include "app_error.h"
#include "app_timer.h"
#include "boards.h"
#include "low_power_pwm.h"
#include "nrf_log.h"

static low_power_pwm_t pwm_module;

static void pwm_module_init();
static void dim(uint8_t percentage);

void dimming_init()
{
	pwm_module_init();
	dim(0);
}

void dimming_execute(const uint8_t* cmd, size_t length)
{
	static char convert_buf[4];

	if (length == 0)
		return;

	size_t convert_len = (length > 3 ? 3 : length);
	memcpy(convert_buf, cmd, convert_len);
	convert_buf[convert_len] = '\0';
	uint8_t dim_level = (uint8_t)strtol(convert_buf, NULL, 10);
	dim(dim_level);
}

static void pwm_module_init()
{
	APP_TIMER_DEF(app_timer);
	low_power_pwm_config_t pwm_config;

	pwm_config.active_high = false;
	pwm_config.period = 255;
	pwm_config.bit_mask = BSP_LED_0_MASK;
	pwm_config.p_timer_id = &app_timer;
	pwm_config.p_port = NRF_GPIO;

	APP_ERROR_CHECK(low_power_pwm_init(&pwm_module, &pwm_config, NULL));
	APP_ERROR_CHECK(low_power_pwm_start(&pwm_module, pwm_module.bit_mask));
}

static void dim(uint8_t percentage)
{
	uint8_t period = 255 - ((percentage * 255) / 100);
	NRF_LOG_DEBUG("Dimming %d%% to duty %d", percentage, period);
	APP_ERROR_CHECK(low_power_pwm_duty_set(&pwm_module, period));
}