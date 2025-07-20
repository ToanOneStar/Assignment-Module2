CC = gcc
CFLAGS = -Wall -Wextra -I./base-uart -I./decorators/compression -I./decorators/crc -I./decorators/encryption -I./decorators/logging

SRCS = $(wildcard *.c) \
       $(wildcard ./base-uart/*.c) \
       $(wildcard ./decorators/logging/*.c) \
       $(wildcard ./decorators/encryption/*.c) \
       $(wildcard ./decorators/compression/*.c) \
       $(wildcard ./decorators/crc/*.c)

TARGETS = uart-demo

all: $(TARGETS)
$(TARGETS): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)

.PHONY: all clean