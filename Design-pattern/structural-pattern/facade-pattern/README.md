# Smart Home Facade Pattern

## 1. Mô tả dự án
Phần mềm bộ điều khiển trung tâm (Hub) cho hệ thống nhà thông minh, sử dụng Facade Pattern để đơn giản hóa giao diện điều khiển các hệ thống con: chiếu sáng, an ninh, điều hòa không khí (HVAC). Thay vì tầng ứng dụng phải thao tác trực tiếp với từng hệ thống con phức tạp, Facade cung cấp một API duy nhất, dễ sử dụng cho các kịch bản phổ biến như "Chào buổi sáng", "Ra khỏi nhà", "Xem phim".

## 2. Cấu trúc source code
```
facade-pattern/
├── main.c                  
├── Makefile                
├── hvac_system/            
│   ├── hvac_system.c
│   └── hvac_system.h
├── light_system/           
│   ├── light_system.c
│   └── light_system.h
├── sercurity_system/       
│   ├── sercurity_system.c
│   └── sercurity_system.h
├── smarthomeFacade/      
│   ├── smarthomeFacade.c  
│   └── smarthomeFacade.h  
```

## 3. Các API, struct, element chính
- **SmartHomeFacade:**
  - Cung cấp các hàm đơn giản hóa cho các kịch bản: activateMorningRoutine(), activateAwayMode(), setMovieNightScene(), ...
  - Ẩn chi tiết điều khiển các hệ thống con, chỉ expose API mức cao cho tầng ứng dụng.
- **LightSystem, SecuritySystem, HVACSystem:**
  - Mỗi module có API riêng để điều khiển (bật/tắt đèn, điều chỉnh độ sáng, kích hoạt báo động, điều chỉnh nhiệt độ, ...).
  - Được quản lý và sử dụng nội bộ bởi SmartHomeFacade.
- **main.c (Client):**
  - Khởi tạo SmartHomeFacade, gọi các hàm kịch bản mà không cần biết chi tiết các hệ thống con.

## 4. How to build & run
```bash
# Build project
make

# Chạy chương trình
./main
```

## 5. Kết quả mẫu
```
Kích hoạt kịch bản: Chào buổi sáng
- Đèn phòng ngủ sáng dần lên...
- Nhiệt độ phòng điều chỉnh về mức thoải mái...
- Hệ thống an ninh chuyển sang chế độ ban ngày...

Kích hoạt kịch bản: Ra khỏi nhà
- Tắt toàn bộ đèn...
- Kích hoạt báo động...
- Điều hòa chuyển sang chế độ tiết kiệm...
```

## 6. Mở rộng
- Dễ dàng thêm các kịch bản mới chỉ bằng cách bổ sung hàm vào SmartHomeFacade.
- Thay đổi, nâng cấp hệ thống con không ảnh hưởng đến tầng ứng dụng.
- Có thể mở rộng thêm các hệ thống con khác (ví dụ: rèm cửa, tưới cây tự động, ...).
