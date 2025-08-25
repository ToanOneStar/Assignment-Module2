CC = gcc
CFLAGS = -Wall -Wextra -I./hvac-system -I./light-system -I./sercurity-system -I./smart-home-facade 

SRC = main.c \
	   hvac-system/hvac-system.c \
	   light-system/light-system.c \
	   sercurity-system/sercurity-system.c \
	   smart-home-facade/smart-home.c

TARGET = smart-home-demo

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean