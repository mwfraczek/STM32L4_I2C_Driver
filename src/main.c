#include "stm32l476.h"
#include "peripherals.h"
#include "utils.h"
#include "i2c.h"
#include "bmp390.h"
#include "usart.h"
#include "gps.h"

int main(void) {
	// Variable declarations
	uint8_t bmpstatus;
	volatile float temperature_c;
	volatile float pressure_pa;
	char gpsdata[100];
	bmp_coeff_t cal_raw; 	// raw coeffs
	bmp_par_t cal;		// converted coeffs
	bmp_raw_t raw;		// raw readings

	// Setup STM32 peripherals 
	rcc_enable();
	gpio_config();
	tim2_enable();
	i2c1_init();
	usart2_init();
	usart3_init();

	// Setup and wait for ready sensor 
	if (bmp390_setup() != 0) led_blink_fast();
	do {
		if (bmp390_status(&bmpstatus) != 0)
			led_blink_fast(); 
	} while (bmpstatus != 0x70);
	
	// Read and Convert Sensor Calibration Coefficients 
	bmp390_coeffdata(&cal_raw);
        bmp390_coeffconvert(&cal_raw, &cal);
	
	// Gather and output temp, pressure, GPS values via UART 
	while (1) {
		bmp390_rawdata(&raw);
		gps_receive(gpsdata);
	      	temperature_c = bmp390_temp(raw.raw_temperature, &cal);
        	pressure_pa = bmp390_pressure(raw.raw_pressure, &cal);
		print_bmp390(temperature_c, pressure_pa);
		print_gps(gpsdata);
		led_blink_slow();
	}
}
