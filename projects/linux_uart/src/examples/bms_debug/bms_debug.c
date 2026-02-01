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
  uint8_t rx_data[6] = {0};  // Fix command size to 6 bytes
  uint8_t tx_data[60] = {0}; // Holder for transmit data

  uint8_t ctr_batch = 0;
  uint8_t diag_mode = 0;

  // Data Frame
  uint8_t start_command = 0x02; // Fixed Value
  uint8_t bm_id = 0x01;         // Default Value only
  uint8_t command_code = 0;     // Default value only
  uint8_t num_of_data = 0;      // Default value only
  uint8_t checksum = 0;         // Default value only

  struct no_os_uart_desc *uart;
  no_os_uart_init(&uart, &uip);
  if (ret)
    return ret;

  printf("Emulate LIPY401 BMS: \n");

  while (1)
  {
    ret = no_os_uart_read(uart, rx_data, 5);
    printf("ret: %d\n", ret);
    if (0 != ret)
    {
      no_os_mdelay(10);
      continue;
    }

    printf("\nReceived: ");
    for (int i = 0; i < 5; i++)
    {
      printf("%0x ", rx_data[i]);
    }
    printf("\n");

    bm_id = rx_data[1];        // Byte 2
    command_code = rx_data[2]; // Byte 3
    no_os_mdelay(10);

    if (command_code == 0x20) // Summary Data
    {
      if ((batch_ctr > 0) && (0 == (batch_ctr % 4)))
      {
        diag_mode++;
      }

      if ((diag_mode > 0) && (0 == (diag_mode % 4)))
      {
        batch_ctr = 0;
        diag_mode = 0;
      }

      num_of_data = 50; // 50 bytes
      tx_data[0] = start_command;
      tx_data[1] = bm_id;
      tx_data[2] = command_code;
      tx_data[3] = num_of_data;

      tx_data[5] = 0x01;  // 2: Leader Battery Status
      tx_data[27] = 0x01; // 24: Num Connected BM
      tx_data[32] = 0x01; // 29: BM ID Voltage Max
      tx_data[35] = 0x01; // 32: BM ID Voltage Min
      tx_data[44] = 0x02; // 41: BM ID Curernt Max
      tx_data[47] = 0x02; // 44: BM ID Current Min

      switch (batch_ctr % 4)
      {
      case 0:
        // 20V
        tx_data[30] = 0x00; // 27: BM Voltage Max Hi
        tx_data[31] = 0x14; // 28: BM Voltage Max Lo

        // 10V
        tx_data[33] = 0x00; // 30: BM Voltage Min Hi
        tx_data[34] = 0x0A; // 31: BM Voltage Min Lo

        // -10A
        tx_data[42] = 0xFF; // 39: BM Current Max Hi
        tx_data[43] = 0xFF; // 40: BM Current Max Lo

        // -20A
        tx_data[45] = 0xFF; // 42: BM Current Min Hi
        tx_data[46] = 0xFE; // 43: BM Current Min Lo
        break;

      case 1:
        // 15V
        tx_data[30] = 0x00; // 27: BM Voltage Max Hi
        tx_data[31] = 0x0F; // 28: BM Voltage Max Lo

        // 5V
        tx_data[33] = 0x00; // 30: BM Voltage Min Hi
        tx_data[34] = 0x05; // 31: BM Voltage Min Lo

        // 0A
        tx_data[42] = 0x00; // 39: BM Current Max Hi
        tx_data[43] = 0x00; // 40: BM Current Max Lo

        // -10A
        tx_data[45] = 0xFF; // 42: BM Current Min Hi
        tx_data[46] = 0xFF; // 43: BM Current Min Lo
        break;

      case 2:
        // 10V
        tx_data[30] = 0x00; // 27: BM Voltage Max Hi
        tx_data[31] = 0x0A; // 28: BM Voltage Max Lo

        // 0V
        tx_data[33] = 0x00; // 30: BM Voltage Min Hi
        tx_data[34] = 0x00; // 31: BM Voltage Min Lo

        // 10A
        tx_data[42] = 0x00; // 39: BM Current Max Hi
        tx_data[43] = 0x01; // 40: BM Current Max Lo

        // 0A
        tx_data[45] = 0x00; // 42: BM Current Min Hi
        tx_data[46] = 0x00; // 43: BM Current Min Lo
        break;

      case 3:
        // 15V
        tx_data[30] = 0x00; // 27: BM Voltage Max Hi
        tx_data[31] = 0x0F; // 28: BM Voltage Max Lo

        // 5V
        tx_data[33] = 0x00; // 30: BM Voltage Min Hi
        tx_data[34] = 0x05; // 31: BM Voltage Min Lo

        // 0A
        tx_data[42] = 0x00; // 39: BM Current Max Hi
        tx_data[43] = 0x00; // 40: BM Current Max Lo

        // -10A
        tx_data[45] = 0xFF; // 42: BM Current Min Hi
        tx_data[46] = 0xFF; // 43: BM Current Min Lo
        break;

      default:
        // Code should not go here.
        break;
      }
      batch_ctr++;

      switch (diag_mode)
      {
      // Normal Status
      case 0:
        tx_data[4] = 0;  // 1: Fail Status 1
        tx_data[17] = 0; // 14: Fail Status 2
        tx_data[18] = 0; // 15: Fail Status 3
        tx_data[19] = 0; // 16: Leader Alarm 1
        tx_data[20] = 0; // 17: Leader Alarm 2
        break;

      // Trigger Fail Status 1
      case 1:
        tx_data[4] = 0xFF; // 1: Fail Status 1
        tx_data[17] = 0;   // 14: Fail Status 2
        tx_data[18] = 0;   // 15: Fail Status 3
        tx_data[19] = 0;   // 16: Leader Alarm 1
        tx_data[20] = 0;   // 17: Leader Alarm 2
        break;

      // Trigger Fail Status 2
      case 2:
        tx_data[4] = 0xFF;  // 1: Fail Status 1
        tx_data[17] = 0xFF; // 14: Fail Status 2
        tx_data[18] = 0;    // 15: Fail Status 3
        tx_data[19] = 0;    // 16: Leader Alarm 1
        tx_data[20] = 0;    // 17: Leader Alarm 2
        break;

      // Trigger Leader Alarm 1
      case 3:
        tx_data[4] = 0xFF;  // 1: Fail Status 1
        tx_data[17] = 0xFF; // 14: Fail Status 2
        tx_data[18] = 0;    // 15: Fail Status 3
        tx_data[19] = 0xFF; // 16: Leader Alarm 1
        tx_data[20] = 0;    // 17: Leader Alarm 2
        break;

      default:
        // Code should not go here.
        break;
      }

      checksum = calculateChecksum(tx_data, 54);
      tx_data[54] = checksum;
      tx_data[55] = 0; // Reserved

      no_os_uart_write(uart, tx_data, 56);

      printf("\nTransmit: ");
      for (int i = 0; i < 56; i++)
      {
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
  for (int i = 0; i < bytes; i++)
  {
    checksum = checksum ^ data[i];
  }
  printf("Checksum = %d\n", checksum);

  return checksum;
}
