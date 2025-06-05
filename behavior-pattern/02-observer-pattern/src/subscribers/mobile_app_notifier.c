#include "../../inc/subscribers/mobile_app_notifier.h"
#include <stdio.h>

// Update method for MobileAppNotifier
void mobileAppUpdate(Subscriber* self, Publisher* context, const char* eventInfo) {
    (void)self;
    (void)context;
    printf("[MobileApp] Alert: %s\n", eventInfo);
}

// Initialize MobileAppNotifier
void mobileAppNotifierInit(MobileAppNotifier* notifier) {
    notifier->base.update = mobileAppUpdate;
    notifier->base.data = NULL;
}
