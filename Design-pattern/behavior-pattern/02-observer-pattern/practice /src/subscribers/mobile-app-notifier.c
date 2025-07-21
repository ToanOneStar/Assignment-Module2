#include <stdio.h>
#include "mobile-app-notifier.h"

void mobileAppUpdate(Subscriber* self, Publisher* context, const char* eventInfo) {
    (void)self;
    (void)context;
    printf("[MobileApp] Alert: %s\n", eventInfo);
}

void mobileAppNotifierInit(MobileAppNotifier* notifier) {
    notifier->base.update = mobileAppUpdate;
    notifier->base.data = NULL;
}
