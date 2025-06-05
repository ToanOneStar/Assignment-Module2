#ifndef MOBILE_APP_NOTIFIER_H
#define MOBILE_APP_NOTIFIER_H

#include "../subscriber.h"

typedef struct {
    Subscriber base;
} MobileAppNotifier;

void mobileAppNotifierInit(MobileAppNotifier* notifier);

#endif // MOBILE_APP_NOTIFIER_H
