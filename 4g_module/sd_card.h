/*
 * sd_card.h
 *
 *  Created on: 15-May-2024
 *      Author: dikshajadhav
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void writePacketsToFile(const char *filename, const char *packetBuffer, size_t bufferSize);
void UART_Transmit_Integer(const UART_t *const handle, int value);


