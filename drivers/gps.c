// GT-U7 GPS Module Driver Library

#include "stm32l476.h"
#include "peripherals.h"
#include "utils.h"
#include "usart.h"
#include "gps.h"

// Gather GPS data from USART3 peripheral
void gps_receive(char gpsdata[100]) {
	uint8_t c; 
	while(1) {
		if (USART3_ISR & (1 << 3)) {	// Check for overrun flag (ORE)
			USART3_ICR |= (1 << 3); // Clear overrun flag
			(void) USART3_RDR; 	// Flush RDR data 
		}

		// Wait for '$' character before gathering gps data
		do {
			while (!(USART3_ISR & (1 << 5))); 
			c = USART3_RDR;
		} while (c != '$');
		gpsdata[0] = '$';
	
		// Gather only GPRMC gps data 
		for (uint8_t i = 1; i < 100; i++) {
			while (!(USART3_ISR & (1 << 5))); // Wait for data (RXNE)
			c = USART3_RDR;
			if (c == '\n') {		  // End of NMEA sentence 
				gpsdata[i] = '\0';  	  // Null-terminate at newline
				if (strncmp(gpsdata, "$GPRMC", 6) == 0)
					return;
				break;
			}
			gpsdata[i] = c; 
		}
	}
}

// Output GPS data 
void print_gps(const char *gpsdata) {		 
	usart2_transmitstr(gpsdata);
	usart2_transmitstr("\r\n\n");
}

