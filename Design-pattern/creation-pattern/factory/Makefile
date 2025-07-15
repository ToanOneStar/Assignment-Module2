CC = gcc
CFLAGS = -Wall -Wextra -I./factory -I./temperature -I./humidity -I./pressure -I./light

SRC = main.c \
	factory/sensor_factory.c \
	temperature/temperature-sensor.c \
	humidity/humidity-sensor.c \
	pressure/pressure-sensor.c \
	light/light-sensor.c

OBJ = $(SRC:.c=.o)
TARGET = factory_demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)