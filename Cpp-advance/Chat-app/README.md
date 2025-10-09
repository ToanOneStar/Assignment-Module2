# 🗨️ P2P Chat Application

[![Version](https://img.shields.io/badge/version-1.0-blue.svg)](https://github.com/ToanOneStar/Assignment-Module2)
[![Build Status](https://img.shields.io/badge/build-unknown-lightgrey.svg)](https://github.com/ToanOneStar/Assignment-Module2)
[![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)

## 📖 Mô tả dự án

Ứng dụng chat P2P đơn giản cho phép nhiều peer kết nối trực tiếp, gửi và nhận thông điệp qua TCP. Mục tiêu là thực hành quản lý kết nối, xử lý lệnh trên CLI và xây dựng server/client đơn giản cho môi trường học tập.

### 🎯 Bài toán giải quyết
- Cho phép khởi chạy một node (server) lắng nghe trên địa chỉ IP và port chỉ định
- Kết nối tới peer khác theo IP:PORT (client-side)
- Quản lý nhiều kết nối (list, terminate)
- Gửi tin nhắn tới peer theo ID
- Giao diện dòng lệnh (CLI) để thao tác nhanh

### ⚙️ Tính năng chính
- Khởi tạo server TCP lắng nghe kết nối đến
- Kết nối ra peer khác (outgoing connections)
- Danh sách peer hiện kết nối với ID, IP, Port
- Gửi và nhận message đơn giản qua socket
- Lệnh CLI: `connect`, `list`, `send`, `terminate`, `myip`, `myport`, `help`, `exit`

---

## 📁 Cấu trúc Source Code

```
Chat-app/
├── inc/
│   ├── chat-server.h         # Khai báo ChatServer
│   ├── command-parser.h      # Parser cho các lệnh CLI
│   ├── connection-manager.h  # Quản lý peers
│   └── chat-cli.h            # Khai báo hàm runCli(...) và helpers CLI
├── src/
│   ├── chat-server.cpp
│   ├── command-parser.cpp
│   ├── connection-manager.cpp
│   └── chat-cli.cpp          # Triển khai vòng lặp CLI / REPL
├── main.cpp                  # Entrypoint: khởi tạo server và gọi runCli
├── Makefile
└── README.md
```

---

## 🧩 Các module chính & API ngắn gọn

### `ChatServer`
- Khởi tạo server lắng nghe: `ChatServer(std::string ip, int port)`
- `bool start()` — bắt đầu lắng nghe
- `void stop()` — dừng server
- `std::string getIpAddress()` / `int getPort()`

### `ConnectionManager`
- Singleton quản lý peers
- `int addPeer(const std::string& ip, int port, int sockFd)`
- `std::shared_ptr<Peer> findPeer(int id)`
- `std::vector<std::shared_ptr<Peer>> getAllPeers()`
- `void removePeer(int id)`

### `CommandParser`
- `ParsedCommand parse(const std::string& line)` — tách action và args
- `void printHelp()` — in hướng dẫn các lệnh

### `chat-cli` (CLI)
- `void runCli(ChatServer& server)` — vòng lặp đọc lệnh từ `stdin` 

---

## 🚀 How to Build & Run

### 📋 Yêu cầu hệ thống
- OS: Linux
- Compiler: g++ (C++17)

### ⚡ Build
Nếu có `Makefile` trong thư mục, chạy:

```bash
make
```

Hoặc compile thủ công (ví dụ):

```bash
g++ -std=c++17 -I./inc src/*.cpp main.cpp -o chat_app
```

### 🏁 Run

```bash
./chat_app <IP_ADDRESS> <PORT>
# ví dụ
./chat_app 127.0.0.1 8080
```

Sau khi chạy, bạn sẽ thấy prompt `> ` để nhập lệnh CLIa.

### 🛠️ Kết quả

Kết quả chạy kiểm thử khi tạo 2 peer:
![logger](https://toanonestar.github.io/Assignment-Module2/compressed.mp4)

---
## 🛠️ Các lệnh CLI (ví dụ và cú pháp)

- `connect <IP> <PORT>` — kết nối tới peer
- `list` — liệt kê các peer đang kết nối
- `send <ID> <MESSAGE>` — gửi `MESSAGE` đến peer có `ID`
- `terminate <ID>` — đóng kết nối tới peer
- `myip` — hiển thị IP hiện tại của server
- `myport` — hiển thị port của server
- `help` — hiển thị hướng dẫn các lệnh
- `exit` — tắt server và thoát chương trình

Ghi chú: `ID` là số nội bộ do `ConnectionManager` cấp khi thêm peer.

---

## 🔧 Lưu ý kỹ thuật & Edge cases

- Kiểm tra `port` hợp lệ (1-65535) trước khi khởi tạo server
- Khi `connect` thất bại, socket sẽ được đóng và peer không được thêm
- `send` cần kiểm tra peer tồn tại và socket vẫn hợp lệ
- Không có mã hóa/ủy quyền — chỉ phù hợp cho bài tập học tập

---

## 🔍 Troubleshooting

- Nếu gặp lỗi biên dịch, kiểm tra include path (`-I./inc`) và các file `.cpp` có compile
- Nếu cổng bị chiếm, chọn port khác hoặc kill tiến trình đang dùng port

---

## 👥 Authors

- **ToanOneStar** - HUST - [GitHub](https://github.com/ToanOneStar)

---

## 🙏 Acknowledgments

- Tham khảo tài liệu sockets trên Linux
- Tài liệu về design patterns và quản lý kết nối

**⭐ Nếu bạn thấy hữu ích, hãy star repo này!**

