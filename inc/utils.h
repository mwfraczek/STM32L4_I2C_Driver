#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void delay_ms(uint32_t ms);
int flag_check_timeout(volatile uint32_t *regaddr, uint32_t bitmask, uint8_t timeout_ms);
void led_blink_slow(void); 
void led_blink_fast(void);

#endif
