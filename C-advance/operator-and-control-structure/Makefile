CC = gcc
CFLAGS = -Wall -Wextra
TARGET = led-driver
SRCS = main.c led_driver.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	@echo "Build Success $(TARGET)"

clean:
	rm -rf $(TARGET)
	@echo "Cleaned exe file"
	