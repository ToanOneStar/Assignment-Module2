#include "crc.h"

CommunicationChannel* create_crc_decorator(CommunicationChannel* baseChannel) {
    CrcDecorator* decorator = (CrcDecorator*)malloc(sizeof(CrcDecorator));
    decorator->baseChannel = baseChannel;

    CommunicationChannel* channel = (CrcDecorator*)malloc(sizeof(CommunicationChannel));
    channel->send = crc_send;
    channel->receive = crc_receive;
    channel->instance = decorator;

    return channel;
}

uint8_t calculate_crc8(const uint8_t* data, size_t length) {
    uint8_t crc = 0xFF;

    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];

        for (int j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x07;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

int crc_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    CrcDecorator* decorator = (CrcDecorator*)instance;
    if (!decorator || !buffer || !receivedLength) {
        return COMM_ERROR_INVALID_PARAM;
    }

    uint8_t* tempBuffer = malloc(bufferLength + 1);
    size_t tempReceived;

    int result =
        decorator->baseChannel->receive(decorator->baseChannel->instance, tempBuffer, bufferLength + 1, &tempReceived);

    if (result == COMM_SUCCESS && tempReceived > 0) {
        if (tempReceived < 1) {
            free(tempBuffer);
            *receivedLength = 0;
            return COMM_SUCCESS;
        }

        size_t dataLength = tempReceived - 1;
        uint8_t receivedCrc = tempBuffer[dataLength];
        uint8_t calculatedCrc = calculate_crc8(tempBuffer, dataLength);

        printf("[CRC] Received CRC: %02X, Calculated: %02X\n", receivedCrc, calculatedCrc);

        if (receivedCrc != calculatedCrc) {
            free(tempBuffer);
            return COMM_ERROR_CRC_MISMATCH;
        }

        memcpy(buffer, tempBuffer, dataLength);
        *receivedLength = dataLength;
    } else {
        *receivedLength = 0;
    }

    free(tempBuffer);
    return result;
}

int crc_send(void* instance, const uint8_t* data, size_t length) {
    CrcDecorator* decorator = (CrcDecorator*)instance;
    if (!decorator || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    uint8_t* packet = malloc(length + 1);
    memcpy(packet, data, length);
    packet[length] = calculate_crc8(data, length);

    printf("[CRC] Added CRC: %02X\n", packet[length]);

    int result = decorator->baseChannel->send(decorator->baseChannel->instance, packet, length + 1);
    free(packet);

    return (result > 0) ? result - 1 : result;
}