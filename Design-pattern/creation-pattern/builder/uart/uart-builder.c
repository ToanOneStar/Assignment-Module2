#include <stdio.h>
#include <stdlib.h>
#include "uart-builder.h"

static UART_Builder* setBaudRate(UART_Builder* builder, uint32_t baudRate) {
    if (baudRate < 1200 || baudRate > 115200) {
        printf("Error: Invalid baud rate. Must be between 1200 and 115200\n");
        return builder;
    }

    builder->config.baudRate = baudRate;
    return builder;
}

static UART_Builder* setParity(UART_Builder* builder, Parity_Bit_e parity) {
    if (parity != NONE && parity != ODD && parity != EVEN) {
        printf("Error: Invalid parity. Must be NONE or ODD or EVEN");
        return builder;
    }

    builder->config.parity = parity;
    return builder;
}

static UART_Builder* setStopBits(UART_Builder* builder, uint8_t stopBits) {
    if (stopBits != 1 && stopBits != 2) {
        printf("Error: Invalid stop bits. Must be 1 or 2");
        return builder;
    }

    builder->config.stopBits = stopBits;
    return builder;
}

static UART_Builder* setDataBits(UART_Builder* builder, uint8_t dataBits) {
    if (dataBits != 8 && dataBits != 9) {
        printf("Error: Invalid data bits. Must be 8 or 9\n");
        return builder;
    }

    builder->config.dataBits = dataBits;
    return builder;
}

static UART_Config_t build(UART_Builder* builder) {
    return builder->config;
}

UART_Builder UART_Builder_Init() {
    UART_Builder builder;
    // Default config
    builder.config.baudRate = BAUDRATE_9600;
    builder.config.parity = NONE;
    builder.config.stopBits = 1;
    builder.config.dataBits = 8;

    builder.setBaudRate = setBaudRate;
    builder.setDataBits = setDataBits;
    builder.setParity = setParity;
    builder.setStopBits = setStopBits;
    builder.build = build;

    return builder;
}