#include "stm32l476.h"

// Enable HSI16 (16 MHz) and switch SYSCLK source to HSI16
void SystemInit(void) {
	RCC_CR |= (1 << 8); 	    // HSI16 clock enable
	while (!(RCC_CR & (1 << 10)));  // Wait for stable oscillator flag
	RCC_CFGR |= (1 << 0); 	    // Select SYSCLK source as HSI16
	while (!(RCC_CFGR & (1 << 2))); // Check for correct clock source
}

// Empty - no C runtime initialization needed
void _init(void) {
}
