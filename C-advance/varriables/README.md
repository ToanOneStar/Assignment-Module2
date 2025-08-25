# Smart Plant Watering System (SPWS)

## 1. Mô tả dự án
Thiết kế hệ thống tưới cây tự động thông minh (SPWS) sử dụng C, mô phỏng hoạt động nhúng: đọc cảm biến, quyết định tưới nước dựa trên cấu hình, điều khiển bơm, LED trạng thái, xử lý nút nhấn và gửi thông báo trạng thái. Hệ thống hỗ trợ chuyển đổi giữa chế độ tự động và thủ công, đảm bảo hoạt động tối ưu và an toàn cho cây trồng.

## 2. Cấu trúc source code
```
varriables/
├── main.c                 
├── Makefile               
├── inc/
│   ├── actuators.h         
│   ├── buttons.h          
│   ├── config.h            
│   ├── sensors.h          
│   └── watering_logic.h    
├── src/
│   ├── actuators.c         
│   ├── buttons.c           
│   ├── sensors.c           
│   └── watering_logic.c    
```

## 3. Các API, struct, element chính
- **enum:**
  - Chế độ hệ thống: MODE_AUTO, MODE_MANUAL
  - Trạng thái bơm: PUMP_OFF, PUMP_ON
  - Trạng thái LED: LED_NORMAL, LED_WATERING, LED_LOW_MOISTURE_ALERT, LED_ERROR
- **struct SensorData:**
  - Lưu giá trị độ ẩm đất, nhiệt độ môi trường
- **struct SystemConfig:**
  - Ngưỡng độ ẩm, thời gian tưới tối đa, chu kỳ kiểm tra, chế độ hiện tại
## 4. How to build & run
```bash
# Build project
make

# Chạy chương trình mô phỏng
./smart-system
```

## 5. Kết quả kiểm thử mẫu
```
=== Smart Plant Watering System (SPWS) ===
Initializing system...

[SENSORS] Initializing sensors...
[SENSORS] Sensors initialized successfully
[ACTUATORS] Initializing actuators...
[ACTUATORS] Pump: OFF, LED: NORMAL
[ACTUATORS] Actuators initialized successfully
[BUTTONS] Initializing buttons...
[BUTTONS] Buttons initialized successfully
[LOGIC] Initializing watering logic...
[LOGIC] Watering logic initialized - Mode: AUTO
[SENSORS] Soil moisture: 97%, Temperature: 24 Degree C
[SYSTEM] Initialization complete

System ready! Starting main loop...
Press Ctrl+C to exit

[SENSORS] Soil moisture: 83%, Temperature: 26 Degree C

--- STATUS REPORT ---
Mode: AUTO
Soil Moisture: 83% (Min: 30%, Max: 70%)
Temperature: 26°C
Pump: OFF
LED Status: NORMAL
System Status: OK
--------------------

[SENSORS] Soil moisture: 37%, Temperature: 32 Degree C
[SENSORS] Soil moisture: 90%, Temperature: 35 Degree C
[SENSORS] Soil moisture: 41%, Temperature: 19 Degree C
[SENSORS] Soil moisture: 17%, Temperature: 33 Degree C
[LED] Status: ORANGE - Low moisture alert
[SENSORS] Soil moisture: 22%, Temperature: 28 Degree C

[DEMO] Simulating mode toggle button press...
[BUTTONS] Button 0 pressed
[SENSORS] Soil moisture: 59%, Temperature: 30 Degree C
[LED] Status: GREEN - System normal
[SENSORS] Soil moisture: 99%, Temperature: 22 Degree C
[SENSORS] Soil moisture: 15%, Temperature: 29 Degree C
[LED] Status: ORANGE - Low moisture alert
[SENSORS] Soil moisture: 7%, Temperature: 25 Degree C
[SENSORS] Soil moisture: 96%, Temperature: 29 Degree C
[LED] Status: GREEN - System normal

--- STATUS REPORT ---
Mode: AUTO
Soil Moisture: 96% (Min: 30%, Max: 70%)
Temperature: 29°C
Pump: OFF
LED Status: NORMAL
System Status: OK
--------------------
```

## 6. Giải thích giải pháp
- Sử dụng enum, struct để quản lý trạng thái, dữ liệu, cấu hình.
- Tách module rõ ràng: cảm biến, bơm/LED, nút nhấn, logic tưới nước.
- Dễ mở rộng, bảo trì, mô phỏng hoặc tích hợp phần cứng thực tế.
- Đảm bảo chuyển đổi mượt mà giữa các chế độ, xử lý an toàn các tình huống đặc biệt.
