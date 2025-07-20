
# Embedded Communication Framework Using Decorator Pattern

## 📌 Mô tả dự án

Dự án này mô phỏng một framework giao tiếp nhúng (**Embedded Communication Framework**) sử dụng kênh truyền cơ bản (UART) kết hợp với nhiều lớp xử lý (processing layers) như:

- 🔒 Mã hóa (Encryption)
- 🧩 Nén (Compression)
- ✅ Kiểm tra lỗi (CRC)
- 📝 Ghi log (Logging)

Các lớp xử lý được xây dựng theo **Decorator Pattern (Mẫu thiết kế Trang trí)** để đảm bảo **tính mở rộng, linh hoạt và dễ bảo trì** cho hệ thống giao tiếp.

## 🧩 Các API chính

Giao diện hoạt động chính là một struct `CommunicationChannel`, định nghĩa hai hàm cơ bản:

```c
typedef struct CommunicationChannel {
    int (*send)(void* instance, const uint8_t* data, size_t length);
    int (*receive)(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);
    void* instance;
} CommunicationChannel;
```

### Các hàm gửi / nhận:
- `int send(void* instance, const uint8_t* data, size_t length);`
- `int receive(void* instance, uint8_t* buffer, size_t bufferLength, size_t* receivedLength);`

## 🏗️ Các struct và thành phần chính

| Thành phần             | Mô tả                                      |
| ---------------------- | ------------------------------------------ |
| `UartChannel`          | Kênh truyền UART gốc.                      |
| `CompressionDecorator` | Thực hiện nén / giải nén dữ liệu bằng RLE. |
| `EncryptionDecorator`  | Mã hóa / giải mã dữ liệu bằng XOR key.     |
| `CrcDecorator`         | Thêm / kiểm tra CRC8.                      |
| `LoggingDecorator`     | In log gửi/nhận ra console kèm timestamp.  |

## 🗂️ Cấu trúc source code

```
├── base-uart
│   ├── base-uart.c
│   └── base-uart.h
├── decorators
│   ├── compression
│   │   ├── compression.c
│   │   └── compression.h
│   ├── crc
│   │   ├── crc.c
│   │   └── crc.h
│   ├── encryption
│   │   ├── encryption.c
│   │   └── encryption.h
│   └── logging
│       ├── logging.c
│       └── logging.h
├── main.c
├── Makefile
```

## 🧠 Cách hoạt động và thứ tự xử lý

### Chuỗi gửi (Sending pipeline):
```
Data -> Logging -> Encryption -> Compression -> CRC -> UART
```

### Chuỗi nhận (Receiving pipeline - ngược lại):
```
UART -> CRC Check -> Decompression -> Decryption -> Logging -> Data
```

Việc sắp xếp thứ tự decorator rất quan trọng để đảm bảo dữ liệu gửi/nhận được xử lý đúng logic.

## ✅ Giải thích giải pháp dùng Decorator Pattern

### 🔧 Vấn đề nếu không dùng Decorator
- Hàm xử lý sẽ **rối, khó bảo trì** khi thêm CRC, mã hóa, nén, log.
- Sẽ cần tạo hàng loạt hàm như `send_with_crc_and_log_and_encrypt()`, rất **khó mở rộng**.
- Không thể cấu hình động các lớp xử lý (bật/tắt).
- Khó tái sử dụng logic CRC, mã hóa ở nơi khác.

### 💡 Giải pháp Decorator Pattern
Mỗi lớp xử lý được đóng gói trong một struct "decorator" riêng, và mọi lớp đều giữ tham chiếu đến `baseChannel`. Khi gọi `send` hoặc `receive`, mỗi decorator chỉ cần:

- **Xử lý nội dung**
- Gọi `send()` / `receive()` tiếp theo trong chuỗi

Nhờ đó:
- Có thể **xếp chồng nhiều decorator** tự do.
- Các decorator **hoàn toàn độc lập và tái sử dụng được**.
- Giao diện nhất quán (`CommunicationChannel`) cho tất cả loại kênh.

## ▶️  How to build & run
```bash
# Build project
make

# Chạy chương trình
./uart-demo
```
---
## Kết quả mẫu
```
=== Embedded Communication Channel Decorator Pattern Demo ===

Original test data (11 bytes): 01 01 01 01 02 02 03 04 04 04 04 

=== SENDING DATA ===
[CRC] Added CRC: 28
Send result: 0

=== RECEIVING DATA ===
Receive result: 0

=== Demo completed ===
```
---

## 🧠 Kiến thức áp dụng
- Design Pattern: **Decorator**
- Embedded System Communication Abstraction
- CRC8 algorithm
- Run-Length Encoding
- XOR-based Encryption
- Logging with `time.h`