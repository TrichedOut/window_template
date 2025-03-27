# collect all source and object files
SRC_FILES := $(shell find src/ -type f -name "*.c")
OBJ_FILES := $(patsubst src/%.c, build%.o, $(SRC_FILES))

# flags to set for c compiler
OPTS = -std=c17 -Wno-unused-command-line-argument -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib

# make all files into main executable
all: main

# make all and run
run: all
	@echo
	cd build; ./main

# compile all object files together
main: $(OBJ_FILES)
	gcc $(OPTS) $^ -o build/main
	@cp -a src/assets/. build/assets

# compile all source files into object files in the build directory
$(OBJ_FILES): build%.o: src%.c
	@mkdir -p $(dir $@)
	gcc $(OPTS) -c $< -o $@

# remove all in the build folder, remove main
clean:
	rm -rf build/*
