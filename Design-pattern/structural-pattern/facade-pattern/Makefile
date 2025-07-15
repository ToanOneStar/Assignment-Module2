CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

SRC_DIR = src
OBJ_DIR = obj
STATE_DIR = $(OBJ_DIR)/states

SRCS = $(SRC_DIR)/musicPlayer.c \
       $(SRC_DIR)/stoppedState.c \
       $(SRC_DIR)/playingState.c \
       $(SRC_DIR)/pausedState.c \
       main.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

TARGET = musicPlayer

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
