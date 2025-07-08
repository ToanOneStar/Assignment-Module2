#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_NAME_SENSOR_MANAGER 20

#define DISCONNECTED_DATABASE       0
#define CONNECTED_DATABASE          1

typedef enum {
    NODE_TEMP,
    NODE_HUMID,
    NODE_LIGHT,
} NodeManager;

typedef enum {
    REAL_TIME,
    PREODIC,
} DataCollectionMethod;

typedef struct {
    NodeManager currentNode;
    DataCollectionMethod dataCollectionMethod;
    char nameSensorManager[SIZE_OF_NAME_SENSOR_MANAGER];
    int statusConnectDatabase;
} SensorManager;

static SensorManager* sensorManager = NULL;

SensorManager* createSensorManager(const char* nameSensorManager, NodeManager currentNode,
                                   DataCollectionMethod dataCollectionMethod, int statusConnectionDatabase) {
    if (sensorManager != NULL) {
        printf("Error: Sensor manager existed! Can't create another one\n");
        return NULL;
    }

    sensorManager = (SensorManager*)malloc(sizeof(SensorManager));
    if (sensorManager != NULL) {
        snprintf(sensorManager->nameSensorManager, sizeof(sensorManager->nameSensorManager), "%s", nameSensorManager);
        sensorManager->currentNode = currentNode;
        sensorManager->dataCollectionMethod = dataCollectionMethod;
        sensorManager->statusConnectDatabase = statusConnectionDatabase;
    }

    return sensorManager;
}

void deleteSensorManager() {
    if (sensorManager != NULL) {
        free(sensorManager);
        sensorManager = NULL;
    }
}

const char* getNodeManagerString(NodeManager node) {
    switch (node) {
        case NODE_TEMP: return "Temperature Node";
        case NODE_HUMID: return "Humidity Node";
        case NODE_LIGHT: return "Light Node";
        default: return "Unknown Node";
    }
}

const char* getDataCollectionMethodString(DataCollectionMethod method) {
    switch (method) {
        case REAL_TIME: return "Real-time";
        case PREODIC: return "Periodic";
        default: return "Unknown Method";
    }
}

int main() {
    SensorManager* manager1 = createSensorManager("manager1", NODE_TEMP, REAL_TIME, CONNECTED_DATABASE);
    if (manager1 != NULL) {
        printf("Sensor manager created\n");
        printf("Name: %s\n", sensorManager->nameSensorManager);
        printf("Node: %s\n", getNodeManagerString(manager1->currentNode));
        printf("Data Collection Method: %s\n", getDataCollectionMethodString(manager1->dataCollectionMethod));
        printf("Database Status: %s\n",
               manager1->statusConnectDatabase == CONNECTED_DATABASE ? "Connected" : "Disconnected");
    }

    SensorManager* manager2 = createSensorManager("manager2", NODE_HUMID, PREODIC, DISCONNECTED_DATABASE);
    if (manager2 == NULL) {
        printf("failed to create manager 2\n");
    }

    deleteSensorManager();
    printf("Sensor manager was deleted\n");

    return 0;
}