/*
 * cartridge.h
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
#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <stdio.h>
#include "serial.h" /* For SERIAL_NO_DATA */

void cartridge_init(void);
int cartridge_haschar(void);
void cartridge_putc(uint8_t c);
uint8_t cartridge_getc(void);
void cartridge_puts(const char *s);

#endif
