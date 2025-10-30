// I2C Driver Library for STM32L476RG applications

#include "stm32l476.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"
#include "utils.h"

uint8_t timeout = 100;

// Reset I2C1 peripheral by toggling PE bit 
void i2c1_reset(void) { 
	I2C1_CR1 &= ~(1 << 0); 
	while (I2C1_CR1 & (1 << 0));
	I2C1_CR1 |= (1 << 0); 
}

// Configure I2C1 peripheral 
void i2c1_init(void) {
	I2C1_CR1 &= ~(1 << 0);   // Disable I2C1 peripheral 
	I2C1_CR1 &= ~(1 << 12);  // Enable ANF
	I2C1_CR1 &= ~(0xF << 8); // Clear DNF
	I2C1_CR1 |=  (2 << 8);	 // Disable DNF
	I2C1_CR1 &= ~(1 << 17);  // Enable Clock Stretching
	I2C1_TIMINGR = 0x30420F13; // 100kHz Standard Mode
	I2C1_CR1 |=  (1 << 0);     // Enable peripheral
}

int i2c1_write(uint8_t slave_addr, uint8_t reg_addr, const uint8_t *data, uint8_t len, uint8_t autoend) {
	uint32_t cr2 = 0;
	I2C1_CR2 &= ~(0x3FF | (1 << 10) | (1 << 11) | (0xFF << 16) | (1 << 25) | (1 << 13));
	cr2 |=  (slave_addr << 1); // 7-bit slave address mode
	cr2 |=  (0 << 10); 	   // Write direction
	cr2 |=  (0 << 11); 	   // 7-bit addressing mode
        cr2 |=  ((len + 1) << 16); // NBYTES + register addr
	cr2 |=  (autoend << 25);   // AUTOEND mode 
	cr2 |=  (1 << 13);         // START generation
	I2C1_CR2 = cr2;		   // Config CR2 register
	if (flag_check_timeout(&I2C1_ISR, (1 << 1), timeout) < 0) // Wait for TXDR empty & ready
		return -1;
	I2C1_TXDR = reg_addr;           // Write register address
	if (data != NULL) {		// WRITE ONLY
		if (flag_check_timeout(&I2C1_ISR, (1 << 1), timeout) < 0) // Wait for TXIS flag
			return -1;
		I2C1_TXDR = *data;              // Write data byte
		if (flag_check_timeout(&I2C1_ISR, (1 << 5), timeout) < 0) // Wait for STOPF flag
			return -1;
                I2C1_ICR |=  (1 << 5);          // Clear STOPF flag
	}
	else {
		if (flag_check_timeout(&I2C1_ISR, (1 << 6), timeout) < 0) // Wait for TC flag
			return -1;
	}
	return 0;
}

int i2c1_read(uint8_t slave_addr, uint8_t *data, uint8_t len, uint8_t autoend) {
	uint32_t cr2 = 0;
	I2C1_CR2 &= ~(0x3FF | (1 << 10) | (1 << 11) | (1 << 12) | (0xFF << 16) | (1 << 25) | (1 << 13));
	cr2 |=  (slave_addr << 1); // 7-bit slave address
	cr2 |=  (1 << 10); 	   // Read direction
	cr2 |=  (0 << 11); 	   // 7-bit addressing mode
        cr2 |=  (len << 16);       // NBYTES 
	cr2 |=  (autoend << 25);   // AUTOEND 
	cr2 |=  (1 << 13); 	   // repeated START
	I2C1_CR2 = cr2;		   // Config CR2 register
	for (uint8_t i = 0; i < len; i++) {
		if (flag_check_timeout(&I2C1_ISR, (1 << 2), timeout) < 0) // Wait for RXDR data
			return -1;
		data[i] = I2C1_RXDR;   // Read RXDR
	}
	if (flag_check_timeout(&I2C1_ISR, (1 << 5), timeout) < 0) // Wait for STOPF flag
		return -1;
	I2C1_ICR |= (1 << 5); // Clear STOPF
	return 0;
}
