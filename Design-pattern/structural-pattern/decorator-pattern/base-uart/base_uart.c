#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "base_uart.h"

CommunicationChannel* create_uart_channel() {
    UartChannel* uart = malloc(sizeof(UartChannel));
    memset(uart, 0, sizeof(UartChannel));
    uart->isConnected = true;

    CommunicationChannel* channel = malloc(sizeof(CommunicationChannel));
    channel->send = uart_send;
    channel->receive = uart_receive;
    channel->instance = uart;

    return channel;
}

int uart_send(void* instance, const uint8_t* data, size_t length) {
    UartChannel* uart = (UartChannel*)instance;
    if (!uart || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    if (uart->sendBufferSize + length > sizeof(uart->sendBuffer)) {
        return COMM_ERROR_BUFFER_FULL;
    }

    memcpy(uart->sendBuffer + uart->sendBufferSize, data, length);
    uart->sendBufferSize += length;

    printf("[UART] Sent %zu bytes: ", length);
    for (size_t i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");

    return (int)length;
}

int uart_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    UartChannel* uart = (UartChannel*)instance;
    if (!uart || !buffer || !receivedLength) {
        return COMM_ERROR_INVALID_PARAM;
    }

    size_t available = uart->sendBufferSize;
    size_t toReceive = (available < bufferLength) ? available : bufferLength;

    if (toReceive > 0) {
        memcpy(buffer, uart->sendBuffer, toReceive);

        memmove(uart->sendBuffer, uart->sendBuffer + toReceive, uart->sendBufferSize - toReceive);
        uart->sendBufferSize -= toReceive;
    }

    *receivedLength = toReceive;

    if (toReceive > 0) {
        printf("[UART] Received %zu bytes: ", toReceive);

        for (size_t i = 0; i < toReceive; i++) {
            printf("%02X ", buffer[i]);
        }
        
        printf("\n");
    }

    return COMM_SUCCESS;
}