#include "network-monitor.h"

void network_collect_data(Monitor* self) {
    NetworkMonitor* net_monitor = (NetworkMonitor*)self;
    struct ifaddrs *ifaddrs_ptr, *ifa;

    net_monitor->data.interface_count = 0;

    if (getifaddrs(&ifaddrs_ptr) == 0) {
        for (ifa = ifaddrs_ptr; ifa != NULL && net_monitor->data.interface_count < MAX_INTERFACES; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr && (ifa->ifa_addr->sa_family == AF_INET)) {
                NetworkInterface* iface = &net_monitor->data.interfaces[net_monitor->data.interface_count];

                strncpy(iface->interface, ifa->ifa_name, sizeof(iface->interface) - 1);
                struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
                strncpy(iface->ip_address, inet_ntoa(addr->sin_addr), sizeof(iface->ip_address) - 1);

                FILE* fp = fopen("/proc/net/dev", "r");
                if (fp) {
                    char buffer[MAX_STRING_LEN];
                    while (fgets(buffer, sizeof(buffer), fp)) {
                        if (strstr(buffer, ifa->ifa_name)) {
                            sscanf(buffer,
                                   "%*s %lu %lu %*u %*u %*u %*u %*u %*u %lu %lu",
                                   &iface->bytes_recv,
                                   &iface->packets_recv,
                                   &iface->bytes_sent,
                                   &iface->packets_sent);

                            iface->download_speed = (rand() % 1000) / 10.0;
                            iface->upload_speed = (rand() % 500) / 10.0;
                            break;
                        }
                    }
                    fclose(fp);
                }
                net_monitor->data.interface_count++;
            }
        }
        freeifaddrs(ifaddrs_ptr);
    }

    FILE* fp = fopen("/proc/net/tcp", "r");

    if (fp) {
        char buffer[MAX_STRING_LEN];
        net_monitor->data.active_connections = 0;

        while (fgets(buffer, sizeof(buffer), fp)) {
            if (strstr(buffer, "01")) {
                net_monitor->data.active_connections++;
            }
        }
        fclose(fp);
    }

    net_monitor->data.total_bandwidth_usage = 0;
    for (int i = 0; i < net_monitor->data.interface_count; i++) {
        net_monitor->data.total_bandwidth_usage +=
            net_monitor->data.interfaces[i].download_speed + net_monitor->data.interfaces[i].upload_speed;
    }

    if (net_monitor->data.total_bandwidth_usage > net_monitor->bandwidth_threshold) {
        AlertData alert = {
            .level = ALERT_WARNING,
            .source = MONITOR_NETWORK,
            .timestamp = time(NULL),
        };
        snprintf(alert.message, sizeof(alert.message), "Over bandwidth network: %.2f", net_monitor->data.total_bandwidth_usage);
        self->subject->notify(self->subject, &alert);
    }
}

NetworkMonitor* create_network_monitor() {
    NetworkMonitor* net_monitor = (NetworkMonitor*)malloc(sizeof(NetworkMonitor));

    net_monitor->base.type = MONITOR_NETWORK;
    net_monitor->base.subject = create_subject();
    net_monitor->base.running = 0;
    net_monitor->base.collect_data = network_collect_data;
    net_monitor->base.start = monitor_start;
    net_monitor->base.stop = monitor_stop;
    net_monitor->bandwidth_threshold = 1000.0;

    return net_monitor;
}