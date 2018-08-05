#pragma once

#include <stddef.h>
#include <stdint.h>

void dimming_init();
void dimming_execute(const uint8_t* cmd, size_t length);