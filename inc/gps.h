#ifndef GPS_H 
#define GPS_H 

#include <stdint.h>
#include <string.h> 

void print_gps(const char *gpsdata);
void USART3_IRQHandler(void);
int gps_parse(char *sentence);

#endif

