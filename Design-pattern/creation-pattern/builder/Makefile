CC = gcc
CFLAGS = -Wall -Wextra -I./modbus

SRC = main.c modbus/modbus_builder.c
OBJ = $(SRC:.c=.o)

TARGET = builder_demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)