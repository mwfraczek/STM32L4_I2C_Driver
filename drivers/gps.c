// GT-U7 GPS Module Driver Library

#include "stm32l476xx.h"
#include "stm32l476.h"
#include "peripherals.h"
#include "utils.h"
#include "usart.h"
#include "gps.h"

#define BUF_SIZE 256
volatile char gps_buf[BUF_SIZE];
volatile uint16_t write_index = 0;

// Output GPS data 
void print_gps(const char *gpsdata) {		 
	usart2_transmitstr(gpsdata);
	usart2_transmitstr("\r\n\n");
}

// Parser for GPS data 
int gps_parse(char *sentence) {
	static uint16_t read_index = 0;   // Persistent index
	uint16_t scan_index = read_index; // Scanning index 

	// Search for sentence start ('$')
	while (scan_index != write_index) {
		if (gps_buf[scan_index] == '$') {
			break;
		}
		scan_index = (scan_index + 1) % BUF_SIZE;
	}
	// Return if no '$' found
	if (scan_index == write_index)
		return 0;

	// Pull bytes 
	uint16_t start = scan_index;
	while (scan_index != write_index) { 
		char c = gps_buf[scan_index];
		sentence[scan_index - start] = c;
		if (c == '\n') { 
			sentence[(scan_index - start) + 1] = '\0';   // Null-terminate
			read_index = (scan_index + 1) % BUF_SIZE; // Update read index
			return 1;  // Complete sentence
		}
		scan_index = (scan_index + 1) % BUF_SIZE; // Continue to populate 
	}
	// Return if incomplete sentence
	return 0;
}

// UART-based GPS data ISR 
void USART3_IRQHandler(void) {
    if (USART3_ISR & (1 << 5)) {   // RXNE flag: data available
        char c = USART3_RDR;       // read the byte
        gps_buf[write_index] = c;     // store it
        write_index = (write_index + 1) % BUF_SIZE;  // wrap index
    }
}
