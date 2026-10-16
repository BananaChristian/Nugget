CC=clang
CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -Iinclude -g
CFLAGS+=$(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)

BUILD=build
TARGET=$(BUILD)/nugget
SRC=$(wildcard src/*.c src/**/*.c)
OBJ=$(SRC:src/%.c=$(BUILD)/%.o)

all: $(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: all
	./$(TARGET)

debug:CFLAGS+=-DDEBUG -fsanitize=address,undefined
debug:LDFLAGS+= -fsanitize=address,undefined
debug:clean all

clean:
	rm -rf $(BUILD)

.PHONY: all run debug clean
