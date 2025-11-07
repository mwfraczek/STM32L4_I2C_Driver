#ifndef GPS_H 
#define GPS_H 

#include <stdint.h>
#include <string.h> 

void gps_receive(char gpsdata[100]);
void print_gps(const char *gpsdata);

#endif

