#include "stm32l476.h"
#include "peripherals.h"
#include "utils.h"
#include "i2c.h"
#include "bmp390.h"

uint8_t bmpid; 
uint8_t bmpstatus;
uint8_t bmpdata[6];

int main(void) {
	// Setup STM32 peripherals 
	rcc_enable();
	gpio_config();
	tim2_enable();

	// Setup I2C1 peripheral 
	i2c1_init();

	// Function Calls
	if (bmp390_setup() != 0)
		led_blink_fast();
	if (bmp390_chipid(&bmpid) != 0)
		led_blink_fast();
	if (bmp390_status(&bmpstatus) != 0)
		led_blink_fast();
	bmp390_data(bmpdata);
	while (1) 
		led_blink_slow();
}
