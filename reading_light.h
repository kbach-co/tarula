#pragma once

#include <stddef.h>
#include <stdint.h>

void reading_light_init();
void reading_light_execute(const uint8_t* cmd, size_t length);