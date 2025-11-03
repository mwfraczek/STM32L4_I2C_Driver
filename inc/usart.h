#ifndef USART_H 
#define USART_H 

#include <stddef.h> // Handles 'NULL'
#include <stdint.h>

void usart2_init(void);
void usart2_write(uint8_t data);
void usart2_write_str(const char *s);
void usart2_write_int(int value);
void usart2_write_float(float value, int decimals);
void print_bmp390_readings(float temp, float press);

#endif
