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
#include "bms_debug.h"
#include "common_data.h"
#include <stdio.h>

uint8_t calculateChecksum(uint8_t data[], uint8_t bytes);

int example_main()
{
	int ret = 0;
  uint8_t rx_data[6] = {0}; // Fix command size to 6 bytes
  uint8_t tx_data[60] = {0}; // Holder for transmit data

  // Data Frame
  uint8_t start_command = 0x02; // Fixed Value
  uint8_t bm_id = 0x01; // Default Value only
  uint8_t command_code = 0; // Default value only
  uint8_t num_of_data = 0; // Default value only
  uint8_t checksum = 0; // Default value only

  struct no_os_uart_desc *uart;
  no_os_uart_init(&uart, &uip);
  if (ret)
    return ret;

  printf("Emulate LIPY401 BMS: \n");

  while(1)
  {
    printf("Waiting for command...\n");
	ret = no_os_uart_read(uart, rx_data, 5);

	printf("\nReceived: ");
	for (int i=0; i<5; i++) {
		printf("%0x ", rx_data[i]);
	}
	printf("\n");
    bm_id = rx_data[1]; // Byte 2
    command_code = rx_data[2]; // Byte 3
    no_os_mdelay(10);
    // Sample Data Frame for Fail Status 1, Fail Status 2
    if((command_code == 0x01) || (command_code == 0x13))
    {
      num_of_data = 1; // Only 1 Byte
      tx_data[0] = start_command;
      tx_data[1] = bm_id;
      tx_data[2] = command_code;
      tx_data[3] = num_of_data;
      tx_data[4] = 1;

      checksum = calculateChecksum(tx_data, 5);
      tx_data[5] = checksum;
      tx_data[6] = 0; // Reserved

      no_os_uart_write(uart, tx_data, 7);

      printf("\nTransmit: ");
      for (int i=0; i<7; i++) {
        printf("%0x ", tx_data[i]);
      }
      printf("\n");
    }
    else if (command_code == 0x02) // Cell Voltage
    {
      num_of_data = 16; // 16 bytes
      tx_data[0] = start_command;
      tx_data[1] = bm_id;
      tx_data[2] = command_code;
      tx_data[3] = num_of_data;
      tx_data[4] = 1;
      tx_data[5] = 1;
      tx_data[6] = 1;
      tx_data[7] = 1;
      tx_data[8] = 1;
      tx_data[9] = 1;
      tx_data[10] = 1;
      tx_data[11] = 1;
      tx_data[12] = 1;
      tx_data[13] = 1;
      tx_data[14] = 1;
      tx_data[15] = 1;
      tx_data[16] = 1;
      tx_data[17] = 1;
      tx_data[18] = 1;
      tx_data[19] = 1;
      
      checksum = calculateChecksum(tx_data, 20);
      tx_data[20] = checksum;
      tx_data[21] = 0; // Reserved

      no_os_uart_write(uart, tx_data, 22);

      printf("\nTransmit: ");
      for (int i=0; i<22; i++) {
        printf("%0x ", tx_data[i]);
      }
      printf("\n");
    }
    else if((command_code == 0x03) || (command_code == 0x04) || (command_code == 0x05) || (command_code == 0x11))     // For Current, Temperature, RC, FCC
    {
      num_of_data = 2; // Only 2 Bytes
      tx_data[0] = start_command;
      tx_data[1] = bm_id;
      tx_data[2] = command_code;
      tx_data[3] = num_of_data;
      tx_data[4] = 1;
      tx_data[5] = 1;

      checksum = calculateChecksum(tx_data, 6);
      tx_data[6] = checksum;
      tx_data[7] = 0; // Reserved

      no_os_uart_write(uart, tx_data, 8);

      printf("\nTransmit: ");
      for (int i=0; i<8; i++) {
        printf("%0x ", tx_data[i]);
      }
      printf("\n");
    }
    else if (command_code == 0x20) // Summary Data
    {
      num_of_data = 50; //50 bytes
      tx_data[0] = start_command;
      tx_data[1] = bm_id;
      tx_data[2] = command_code;
      tx_data[3] = num_of_data;
      tx_data[4] = 1;
      tx_data[5] = 1;
      tx_data[6] = 1;
      tx_data[7] = 1;
      tx_data[8] = 1;
      tx_data[9] = 1;
      tx_data[10] = 1;
      tx_data[11] = 1;
      tx_data[12] = 1;
      tx_data[13] = 1;
      tx_data[14] = 1;
      tx_data[15] = 1;
      tx_data[16] = 1;
      tx_data[17] = 1;
      tx_data[18] = 1;
      tx_data[19] = 1;
      tx_data[20] = 1;
      tx_data[21] = 1;
      tx_data[22] = 1;
      tx_data[23] = 1;
      tx_data[24] = 1;
      tx_data[25] = 1;
      tx_data[26] = 1;
      tx_data[27] = 1;
      tx_data[28] = 1;
      tx_data[29] = 1;
      tx_data[30] = 1;
      tx_data[31] = 1;
      tx_data[32] = 1;
      tx_data[33] = 1;
      tx_data[34] = 1;
      tx_data[35] = 1;
      tx_data[36] = 1;
      tx_data[37] = 1;
      tx_data[38] = 1;
      tx_data[39] = 1;
      tx_data[40] = 1;
      tx_data[41] = 1;
      tx_data[42] = 1;
      tx_data[43] = 1;
      tx_data[44] = 1;
      tx_data[45] = 1;
      tx_data[46] = 1;
      tx_data[47] = 1;
      tx_data[48] = 1;
      tx_data[49] = 1;
      tx_data[50] = 1;
      tx_data[51] = 1;
      tx_data[52] = 1;
      tx_data[53] = 1;

      checksum = calculateChecksum(tx_data, 54);
      tx_data[54] = checksum;
      tx_data[55] = 0; //Reserved

      no_os_uart_write(uart, tx_data, 56);

      printf("\nTransmit: ");
      for (int i=0; i<56; i++) {
        printf("%0x ", tx_data[i]);
      }
    }
    
    // Reset RX and TX
    memset(tx_data, 0, sizeof(tx_data));
    memset(rx_data, 0, sizeof(rx_data));
  }

	printf("\n");
	no_os_uart_remove(uart);

	return 0;
}

uint8_t calculateChecksum(uint8_t data[], uint8_t bytes)
{
  uint8_t checksum = 0;
  for(int i = 0; i<bytes; i++)
  {
    checksum = checksum ^ data[i];
  }
  printf("Checksum = %d\n", checksum);
  return checksum;

}
