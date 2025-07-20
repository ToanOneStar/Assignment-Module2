#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "base-uart.h"

typedef struct {
    CommunicationChannel* baseChannel;
} CompressionDecorator;

CommunicationChannel* create_compression_decorator(CommunicationChannel* baseChannel);

size_t rle_compress(const uint8_t* input, size_t inputLength, uint8_t* output, size_t outputBufferSize);
size_t rle_decompress(const uint8_t* input, size_t inputLength, uint8_t* output, size_t outputBufferSize);
int compression_send(void* instance, const uint8_t* data, size_t length);
int compression_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);

#endif // COMPRESSION_H