#ifndef BASE_UART_H
#define BASE_UART_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    COMM_SUCCESS,
    COMM_ERROR_INVALID_PARAM,
    COMM_ERROR_BUFFER_FULL,
    COMM_ERROR_CRC_MISMATCH,
    COMM_ERROR_ENCRYPTION_FAIL,
    COMM_ERROR_COMPRESSION_FAIL,
} ErrorCode;

typedef struct CommunicationChannel {
    int (*send)(void* instance, const uint8_t* data, size_t length);
    int (*receive)(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);
    void* instance;
} CommunicationChannel;

typedef struct {
    uint8_t sendBuffer[1024];
    size_t sendBufferSize;
    uint8_t receiveBuffer[1024];
    size_t receiveBufferSize;
    bool isConnected;
} UartChannel;

CommunicationChannel* create_uart_channel();

int uart_send(void* instance, const uint8_t* data, size_t length);
int uart_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);

#endif // BASE_UART_H