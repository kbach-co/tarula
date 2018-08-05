#include "reading_light.h"

#include <string.h>

#include "nrf_gpio.h"
#include "nrf_log.h"

#define PIN 30

void reading_light_init()
{
	nrf_gpio_cfg(PIN, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_DISCONNECT, NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_S0H1, NRF_GPIO_PIN_NOSENSE);
	nrf_gpio_pin_clear(PIN);
}

void reading_light_execute(const uint8_t* cmd, size_t length)
{
	if (length < 2)
		return;

	char* trigger = (char*)cmd;

	if (cmd[0] == 'o' && cmd[1] == 'n')
		nrf_gpio_pin_set(PIN);

	if (cmd[0] == 'o' && cmd[1] == 'f' && cmd[2] == 'f')
		nrf_gpio_pin_clear(PIN);
}