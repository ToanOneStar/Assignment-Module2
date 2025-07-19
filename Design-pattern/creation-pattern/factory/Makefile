CC = gcc
CFLAGS = -Wall -Wextra -I./factory -I./temperature -I./humidity -I./pressure -I./light

SRC = main.c \
	factory/sensor-factory.c \
	temperature/temperature-sensor.c \
	humidity/humidity-sensor.c \
	pressure/pressure-sensor.c \
	light/light-sensor.c

TARGET = factory_demo

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o