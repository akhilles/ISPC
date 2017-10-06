# pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdint.h>

void crack_ispc(uint8_t initial_msg[4]);
void crack_serial(uint8_t initial_msg[4]);
void md5(uint8_t initial_msg[4], unsigned int *h0, unsigned int *h1, unsigned int *h2, unsigned int *h3);