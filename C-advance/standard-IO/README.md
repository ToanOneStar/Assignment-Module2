# Logger Module - Standard I/O

## 1. Mô tả dự án
Xây dựng module logger chuyên nghiệp cho C, hỗ trợ ghi log ra nhiều nơi (console, file), lọc theo mức độ log, tự động thêm timestamp, tên file, số dòng vào mỗi thông điệp. Module dễ cấu hình, tái sử dụng cho mọi dự án C.

## 2. Cấu trúc source code
```
standard-IO/
├── logger.h        
├── logger.c         
├── main.c          
├── Makefile        
```

## 3. Các API, struct, element chính
- **enum LogLevel:**
  - LOG_EMERGENCY, LOG_ALERT, LOG_CRITICAL, LOG_ERROR, LOG_WARNING, LOG_NOTICE, LOG_INFO, LOG_DEBUG
- **static const char* getFileName(const char* filepath)**
  - Lấy file name
- **static void getTimestamp(char* buffer, size_t buffersize)**
  - Định thời gian
- **static const char* convertStringLevel(LogLevel level)**
  - Chuyển string -> log level
- **void logger_log(LogLevel level, const char* file, int line, const char* fmt, ...);**
  - Ghi log với metadata (timestamp, file, line), định dạng message như printf.
- **Macro log_message(level, ...):**
  - Gọi logger_log với __FILE__, __LINE__ tự động.

## 4. How to build & run
```bash
# Build project
make

# Run
./logger-demo
```

## 5. Kết quả kiểm thử mẫu
```
=== DEMO LOGGER ===

[2025-07-08 17:51:18] [INFORMATIONAL] [main.c:9] - Start program
[2025-07-08 17:51:18] [DEBUG] [main.c:10] - Init system...
[2025-07-08 17:51:18] [WARNING] [main.c:11] - Warning !!!
[2025-07-08 17:51:18] [ERROR] [main.c:12] - Error: Can not connect to Internet
[2025-07-08 17:51:18] [CRITICAL] [main.c:13] - Serious: System is unstable.
[2025-07-08 17:51:18] [INFORMATIONAL] [main.c:16] - User admin (ID: 12345) logged in
[2025-07-08 17:51:18] [ALERT] [main.c:17] - ALERT: Disk space low
[2025-07-08 17:51:18] [INFORMATIONAL] [main.c:18] - End Program

Check file 'log.txt' to view the log that has been recorded.
```
Log file log.txt cũng có nội dung tương tự.

## 6. Giải thích giải pháp
- Sử dụng enum cho log level, macro tiện lợi để tự động chèn metadata.
- Lọc log theo mức độ, ghi ra stderr/stdout và file.
- Định dạng log chuẩn, dễ tích hợp và mở rộng.
- Đóng gói trạng thái logger bằng static, đảm bảo an toàn và tái sử dụng.
