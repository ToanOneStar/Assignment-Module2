#ifndef CRC_H
#define CRC_H

#include "base-uart.h"

typedef struct {
    CommunicationChannel* baseChannel;
} CrcDecorator;

CommunicationChannel* create_crc_decorator(CommunicationChannel* baseChannel);

uint8_t calculate_crc8(const uint8_t* data, size_t length);
int crc_send(void* instance, const uint8_t* data, size_t length);
int crc_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);

#endif // CRC_H