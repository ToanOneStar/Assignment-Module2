#include "base-uart.h"
#include "compression.h"
#include "crc.h"
#include "encryption.h"
#include "logging.h"

int main() {
    printf("=== Embedded Communication Channel Decorator Pattern Demo ===\n\n");

    CommunicationChannel* uart = create_uart_channel();
    CommunicationChannel* withLogging = create_logging_decorator(uart);
    CommunicationChannel* withEncryption = create_encryption_decorator(withLogging, 0xAB);
    CommunicationChannel* withCompression = create_compression_decorator(withEncryption);
    CommunicationChannel* withCrc = create_crc_decorator(withCompression);

    uint8_t testData[] = {0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x04};
    size_t testDataLength = sizeof(testData);

    printf("Original test data (%zu bytes): ", testDataLength);

    for (size_t i = 0; i < testDataLength; i++) {
        printf("%02X ", testData[i]);
    }

    printf("\n\n");
    printf("=== SENDING DATA ===\n");

    int sendResult = withCrc->send(withCrc->instance, testData, testDataLength);

    printf("Send result: %d\n\n", sendResult);
    printf("=== RECEIVING DATA ===\n");

    uint8_t receiveBuffer[256];
    size_t receivedLength;
    int receiveResult = withCrc->receive(withCrc->instance, receiveBuffer, sizeof(receiveBuffer), &receivedLength);

    printf("Receive result: %d\n", receiveResult);

    if (receiveResult == COMM_SUCCESS && receivedLength > 0) {
        printf("Received data (%zu bytes): ", receivedLength);

        for (size_t i = 0; i < receivedLength; i++) {
            printf("%02X ", receiveBuffer[i]);
        }
        printf("\n");

        bool dataMatch = (receivedLength == testDataLength) && (memcmp(testData, receiveBuffer, testDataLength) == 0);
        printf("Data integrity check: %s\n", dataMatch ? "PASS" : "FAIL");
    }

    printf("\n=== Demo completed ===\n");
    return 0;
}