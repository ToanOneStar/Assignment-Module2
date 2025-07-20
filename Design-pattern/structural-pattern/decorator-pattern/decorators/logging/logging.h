#ifndef LOGGING_H
#define LOGGING_H

#include "base-uart.h"

typedef struct {
    CommunicationChannel* baseChannel;
    FILE* logFile;
} LoggingDecorator;

CommunicationChannel* create_logging_decorator(CommunicationChannel* baseChannel);

int logging_send(void* instance, const uint8_t* data, size_t length);
int logging_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);

#endif // LOGGING_H