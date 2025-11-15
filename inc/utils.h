#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

extern volatile uint32_t tick_ms;

void delay_ms(uint32_t ms);
int flag_check_timeout(volatile uint32_t *regaddr, uint32_t bitmask, uint8_t timeout_ms);
void TIM2_IRQHandler(void);
void led_blink_fast(void);

#endif
