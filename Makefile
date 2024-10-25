CC = gcc
CFLAGS = -Wall -Iinclude -Isrc
LDFLAGS = -lSDL2 -lSDL2_ttf

SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c, build/%.o, $(SRC_FILES))
TARGET = build/game

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*

.PHONY: all clean
