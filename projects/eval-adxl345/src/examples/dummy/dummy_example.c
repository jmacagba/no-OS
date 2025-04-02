/***************************************************************************//**
 *   @file   dummy_example.c
 *   @brief  DUMMY example header for eval-adxl355-pmdz project
 *   @author RBolboac (ramona.bolboaca@analog.com)
********************************************************************************
 * Copyright 2022(c) Analog Devices, Inc.
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

#include "common_data.h"
#include "adxl345.h"
#include "no_os_delay.h"
#include "no_os_print_log.h"

/***************************************************************************//**
 * @brief Dummy example main execution.
 *
 * @return ret - Result of the example execution. If working correctly, will
 *               execute continuously the while(1) loop and will not return.
*******************************************************************************/
int example_main()
{
	struct adxl345_dev *adxl345_desc;
	int ret;

	ret = adxl345_init(&adxl345_desc, adxl345_ip);
	if (ret)
		goto error;

	// Raw Data Output
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;
	
	float x_f = 0.0;
	float y_f = 0.0;
	float z_f = 0.0;
	
	int power_ctl_reg_val = adxl345_get_register_value(adxl345_desc,ADXL345_POWER_CTL);
	pr_info(" POWER_CTL REG=0x%X\n", power_ctl_reg_val);
	
	pr_info("\n\n");
	int fifo_ctl_reg_val = adxl345_get_register_value(adxl345_desc,ADXL345_FIFO_CTL);
	pr_info(" FIFO_CTL REG=0x%X\n", fifo_ctl_reg_val);

	// Enable measurement mode
	adxl345_set_power_mode(adxl345_desc,0x1);
	
	power_ctl_reg_val = adxl345_get_register_value(adxl345_desc,ADXL345_POWER_CTL);
	pr_info(" POWER_CTL REG=0x%X\n", power_ctl_reg_val);

	while (1) {

		pr_info("Single read (INT)\n");
		adxl345_get_xyz(adxl345_desc, &x, &y, &z);

		pr_info(" x=%d", (int)x);
		pr_info(" y=%d", (int)y);
		pr_info(" z=%d\n", (int)z);

		no_os_mdelay(10);
		
		pr_info("Single read (FLOAT)\n");
		adxl345_get_g_xyz(adxl345_desc, &x_f, &y_f, &z_f);
		pr_info(" x in g=%f", x_f);
		pr_info(" y in g=%f", y_f);
		pr_info(" z in g=%f\n", z_f);

	}


error:
	pr_info("Error!\n");
	return 0;
}
