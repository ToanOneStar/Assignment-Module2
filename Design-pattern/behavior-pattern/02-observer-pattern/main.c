#include "inc/sensors/door_sensor.h"
#include "inc/sensors/motion_sensor.h"
#include "inc/sensors/smoke_sensor.h"
#include "inc/sensors/temperature_sensor.h"
#include "inc/subscribers/alarm_system_controller.h"
#include "inc/subscribers/hvac_system_controller.h"
#include "inc/subscribers/light_system_controller.h"
#include "inc/subscribers/mobile_app_notifier.h"

#include <stdio.h>

int main() {
    DoorSensor doorSensor;
    doorSensorInit(&doorSensor);

    SmokeSensor smokeSensor;
    smokeSensorInit(&smokeSensor);

    TemperatureSensor tempSensor;
    temperatureSensorInit(&tempSensor);

    MotionSensor motionSensor;
    motionSensorInit(&motionSensor);

    MobileAppNotifier mobileApp;
    mobileAppNotifierInit(&mobileApp);

    AlarmSystemController alarmSystem;
    alarmSystemControllerInit(&alarmSystem);

    HAVCSystemController havcSystem;
    hvacSystemControllerInit(&havcSystem);

    LightSystemController lightSystem;
    lightSystemControllerInit(&lightSystem);

    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&mobileApp);
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&alarmSystem);

    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&mobileApp);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&alarmSystem);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&havcSystem);

    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&mobileApp);
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&lightSystem);

    tempSensor.base.subscribe(&tempSensor.base, (Subscriber*)&mobileApp);
    tempSensor.base.subscribe(&tempSensor.base, (Subscriber*)&havcSystem);

    printf("== Simulate Door Open Event ==\n");
    doorSensorTrigger(&doorSensor, 1);

    printf("\n== Simulate Smoke Detected Event ==\n");
    smokeSensorTrigger(&smokeSensor, 1);

    return 0;
}
