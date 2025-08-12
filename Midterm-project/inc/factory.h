#ifndef FACTORY_H
#define FACTORY_H

#include "monitor.h"

typedef struct {
    Monitor* (*create_monitor)(MonitorType type);
} MonitorFactory;

Monitor* create_monitor(MonitorType type);
extern MonitorFactory factory;

#endif // FACTORY_H