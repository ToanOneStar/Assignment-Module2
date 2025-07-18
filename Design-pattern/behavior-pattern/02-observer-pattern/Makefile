CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

SRC_DIR = src
OBJ_DIR = obj
SENSORS_OBJ_DIR = $(OBJ_DIR)/sensors
SUBSCRIBERS_OBJ_DIR = $(OBJ_DIR)/subscribers

SRCS = main.c \
       $(SRC_DIR)/publisher.c \
       $(SRC_DIR)/sensors/door_sensor.c \
       $(SRC_DIR)/sensors/smoke_sensor.c \
       $(SRC_DIR)/subscribers/mobile_app_notifier.c \
       $(SRC_DIR)/subscribers/alarm_system_controller.c

OBJS = $(OBJ_DIR)/main.o \
       $(OBJ_DIR)/publisher.o \
       $(SENSORS_OBJ_DIR)/door_sensor.o \
       $(SENSORS_OBJ_DIR)/smoke_sensor.o \
       $(SUBSCRIBERS_OBJ_DIR)/mobile_app_notifier.o \
       $(SUBSCRIBERS_OBJ_DIR)/alarm_system_controller.o

TARGET = smartHome

all: $(OBJ_DIR) $(SENSORS_OBJ_DIR) $(SUBSCRIBERS_OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(SENSORS_OBJ_DIR):
	mkdir -p $(SENSORS_OBJ_DIR)

$(SUBSCRIBERS_OBJ_DIR):
	mkdir -p $(SUBSCRIBERS_OBJ_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/publisher.o: $(SRC_DIR)/publisher.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SENSORS_OBJ_DIR)/%.o: $(SRC_DIR)/sensors/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SUBSCRIBERS_OBJ_DIR)/%.o: $(SRC_DIR)/subscribers/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
