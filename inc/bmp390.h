#ifndef BMP390_H
#define BMP390_H

// BMP390 Memory Address
#define BMP_CHIPID_ADDR    0x00
#define BMP_STATUS_ADDR    0x03
#define BMP_DATA_ADDR      0x04 // 0x04-0x09
#define BMP_PWRCTRL_ADDR   0x1B
#define BMP_OSR_ADDR       0x1C
#define BMP_ODR_ADDR       0x1D
#define BMP_CONFIG_ADDR    0x1F
#define BMP_SLAVE_ADDR     0x76

int bmp390_setup(void);
int bmp390_status(uint8_t *bmp_status);
int bmp390_chipid(uint8_t *bmp_chipid);
int bmp390_data(uint8_t *bmp_data);

#endif
