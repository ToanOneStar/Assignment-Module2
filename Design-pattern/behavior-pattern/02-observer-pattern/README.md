# Smart Home Event Notification System

## Mô tả dự án

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

## Cấu trúc Source Code

```
02-observer-pattern/
├── inc/                           # Header files
│   ├── sensors/                   # Sensor headers (Publishers)
│   │   ├── door_sensor.h         
│   │   ├── motion_sensor.h       
│   │   ├── smoke_sensor.h        
│   │   └── temperature_sensor.h  
│   ├── subscribers/              # Subscriber headers
│   │   ├── publisher.h           
│   │   └── subscriber.h          
├── src/                          # Source files
│   ├── sensors/                  
│   │   ├── door_sensor.c
│   │   ├── motion_sensor.c
│   │   ├── smoke_sensor.c
│   │   └── temperature_sensor.c
│   ├── subscribers/              # Subscriber
│   │   ├── alarm_system_controller.c    
│   │   ├── hvac_system_controller.c     
│   │   ├── light_system_controller.c    
│   │   └── mobile_app_notifier.c       
│   ├── publisher.c               
│   └── main.c                   
├── obj/                          # Object files 
└── Makefile                      
```

## Các API, Struct và Element Chính

### 1. Publisher Interface (`publisher.h`)
```c
typedef struct Publisher {
    Subscriber* subscribers[MAX_SUBSCRIBERS]; 
    int subscriberCount;                       

    void (*subscribe)(struct Publisher* self, Subscriber* s);
    void (*unsubscribe)(struct Publisher* self, Subscriber* s);
    void (*notifySubscribers)(struct Publisher* self, const char* eventInfo);
} Publisher;

void publisherInit(Publisher* pub);
```

### 2. Subscriber Interface (`subscriber.h`)
```c
typedef struct Subscriber {
    void (*update)(struct Subscriber* self, Publisher* context, const char* eventInfo);
    void* data;  
} Subscriber;
```

### 3. Concrete Publishers (Sensors)

#### DoorSensor (`door_sensor.h`)
```c
typedef struct {
    Publisher base;
    int isOpen;
} DoorSensor;

void doorSensorInit(DoorSensor* sensor);
void doorSensorTrigger(DoorSensor* sensor, int open);
```

#### MotionSensor (`motion_sensor.h`)
```c
typedef struct {
    Publisher base;
    int motionDetected;
} MotionSensor;

void motionSensorInit(MotionSensor* sensor);
void motionSensorTrigger(MotionSensor* sensor, int detected);
```

#### SmokeSensor (`smoke_sensor.h`)
```c
typedef struct {
    Publisher base;
    int smokeDetected;
} SmokeSensor;

void smokeSensorInit(SmokeSensor* sensor);
void smokeSensorTrigger(SmokeSensor* sensor, int detected);
```

#### TemperatureSensor (`temperature_sensor.h`)
```c
typedef struct {
    Publisher base;
    int overTemperature;
} TemperatureSensor;

void temperatureSensorInit(TemperatureSensor* sensor);
void temperatureSensorTrigger(TemperatureSensor* sensor, int over);
```

### 4. Concrete Subscribers (Control Systems)

#### MobileAppNotifier
- **Chức năng**: Gửi thông báo đến ứng dụng mobile
- **Phản ứng**: Hiển thị alert cho tất cả sự kiện

#### AlarmSystemController
- **Chức năng**: Điều khiển hệ thống báo động
- **Phản ứng**: Kích hoạt báo động cho tất cả sự kiện

#### HVACSystemController
- **Chức năng**: Điều khiển hệ thống HVAC
- **Phản ứng**: Bật HVAC khi phát hiện khói hoặc nhiệt độ cao

#### LightSystemController
- **Chức năng**: Điều khiển hệ thống đèn
- **Phản ứng**: Bật đèn khi phát hiện chuyển động

## How to Build and Run

### Prerequisites
- GCC compiler
- Make utility
- Linux/Unix environment

### Build Instructions

1. **Clone hoặc download source code**
2. **Compile the project:**
   ```bash
   make
   ```
   
3. **Run the program:**
   ```bash
   ./smartHome
   ```

4. **Clean build files:**
   ```bash
   make clean
   ```

### Makefile Targets
- `make` hoặc `make all`: Compile toàn bộ project
- `make clean`: Xóa object files và executable
- `make $(TARGET)`: Build executable
- Object files được tạo trong thư mục `obj/`

### Sample Output
```
== Simulate Door Open Event ==
[MobileApp] Alert: Door Opened
[AlarmSystem] Alarm: Door Opened

== Simulate Smoke Detected Event ==
[MobileApp] Alert: Smoke Detected
[AlarmSystem] Alarm: Smoke Detected
[HVACSystem] alert: Smoke Detected - HAVC System is opend
```

## Luồng Hoạt Động Chi Tiết

### 1. Initialization Phase
```
Main → Initialize Sensors → Initialize Subscribers → Register Subscriptions
```

### 2. Event Detection Phase
```
Sensor detects event → Trigger function called → Update sensor state
```

### 3. Notification Phase
```
notifySubscribers() → Iterate through subscriber list → Call update() for each subscriber
```

### 4. Response Phase
```
Subscriber receives event → Execute specific action → Display/Control result
```

### 5. Subscription Management
```
Runtime: Can add/remove subscribers dynamically
subscribe() → Add to subscriber list
unsubscribe() → Remove from subscriber list
```

## Kết luận

Dự án này thể hiện việc áp dụng thành công **Observer Pattern** trong C để xây dựng hệ thống nhà thông minh. Hệ thống đảm bảo:

- **Tính mở rộng**: Dễ dàng thêm sensor và subscriber mới
- **Tính bảo trì**: Code rõ ràng, tách biệt các thành phần
- **Tính linh hoạt**: Có thể thay đổi behavior mà không ảnh hưởng toàn hệ thống
- **Hiệu suất**: Sử dụng function pointers cho polymorphism trong C

Hệ thống có thể được mở rộng để thêm nhiều loại sensor, subscriber và logic xử lý phức tạp hơn.