//  STM32L476RG Peripheral Setup and Enable Functions

#include "stm32l476.h"
#include "peripherals.h"

void rcc_enable(void) {
	RCC_AHB2ENR  |= (0x3 << 0);  // Enable GPIOA & GPIOB clocks
	RCC_APB1ENR1 |= (0x1 << 21); // Enable I2C1 clock
	RCC_CCIPR    |= (0x1 << 12); // Select SYSCLK (HSI16) as I2C1 source clock
	RCC_APB1ENR1 |= (0x1 << 0);  // Enable TIM2 clock
}

void gpio_config(void) {
	// Set Nucleo User LD2 LED 
	GPIOA_MODER &= ~(0x3 << 10); 	// Clear PA5 bits
	GPIOA_MODER |=  (0x1 << 10); 	// Set PA5 to output mode

	// Set PB8/PB9 as alternate function pins for I2C use case
	GPIOB_AFRH  |=  (0x4 << 4) | (0x4 << 0);    // Set pins to AF4 (I2C selection) 
	GPIOB_OTYPER |=  (0x3 << 8);    // Set to open-drain
	GPIOB_PUPDR  &= ~(0xF << 16);   // Set NO pull up/downs (use external resistors)
	GPIOB_MODER &= ~(0xF << 16);    // Clear PB8/PB9 bits
	GPIOB_MODER |=  (0xA << 16);    // Set PB8/PB9 to AF4

	// Set GPIO debug pin (Nucleo D10 - PB6)
	GPIOB_OSPEEDR |= (0x2 << 12);   // High speed
	GPIOB_MODER &= ~(0x3 << 12);    // Clear PB6 bit
	GPIOB_MODER |=  (0x1 << 12);    // Set PB6 to output mode
}

void tim2_enable(void) {
	TIM2_SMCR &= ~(0x7 << 0);// Disable slave mode controller 
	TIM2_PSC = 15; 		 // Define prescaler (CK_CNT = fCK_PSC/(PSC+1) = 16MHz/(15 + 1) = 1 MHz) 
	TIM2_ARR = 999; 	 // Define auto-reload register for 1000 ticks (1000/1Mhz = 1ms)
	TIM2_CNT = 0; 		 // Define counter to start at zero (upcounting mode)
	TIM2_EGR |= (1 << 0);  	 // UG bit synchronizes settings to timer operation
	TIM2_CR1 |= (1 << 0); 	 // Enable TIM2 counter 
}
