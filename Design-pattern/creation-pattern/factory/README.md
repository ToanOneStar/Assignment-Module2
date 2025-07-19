# Factory Pattern - Sensor System

## 1. Mô tả dự án
Bài toán: Phát triển hệ thống nhúng giao tiếp với nhiều loại cảm biến (nhiệt độ, độ ẩm, áp suất, ánh sáng, ...). Ban đầu chỉ có cảm biến nhiệt độ, nhưng cần mở rộng để tích hợp thêm các loại cảm biến mới mà không phải sửa đổi mã nguồn cũ, đảm bảo tuân thủ nguyên tắc Open/Closed Principle (OCP).

Nếu không áp dụng OCP:
- Mỗi lần thêm cảm biến mới phải sửa nhiều nơi trong mã nguồn, dễ gây lỗi.
- Tăng độ phức tạp, giảm khả năng bảo trì và mở rộng.

Giải pháp: Sử dụng Factory Pattern để tạo ra các đối tượng cảm biến thông qua một interface chung. Khi cần thêm cảm biến mới, chỉ cần mở rộng (thêm class/concrete struct mới và cập nhật factory), không cần sửa mã nguồn cũ.

## 2. Cấu trúc source code
```
factory/
├── main.c                       
├── Makefile                     
├── factory/
│   ├── sensor_factory.c         
│   ├── sensor_factory.h          
│   ├── sensor.h                  
├── temperature/
│   ├── temperature-sensor.c      
│   └── temperature-sensor.h
├── humidity/
│   ├── humidity-sensor.c       
│   └── humidity-sensor.h
├── pressure/
│   ├── pressure-sensor.c        
│   └── pressure-sensor.h
├── light/
│   ├── light-sensor.c           
│   └── light-sensor.h
```

## 3. Các API, struct, element chính
- **Sensor (interface/struct):**
  - Định nghĩa các hàm chung cho cảm biến: init(), readData(), ...
- **SensorFactory:**
  - Hàm createSensor(type) trả về con trỏ đến đối tượng Sensor phù hợp (nhiệt độ, độ ẩm, ...).
  - Dễ dàng mở rộng thêm loại cảm biến mới chỉ bằng cách bổ sung implementation và cập nhật factory.
- **Các cảm biến cụ thể (TemperatureSensor, HumiditySensor, ...):**
  - Triển khai interface Sensor, định nghĩa hành vi riêng cho từng loại cảm biến.
- **main.c (Client):**
  - Sử dụng SensorFactory để tạo và thao tác với các cảm biến mà không cần biết chi tiết từng loại cảm biến.

## 4. How to build & run
```bash
# Build project
make

# Chạy chương trình
./factory_demo
```

## 5. Kết quả mẫu
```
Temperature sensor initialized.
Temperature: 25.50°C
Humidity sensor initialized.
Humidity: 60.00%
Light sensor initialized.
Light Intensity: 300.00 lux
Pressure sensor initialized.
Pressure: 20.00 atm
```

## 6. Giải thích giải pháp Factory & OCP
- Khi cần thêm cảm biến mới, chỉ cần tạo file .c/.h cho cảm biến đó và cập nhật factory.
- Không cần sửa đổi mã nguồn cũ, giảm nguy cơ lỗi, tăng khả năng mở rộng và bảo trì.
- Tầng ứng dụng chỉ làm việc với interface Sensor, không phụ thuộc vào chi tiết từng loại cảm biến.
