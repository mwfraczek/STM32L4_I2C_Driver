#ifndef STM32L476_H
#define STM32L476_H

#include <stdint.h>

#define RCC_AHB2ENR   (*(volatile uint32_t*)0x4002104C) // peripheral clock enable (GPIOA/B)
#define RCC_APB1ENR1  (*(volatile uint32_t*)0x40021058) // peripheral clock enable (I2C1)
#define RCC_CR        (*(volatile uint32_t*)0x40021000) // clock control 
#define RCC_CCIPR     (*(volatile uint32_t*)0x40021088) // peripheral independent clock source select
#define RCC_APB1RSTR1 (*(volatile uint32_t*)0x40021038) // clock reset 
#define RCC_CFGR      (*(volatile uint32_t*)0x40021008) // clock configuration

#define TIM2_CR1      (*(volatile uint32_t*)0x40000000) // TIM2 control register 
#define TIM2_SMCR     (*(volatile uint32_t*)0x40000008) // TIM2 slave mode control  
#define TIM2_SR       (*(volatile uint32_t*)0x40000010) // TIM2 status register (flags)
#define TIM2_EGR      (*(volatile uint32_t*)0x40000014) // TIM2 event generation
#define TIM2_CNT      (*(volatile uint32_t*)0x40000024) // TIM2 slave mode control
#define TIM2_PSC      (*(volatile uint32_t*)0x40000028) // TIM2 prescaler
#define TIM2_ARR      (*(volatile uint32_t*)0x4000002C) // TIM2 auto-reload 

#define GPIOA_MODER   (*(volatile uint32_t*)0x48000000) // GPIOA mode
#define GPIOA_OTYPER  (*(volatile uint32_t*)0x48000004) // GPIOA Type - Open drain vs push/pull 
#define GPIOA_ODR     (*(volatile uint32_t*)0x48000014) // GPIOA output data
#define GPIOA_AFRL    (*(volatile uint32_t*)0x48000020) // GPIOA alternate function LO
#define GPIOA_PUPDR   (*(volatile uint32_t*)0x4800000C) // GPIOA pull up/down

#define GPIOB_MODER   (*(volatile uint32_t*)0x48000400) // GPIOB base address/mode
#define GPIOB_OTYPER  (*(volatile uint32_t*)0x48000404) // Type - Open drain vs push/pull
#define GPIOB_OSPEEDR (*(volatile uint32_t*)0x48000408) // GPIOB output speed register
#define GPIOB_IDR     (*(volatile uint32_t*)0x48000410) // GPIOB input data register
#define GPIOB_ODR     (*(volatile uint32_t*)0x48000414) // GPIOB output data register
#define GPIOB_BSRR    (*(volatile uint32_t*)0x48000418) // GPIOB bit set/reset register
#define GPIOB_PUPDR   (*(volatile uint32_t*)0x4800040C) // GPIOB pull up/down register
#define GPIOB_AFRH    (*(volatile uint32_t*)0x48000424) // GPIOB alt function register

#define I2C1_CR1      (*(volatile uint32_t*)0x40005400) // I2C1 configuration register
#define I2C1_CR2      (*(volatile uint32_t*)0x40005404) // I2C1 transaction/control register
#define I2C1_TIMINGR  (*(volatile uint32_t*)0x40005410) // I2C1 timing register
#define I2C1_ISR      (*(volatile uint32_t*)0x40005418) // I2C1 status register
#define I2C1_ICR      (*(volatile uint32_t*)0x4000541C) // I2C1 flag clearing register
#define I2C1_RXDR     (*(volatile uint32_t*)0x40005424) // I2C1 receive data register
#define I2C1_TXDR     (*(volatile uint32_t*)0x40005428) // I2C1 transmit data register

#define USART2_CR1    (*(volatile uint32_t*)0x40004400) 
#define USART2_CR2    (*(volatile uint32_t*)0x40004404) 
#define USART2_BRR    (*(volatile uint32_t*)0x4000440C)
#define USART2_ISR    (*(volatile uint32_t*)0x4000441C) 
#define USART2_TDR    (*(volatile uint32_t*)0x40004428) 

#endif
