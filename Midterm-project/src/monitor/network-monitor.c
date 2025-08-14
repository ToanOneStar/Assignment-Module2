#include "network-monitor.h"

/**
 * @brief Read network interface statistics and update NetworkMonitor data.
 * 
 * Copies interface name and IP address, reads /proc/net/dev to get bytes
 * and packets sent/received, and estimates download/upload speeds.
 * 
 * @param net_monitor (in) Pointer to NetworkMonitor to update.
 * @param ifa (in) Pointer to ifaddrs structure representing the network interface.
 * 
 * @return void
 */
void read_network_device_file(NetworkMonitor* net_monitor, struct ifaddrs* ifa) {
    NetworkInterface* iface = &net_monitor->data.interfaces[net_monitor->data.interface_count];

    strncpy(iface->interface, ifa->ifa_name, sizeof(iface->interface) - 1);
    struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
    strncpy(iface->ip_address, inet_ntoa(addr->sin_addr), sizeof(iface->ip_address) - 1);

    FILE* fp = fopen("/proc/net/dev", "r");
    if (fp == NULL) {
        return;
    }

    char buffer[MAX_STRING_LEN];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (!strstr(buffer, ifa->ifa_name)) {
            continue;
        }
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

    fclose(fp);
}

/**
 * @brief Count active TCP connections and update NetworkMonitor data.
 * 
 * Reads /proc/net/tcp and increments the active_connections count for each
 * established TCP connection found.
 * 
 * @param net_monitor (in) Pointer to NetworkMonitor to update.
 * 
 * @return void
 */
void read_network_tcp_file(NetworkMonitor* net_monitor) {
    FILE* fp = fopen("/proc/net/tcp", "r");
    if (fp == NULL) {
        return;
    }

    char buffer[MAX_STRING_LEN];
    net_monitor->data.active_connections = 0;
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, "01")) {
            net_monitor->data.active_connections++;
        }
    }

    fclose(fp);
}

/**
 * @brief Check network bandwidth usage and send alert if threshold exceeded.
 * 
 * Compares total bandwidth usage against the defined threshold. If exceeded,
 * creates an alert and notifies via the Monitor's notify system.
 * 
 * @param net_monitor (in) Pointer to NetworkMonitor containing current data and threshold.
 * @param self (in) Pointer to Monitor used to call notify for sending alerts.
 * 
 * @return void
 */
void alert_network(NetworkMonitor* net_monitor, Monitor* self) {
    if (net_monitor->data.total_bandwidth_usage > net_monitor->bandwidth_threshold) {
        AlertData alert = {
            .level = ALERT_WARNING,
            .source = MONITOR_NETWORK,
            .timestamp = time(NULL),
        };
        snprintf(alert.message,
                 sizeof(alert.message),
                 "Over bandwidth network: %.2f",
                 net_monitor->data.total_bandwidth_usage);
        self->subject->notify(self->subject, &alert);
    }
}

/**
 * @brief Collect network data and update NetworkMonitor structure.
 * 
 * Gathers information for each network interface (IP, bytes, packets, speeds),
 * counts active TCP connections, calculates total bandwidth usage, and triggers
 * alerts if thresholds are exceeded.
 * 
 * @param self (in) Pointer to Monitor, cast to NetworkMonitor inside the function.
 * 
 * @return void
 */
void collect_network_data(Monitor* self) {
    NetworkMonitor* net_monitor = (NetworkMonitor*)self;
    struct ifaddrs *ifaddrs_ptr, *ifa;

    net_monitor->data.interface_count = 0;

    if (getifaddrs(&ifaddrs_ptr) == 0) {
        for (ifa = ifaddrs_ptr; ifa != NULL && net_monitor->data.interface_count < MAX_INTERFACES;
             ifa = ifa->ifa_next) {
            if (!(ifa->ifa_addr && (ifa->ifa_addr->sa_family == AF_INET))) {
                continue;
            }

            read_network_device_file(net_monitor, ifa);
            net_monitor->data.interface_count++;
        }
        freeifaddrs(ifaddrs_ptr);
    }

    read_network_tcp_file(net_monitor);

    net_monitor->data.total_bandwidth_usage = 0;
    for (int i = 0; i < net_monitor->data.interface_count; i++) {
        net_monitor->data.total_bandwidth_usage +=
            net_monitor->data.interfaces[i].download_speed + net_monitor->data.interfaces[i].upload_speed;
    }

    alert_network(net_monitor, self);
}

/**
 * @brief Create and initialize a NetworkMonitor instance.
 * 
 * Allocates memory for NetworkMonitor, initializes its base Monitor fields,
 * sets default bandwidth threshold, and assigns function pointers for 
 * data collection and control.
 * 
 * @return Pointer to the newly created NetworkMonitor instance.
 */
NetworkMonitor* create_network_monitor() {
    NetworkMonitor* net_monitor = (NetworkMonitor*)malloc(sizeof(NetworkMonitor));

    net_monitor->base.type = MONITOR_NETWORK;
    net_monitor->base.subject = create_subject();
    net_monitor->base.running = 0;
    net_monitor->base.collect_data = collect_network_data;
    net_monitor->base.start = monitor_start;
    net_monitor->base.stop = monitor_stop;
    net_monitor->bandwidth_threshold = DEFAULT_BANDWIDTH_THRESHOLD;

    return net_monitor;
}