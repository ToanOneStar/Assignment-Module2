#include "inc/sensors/door_sensor.h"
#include "inc/sensors/motion_sensor.h"
#include "inc/sensors/smoke_sensor.h"
#include "inc/sensors/temperature_sensor.h"
#include "inc/subscribers/HVAC_system_controller.h"
#include "inc/subscribers/alarm_system_controller.h"
#include "inc/subscribers/light_system_controller.h"
#include "inc/subscribers/mobile_app_notifier.h"

#include <stdio.h>

int main() {
    // Initialize sensors (publishers)
    DoorSensor doorSensor;
    doorSensorInit(&doorSensor);

    SmokeSensor smokeSensor;
    smokeSensorInit(&smokeSensor);

    TemperatureSensor tempSensor;
    temperatureSensorInit(&tempSensor);

    MotionSensor motionSensor;
    motionSensorInit(&motionSensor);

    // Initialize subscribers
    MobileAppNotifier mobileApp;
    mobileAppNotifierInit(&mobileApp);

    AlarmSystemController alarmSystem;
    alarmSystemControllerInit(&alarmSystem);

    HAVCSystemController havcSystem;
    hvacSystemControllerInit(&havcSystem);

    LightSystemController lightSystem;
    lightSystemControllerInit(&lightSystem);

    // Register subscribers to door sensor (publisher)
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&mobileApp);
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&alarmSystem);

    // Register subscribers to smoke sensor (publisher)
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&mobileApp);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&alarmSystem);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&havcSystem);

    // Register subscribers to motion sensor (publisher)
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&mobileApp);
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&lightSystem);

    // Register subscribers to temperature sensor (publisher)
    tempSensor.base.subscribe(&tempSensor.base, (Subscriber*)&mobileApp);
    tempSensor.base.subscribe(&tempSensor.base, (Subscriber*)&havcSystem);

    // Simulate events
    printf("== Simulate Door Open Event ==\n");
    doorSensorTrigger(&doorSensor, 1);

    printf("\n== Simulate Smoke Detected Event ==\n");
    smokeSensorTrigger(&smokeSensor, 1);

    return 0;
}
