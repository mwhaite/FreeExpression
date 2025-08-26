/*
 * cartridge.c
 *
 * This file provides an interface to the cartridge port, which is connected
 * to the SPI bus. It is intended to be an alternative command source to the
 * USB serial port.
 *
 * This file is part of FreeExpression.
 *
 * https://github.com/thetazzbot/FreeExpression
 *
 * FreeExpression is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2.
 *
 * FreeExpression is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with FreeExpression. If not, see http://www.gnu.org/licenses/.
 *
 */

#include <avr/io.h>
#include "cartridge.h"
#include "spi.h"
#include "serial.h" /* For SERIAL_NO_DATA */

// A simple single-byte buffer to hold a character read from the cartridge
// before it is consumed by the application.
static uint8_t cartridge_rx_buffer;
static uint8_t cartridge_rx_buffer_full = 0;

// Polls the cartridge for a character and fills the buffer if a character is available.
// This is a helper function and not part of the public API.
static void fill_buffer_if_empty(void) {
    if (!cartridge_rx_buffer_full) {
        // To get a byte from the SPI slave, we must send one.
        // We send a dummy byte (0xFF) and the slave will respond with either
        // a data byte or the dummy byte if no data is available.
        uint8_t data = spiTransferByte(0xFF);
        if (data != 0xFF) {
            cartridge_rx_buffer = data;
            cartridge_rx_buffer_full = 1;
        }
    }
}

void cartridge_init(void) {
    spiInit();
}

void cartridge_putc(uint8_t c) {
    // We can use spiTransferByte and just ignore the returned value.
    spiTransferByte(c);
}

void cartridge_puts(const char *s) {
    while (*s != '\0') {
        cartridge_putc(*s++);
    }
}

uint8_t cartridge_getc(void) {
    fill_buffer_if_empty();

    if (cartridge_rx_buffer_full) {
        // Consume the character from the buffer
        cartridge_rx_buffer_full = 0;
        return cartridge_rx_buffer;
    }

    return SERIAL_NO_DATA;
}

int cartridge_haschar(void) {
    fill_buffer_if_empty();
    return cartridge_rx_buffer_full;
}
