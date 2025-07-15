#include "compression.h"

size_t rle_compress(const uint8_t* input, size_t inputLength, uint8_t* output, size_t outputBufferSize) {
    if (inputLength == 0) {
        return 0;
    }

    size_t outputIndex = 0;
    size_t i = 0;

    while (i < inputLength && outputIndex < outputBufferSize - 1) {
        uint8_t currentByte = input[i];
        uint8_t count = 1;

        while (i + count < inputLength && input[i + count] == currentByte && count < 255) {
            count++;
        }

        if (outputIndex + 2 <= outputBufferSize) {
            output[outputIndex++] = count;
            output[outputIndex++] = currentByte;
        } else {
            break;
        }

        i += count;
    }

    return outputIndex;
}

size_t rle_decompress(const uint8_t* input, size_t inputLength, uint8_t* output, size_t outputBufferSize) {
    size_t outputIndex = 0;
    size_t i = 0;

    while (i < inputLength - 1 && outputIndex < outputBufferSize) {
        uint8_t count = input[i++];
        uint8_t value = input[i++];

        for (uint8_t j = 0; j < count && outputIndex < outputBufferSize; j++) {
            output[outputIndex++] = value;
        }
    }

    return outputIndex;
}

int compression_send(void* instance, const uint8_t* data, size_t length) {
    CompressionDecorator* decorator = (CompressionDecorator*)instance;
    if (!decorator || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    uint8_t* compressed = malloc(length * 2); 
    size_t compressedLength = rle_compress(data, length, compressed, length * 2);

    printf("[COMPRESSION] Original: %zu bytes, Compressed: %zu bytes\n", length, compressedLength);

    int result = decorator->baseChannel->send(decorator->baseChannel->instance, compressed, compressedLength);
    free(compressed);

    return (result > 0) ? (int)length : result; 
}

int compression_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    CompressionDecorator* decorator = (CompressionDecorator*)instance;
    if (!decorator || !buffer || !receivedLength) {
        return COMM_ERROR_INVALID_PARAM;
    }

    uint8_t* compressedBuffer = malloc(bufferLength * 2);
    size_t compressedReceived;

    int result = decorator->baseChannel->receive(decorator->baseChannel->instance,
                                                 compressedBuffer,
                                                 bufferLength * 2,
                                                 &compressedReceived);

    if (result == COMM_SUCCESS && compressedReceived > 0) {
        size_t decompressedLength = rle_decompress(compressedBuffer, compressedReceived, buffer, bufferLength);
        *receivedLength = decompressedLength;
        printf("[COMPRESSION] Compressed: %zu bytes, Decompressed: %zu bytes\n",
               compressedReceived,
               decompressedLength);
    } else {
        *receivedLength = 0;
    }

    free(compressedBuffer);
    return result;
}

CommunicationChannel* create_compression_decorator(CommunicationChannel* baseChannel) {
    CompressionDecorator* decorator = malloc(sizeof(CompressionDecorator));
    decorator->baseChannel = baseChannel;

    CommunicationChannel* channel = malloc(sizeof(CommunicationChannel));
    channel->send = compression_send;
    channel->receive = compression_receive;
    channel->instance = decorator;

    return channel;
}