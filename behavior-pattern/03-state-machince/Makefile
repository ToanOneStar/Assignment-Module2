# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinc -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
STATE_DIR = $(OBJ_DIR)/states

# Source files
SRCS = $(SRC_DIR)/musicPlayer.c \
       $(SRC_DIR)/stoppedState.c \
       $(SRC_DIR)/playingState.c \
       $(SRC_DIR)/pausedState.c \
       main.c

# Object files
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Output executable
TARGET = musicPlayer

# Build rules
all: $(OBJ_DIR) $(STATE_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(STATE_DIR):
	mkdir -p $(STATE_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
