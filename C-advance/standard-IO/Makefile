# Makefile đơn giản cho Logger
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = logger_demo
SOURCES = main.c logger.c

# Build chương trình
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
	@echo "Build thành công! Chạy với: ./$(TARGET)"

# Dọn dẹp
clean:
	rm -f $(TARGET) log.txt
	@echo "Đã xóa file executable và log"

# Chạy chương trình
run: $(TARGET)
	./$(TARGET)

# Xem nội dung file log
show-log:
	@echo "=== NỘI DUNG FILE LOG.TXT ==="
	@cat log.txt 2>/dev/null || echo "File log.txt chưa tồn tại"

.PHONY: all clean run show-log