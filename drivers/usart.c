// USART Driver Library for STM32L476RG applications

#include "stm32l476.h"
#include "i2c.h"
#include "peripherals.h"
#include "bmp390.h"
#include "utils.h"

// Setup USART peripheral
void usart2_init(void) { 
	USART2_CR1 &= ~(1 << 12); // M0 word length
	USART2_CR1 &= ~(1 << 28); // M1 word length (8-bit word length)
	USART2_CR2 &= ~(3 << 12); // STOP bits (n = 0)
	USART2_BRR  = 0x0683;     // Baud rate = 9600 (fCK / baud)
	USART2_CR1 |=  (1 << 3);  // Transmitter enable (TE)
	USART2_CR1 |=  (1 << 0);  // USART enable (UE)
}

// General Write Function
void usart2_write(uint8_t data) {
	while (!(USART2_ISR & (1 << 7))); // Wait for empty transmit data register (TXE)
	USART2_TDR = data;
}

// String Output
void usart2_write_str(const char *s) {
	while (*s) {
		usart2_write(*s++);
	}
}

// Integer Output
void usart2_write_int(int value) {
	char buffer[12];
	unsigned int i = 0;

	if (value < 0) {
		usart2_write('-');
		value = -value;
	}

	while (value > 0 && i < sizeof(buffer)-1) {
		buffer[i++] = (value % 10) + '0';
		value /= 10;
	}

	while (i > 0) {
		usart2_write(buffer[--i]);
	}
}

// Float Output
void usart2_write_float(float value, int decimals) {
	if (value < 0) {
		usart2_write('-');
		value = -value;
	}
	int whole = (int)value;
	float frac_part = value - (float)whole;

	// scale fractional part
	for (int i = 0; i < decimals; i++) {
		frac_part *= 10.0f;
	}
	int frac = (int)frac_part;

	usart2_write_int(whole);
	usart2_write('.');

	// ensure leading zeros in fractional part
	int div = 1;
	for (int i = 1; i < decimals; i++)
		div *= 10;
	while (frac < div) {
		usart2_write('0');
		div /= 10;
	}
	usart2_write_int(frac);
}

// Print BMP390 Temperature & Pressure Readings
void print_bmp390_readings(float temp, float press) {
	usart2_write_str("Temp (C): ");
	usart2_write_float(temp, 2);
	usart2_write_str("\r\n");

	usart2_write_str("Pressure (Pa): ");
	usart2_write_float(press, 2);
	usart2_write_str("\r\n\r\n");
}
