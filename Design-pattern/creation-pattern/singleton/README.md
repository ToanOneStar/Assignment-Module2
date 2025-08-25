# Singleton Pattern - SensorManager

## 1. Mô tả dự án
Bài toán: Trong hệ thống quản lý dữ liệu cảm biến, chỉ được phép tồn tại một thể hiện duy nhất của đối tượng SensorManager. SensorManager chịu trách nhiệm quản lý, thu thập dữ liệu từ các cảm biến (SensorNode) và đưa dữ liệu lên cơ sở dữ liệu một cách hiệu quả, nhất quán.

Nếu không đảm bảo chỉ có một SensorManager duy nhất:
- Dữ liệu bị trùng lặp do nhiều SensorManager cùng thu thập và lưu trữ dữ liệu.
- Xung đột tài nguyên khi nhiều SensorManager thao tác trên tài nguyên chung.
- Khó kiểm soát, giảm tính ổn định và bảo trì hệ thống.

Giải pháp: Sử dụng Singleton Pattern để đảm bảo chỉ có một thể hiện SensorManager tồn tại trong toàn bộ hệ thống.

## 2. Cấu trúc source code
```
singleton/
├── main.c                
├── Makefile             
```

## 3. Các API, struct, element chính
- **SensorManager (struct):**
  - Quản lý thông tin node cảm biến, phương thức thu thập dữ liệu, trạng thái kết nối database, tên manager.
- **createSensorManager(...):**
  - Tạo mới SensorManager nếu chưa tồn tại, trả về con trỏ đến instance duy nhất.
  - Nếu đã tồn tại, trả về NULL và in thông báo lỗi.
- **deleteSensorManager():**
  - Giải phóng bộ nhớ và xóa instance SensorManager.
- **getNodeManagerString(...), getDataCollectionMethodString(...):**
  - Trả về chuỗi mô tả cho các enum.

## 4. How to build & run
```bash
# Build project
make

# Chạy chương trình
./main
```

## 5. Kết quả mẫu
```
Sensor manager created
Name: manager1
Node: Temperature Node
Data Collection Method: Real-time
Database Status: Connected
Error: Sensor manager existed! Can't create another one
failed to create manager 2
Sensor manager was deleted
```

## 6. Giải thích giải pháp Singleton
- Chỉ cho phép tạo một instance SensorManager duy nhất trong toàn bộ chương trình.
- Nếu cố gắng tạo thêm, hàm createSensorManager sẽ trả về NULL và cảnh báo.
- Đảm bảo dữ liệu không bị trùng lặp, tránh xung đột tài nguyên, dễ kiểm soát và bảo trì hệ thống.
