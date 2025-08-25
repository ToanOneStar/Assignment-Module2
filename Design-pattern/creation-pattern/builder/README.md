
# UART Configuration with Builder Pattern

## 📌 Mô tả dự án

Dự án này cung cấp một cách tiếp cận linh hoạt và mở rộng để cấu hình giao tiếp UART (Universal Asynchronous Receiver/Transmitter) bằng cách sử dụng **Builder Pattern** (Mẫu thiết kế Xây dựng). Thay vì khởi tạo một đối tượng `UART_Config_t` với quá nhiều tham số, chúng ta sử dụng `UART_Builder` để từng bước cấu hình các thuộc tính như:

- Baud rate
- Parity bit
- Stop bits
- Data bits

Mục tiêu chính là:
- Đơn giản hóa quá trình khởi tạo.
- Giảm thiểu lỗi cấu hình.
- Tuân thủ **Nguyên lý Mở – Đóng (Open/Closed Principle - OCP)**.

---

## 📂 Cấu trúc thư mục

```
practice/
├── uart/
│   ├── uart-builder.h        # Khai báo API và struct chính
│   ├── uart-builder.c        # Định nghĩa các hàm builder
├── main.c                    # Ví dụ sử dụng builder
├── Makefile
```
---
## 🧩 Các API chính

### Hàm khởi tạo Builder:
```c
UART_Builder UART_Builder_Init();
```

### Các hàm thiết lập thuộc tính:
```c
UART_Builder* setBaudRate(UART_Builder* builder, uint32_t baudRate);
UART_Builder* setParity(UART_Builder* builder, Parity_Bit_e parity);
UART_Builder* setStopBits(UART_Builder* builder, uint8_t stopBits);
UART_Builder* setDataBits(UART_Builder* builder, uint8_t dataBits);
```

### Hàm tạo `UART_Config_t`:
```c
UART_Config_t build(UART_Builder* builder);
```

---

## 🏗️ Struct và thành phần chính

### `UART_Config_t`
Cấu hình UART chứa:

```c
typedef struct {
    uint32_t baudRate;
    Parity_Bit_e parity;
    uint8_t stopBits;
    uint8_t dataBits;
} UART_Config_t;
```

### `UART_Builder`
Struct chính dùng cho Builder Pattern:

```c
typedef struct UART_Builder {
    UART_Config_t config;
    struct UART_Builder* (*setBaudRate)(struct UART_Builder*, uint32_t);
    struct UART_Builder* (*setParity)(struct UART_Builder*, Parity_Bit_e);
    struct UART_Builder* (*setStopBits)(struct UART_Builder*, uint8_t);
    struct UART_Builder* (*setDataBits)(struct UART_Builder*, uint8_t);
    UART_Config_t (*build)(struct UART_Builder*);
} UART_Builder;
```

### `Parity_Bit_e`
Enum biểu diễn các lựa chọn parity bit:

```c
typedef enum {
    NONE,
    ODD,
    EVEN,
} Parity_Bit_e;
```

---
## How to build & run
```bash
# Build project
make

# Chạy chương trình
./uart_demo
```
---
## Kết quả mẫu
```
UART Configuration:
Baud Rate: 115200
Parity: 1
Stop Bits: 2
Data Bits: 9
```
---
## 🧠 Giải thích giải pháp: Builder Pattern & Open/Closed Principle (OCP)

### ✅ Vì sao dùng Builder Pattern?

**Vấn đề ban đầu**:
- Cấu hình UART cần nhiều tham số → dễ lỗi.
- Cấu hình chồng chéo, phụ thuộc lẫn nhau.
- Khó tái sử dụng và mở rộng.

**Giải pháp**:
Builder Pattern cho phép bạn tạo từng bước các cấu hình UART mà không cần truyền quá nhiều tham số một lúc.

```c
UART_Builder builder = UART_Builder_Init();
UART_Config_t config = builder
    .setBaudRate(&builder, BAUDRATE_115200)
    ->setParity(&builder, ODD)
    ->setStopBits(&builder, 2)
    ->setDataBits(&builder, 8)
    ->build(&builder);
```

Nhờ Builder Pattern, bạn:
- Cấu hình dễ đọc, từng bước.
- Mặc định ban đầu an toàn, dễ thay đổi.
- Có thể thêm tùy chọn mới (VD: flow control) mà không sửa mã nguồn cũ.

---

### ✅ Tuân thủ nguyên lý OCP (Open/Closed Principle)

> **Mở rộng được mà không sửa đổi mã cũ**.

Builder Pattern giúp:
- Dễ dàng thêm method mới (VD: `setFlowControl()`) mà không cần sửa `main.c`.
- Mỗi method cấu hình là một hàm riêng biệt → có thể mở rộng hoặc thay thế.
- Mọi logic kiểm tra (validation) được tách biệt, giúp dễ bảo trì.


---

## 🔚 Tổng kết

Giải pháp này sử dụng **Builder Pattern** để tạo cấu hình UART một cách rõ ràng, dễ mở rộng và dễ bảo trì, tuân thủ nguyên lý **OCP** trong thiết kế phần mềm hiện đại.
