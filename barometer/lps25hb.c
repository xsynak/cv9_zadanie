/*
 * lps25hb.c
 *
 *  Created on: 30. 12. 2021
 *      Author: synak
 */

#include "lps25hb.h"

uint8_t address_bar = LPS25HB_DEVICE_ADDRESS_0;

uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, address_bar, 0));
}


void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, address_bar, 0);
}


void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, address_bar, 1);
}


float lps25hb_get_temp()
{
	uint8_t data[2];
	int16_t temperature;

	lps25hb_readArray(data, LPS25HB_ADDRESS_TEMP, 2);

	temperature = ((int16_t)((data[1] << 8) | data[0]));

    return (42.5 + (temperature/480));
}


float lps25hb_get_pressure()
{
	uint8_t data[3];

	uint32_t pressure;
    uint8_t pressOut_XL, pressOut_L, pressOut_H;


	lps25hb_readArray(data, LPS25HB_ADDRESS_PRESS, 3);

	pressOut_XL = data[0];
	pressOut_L = data[1];
    pressOut_H = data[2];
	pressure = (uint32_t)pressOut_L << 8 | pressOut_XL;
	pressure = (uint32_t)pressOut_H << 16 | pressure;

	return (pressure/4096.0);
}


uint8_t lps25hb_init(void)
{

	uint8_t status = 1;


	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);

	if(val == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else
	{
		address_bar = LPS25HB_DEVICE_ADDRESS_1;
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);
		if(val == LPS25HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			return status;
		}
	}


	uint8_t ctrl1 = 0b11000000;
	lps25hb_write_byte(LPS25HB_ADDRESS_CTRL1, ctrl1);

	return status;
}

