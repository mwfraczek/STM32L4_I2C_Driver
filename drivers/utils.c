// STM32L476RG Application Layer Functions

#include "stm32l476.h"
#include "peripherals.h"


// Delay function using TIM2 timer
void delay_ms(uint32_t ms) {
	for (uint32_t i = 0; i < ms; i++) {
		while (!(TIM2_SR & (1 << 0))); // Wait for update interrupt flag
		TIM2_SR &= ~(1 << 0); // Reset flag 
	}
}

// Timeout loop for flag checks
int flag_check_timeout(volatile uint32_t *regaddr, uint32_t bitmask, uint32_t timeout_ms) {
	uint8_t counter = 0;
	while (!(*regaddr & bitmask)) {		// Loop while flag is NOT set
		if (TIM2_SR & (1 << 0)) { 	// Check if 1ms has passed via update interrupt flag
			counter++; 		// Increment millisecond counter
			TIM2_SR &= ~(1 << 0); 	// Reset update interrupt flag
			if (counter >= timeout_ms) {
				return -1; 	// Timeout
			}
		}
	}
	return 0; 
}

void led_blink_slow(void) {
	GPIOA_ODR |= (1 << 5); // Set PA5 
	delay_ms(1000);
	GPIOA_ODR &= ~(1 << 5); // Clear PA5
	delay_ms(1000);
}

void led_blink_fast(void) {
        GPIOA_ODR |= (1 << 5); // Set PA5
	delay_ms(100);
        GPIOA_ODR &= ~(1 << 5); // Clear PA5 
	delay_ms(100);
}
