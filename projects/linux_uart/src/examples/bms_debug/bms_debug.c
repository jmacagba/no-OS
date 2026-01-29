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
    ret = no_os_uart_read(uart, rx_data, 5);
    printf("ret: %d\n", ret);
    if (0 != ret)
    {
      no_os_mdelay(10);
      continue;
    }

    printf("\nReceived: ");
    for (int i=0; i<5; i++)
    {
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
      // Mock Summary Data from UART
      num_of_data = 50; //50 bytes

      // 0x02 0x01 0x20 0x32
      tx_data[0] = 0x02;
      tx_data[1] = 0x01;
      tx_data[2] = 0x20;
      tx_data[3] = 0x32;
  
      // 0x40 0x03 0x63 0x63 0x64
      tx_data[4] = 0x40;
      tx_data[5] = 0x03;
      tx_data[6] = 0x63;
      tx_data[7] = 0x63;
      tx_data[8] = 0x64;

      // 0x00 0xD5 0x00 0x00 0x00
      tx_data[9] = 0x00;
      tx_data[10] = 0xD5;
      tx_data[11] = 0x00;
      tx_data[12] = 0x00;
      tx_data[13] = 0x00;

      // 0x00 0x68 0x10 0x00 0x00
      tx_data[14] = 0x00;
      tx_data[15] = 0x68;
      tx_data[16] = 0x10;
      tx_data[17] = 0x00;
      tx_data[18] = 0x00;

      // 0x00 0x00 0x08 0x34 0x08
      tx_data[19] = 0x00;
      tx_data[20] = 0x00;
      tx_data[21] = 0x08;
      tx_data[22] = 0x34;
      tx_data[23] = 0x08;

      // 0x34 0x08 0x33 0x01 0x13
      tx_data[24] = 0x34;
      tx_data[25] = 0x08;
      tx_data[26] = 0x33;
      tx_data[27] = 0x01;
      tx_data[28] = 0x13;

      // 0x10 0x68 0x10 0x01 0x68
      tx_data[29] = 0x10;;
      tx_data[30] = 0x68;
      tx_data[31] = 0x10;
      tx_data[32] = 0x01;
      tx_data[33] = 0x68;

      // 0x10 0x01 0x00 0xD7 0x01
      tx_data[34] = 0x10;
      tx_data[35] = 0x01;
      tx_data[36] = 0x00;
      tx_data[37] = 0xD7;
      tx_data[38] = 0x01;

      // 0x00 0xD5 0x01 0x00 0x00
      tx_data[39] = 0x00;
      tx_data[40] = 0xD5;
      tx_data[41] = 0x01;
      tx_data[42] = 0x00;
      tx_data[43] = 0x00;

      // 0x01 0x00 0x00 0x01 0x0D
      tx_data[44] = 0x01;;
      tx_data[45] = 0x00;
      tx_data[46] = 0x00;
      tx_data[47] = 0x01;
      tx_data[48] = 0x0D;

      // 0x05 0x01 0x0C 0xFD 0x01
      tx_data[49] = 0x05;
      tx_data[50] = 0x01;
      tx_data[51] = 0x0C;
      tx_data[52] = 0xFD;
      tx_data[53] = 0x01;

      // 0x59 0x00
      tx_data[54] = 0x59;
      tx_data[55] = 0x00;

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
