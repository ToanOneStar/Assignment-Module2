#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "../../base-uart/base_uart.h"

typedef struct {
    CommunicationChannel* baseChannel;
    uint8_t key;
} EncryptionDecorator;

CommunicationChannel* create_encryption_decorator(CommunicationChannel* baseChannel, uint8_t key);

int encryption_send(void* instance, const uint8_t* data, size_t length);
int encryption_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);

#endif