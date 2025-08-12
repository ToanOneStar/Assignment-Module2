CC = gcc
CFLAGS = -Wall -Wextra -g -I./inc -I./inc/monitor -I./inc/observer

SRCS = $(wildcard src/monitor/*.c) \
	   $(wildcard src/observer/*.c) \
	   $(wildcard src/*.c) \
       main.c

TARGET = monitoring-system

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	@echo "Build Success $(TARGET)"

clean:
	rm -rf $(TARGET) monitoring.log
	@echo "Cleaned exe and log file"