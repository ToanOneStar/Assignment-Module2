CC = gcc
CFLAGS = -Wall -Wextra 
TARGET = logger-demo
SRCS = main.c logger.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	@echo "Build Success $(TARGET)"

clean: 
	rm -rf $(TARGET) log.txt
	@echo "Cleaned exe and log file"

show-log:
	@echo "=== FILE LOG.TXT ==="
	@cat log.txt 2>/dev/null || echo "File log.txt doesn't exist"