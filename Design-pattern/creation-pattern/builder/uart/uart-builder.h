#ifndef UART_BUILDER_H
#define UART_BUILDER_H

#include <stdint.h>

#define BAUDRATE_9600   9600
#define BAUDRATE_115200 115200

typedef enum {
    NONE,
    ODD,
    EVEN,
} Parity_Bit_e;

typedef struct {
    uint32_t baudRate;
    Parity_Bit_e parity;
    uint8_t stopBits; // 1: 1 bit stop, 2: 2 bit stop
    uint8_t dataBits; // 8: 8 bit data, 9: 9 bit data
} UART_Config_t;

typedef struct UART_Builder {
    UART_Config_t config;
    struct UART_Builder* (*setBaudRate)(struct UART_Builder*, uint32_t);
    struct UART_Builder* (*setParity)(struct UART_Builder*, Parity_Bit_e);
    struct UART_Builder* (*setStopBits)(struct UART_Builder*, uint8_t);
    struct UART_Builder* (*setDataBits)(struct UART_Builder*, uint8_t);
    UART_Config_t (*build)(struct UART_Builder*);
} UART_Builder;

UART_Builder UART_Builder_Init();

#endif // UART_BUILDER_H