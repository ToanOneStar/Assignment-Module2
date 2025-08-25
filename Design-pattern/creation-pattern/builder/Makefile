CC = gcc 
CFLAGS = -Wall -Wextra -I./uart

SRC = main.c \
	uart/uart-builder.c 

TARGET = uart_demo

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o
