#ifndef PERIPHERALS_H
#define PERIPHERALS_H

extern volatile uint32_t tick_ms;

void rcc_enable(void); 
void gpio_config(void);
void tim2_enable(void);
void TIM2_IRQHandler(void);
void exti_enable(void);
void syscfg_enable(void);

#endif
