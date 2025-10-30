// BMP390 Device Driver Library 

#include "stm32l476.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"
#include "utils.h"

uint8_t bmp_pwrctrl = 0x13; // Forced Mode - Temp/Pressure Enable
uint8_t bmp_osr = 0x00;	    // No Oversampling
uint8_t bmp_odr = 0x00;	    // 5ms Sampling Period

// Configuration Function 
int bmp390_setup(void) {
	if (i2c1_write(BMP_SLAVE_ADDR, BMP_PWRCTRL_ADDR, &bmp_pwrctrl, 1, 1) != 0)
		return -1; 
        if (i2c1_write(BMP_SLAVE_ADDR, BMP_OSR_ADDR, &bmp_osr, 1, 1) != 0)
		return -1; 
        if (i2c1_write(BMP_SLAVE_ADDR, BMP_ODR_ADDR, &bmp_odr, 1, 1) != 0)
		return -1;
	return 0;
}

// Sensor Status
int bmp390_status(uint8_t *bmp_status) {
	if (i2c1_write(BMP_SLAVE_ADDR, BMP_STATUS_ADDR, NULL, 0, 0) != 0)
		return -1; 
        if (i2c1_read(BMP_SLAVE_ADDR, bmp_status, 1, 1) != 0)
		return -1;
	return 0;
}

// Read Chip ID
int bmp390_chipid(uint8_t *bmp_chipid) {
        if (i2c1_write(BMP_SLAVE_ADDR, BMP_CHIPID_ADDR, NULL, 0, 0) != 0)
		return -1;
        if (i2c1_read(BMP_SLAVE_ADDR, bmp_chipid, 1, 1) != 0)
		return -1;
	return 0;
}

// Read Temperature Data
int bmp390_data(uint8_t *bmp_data) {
	if (i2c1_write(BMP_SLAVE_ADDR, BMP_DATA_ADDR, NULL, 0, 0) != 0)
		return -1;
	if (i2c1_read(BMP_SLAVE_ADDR, bmp_data, 6, 1) != 0)
		return -1;
	return 0;
}
