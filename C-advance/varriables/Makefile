CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

SRC_DIR = src
OBJ_DIR = obj
STATE_DIR = $(OBJ_DIR)/states

SRCS = $(SRC_DIR)/actuators.c \
       $(SRC_DIR)/buttons.c \
       $(SRC_DIR)/sensors.c \
       $(SRC_DIR)/watering_logic.c \
       main.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

TARGET = smart-system

all: $(OBJ_DIR) $(STATE_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(STATE_DIR):
	mkdir -p $(STATE_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
