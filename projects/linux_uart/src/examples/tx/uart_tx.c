/***************************************************************************//**
 *   @file   linux_uart/src/examples/tx/uart_tx.c
 *   @brief  UART Tx example
 *   @author Jamila Macagba (jamila.macagba@analog.com)
********************************************************************************
 * Copyright 2025(c) Analog Devices, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. “AS IS” AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ANALOG DEVICES, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "no_os_uart.h"
#include "uart_tx.h"
#include "common_data.h"

int example_main()
{
	int ret = 0;
	struct no_os_uart_desc *uart;
	no_os_uart_init(&uart, &uip);
	if (ret)
		return ret;

	uint8_t tx_data[9] = {0};
	tx_data[0] = 0x44; // D
	tx_data[1] = 0x45; // E
	tx_data[2] = 0x41; // A
	tx_data[3] = 0x44; // D
	tx_data[4] = 0x42; // B
	tx_data[5] = 0x45; // E
	tx_data[6] = 0x45; // E
	tx_data[7] = 0x46; // F
	tx_data[8] = 0x20; // Space

	no_os_uart_write(uart, tx_data, 9);

	no_os_uart_remove(uart);

	return 0;
}

