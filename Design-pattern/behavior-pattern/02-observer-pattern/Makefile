CC = gcc
CFLAGS = -Wall -Wextra -I./inc -I./inc/sensors -I./inc/subscribers

SRC = main.c \
	   $(wildcard src/sensors/*.c)\
	   $(wildcard src/subscribers/*.c) \
	   src/publisher.c \

TARGET = smart-home

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean