#include "encryption.h"

CommunicationChannel* create_encryption_decorator(CommunicationChannel* baseChannel, uint8_t key) {
    EncryptionDecorator* decorator = malloc(sizeof(EncryptionDecorator));
    decorator->baseChannel = baseChannel;
    decorator->key = key;

    CommunicationChannel* channel = malloc(sizeof(CommunicationChannel));
    channel->send = encryption_send;
    channel->receive = encryption_receive;
    channel->instance = decorator;

    return channel;
}

int encryption_send(void* instance, const uint8_t* data, size_t length) {
    EncryptionDecorator* decorator = (EncryptionDecorator*)instance;
    if (!decorator || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    uint8_t* encrypted = malloc(length);
    for (size_t i = 0; i < length; i++) {
        encrypted[i] = data[i] ^ decorator->key;
    }

    printf("[ENCRYPTION] Applied XOR with key: %02X\n", decorator->key);

    int result = decorator->baseChannel->send(decorator->baseChannel->instance, encrypted, length);
    free(encrypted);

    return result;
}

int encryption_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    EncryptionDecorator* decorator = (EncryptionDecorator*)instance;
    if (!decorator || !buffer || !receivedLength) {
        return COMM_ERROR_INVALID_PARAM;
    }

    int result =
        decorator->baseChannel->receive(decorator->baseChannel->instance, buffer, bufferLength, receivedLength);

    if (result == COMM_SUCCESS && *receivedLength > 0) {
        for (size_t i = 0; i < *receivedLength; i++) {
            buffer[i] = buffer[i] ^ decorator->key;
        }
        printf("[ENCRYPTION] Applied XOR decryption with key: %02X\n", decorator->key);
    }

    return result;
}