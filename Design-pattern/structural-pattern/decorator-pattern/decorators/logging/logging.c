#include "logging.h"
#include <time.h>

int logging_send(void* instance, const uint8_t* data, size_t length) {
    LoggingDecorator* decorator = (LoggingDecorator*)instance;
    if (!decorator || !data || length == 0) {
        return COMM_ERROR_INVALID_PARAM;
    }

    time_t now = time(NULL);
    char* timeStr = ctime(&now);
    timeStr[strlen(timeStr) - 1] = '\0'; 

    printf("[LOG] %s - SEND: %zu bytes - Data: ", timeStr, length);
    for (size_t i = 0; i < (length < 8 ? length : 8); i++) { 
        printf("%02X ", data[i]);
    }
    if (length > 8) {
        printf("...");
    }
    printf("\n");

    return decorator->baseChannel->send(decorator->baseChannel->instance, data, length);
}

int logging_receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength) {
    LoggingDecorator* decorator = (LoggingDecorator*)instance;
    if (!decorator || !buffer || !receivedLength) {
        return COMM_ERROR_INVALID_PARAM;
    }

    int result =
        decorator->baseChannel->receive(decorator->baseChannel->instance, buffer, bufferLength, receivedLength);

    if (result == COMM_SUCCESS && *receivedLength > 0) {
        time_t now = time(NULL);
        char* timeStr = ctime(&now);
        timeStr[strlen(timeStr) - 1] = '\0'; 

        printf("[LOG] %s - RECEIVE: %zu bytes - Data: ", timeStr, *receivedLength);
        for (size_t i = 0; i < (*receivedLength < 8 ? *receivedLength : 8); i++) {
            printf("%02X ", buffer[i]);
        }
        if (*receivedLength > 8) {
            printf("...");
        }
        printf("\n");
    }

    return result;
}

CommunicationChannel* create_logging_decorator(CommunicationChannel* baseChannel) {
    LoggingDecorator* decorator = malloc(sizeof(LoggingDecorator));
    decorator->baseChannel = baseChannel;
    decorator->logFile = NULL; 

    CommunicationChannel* channel = malloc(sizeof(CommunicationChannel));
    channel->send = logging_send;
    channel->receive = logging_receive;
    channel->instance = decorator;

    return channel;
}