# Smart Home Notification System using Observer Pattern

## 📝 Mô tả dự án
Dự án này triển khai một hệ thống quản lý nhà thông minh sử dụng **Observer Pattern** để xử lý các sự kiện từ cảm biến và thông báo đến các thiết bị liên quan. Hệ thống cho phép các cảm biến (Publishers) thông báo sự kiện đến nhiều thiết bị điều khiển (Subscribers) mà không cần biết chi tiết cụ thể về các thiết bị đó.

### Bài toán giải quyết:
- **Phát hiện sự kiện**: Các cảm biến (cửa, chuyển động, khói, nhiệt độ) phát hiện và thông báo sự kiện
- **Phản ứng tự động**: Các thiết bị (ứng dụng mobile, hệ thống báo động, đèn, HVAC) tự động phản ứng với sự kiện
- **Tính linh hoạt**: Dễ dàng thêm/bớt cảm biến và thiết bị mà không cần thay đổi code hiện có
- **Tách rời**: Các thành phần không phụ thuộc chặt chẽ vào nhau

### Các yêu cầu đạt được:
✅ Loose Coupling: Publishers không cần biết chi tiết về Subscribers  
✅ Extensibility: Dễ dàng thêm sensors và subscribers mới  
✅ Dynamic Subscription: Có thể đăng ký/hủy đăng ký trong runtime  
✅ Event-driven Architecture: Hệ thống phản ứng theo sự kiện  

---
## 🧱 Cấu trúc Source Code

```
├── inc
│   ├── publisher.h
│   ├── sensors
│   │   ├── door-sensor.h
│   │   ├── motion-sensor.h
│   │   ├── smoke-sensor.h
│   │   └── temperature-sensor.h
│   ├── subscriber.h
│   └── subscribers
│       ├── alarm-system-controller.h
│       ├── hvac-system-controller.h
│       ├── light-system-controller.h
│       └── mobile-app-notifier.h
├── main.c
├── Makefile
├── README.md
└── src
    ├── publisher.c
    ├── sensors
    │   ├── door-sensor.c
    │   ├── motion-sensor.c
    │   ├── smoke-sensor.c
    │   └── temperature-sensor.c
    └── subscribers
        ├── alarm-system-controller.c
        ├── hvac-system-controller.c
        ├── light-system-controller.c
        └── mobile-app-notifier.c
```

---

## 🔌 Các API

### Publisher

```c
void subscribe(Publisher* self, Subscriber* s);
void unsubscribe(Publisher* self, Subscriber* s);
void notifySubscribers(Publisher* self, const char* eventInfo);
````

### Subscriber

```c
void (*update)(Subscriber* self, Publisher* context, const char* eventInfo);
```

### Cảm biến (Sensors – Publisher):

* `doorSensorTrigger(DoorSensor* sensor, int open);`
* `motionSensorTrigger(MotionSensor* sensor, int detected);`
* `smokeSensorTrigger(SmokeSensor* sensor, int detected);`
* `temperatureSensorTrigger(TemperatureSensor* sensor, int over);`

---

## 📦 Structs & Thành phần chính

### `Publisher`

> Đại diện cho cảm biến (sensor). Duy trì danh sách `subscribers` và cung cấp logic `subscribe`, `unsubscribe`, và `notifySubscribers`.

```c
typedef struct Publisher {
    Subscriber* subscribers[MAX_SUBSCRIBERS];
    int subscriberCount;
    void (*subscribe)(...);
    void (*unsubscribe)(...);
    void (*notifySubscribers)(...);
} Publisher;
```

### `Subscriber`

> Giao diện cho các thiết bị nhận thông báo.

```c
typedef struct Subscriber {
    void (*update)(...);
    void* data;
} Subscriber;
```

### Các struct cảm biến

```c
typedef struct {
    Publisher base;
    int isOpen;
} DoorSensor;
```

Tương tự cho: `MotionSensor`, `SmokeSensor`, `TemperatureSensor`.

### Các thiết bị nhận thông báo (Concrete Subscribers)

```c
typedef struct {
    Subscriber base;
} AlarmSystemController;
```

Tương tự cho: `MobileAppNotifier`, `LightSystemController`, `HvacSystemController`.

---

## 🧠 Giải thích giải pháp sử dụng

### ✅ Tách rời (Loose Coupling)

* Các cảm biến không cần biết về các thiết bị đích.
* Tăng khả năng **bảo trì** và **mở rộng** hệ thống.

### ✅ Linh hoạt

* Có thể dễ dàng **thêm** hoặc **loại bỏ** một thiết bị nhận thông báo tại runtime thông qua các hàm `subscribe()` và `unsubscribe()`.

### ✅ Dễ quản lý logic phản ứng

* Mỗi thiết bị xử lý logic phản ứng riêng biệt trong hàm `update()`.
* Giảm lặp lại code và dễ kiểm thử.

### ✅ Áp dụng rõ ràng Observer Pattern:

* `Publisher` đóng vai trò Subject
* `Subscriber` là giao diện chung
* Các thiết bị cụ thể như `AlarmSystemController`, `MobileAppNotifier` là các Concrete Subscribers.

---

## 🔧 Build & Run

```c
// Build
make
// Run
./smart_home
```

---

## ▶️ Kết quả

```c
== Simulate Door Open Event ==
[MobileApp] Alert: Door Opened
[AlarmSystem] Alarm: Door Opened

== Simulate Smoke Detected Event ==
[MobileApp] Alert: Smoke Detected
[AlarmSystem] Alarm: Smoke Detected
[HvacSystem] alert: Smoke Detected - HVAC System is opened
```

---