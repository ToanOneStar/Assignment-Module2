
# Smart Home Controller using Facade Pattern

## 📌 Mô tả dự án

Dự án này mô phỏng một **bộ điều khiển trung tâm (Hub)** của hệ thống nhà thông minh, quản lý các hệ thống con như:

- 💡 **Chiếu sáng (Lighting system)**
- 🛡️ **An ninh (Security system)**
- 🌬️ **Điều hòa không khí (HVAC system)**

Mỗi hệ thống con có API riêng biệt, nhưng để điều khiển toàn bộ nhà, cần phối hợp nhiều hệ thống cùng lúc (ví dụ: "Chào buổi sáng", "Ra khỏi nhà"). Việc gọi từng API riêng sẽ phức tạp, rối rắm và dễ lỗi.

Giải pháp được áp dụng là **Facade Pattern**, giúp:

- ✅ Đơn giản hóa giao diện điều khiển.
- ✅ Tách tầng ứng dụng khỏi chi tiết hệ thống con (giảm phụ thuộc).
- ✅ Dễ mở rộng và bảo trì.
---

## 📂 Cấu trúc source code

```
facade-pattern/
├── hvac-system
│   ├── hvac-system.c
│   └── hvac-system.h
├── light-system
│   ├── light-system.c
│   └── light-system.h
├── sercurity-system
│   ├── sercurity-system.c
│   └── sercurity-system.h
└── smart-home-facade
|   ├── smart-home.c
|   └── smart-home.h
├── main.c
├── Makefile
├── README.md
```
---

## 🧩 Các API chính

```c
// smart-home.h
SmartHomeFacade* createSmartHomeFacade(void);

void activateMorningRoutine(SmartHomeFacade* facade);
void activateAwayMode(SmartHomeFacade* facade);
void setMovieNightScene(SmartHomeFacade* facade);
```

---

## 🏗️ Struct và thành phần chính

### `SmartHomeFacade`

Lớp facade tổng hợp 3 hệ thống con:

```c
typedef struct SmartHomeFacade {
    LightSystem* lightSystem;
    HvacSystem* hvacSystem;
    SercuritySystem* sercuritySystem;
} SmartHomeFacade;
```

### `LightSystem`

```c
typedef struct {
    void (*turnOnLightSystem)(void);
    void (*turnOffLightSystem)(void);
    void (*setBrightness)(int value);
} LightSystem;
```

### `HvacSystem`

```c
typedef struct {
    void (*setTemperature)(int value);
    void (*setMode)(const char* mode);
} HvacSystem;
```

### `SercuritySystem`

```c
typedef struct {
    void (*activeAlarm)(void);
    void (*deactiveAlarm)(void);
    void (*monitorSensor)(void);
} SercuritySystem;
```

---

## How to build & run
```bash
# Build project
make

# Chạy chương trình
./smart-home-demo
```
---
## Kết quả mẫu
```
>>> Activating morning routine...
The lighting system is off
Brightness is 100%
Room temperature is 25
Current mode is Cooling
Deactived alarm
Morning routine actived

>>> Activating away mode...
The lighting system is off
Actived alarm
Room temperature is 26
Current mode is Eco
Away mode activated.

>>> Setting movie night scene...
Brightness is 21%
Room temperature is 21
Deactived alarm
Movie night scene set.

Freeing allocated memory...
```
---

## 🧠 Giải thích: Facade Pattern là gì và ứng dụng

### ✅ Vấn đề ban đầu

- Giao diện điều khiển **phức tạp**, cần gọi nhiều hàm từ nhiều hệ thống con.
- Mỗi kịch bản (scene) như "Chào buổi sáng", "Xem phim" phải viết mã dài dòng.
- Mã tầng ứng dụng bị **ràng buộc chặt** với chi tiết hệ thống con.

### ✅ Giải pháp: Facade Pattern

Facade Pattern cung cấp một **giao diện đơn giản** (SmartHomeFacade) để gọi một chuỗi hành động phức tạp phía sau:

```c
activateMorningRoutine(smartHome);
```

Thay vì:
```c
lightSystem->setBrightness(100);
hvacSystem->setTemperature(25);
...
```

### ✅ Lợi ích:

| Tính chất                       | Facade Pattern mang lại                 |
| ------------------------------- | --------------------------------------- |
| Đơn giản hóa giao diện          | ✅ Dễ gọi, dễ hiểu                       |
| Giảm phụ thuộc (Loose Coupling) | ✅ Không cần biết chi tiết từng hệ thống |
| Dễ bảo trì & mở rộng            | ✅ Thay module không ảnh hưởng tầng trên |

---

## 🔚 Tổng kết

Dự án này sử dụng **Facade Pattern** để đơn giản hóa điều khiển nhà thông minh, giúp tầng ứng dụng gọi các kịch bản phức tạp một cách dễ dàng, tách biệt rõ ràng và dễ bảo trì khi hệ thống phát triển.