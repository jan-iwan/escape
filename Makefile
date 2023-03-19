MAKEFLAGS += --silent

CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -Wpedantic -fPIC -O2
LDFLAGS = -shared

TARGET_SHARED = libescape.so
TARGET_STATIC = libescape.a
HEADER = src/escape.h 
PREFIX=/usr/local
INSTALL_DIR = $(PREFIX)/lib
INCLUDE_INSTALL_DIR = $(PREFIX)/include

SRC_DIR = ./src
SRCS = $(shell find $(SRC_DIR) -name '*.c')
BUILD_DIR = ./build
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: shared static

shared: $(TARGET_SHARED)

static: $(TARGET_STATIC)

$(TARGET_SHARED): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@
	strip $@

$(TARGET_STATIC): $(OBJS)
	ar rcs $@  $^

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

install-shared: shared
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET_SHARED) $(INSTALL_DIR)

install-static: static
	mkdir -p $(INSTALL_DIR)
	cp $(TARGET_STATIC) $(INSTALL_DIR)

install: install-shared install-static $(HEADER)
	mkdir -p $(INCLUDE_INSTALL_DIR)
	cp $(HEADER) $(INCLUDE_INSTALL_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET_SHARED)
	rm -f $(TARGET_STATIC)
