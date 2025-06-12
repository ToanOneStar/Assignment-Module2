#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_NAME_SENSOR_MANAGER 20

/*status connect with database*/
#define DISCONNECTED_DATABASE       0
#define CONNECTED_DATABASE          1

/*define enum for modes of sensor manager*/
typedef enum {
    NODE_TEMP,
    NODE_HUMID,
    NODE_LIGHT,
} NodeManager;

/*define enum for methods collect data*/
typedef enum {
    REAL_TIME,
    PREODIC,
} DataCollectionMethod;

/*Define SensorManager structure*/
typedef struct {
    NodeManager currentNode;
    DataCollectionMethod dataCollectionMethod;
    char nameSensorManager[SIZE_OF_NAME_SENSOR_MANAGER];
    int statusConnectDatabase;
} SensorManager;

/*static variable to store the unique instance of SensorManager*/
static SensorManager* sensorManager = NULL;

/*function to create SensorManager instance*/
SensorManager* createSensorManager(const char* nameSensorManager, NodeManager currentNode,
                                   DataCollectionMethod dataCollectionMethod, int statusConnectionDatabase) {
    if (sensorManager != NULL) {
        printf("Error: Sensor manager existed! Can't create another one\n");
        return NULL;
    }

    /*create sensor manager if it does not already exist*/
    sensorManager = (SensorManager*)malloc(sizeof(SensorManager));
    if (sensorManager != NULL) {
        snprintf(sensorManager->nameSensorManager, sizeof(sensorManager->nameSensorManager), "%s", nameSensorManager);
        sensorManager->currentNode = currentNode;
        sensorManager->dataCollectionMethod = dataCollectionMethod;
        sensorManager->statusConnectDatabase = statusConnectionDatabase;
    }
    return sensorManager;
}

/*function to delete the sensormanager instance*/
void deleteSensorManager() {
    if (sensorManager != NULL) {
        free(sensorManager);
        sensorManager = NULL;
    }
}

/*function to get the string representation of NodeManager*/
const char* getNodeManagerString(NodeManager node) {
    switch (node) {
        case NODE_TEMP: return "Temperature Node";
        case NODE_HUMID: return "Humidity Node";
        case NODE_LIGHT: return "Light Node";
        default: return "Unknown Node";
    }
}

/*function to get the string representation of DataCollectionMethod*/
const char* getDataCollectionMethodString(DataCollectionMethod method) {
    switch (method) {
        case REAL_TIME: return "Real-time";
        case PREODIC: return "Periodic";
        default: return "Unknown Method";
    }
}

int main() {
    /*create sensor manager*/
    SensorManager* manager1 = createSensorManager("manager1", NODE_TEMP, REAL_TIME, CONNECTED_DATABASE);
    if (manager1 != NULL) {
        printf("Sensor manager created\n");
        printf("Name: %s\n", sensorManager->nameSensorManager);
        printf("Node: %s\n", getNodeManagerString(manager1->currentNode));
        printf("Data Collection Method: %s\n", getDataCollectionMethodString(manager1->dataCollectionMethod));
        printf("Database Status: %s\n",
               manager1->statusConnectDatabase == CONNECTED_DATABASE ? "Connected" : "Disconnected");
    }

    /*try to create a second sensor manager*/
    SensorManager* manager2 = createSensorManager("manager2", NODE_HUMID, PREODIC, DISCONNECTED_DATABASE);
    if (manager2 == NULL) {
        printf("failed to create manager 2\n");
    }

    deleteSensorManager();
    printf("Sensor manager was deleted\n");

    return 0;
}