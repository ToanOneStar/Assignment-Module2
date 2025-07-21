#include <stdio.h>
#include "alarm-system-controller.h"
#include "door-sensor.h"
#include "hvac-system-controller.h"
#include "light-system-controller.h"
#include "mobile-app-notifier.h"
#include "motion-sensor.h"
#include "smoke-sensor.h"
#include "temperature-sensor.h"

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

    HvacSystemController hvacSystem;
    hvacSystemControllerInit(&hvacSystem);

    LightSystemController lightSystem;
    lightSystemControllerInit(&lightSystem);

    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&mobileApp);
    doorSensor.base.subscribe(&doorSensor.base, (Subscriber*)&alarmSystem);

    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&mobileApp);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&alarmSystem);
    smokeSensor.base.subscribe(&smokeSensor.base, (Subscriber*)&hvacSystem);

    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&mobileApp);
    motionSensor.base.subscribe(&motionSensor.base, (Subscriber*)&lightSystem);

    tempSensor.base.subscribe(&tempSensor.base, (Subscriber*)&mobileApp);
    tempSensor.base.subscribe(&tempSensor.base, (Subscriber*)&hvacSystem);

    printf("== Simulate Door Open Event ==\n");
    doorSensorTrigger(&doorSensor, 1);

    printf("\n== Simulate Smoke Detected Event ==\n");
    smokeSensorTrigger(&smokeSensor, 1);

    return 0;
}
